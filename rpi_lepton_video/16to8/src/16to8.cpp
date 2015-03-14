#include "16to8.h"
#include <string>

#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>

using namespace std;

void processDir(string in, string out, int num_files) {
    
//    cv::VideoWriter vid(out.c_str(), CV_FOURCC('X','V','I','D'), 25, cv::Size(80,60)); 

    for (int i=1; i <= num_files; i++) {
        char fname[50];
        sprintf(fname, "/img_%06d.png", i);
        
        cv::Mat image = cv::imread(in + "/" + fname, -1);
//        cout << fname << "\n";
        
        cv::Mat output;
        double minVal, maxVal;
        minMaxLoc(image, &minVal, &maxVal);
        image.convertTo(output, 8, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));

//        vid.write(output);

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

    processDir(input_dir, output_dir, num_files);

    return 0;
}
