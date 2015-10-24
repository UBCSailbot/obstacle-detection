// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how you can use dlib to make an object detector
    for things like faces, pedestrians, and any other semi-rigid object.  In
    particular, we go though the steps to train the kind of sliding window
    object detector first published by Dalal and Triggs in 2005 in the paper
    Histograms of Oriented Gradients for Human Detection.

    Note that this program executes fastest when compiled with at least SSE2
    instructions enabled.  So if you are using a PC with an Intel or AMD chip
    then you should enable at least SSE2 instructions.  If you are using cmake
    to compile this program you can enable them by using one of the following
    commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.

*/


#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>
#include <unistd.h>
#include <iostream>
#include <fstream>


using namespace std;
using namespace dlib;

// ----------------------------------------------------------------------------------------

int main(int argc, char** argv)
{

    try
    {
        if (argc != 3)
        {
            cout << "Give the path to the testing directory and your model as the argument to this" << endl;
            cout << "You can do this this program by running: " << endl;
            cout << "   ./ObjectDetectionRunner path/to/images model.svm " << endl;
            cout << endl;
            return 0;
        }
        dlib::array<array2d<unsigned char> > images_test;
        std::vector<std::vector<rectangle> > boxes_test;

        typedef scan_fhog_pyramid<pyramid_down<6> > image_scanner_type;

        std::vector<object_detector<image_scanner_type> > my_detectors;
        object_detector<image_scanner_type> detector;
        for(int i = 2; i < argc; i++){
          deserialize(argv[i]) >> detector;
          my_detectors.push_back(detector);
        }

        const std::string testing_directory = argv[1];
        cout << "num testing images:  " << images_test.size() << endl;



        load_image_dataset(images_test, boxes_test, testing_directory+"/testing.xml");

        //need to figure out how to test multiple models
        //cout << "testing results:  " << test_object_detection_function(my_detectors, images_test, boxes_test) << endl;

        // Now for the really fun part.  Let's display the testing images on the screen and
        // show the output of the face detector overlaid on each image.
        image_window win;
        for (unsigned long i = 0; i < images_test.size(); ++i)
        {
            std::vector<rectangle> dets =   evaluate_detectors(my_detectors, images_test[i]);
            win.clear_overlay();
            win.set_image(images_test[i]);
            win.add_overlay(dets, rgb_pixel(255,0,0));
             cout << "Hit enter to continue..." << endl;
              cin.get();
        }


    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}

// ----------------------------------------------------------------------------------------
