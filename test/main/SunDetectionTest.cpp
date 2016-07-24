#include <camera/lepton/LeptonRegistry.h>
#include <features/SunImage.h>

int main(int argc, char **argv) {
    if (argc < 5) {
        std::cout << "Usage: <lepton_cs> <sun_brightness>" << std::endl;
        return -1;
    }
    int lepton_cs = atoi(argv[1]);
    Image16bit frame0;

    while(true) {
        try {
            if (lepton_cs) {
                frame0 = LeptonRegistry::getLepton1().captureFrame();
            } else {
                frame0 = LeptonRegistry::getLepton0().captureFrame();
            }

            Horizon h(cv::Point2f(0, 0), cv::Point2f(LeptonCameraSpecifications.pixelWidth - 1, 0));
            SunImage sunImage = SunImage(h, frame0, atoi(argv[2]), 0, 0);
            sunImage.findSunPosition();

            if(sunImage.containsSun()) {
                std::cout << "There's a sun \n";
            }
        }

        catch (LeptonException e) {
            std::cout << "Resetting Lepton";
            if (lepton_cs) {
                LeptonRegistry::getLepton1().resetVideoStream(1000000);
            } else {
                LeptonRegistry::getLepton0().resetVideoStream(1000000);
            }
            std::cout << "Finished reset\n";
        }
    }
}

