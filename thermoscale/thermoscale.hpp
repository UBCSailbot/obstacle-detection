#define APP_NAME "thermoscale"
#define WIN_ZOOM_FACTOR 8
#define WIN_WIDTH 80 * WIN_ZOOM_FACTOR
#define WIN_HEIGHT 60 * WIN_ZOOM_FACTOR
#define EIGHT_BITS 256

struct TrackbarInfo {
    int minVal_orig;
    int* trackbarMin;
    int* trackbarMax; 
};

struct ProcessedFrameInfo {
    cv::Mat* imagePtr;
    TrackbarInfo* trackbarInfo;
    std::string* win_name;
};

void onTrackbarSlide(int pos, void *VP);
int trackbarValToPixelVal(int trackbarVal,int origMinVal);
struct TrackbarInfo *newTrackbarInfo(int minVal_orig,int *trackbarMin,int *trackbarMax);
char showProcessedImage(cv::Mat* image, TrackbarInfo* info, std::string* win_name);