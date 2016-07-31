#include <iostream>
#include <fstream>
#include <sstream>

#include <tclap/CmdLine.h>
#include <geometry/Horizon.h>
#include <io/OrientationFileReader.h>
#include <geometry/HorizonFactory.h>

namespace tclap = TCLAP;

const std::string DOCSTRING =
"Evaluate the performance of an algorithm that detects the position of the horizon in an image frame "
        "by comparing its results to a ground truth.\n\n"
        "The method of evaluation is to quantify the "
        "frequency of mislabeled pixels: since a horizon line is used to categorize image pixels as "
        "either 'below-horizon' or 'above-horizon', the percentage of image pixels correctly labeled "
        "in this way by the algorithm under evaluation can be used as a measure of the accuracy of "
        "the horizon line for each individual frame.\n\n"
        "This accuracy measure is computed for each frame for which there exists ground truth information,"
        "and is output to a text file for later processing by another application.";

double crossProduct(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

/**
 * Generates horizon objects from a file containing ground truth labels for
 * the positions of horizon lines in image files.
 */
class GroundTruthHorizonReader {
public:
    GroundTruthHorizonReader(const std::string &filePath) {
        fileReader_.open(filePath);
    }

    // Prefer to the let the destructor do the closing of the file reader.

    /**
     * Get a horizon object for the next horizon contained in the ground truth file.
     * @return a pair containing:
     *      1) the number of the video frame containing a labeled horizon line, and
     *      2) a Horizon object constructed from the label information for that frame
     */
    std::pair<int, Horizon> next() {
        std::string line;
        std::getline(fileReader_, line);
        std::stringstream iss(line);

        std::string token;
        // get frame number
        int frameNum;
        iss >> frameNum;

        // get horizon
        float x1, y1, x2, y2, skyX, skyY;
        const auto &cur = std::ios_base::cur;
        iss.seekg(3, cur);
        iss >> x1; iss.seekg(2, cur);
        iss >> y1; iss.seekg(4, cur);
        iss >> x2; iss.seekg(2, cur);
        iss >> y2; iss.seekg(4, cur);
        iss >> skyX; iss.seekg(2, cur);
        iss >> skyY;

        double horizonVectorX = x2 - x1;
        double horizonVectorY = y2 - y1;

        if (crossProduct(horizonVectorX, horizonVectorY, skyX, skyY) > 0) {
            return {frameNum, Horizon({x1, y1}, {x2, y2})};
        }
        else {
            return {frameNum, Horizon({x2, y2}, {x1, y1})};
        }
    }

    /**
     * @return true if the ground truth file contains horizon info for more frames.
     */
    bool hasNext() {
        return fileReader_.peek() != std::char_traits<char>::eof();
    }

private:
    std::ifstream fileReader_;
};

/**
 * Quantify the degree of similarity between a horizon produced by the algorithm
 *  being evaluated, and a ground truth Horizon
 *
 * @param eval - the horizon produced by the algorithm under evaluation
 * @param groundTruth - the ground truth horizon
 * @return a score of similarity, calculated as the percentage of pixels correctly
 *  labeled as "above-horizon" or "below-horizon" by the horizon under evaluation
 */
double evaluateHorizon(const Horizon &eval, const Horizon &groundTruth) {
    double correctly_classified = 0;
    double total_classified = 0;

    // Perform a crude grid search over the image to look for incorrectly-labeled pixels
    // A more motivated developer might see fit to replace this implementation with one
    // that is constant-time, using geometrically-calculated areas of intersection
    for (int x = 0; x < LeptonCameraSpecifications.pixelWidth; x += 4) {
        for (int y = 0; y < LeptonCameraSpecifications.pixelHeight; y += 4) {
            if (eval.isPointAbove(x, y) && groundTruth.isPointAbove(x, y) ||
                    !eval.isPointAbove(x, y) && !groundTruth.isPointAbove(x, y)) {
                correctly_classified++;
            }

            total_classified++;
        }
    }

    return correctly_classified / total_classified;
}

int main(int argc, const char *const *argv) {

    tclap::CmdLine cmd(DOCSTRING,
                       ' ', "0.1");

    tclap::UnlabeledValueArg <std::string>
            imuFilePath("imu-file",
                        "File containing raw output from the IMU",
                        true, "", "imu file", cmd);

    tclap::UnlabeledValueArg <std::string>
            groundTruthFilePath("gt-file",
                                "File containing ground truths for horizons corresponding to the given IMU file."
                                        "This should be a file produced by the `label_horizons.py` utility in "
                                        "Sailbot's data-analysis repository.",
                                true, "", "ground truth file", cmd);

    tclap::UnlabeledValueArg <std::string>
            outputFramesArg("output-file",
                            "File to which to output the results of the evaluation of the algorithm.",
                            true, "", "output evaluation file", cmd);

    cmd.parse(argc, argv);

    // open reader into imu file to generate horizons
    OrientationFileReader oreader(imuFilePath.getValue(), false, false);

    // open reader into gt file to generate ground truth horizons
    GroundTruthHorizonReader gtreader(groundTruthFilePath.getValue());

    // open reader into output file to output results of evaluation
    std::ofstream metricsWriter;
    metricsWriter.open(outputFramesArg.getValue());

    int imuLineNum = 1;
    HorizonFactory factory(LeptonCameraSpecifications);

    // info as a courtesy to the user
    std::cout << "Performance per labeled frame: " << std::endl;
    double runningTotalScore = 0;
    unsigned int numFramesEvaluated = 0;

    while (gtreader.hasNext()) {
        const auto frameNumHorizonPair = gtreader.next();

        // iterate to the right line in imu file
        while (imuLineNum < frameNumHorizonPair.first) {
            oreader.next();
            imuLineNum++;
        }

        const auto &predictedHorizon = factory.makeHorizon(oreader.next());
        imuLineNum++;

        double coverageScore = evaluateHorizon(predictedHorizon, frameNumHorizonPair.second);
        runningTotalScore += coverageScore;
        numFramesEvaluated++;

        // output evaluation to file
        metricsWriter << frameNumHorizonPair.first << " " << coverageScore << std::endl;

        // print info for user
        std::cout << frameNumHorizonPair.first << " " << coverageScore << std::endl;
    }

    std::cout << "Average coverage score for this ground truth file: "
              << runningTotalScore / numFramesEvaluated << std::endl;
}
