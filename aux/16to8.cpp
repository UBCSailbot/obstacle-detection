#include "16to8.h"
#include <string>

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <queue>

#define NUM_ROWS 60
#define NUM_COLS 80
#define HISTO_SMOOTHING 20

using namespace std;

struct Histogram {
    int* vals;
    int size;
    int min;
    int max;
};

typedef struct Histogram* hist_t;

struct PeakTracker {
    int running_sum;
    std::queue<int>* memory;
};

typedef struct PeakTracker* peak_t;

peak_t new_PeakTracker() {
    peak_t p = (peak_t) malloc(sizeof(PeakTracker));
    std::queue<int>* q = new std::queue<int>();
    p->memory = q;
    p->running_sum = 0;
    return p;        
}

peak_t g_pt;

void zero(int* int_array, int size) {
    for(int i=0; i < size; i++)
        int_array[i] = 0;
}

hist_t new_Histogram(int init_size) {
    hist_t histo = (hist_t) malloc(sizeof(struct Histogram));
    histo->size = init_size;
    histo->vals = (int*) malloc(sizeof(int) * init_size);
    zero(histo->vals, init_size);
    return histo;
}

void delete_Histogram(hist_t histo) {
    free(histo->vals);
    free(histo);
}

/**
 * Scale by compressing the full range of the image into the range [0..256]
 */
cv::Mat default_scale(cv::Mat image) {
    cv::Mat output;
    double minVal, maxVal;
    minMaxLoc(image, &minVal, &maxVal);
    image.convertTo(output, 8, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    return output;
}

hist_t calcHisto(cv::Mat image) {
    double minVal, maxVal;
    minMaxLoc(image, &minVal, &maxVal);
    int histo_size = maxVal - minVal + 1;
    hist_t histo = new_Histogram(histo_size);
    histo->min = minVal;
    histo->max = maxVal;

    for (int row=0; row < NUM_ROWS; row++) {
        for (int col=0; col < NUM_COLS; col++) {
            int i = image.at<uint16_t>(row, col) - minVal;
            histo->vals[i] ++;
        }
    }

    return histo;
}

int index_of_max(hist_t histo) {
    int max_val, max_index;
    max_val = 0; max_index = 0;

    for (int i=0; i < histo->size; i++) {
        if (histo->vals[i] > max_val) {
            max_val = histo->vals[i];
            max_index = i;
        }
    }

    return max_index;
}

int find_peak(hist_t histo) {
    int cur_peak = index_of_max(histo);
    
    g_pt->memory->push(cur_peak);
    g_pt->running_sum += cur_peak;
    
    if (g_pt->memory->size() >= HISTO_SMOOTHING) {
        cur_peak = g_pt->running_sum / HISTO_SMOOTHING;
        g_pt->running_sum -= g_pt->memory->front();
        g_pt->memory->pop();
    }

    return cur_peak;
}

void find_range(int peak_index, int num_vals, int& min, int& max) {
    if (peak_index - 127 < 0) {
        min = 0;
        max = min + 255;
    }
    else if (peak_index + 128 > num_vals) {
        max = num_vals;
        min = max - 255;
    }
    else {
        min = peak_index - 127;
        max = min + 255;
    }
}

/**
 * Scale around the histogram of the image by clipping the extremes.
 */
cv::Mat modal_scale(cv::Mat image) {
    cv::Mat output;
    hist_t histo = calcHisto(image);
    int peak_index = find_peak(histo);
    int new_min, new_max;
    find_range(peak_index, histo->size, new_min, new_max);

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int scaled_val = image.at<uint16_t>(row, col) - (new_min + histo->min);
            if (scaled_val > 255) 
                scaled_val = 255;
            else if (scaled_val < 0)
                scaled_val = 0;
            image.at<uint16_t>(row, col) = scaled_val;
        }
    }

    image.convertTo(output, 8);
    delete_Histogram(histo);
    histo = NULL;
    return output;
}

void processDir(string in, string out, int num_files) {
    
    for (int i=1; i <= num_files; i++) {
        char fname[50];
        sprintf(fname, "/img_%06d.png", i);
        
        cv::Mat image = cv::imread(in + "/" + fname, -1);
        // cout << "Now processing " << fname << endl;  
        //cv::Mat output = default_scale(image);
        cv::Mat output = modal_scale(image);
        
        imwrite(out + "/" + fname, output);
    }
}

int main(int argc, char** argv )
{
    if ( argc != 4 )
    {
        printf("usage: 16to8 <input_dir> <output_dir> <num_files>\n");
        return -1;
    }

    string input_dir = argv[1];
    string output_dir = argv[2];
    int num_files = atoi(argv[3]);

    g_pt = new_PeakTracker();
    processDir(input_dir, output_dir, num_files);

    return 0;
}
