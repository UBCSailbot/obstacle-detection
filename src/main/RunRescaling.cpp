//
// Created by paul on 14/06/15.
//

#include <string>
#include <iostream>

#include <tclap/CmdLine.h>
#include <QtCore/qstring.h>
#include <QtCore/qdir.h>
#include <opencv2/highgui/highgui.hpp>
#include <io/OrientationFileReader.h>
#include <geometry/HorizonFactory.h>

#include "imageProc/rescale/Rescaling.h"
#include "imageProc/rescale/SimpleRescaler.h"
#include "imageProc/rescale/ClippingRescaler.h"
#include "imageProc/histogram/HorizonHistogramGenerator.h"
#include "imageProc/histogram/SimpleHistogramGenerator.h"
#include "imageProc/histogram/ModeGetter.h"
#include "imageProc/histogram/MedianGetter.h"
#include "imageProc/histogram/SmoothingGetter.h"
#include "imageProc/liveFeed/base64EncDec.h"

#include "io/ImageReader.h"
#include "io/Paths.h"

using namespace std;
using namespace cv;
using namespace TCLAP;

const string VERSION_NUMBER = "0.9";

void rescale(const string &inputFrameDir, const string &outputFrameDir, const string &imuLogFilePath,
             RescalingType typeOfRescaling, int smoothingWindow, bool paintHorizon, bool numberFrames,
             bool invertRoll, bool invertPitch, bool display);


Rescaler *buildRescaler(const string &imuLogFilePath, const RescalingType &typeOfRescaling, int smoothingWindow,
                        bool invertRoll, bool invertPitch);

// TODO: This program makes use of some classes that use assert.
// TODO: Replace the remaining assert statements with exceptions.
int main(int argc, const char *const *argv) {

    try {

        CmdLine cmd("Rescale a directory of image frames.", ' ', VERSION_NUMBER);

        UnlabeledValueArg <string> inputFramesArg("input-frame-dir",
                                                  "Directory containing frames to rescale.",
                                                  true,
                                                  "",
                                                  "input-dir",
                                                  cmd);

        UnlabeledValueArg <string> outputFramesArg("output-frame-dir",
                                                   "Directory to which rescaled frames should be written.",
                                                   true,
                                                   "",
                                                   "output-dir",
                                                   cmd);

        ValueArg <string> horizonRescaleArg("i",
                                            "imu-logfile",
                                            "Perform rescaling based on the position of the horizon.",
                                            false,
                                            "NULL",
                                            "location of IMU log file",
                                            cmd);

        SwitchArg paintHorizonArg("p",
                                  "paint-horizon",
                                  "Paint the horizon on each frame. Must be specified with an IMU log file.",
                                  cmd,
                                  false);

        SwitchArg numberFramesArg("n",
                                  "number-frames",
                                  "Label each frame with its number (helps with debugging).",
                                  cmd,
                                  false);

        SwitchArg invertRollArg("",
                                "invert-roll",
                                "Invert the roll axis in parsing horizon info.",
                                cmd,
                                false);

        SwitchArg invertPitchArg("",
                                 "invert-pitch",
                                 "Invert the pitch axis in parsing horizon info.",
                                 cmd,
                                 false);

        ValueArg<int> smoothingArg("w",
                                   "smoothing-window",
                                   "Whether rescaling should be smoothed across multiple frames.",
                                   false,
                                   1,
                                   "smoothing",
                                   cmd);

        SwitchArg displayArg("d",
                             "display",
                             "Whether to display the frames as video as rescaling is being performed.",
                             cmd,
                             false);

        vector<int> typesOfRescaling;
        typesOfRescaling.push_back(1);
        typesOfRescaling.push_back(2);
        typesOfRescaling.push_back(3);
        ValuesConstraint<int> typeConstraint(typesOfRescaling);

        ValueArg<int> typeArg("t",
                              "rescaling-type",
                              "Type of rescaling to perform (default is `simple'): "
                                  "\t1: simple"
                                  "\t2: modal"
                                  "\t3: median",
                              false,
                              1,
                              &typeConstraint,
                              cmd);

        cmd.parse(argc, argv);

        string inputFrameDir = inputFramesArg.getValue();
        string outputFrameDir = outputFramesArg.getValue();
        string imuLogFilePath = horizonRescaleArg.getValue();
        RescalingType typeOfRescaling = (RescalingType) typeArg.getValue();
        bool paintHorizon = paintHorizonArg.getValue();
        bool numberFrames = numberFramesArg.getValue();
        bool invertRoll = invertRollArg.getValue();
        bool invertPitch = invertPitchArg.getValue();
        int smoothingWindow = smoothingArg.getValue();
        bool display = displayArg.getValue();

        rescale(inputFrameDir, outputFrameDir, imuLogFilePath, typeOfRescaling, smoothingWindow, paintHorizon,
                numberFrames, invertRoll, invertPitch, display);
    }
    catch (ArgException &e) {
        cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
    }

}

void rescale(const string &inputFrameDir,
             const string &outputFrameDir,
             const string &imuLogFilePath,
             RescalingType typeOfRescaling,
             int smoothingWindow,
             bool paintHorizon,
             bool numberFrames,
             bool invertRoll,
             bool invertPitch,
             bool display) {

    vector <string> frameList = Paths::generateListOfFiles(inputFrameDir, "*.png");

    Rescaler *rescaler = buildRescaler(imuLogFilePath, typeOfRescaling, smoothingWindow, invertRoll, invertPitch);

    OrientationFileReader orientationStream2(imuLogFilePath, invertRoll, invertPitch);
    HorizonFactory horizonFactory(LeptonCameraSpecifications);
    SimpleRescaler exampleRescaler;

    for (int i = 0; i < frameList.size(); i++) {
        string frameFile = frameList[i];
#ifdef DEBUG
        cout << frameFile << endl;
#endif
        string frameFilePath = Paths::join(inputFrameDir, frameFile);

        Image16bit rawFrame = ImageReader::read16bitImage(frameFilePath);
        Image8bit rescaledFrame(rawFrame.rows, rawFrame.cols);

        try {
            rescaler->scale16bitTo8bit(rawFrame, rescaledFrame);
        }
        catch (NoSuchElementException e) {
            cout << "WARNING: Ran out of IMU coordinates in imu logfile at frame " << i << endl;
            exit(0);
        }

        string outputFilePath = Paths::join(outputFrameDir, frameFile);

        cv::Mat outputFrame = Mat(rescaledFrame.rows, rescaledFrame.cols, CV_8UC3);
        cv::cvtColor(rescaledFrame, outputFrame, cv::COLOR_GRAY2BGR);

        if (numberFrames) {
            ostringstream text;
            text << i;
            putText(outputFrame, text.str().c_str(), cv::Point(4, 14), cv::FONT_HERSHEY_PLAIN, 0.8, Scalar(0, 255, 0));
        }

        if (paintHorizon) {
            try {
                Horizon h = horizonFactory.makeHorizon(orientationStream2.next());
                line(outputFrame, h.getStartPoint(), h.getEndPoint(), Scalar(0, 0, 255), 1);
            } catch (NoSuchElementException e) {
                cout << "WARNING: Ran out of IMU coordinates in imu logfile at frame " << i << endl;
                exit(0);
            }
        } else {
            outputFrame = rescaledFrame;
        }

        imwrite(outputFilePath, outputFrame);

        if (display) {
            resize(outputFrame, outputFrame, Size(0, 0), 6, 6, INTER_NEAREST);
            imshow("rescaled", outputFrame);

            Image8bit simpleRescaled;
            exampleRescaler.scale16bitTo8bit(rawFrame, simpleRescaled);
            resize(simpleRescaled, simpleRescaled, Size(0, 0), 6, 6, INTER_NEAREST);
            imshow("original", simpleRescaled);

            int k = waitKey(33 * 3) & 255;

            if (k == 32) {
                waitKey(0);
            } else if (k == 27) {
                break;
            }
        }

    }

}

Rescaler *buildRescaler(const string &imuLogFilePath, const RescalingType &typeOfRescaling, int smoothingWindow,
                        bool invertRoll, bool invertPitch) {
    Rescaler *rescaler;

    bool horizon = imuLogFilePath != "NULL";

    HistogramGenerator *histoGenerator;
    ObjectStream <Orientation> *orientationStream;
    CentralTendencyGetter *ctg;

    if (horizon) {
        orientationStream = new OrientationFileReader(imuLogFilePath, invertRoll, invertPitch);
        histoGenerator = new HorizonHistogramGenerator(orientationStream);
    } else {
        histoGenerator = new SimpleHistogramGenerator();
    }

    switch (typeOfRescaling) {
        case SIMPLE:
            rescaler = new SimpleRescaler();
            break;

        case MODAL:
            ctg = new ModeGetter();
            if (smoothingWindow > 1) {
                ctg = new SmoothingGetter(ctg, new AveragedBufferedSmoother(smoothingWindow));
            }
            rescaler = new ClippingRescaler(histoGenerator, ctg);
            break;

        case MEDIAN:
            ctg = new MedianGetter();
            if (smoothingWindow > 1) {
                ctg = new SmoothingGetter(ctg, new AveragedBufferedSmoother(smoothingWindow));
            }
            rescaler = new ClippingRescaler(histoGenerator, ctg);
            break;
        default:
            break;
    }

    return rescaler;
}
