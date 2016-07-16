#include <camera/lepton/LeptonRegistry.h>

int main(int argc, char **argv) {
    int lepton_cs = 0;
    if (argc == 2) {
        lepton_cs = atoi(argv[1]);
    }

    // This tests if an exception is thrown when calling captureFrame. If no Lepton is connected, after
    // about 10 seconds, captureFrame should throw an exception.
    int frame_counter = 1;
    Image16bit frame0;

    while(true) { 
       try {
            if (lepton_cs) {
                frame0 = LeptonRegistry::getLepton1().captureFrame();
            } else {
                frame0 = LeptonRegistry::getLepton0().captureFrame();
            }
            std::cout << "lepton " << lepton_cs
            << " got frame " << frame_counter << std::endl;
            frame_counter++;
        } catch (...) {
            std::cout << "Lepton is disconnected. resetting for 10 seconds\n";
            if (lepton_cs) {
                LeptonRegistry::getLepton1().resetVideoStream(10000000);
            } else {
                LeptonRegistry::getLepton0().resetVideoStream(10000000);
            }
            std::cout << "Finished reset\n";
        }
    }
}

