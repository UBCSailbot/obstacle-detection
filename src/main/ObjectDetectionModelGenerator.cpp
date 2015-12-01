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

typedef scan_fhog_pyramid<pyramid_down<6>> image_scanner_type;
// ----------------------------------------------------------------------------------------

object_detector<image_scanner_type> train_object_detector(std::string file_name, double c_value, double eps_value)
{
	cout << "TRAINING WITH C VALUE " << c_value << endl;
	try {

                dlib::array<array2d<unsigned char> > images_train;
                std::vector<std::vector<rectangle> > boxes_train;

                load_image_dataset(images_train, boxes_train, file_name);

                upsample_image_dataset<pyramid_down<2> >(images_train, boxes_train);
                add_image_left_right_flips(images_train, boxes_train);

                // Finally we get to the training code.  dlib contains a number of
                // object detectors.  This typedef tells it that you want to use the one
                // based on Felzenszwalb's version of the Histogram of Oriented
                // Gradients (commonly called HOG) detector.  The 6 means that you want
                // it to use an image pyramid that downsamples the image at a ratio of
                // 5/6.  Recall that HOG detectors work by creating an image pyramid and
                // then running the detector over each pyramid level in a sliding window
                // fashion.
                image_scanner_type scanner;
                // The sliding window detector will be 80 pixels wide and 80 pixels tall.
                scanner.set_detection_window_size(50, 30);
                structural_object_detection_trainer<image_scanner_type> trainer(scanner);
                // Set this to the number of processing cores on your machine.
                trainer.set_num_threads(4);
                // The trainer is a kind of support vector machine and therefore has the usual SVM
                // C parameter.  In general, a bigger C encourages it to fit the training data
                // better but might lead to overfitting.  You must find the best C value
                // empirically by checking how well the trained detector works on a test set of
                // images you haven't trained on.  Don't just leave the value set at 1.  Try a few
                // different C values and see what works best for your data.
                trainer.set_c(c_value);
                // We can tell the trainer to print it's progress to the console if we want.
                trainer.be_verbose();
                // The trainer will run until the "risk gap" is less than 0.01.  Smaller values
                // make the trainer solve the SVM optimization problem more accurately but will
                // take longer to train.  For most problems a value in the range of 0.1 to 0.01 is
                // plenty accurate.  Also, when in verbose mode the risk gap is printed on each
                // iteration so you can see how close it is to finishing the training.
                trainer.set_epsilon(0.001);
                trainer.set_match_eps(eps_value);


                // Now we run the trainer.  For this example, it should take on the order of 10
                // seconds to train.
                object_detector<image_scanner_type> detector = trainer.train(images_train, boxes_train);
		return detector;
        }
        catch (exception& e)
        {
                cout << "\nexception thrown!" << endl;
                cout << e.what() << endl;
        }

}

void generate_optimal_model(std::string train_file_name, std::string test_file_name, std::string model_name, double c_low, double c_high)
{
	cout << "C RANGE BETWEEN: " << c_low << " AND " << c_high << endl;

	int c_third = (c_high - c_low)/3;
	int c_two_thirds = 2*(c_high - c_low)/3;
	int c_mid = (c_high - c_low)/2;

        dlib::array<array2d<unsigned char> > images_test;
        std::vector<std::vector<rectangle> > boxes_test;

        load_image_dataset(images_test, boxes_test, test_file_name);

        upsample_image_dataset<pyramid_down<2> >(images_test, boxes_test);
        add_image_left_right_flips(images_test, boxes_test);

	// Acquire the results of testing on 1/3 of range and 2/3 of range
	object_detector<image_scanner_type> third_detector = train_object_detector(train_file_name, c_third, 0.1);
        matrix<double> third_results = test_object_detection_function(third_detector, images_test, boxes_test);

	object_detector<image_scanner_type> twothirds_detector = train_object_detector(train_file_name, c_two_thirds, 0.1);
        matrix<double> twothird_results = test_object_detection_function(twothirds_detector, images_test, boxes_test);

	// We've found our optimal object detector.
	// 0.1 is our arbitrarily decided precision.
	if((twothird_results(0, 2) - third_results(0, 2)) < 0.01)
	{
		cout << "C - VALUE: " << c_third << endl;
		serialize(model_name) << third_detector;
		cout << "Found optimal detector" << endl;

	}
	// This condition tells us that the the test results are better with the c_value set to 1/3 of the range
	// than with the c_value said to 2/3 of the range.
	else if(third_results > twothird_results)
	{
		generate_optimal_model(train_file_name, test_file_name, model_name, c_low, c_mid);
	}
	// On the other hand if the two third results are better, we go to the right.
	else {
		generate_optimal_model(train_file_name, test_file_name, model_name, c_mid, c_high);
	}
}



int main(int argc, char** argv)
{
	// We should have 3*k command-line arguments, where k is the number of models we want to output.
	// For each model, we should have (1) training directory, (2) testing directory, (3) model name.
	if (argc % 3 != 1 || argc == 1)
	{
        cout << "Give the arguments for each model as a list. For each model give the training" << endl;
		cout << "directory, the testing directory and the model name. An example for the one mode" << endl;
		cout << "would be: ./objectDetectionModelGenerator path/to/training/dir path/to/testing/dir model_name" << endl;
	        cout << endl;
	        return 0;
	}

	for(int i = 1; i < argc; i += 3) {
		std::string train_file_name = argv[i];
		train_file_name += "/testing.xml";
		std::string test_file_name = argv[i+1];
		test_file_name += "/training.xml";
		generate_optimal_model(train_file_name, test_file_name, argv[i+2], 0.01, 100);

	}

	return 0;
}

// ----------------------------------------------------------------------------------------
