#ifndef OBSTACLE_AVOIDANCE_LIVEFEED_H
#define OBSTACLE_AVOIDANCE_LIVEFEED_H

#include "imu/IMU.h"
#include "imu/ParallelIMU.h"
#include "camera/lepton/Lepton.h"
#include "features/SunImage.h"

#include "types/Image8bit.h"
#include "types/Image16bit.h"
#include "geometry/Horizon.h"
#include "imageProc/rescale/SimpleRescaler.h"
#include "imageProc/liveFeed/base64EncDec.h"
#include "io/JSONSerializer.h"

#include "comm/ZmqContextSingleton.h"
#include "exceptions/LeptonException.h"
#include "comm/ImageFeedZmq.h"

#include <vector>
#include <unistd.h>
#include <signal.h>
#include <fstream>
#include <display/DisplayUtils.h>
#include <io/ImageStream.h>
#include <io/FileSystemImageStream.h>
#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>
#include <dlib/opencv.h>
#include <imageProc/liveFeed/FeedReader.h>
#include "imageProc/dlib/DLibProcessor.h"

class liveFeedImpl;
/**
 * DEPRECATED
 */
class LiveFeed: public FeedReader { ;
  public:
    LiveFeed(ImageStream *stream, const DLibProcessor &dLibProcessor, char *output_dir,
             bool rumImu);

    static void printUsage(int argc, char **argv);

  protected:

    static void hangup_handler(int signum);

    void setup_sighandler();

    void displayFrameWithHorizonLine(Image8bit image, double roll, double pitch, Display &d);

    DLibProcessor dLibProcessor;

    ImageFeedZmq zmqfeed;

    std::ofstream imuLog;

    ParallelIMU *imu;

    char *output_dir;

    int frame_counter = 0;

    virtual void beforeCapture() override;

    virtual void onImageRead(Image16bit image) override;

    SimpleRescaler rescaler;

    bool runImu;
};

#endif //OBSTACLE_AVOIDANCE_LIVEFEED_H
