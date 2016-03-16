#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std::chrono;

using namespace std;
using namespace dlib;

// ----------------------------------------------------------------------------------------

int main(int argc, char **argv) {
    try {
        if (argc != 3) {
            cout << "Give the path to the testing directory and your model as the argument to this" << endl;
            cout << "You can do this this program by running: " << endl;
            cout << "   ./objectDetectionRunner path/to/images model.svm " << endl;
            cout << endl;
            return 0;
        }
        dlib::array<array2d<unsigned char> > images_test;
        std::vector<std::vector<rectangle> > boxes_test;

        const std::string testing_directory = argv[1];
        load_image_dataset(images_test, boxes_test, testing_directory + "/testing.xml");

        typedef scan_fhog_pyramid<pyramid_down<6> > image_scanner_type;

        object_detector<image_scanner_type> detector;
        deserialize(argv[2]) >> detector;

        unsigned long num_images = images_test.size();
        cout << "Number of images to process: " << num_images << endl;

        long durations[num_images];

        for (int i = 0; i < num_images; ++i) {
            high_resolution_clock::time_point t1 = high_resolution_clock::now();
            std::vector<rectangle> dets = detector(images_test[i]);
            high_resolution_clock::time_point t2 = high_resolution_clock::now();
            long duration = duration_cast<milliseconds>(t2 - t1).count();
            cout << "image " << i << " took " << duration << " ms" << endl;
            durations[i] = duration;
        }

        long sum;

        for(int i=0; i < num_images; i++)
        {
            sum+=durations[i];
        }
        
        long average = sum / num_images;
        cout << "Number of images processed: " << num_images << endl;
        cout << "Average detection time per image is: " << average << "ms" << endl;


    }
    catch (exception &e) {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}
