//
// Created by paul on 10/05/15.
//

#include "Lepton.h"

Lepton::Lepton() : Lepton(0) {

}

Lepton::Lepton(int spi_cs) {
    SpiOpenPort(0);

    int ret = 0;
    int fd;

    fd = open(device, O_RDWR);
    if (fd < 0)
    {
        pabort("can't open device");
    }

    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
    {
        pabort("can't set spi mode");
    }

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
    {
        pabort("can't get spi mode");
    }

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
    {
        pabort("can't set bits per word");
    }

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
    {
        pabort("can't get bits per word");
    }

    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    {
        pabort("can't set max speed hz");
    }

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    {
        pabort("can't get max speed hz");
    }

    _latestFrame = (uint16_t*) malloc(VIEWPORT_WIDTH_PIX * VIEWPORT_HEIGHT_PIX * sizeof(uint16_t));
    _newFrameAvailable = false;
    _canOverwriteLatestFrame = true;

    std::thread tempThread(&Lepton::startCapture, this);
    std::swap(tempThread, _leptonThread);
}

Lepton::~Lepton() {
    SpiClosePort(0);
    free(_latestFrame);
}

Image16bit Lepton::nextImage() {
    Image16bit* frame = new Image16bit;
    getFrame(*frame);
    return Image16bit();
}

bool Lepton::hasNext() const {
    return _newFrameAvailable;
}

int Lepton::getImageWidth() const {
    return LeptonCameraSpecifications.pixelHeight;
}

int Lepton::getImageHeight() const {
    return LeptonCameraSpecifications.pixelHeight;
}

void Lepton::getFrame(Image16bit &frame) {
    // wait to get the lock before grabbing the latest frame

    {
        std::unique_lock<std::mutex> lock(_mtx);
        if (!_newFrameAvailable){
            _cv.wait(lock);
        }
        _canOverwriteLatestFrame = false;
    }

    for(int row=0; row < frame.rows; row++) {
        for (int col=0; col < frame.cols; col++) {
            frame.pixelAt(row, col) = _latestFrame[row * VIEWPORT_WIDTH_PIX + col];
        }
    }

    _newFrameAvailable = false;
    _canOverwriteLatestFrame = true;

}

void Lepton::captureFrame() {

    //read data packets from lepton over SPI
    int resets = 0;
    for (int j = 0; j < PACKETS_PER_FRAME; j++) {
        //if it's a drop packet, reset j to 0, set to -1 so he'll be at 0 again loop
        ssize_t result = read(spi_cs0_fd, _result + sizeof(uint8_t) * PACKET_SIZE * j, sizeof(uint8_t) * PACKET_SIZE);
        // TODO: check that read was successful
        int packetNumber = _result[j * PACKET_SIZE + 1];
        if (packetNumber != j) {
            j = -1;
            resets += 1;
            usleep(1000);
            if (resets == 750) {
                SpiClosePort(0);
                usleep(750000);
                SpiOpenPort(0);
            }
        }
    }

    if (resets >= 30) {
        std::cout << "Done reading, resets: " << resets << std::endl;
    }

    _frameBuffer = (uint16_t *) _result;
    int row, column;

    for (int i = 0; i < FRAME_SIZE_UINT16; i++) {
        //skip the first 2 uint16_t's of every packet, they're 4 header bytes
        if (i % PACKET_SIZE_UINT16 < 2) {
            continue;
        }

        //flip the MSB and LSB at the last second
        uint8_t temp = _result[i * 2];
        _result[i * 2] = _result[i * 2 + 1];
        _result[i * 2 + 1] = temp;

    }

    /* Obtain the lock to check if allowed to overwrite the latest frame.
     *  If so, keep the lock until done overwriting it. */
    _mtx.lock();
    if (_canOverwriteLatestFrame) {

        for (int i = 0; i < FRAME_SIZE_UINT16; i++) {
            if (i % PACKET_SIZE_UINT16 < 2) {
                continue;
            }

            column = (i % PACKET_SIZE_UINT16) - 2;
            row = i / PACKET_SIZE_UINT16;
            _latestFrame[row * VIEWPORT_WIDTH_PIX + column] = _frameBuffer[i];
        }

        _cv.notify_one();
    }
    _mtx.unlock();
}


void Lepton::performFFC() {
    lepton_perform_ffc();
}

void Lepton::startCapture() {

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<float> elapsed_seconds;
    float leptonPeriodSeconds = 1 / LEPTON_FPS;

    // regularly poll the lepton
    while (1) {
        start = std::chrono::system_clock::now();

        captureFrame();

        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;

        if (elapsed_seconds.count() < leptonPeriodSeconds) {
            unsigned int sleepTimeMicros = (unsigned int) (leptonPeriodSeconds - elapsed_seconds.count()) * 1000 * 1000;
            usleep(sleepTimeMicros);
        }

    }

}
