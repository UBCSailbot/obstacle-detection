#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace cv
{

// Classical Hough Transform
struct LinePolar
{
    float rho;
    float angle;
};


struct hough_cmp_gt
{
    hough_cmp_gt(const int* _aux) : aux(_aux) {}
    bool operator()(int l1, int l2) const
    {
        return aux[l1] > aux[l2] || (aux[l1] == aux[l2] && l1 < l2);
    }
    const int* aux;
};


/*
Here image is an input raster;
step is it's step; size characterizes it's ROI;
rho and theta are discretization steps (in pixels and radians correspondingly).
threshold is the minimum number of pixels in the feature for it
to be a candidate for line. lines is the output
array of (rho, theta) pairs. linesMax is the buffer size (number of pairs).
Functions return the actual number of found lines.
*/
static void
HoughLinesStandard( const Mat& img, float rho, float theta,
                    int threshold, std::vector<Vec2f>& lines, int linesMax,
                    double min_theta, double max_theta )
{
    int i, j;
    float irho = 1 / rho;

    CV_Assert( img.type() == CV_8UC1 );

    const uchar* image = img.ptr();
    int step = (int)img.step;
    int width = img.cols;
    int height = img.rows;

    if (max_theta < 0 || max_theta > CV_PI ) {
        CV_Error( CV_StsBadArg, "max_theta must fall between 0 and pi" );
    }
    if (min_theta < 0 || min_theta > max_theta ) {
        CV_Error( CV_StsBadArg, "min_theta must fall between 0 and max_theta" );
    }
    int numangle = cvRound((max_theta - min_theta) / theta);
    int numrho = cvRound(((width + height) * 2 + 1) / rho);


    AutoBuffer<int> _accum((numangle+2) * (numrho+2));
    std::vector<int> _sort_buf;
    AutoBuffer<float> _tabSin(numangle);
    AutoBuffer<float> _tabCos(numangle);
    int *accum = _accum;
    float *tabSin = _tabSin, *tabCos = _tabCos;

    memset( accum, 0, sizeof(accum[0]) * (numangle+2) * (numrho+2) );

    float ang = static_cast<float>(min_theta);
    for(int n = 0; n < numangle; ang += theta, n++ )
    {
        tabSin[n] = (float)(sin((double)ang) * irho);
        tabCos[n] = (float)(cos((double)ang) * irho);
    }

    // stage 1. fill accumulator
    for( i = 0; i < height; i++ )
        for( j = 0; j < width; j++ )
        {
            if( image[i * step + j] != 0 )
                for(int n = 0; n < numangle; n++ )
                {
                    int r = cvRound( j * tabCos[n] + i * tabSin[n] );
                    r += (numrho - 1) / 2;
                    accum[(n+1) * (numrho+2) + r+1]++;
                }
        }

    // stage 2. find local maximums
    for(int r = 0; r < numrho; r++ )
        for(int n = 0; n < numangle; n++ )
        {
            int base = (n+1) * (numrho+2) + r+1;
            if( accum[base] > threshold &&
                accum[base] > accum[base - 1] && accum[base] >= accum[base + 1] &&
                accum[base] > accum[base - numrho - 2] && accum[base] >= accum[base + numrho + 2] )
                _sort_buf.push_back(base);
        }

    // stage 3. sort the detected lines by accumulator value
    std::sort(_sort_buf.begin(), _sort_buf.end(), hough_cmp_gt(accum));

    // stage 4. store the first min(total,linesMax) lines to the output buffer
    linesMax = std::min(linesMax, (int)_sort_buf.size());
    double scale = 1./(numrho+2);
    for( i = 0; i < linesMax; i++ )
    {
        LinePolar line;
        int idx = _sort_buf[i];
        int n = cvFloor(idx*scale) - 1;
        int r = idx - (n+1)*(numrho+2) - 1;
        line.rho = (r - (numrho - 1)*0.5f) * rho;
        line.angle = n * theta;
        lines.push_back(Vec2f(line.rho, line.angle));
    }
}


// Multi-Scale variant of Classical Hough Transform

struct hough_index
{
    hough_index() : value(0), rho(0.f), theta(0.f) {}
    hough_index(int _val, float _rho, float _theta)
    : value(_val), rho(_rho), theta(_theta) {}

    int value;
    float rho, theta;
};


static void
HoughLinesSDiv( const Mat& img,
                float rho, float theta, int threshold,
                int srn, int stn,
                std::vector<Vec2f>& lines, int linesMax,
                double min_theta, double max_theta )
{
    #define _POINT(row, column)\
        (image_src[(row)*step+(column)])

    int index, i;
    int ri, ti, ti1, ti0;
    int row, col;
    float r, t;                 /* Current rho and theta */
    float rv;                   /* Some temporary rho value */

    int fn = 0;
    float xc, yc;

    const float d2r = (float)(CV_PI / 180);
    int sfn = srn * stn;
    int fi;
    int count;
    int cmax = 0;

    std::vector<hough_index> lst;

    CV_Assert( img.type() == CV_8UC1 );
    CV_Assert( linesMax > 0 );

    threshold = MIN( threshold, 255 );

    const uchar* image_src = img.ptr();
    int step = (int)img.step;
    int w = img.cols;
    int h = img.rows;

    float irho = 1 / rho;
    float itheta = 1 / theta;
    float srho = rho / srn;
    float stheta = theta / stn;
    float isrho = 1 / srho;
    float istheta = 1 / stheta;

    int rn = cvFloor( std::sqrt( (double)w * w + (double)h * h ) * irho );
    int tn = cvFloor( 2 * CV_PI * itheta );

    lst.push_back(hough_index(threshold, -1.f, 0.f));

    // Precalculate sin table
    std::vector<float> _sinTable( 5 * tn * stn );
    float* sinTable = &_sinTable[0];

    for( index = 0; index < 5 * tn * stn; index++ )
        sinTable[index] = (float)cos( stheta * index * 0.2f );

    std::vector<uchar> _caccum(rn * tn, (uchar)0);
    uchar* caccum = &_caccum[0];

    // Counting all feature pixels
    for( row = 0; row < h; row++ )
        for( col = 0; col < w; col++ )
            fn += _POINT( row, col ) != 0;

    std::vector<int> _x(fn), _y(fn);
    int* x = &_x[0], *y = &_y[0];

    // Full Hough Transform (it's accumulator update part)
    fi = 0;
    for( row = 0; row < h; row++ )
    {
        for( col = 0; col < w; col++ )
        {
            if( _POINT( row, col ))
            {
                int halftn;
                float r0;
                float scale_factor;
                int iprev = -1;
                float phi, phi1;
                float theta_it;     // Value of theta for iterating

                // Remember the feature point
                x[fi] = col;
                y[fi] = row;
                fi++;

                yc = (float) row + 0.5f;
                xc = (float) col + 0.5f;

                /* Update the accumulator */
                t = (float) fabs( cvFastArctan( yc, xc ) * d2r );
                r = (float) std::sqrt( (double)xc * xc + (double)yc * yc );
                r0 = r * irho;
                ti0 = cvFloor( (t + CV_PI*0.5) * itheta );

                caccum[ti0]++;

                theta_it = rho / r;
                theta_it = theta_it < theta ? theta_it : theta;
                scale_factor = theta_it * itheta;
                halftn = cvFloor( CV_PI / theta_it );
                for( ti1 = 1, phi = theta_it - (float)(CV_PI*0.5), phi1 = (theta_it + t) * itheta;
                     ti1 < halftn; ti1++, phi += theta_it, phi1 += scale_factor )
                {
                    rv = r0 * std::cos( phi );
                    i = (int)rv * tn;
                    i += cvFloor( phi1 );
                    assert( i >= 0 );
                    assert( i < rn * tn );
                    caccum[i] = (uchar) (caccum[i] + ((i ^ iprev) != 0));
                    iprev = i;
                    if( cmax < caccum[i] )
                        cmax = caccum[i];
                }
            }
        }
    }

    // Starting additional analysis
    count = 0;
    for( ri = 0; ri < rn; ri++ )
    {
        for( ti = 0; ti < tn; ti++ )
        {
            if( caccum[ri * tn + ti] > threshold )
                count++;
        }
    }

    if( count * 100 > rn * tn )
    {
        HoughLinesStandard( img, rho, theta, threshold, lines, linesMax, min_theta, max_theta );
        return;
    }

    std::vector<uchar> _buffer(srn * stn + 2);
    uchar* buffer = &_buffer[0];
    uchar* mcaccum = buffer + 1;

    count = 0;
    for( ri = 0; ri < rn; ri++ )
    {
        for( ti = 0; ti < tn; ti++ )
        {
            if( caccum[ri * tn + ti] > threshold )
            {
                count++;
                memset( mcaccum, 0, sfn * sizeof( uchar ));

                for( index = 0; index < fn; index++ )
                {
                    int ti2;
                    float r0;

                    yc = (float) y[index] + 0.5f;
                    xc = (float) x[index] + 0.5f;

                    // Update the accumulator
                    t = (float) fabs( cvFastArctan( yc, xc ) * d2r );
                    r = (float) std::sqrt( (double)xc * xc + (double)yc * yc ) * isrho;
                    ti0 = cvFloor( (t + CV_PI * 0.5) * istheta );
                    ti2 = (ti * stn - ti0) * 5;
                    r0 = (float) ri *srn;

                    for( ti1 = 0; ti1 < stn; ti1++, ti2 += 5 )
                    {
                        rv = r * sinTable[(int) (std::abs( ti2 ))] - r0;
                        i = cvFloor( rv ) * stn + ti1;

                        i = CV_IMAX( i, -1 );
                        i = CV_IMIN( i, sfn );
                        mcaccum[i]++;
                        assert( i >= -1 );
                        assert( i <= sfn );
                    }
                }

                // Find peaks in maccum...
                for( index = 0; index < sfn; index++ )
                {
                    i = 0;
                    int pos = (int)(lst.size() - 1);
                    if( pos < 0 || lst[pos].value < mcaccum[index] )
                    {
                        hough_index vi(mcaccum[index],
                                       index / stn * srho + ri * rho,
                                       index % stn * stheta + ti * theta - (float)(CV_PI*0.5));
                        lst.push_back(vi);
                        for( ; pos >= 0; pos-- )
                        {
                            if( lst[pos].value > vi.value )
                                break;
                            lst[pos+1] = lst[pos];
                        }
                        lst[pos+1] = vi;
                        if( (int)lst.size() > linesMax )
                            lst.pop_back();
                    }
                }
            }
        }
    }

    for( size_t idx = 0; idx < lst.size(); idx++ )
    {
        if( lst[idx].rho < 0 )
            continue;
        lines.push_back(Vec2f(lst[idx].rho, lst[idx].theta));
    }
}


#ifdef HAVE_OPENCL

#define OCL_MAX_LINES 4096

static bool ocl_makePointsList(InputArray _src, OutputArray _pointsList, InputOutputArray _counters)
{
    UMat src = _src.getUMat();
    _pointsList.create(1, (int) src.total(), CV_32SC1);
    UMat pointsList = _pointsList.getUMat();
    UMat counters = _counters.getUMat();
    ocl::Device dev = ocl::Device::getDefault();

    const int pixPerWI = 16;
    int workgroup_size = min((int) dev.maxWorkGroupSize(), (src.cols + pixPerWI - 1)/pixPerWI);
    ocl::Kernel pointListKernel("make_point_list", ocl::imgproc::hough_lines_oclsrc,
                                format("-D MAKE_POINTS_LIST -D GROUP_SIZE=%d -D LOCAL_SIZE=%d", workgroup_size, src.cols));
    if (pointListKernel.empty())
        return false;

    pointListKernel.args(ocl::KernelArg::ReadOnly(src), ocl::KernelArg::WriteOnlyNoSize(pointsList),
                         ocl::KernelArg::PtrWriteOnly(counters));

    size_t localThreads[2]  = { workgroup_size, 1 };
    size_t globalThreads[2] = { workgroup_size, src.rows };

    return pointListKernel.run(2, globalThreads, localThreads, false);
}

static bool ocl_fillAccum(InputArray _pointsList, OutputArray _accum, int total_points, double rho, double theta, int numrho, int numangle)
{
    UMat pointsList = _pointsList.getUMat();
    _accum.create(numangle + 2, numrho + 2, CV_32SC1);
    UMat accum = _accum.getUMat();
    ocl::Device dev = ocl::Device::getDefault();

    float irho = (float) (1 / rho);
    int workgroup_size = min((int) dev.maxWorkGroupSize(), total_points);

    ocl::Kernel fillAccumKernel;
    size_t localThreads[2];
    size_t globalThreads[2];

    size_t local_memory_needed = (numrho + 2)*sizeof(int);
    if (local_memory_needed > dev.localMemSize())
    {
        accum.setTo(Scalar::all(0));
        fillAccumKernel.create("fill_accum_global", ocl::imgproc::hough_lines_oclsrc,
                                format("-D FILL_ACCUM_GLOBAL"));
        if (fillAccumKernel.empty())
            return false;
        globalThreads[0] = workgroup_size; globalThreads[1] = numangle;
        fillAccumKernel.args(ocl::KernelArg::ReadOnlyNoSize(pointsList), ocl::KernelArg::WriteOnlyNoSize(accum),
                        total_points, irho, (float) theta, numrho, numangle);
        return fillAccumKernel.run(2, globalThreads, NULL, false);
    }
    else
    {
        fillAccumKernel.create("fill_accum_local", ocl::imgproc::hough_lines_oclsrc,
                                format("-D FILL_ACCUM_LOCAL -D LOCAL_SIZE=%d -D BUFFER_SIZE=%d", workgroup_size, numrho + 2));
        if (fillAccumKernel.empty())
            return false;
        localThreads[0] = workgroup_size; localThreads[1] = 1;
        globalThreads[0] = workgroup_size; globalThreads[1] = numangle+2;
        fillAccumKernel.args(ocl::KernelArg::ReadOnlyNoSize(pointsList), ocl::KernelArg::WriteOnlyNoSize(accum),
                        total_points, irho, (float) theta, numrho, numangle);
        return fillAccumKernel.run(2, globalThreads, localThreads, false);
    }
}

static bool ocl_HoughLines(InputArray _src, OutputArray _lines, double rho, double theta, int threshold,
                           double min_theta, double max_theta)
{
    CV_Assert(_src.type() == CV_8UC1);

    if (max_theta < 0 || max_theta > CV_PI ) {
        CV_Error( CV_StsBadArg, "max_theta must fall between 0 and pi" );
    }
    if (min_theta < 0 || min_theta > max_theta ) {
        CV_Error( CV_StsBadArg, "min_theta must fall between 0 and max_theta" );
    }
    if (!(rho > 0 && theta > 0)) {
        CV_Error( CV_StsBadArg, "rho and theta must be greater 0" );
    }

    UMat src = _src.getUMat();
    int numangle = cvRound((max_theta - min_theta) / theta);
    int numrho = cvRound(((src.cols + src.rows) * 2 + 1) / rho);

    UMat pointsList;
    UMat counters(1, 2, CV_32SC1, Scalar::all(0));

    if (!ocl_makePointsList(src, pointsList, counters))
        return false;

    int total_points = counters.getMat(ACCESS_READ).at<int>(0, 0);
    if (total_points <= 0)
    {
        _lines.assign(UMat(0,0,CV_32FC2));
        return true;
    }

    UMat accum;
    if (!ocl_fillAccum(pointsList, accum, total_points, rho, theta, numrho, numangle))
        return false;

    const int pixPerWI = 8;
    ocl::Kernel getLinesKernel("get_lines", ocl::imgproc::hough_lines_oclsrc,
                               format("-D GET_LINES"));
    if (getLinesKernel.empty())
        return false;

    int linesMax = threshold > 0 ? min(total_points*numangle/threshold, OCL_MAX_LINES) : OCL_MAX_LINES;
    UMat lines(linesMax, 1, CV_32FC2);

    getLinesKernel.args(ocl::KernelArg::ReadOnly(accum), ocl::KernelArg::WriteOnlyNoSize(lines),
                        ocl::KernelArg::PtrWriteOnly(counters), linesMax, threshold, (float) rho, (float) theta);

    size_t globalThreads[2] = { (numrho + pixPerWI - 1)/pixPerWI, numangle };
    if (!getLinesKernel.run(2, globalThreads, NULL, false))
        return false;

    int total_lines = min(counters.getMat(ACCESS_READ).at<int>(0, 1), linesMax);
    if (total_lines > 0)
        _lines.assign(lines.rowRange(Range(0, total_lines)));
    else
        _lines.assign(UMat(0,0,CV_32FC2));
    return true;
}

static bool ocl_HoughLinesP(InputArray _src, OutputArray _lines, double rho, double theta, int threshold,
                           double minLineLength, double maxGap)
{
    CV_Assert(_src.type() == CV_8UC1);

    if (!(rho > 0 && theta > 0)) {
        CV_Error( CV_StsBadArg, "rho and theta must be greater 0" );
    }

    UMat src = _src.getUMat();
    int numangle = cvRound(CV_PI / theta);
    int numrho = cvRound(((src.cols + src.rows) * 2 + 1) / rho);

    UMat pointsList;
    UMat counters(1, 2, CV_32SC1, Scalar::all(0));

    if (!ocl_makePointsList(src, pointsList, counters))
        return false;

    int total_points = counters.getMat(ACCESS_READ).at<int>(0, 0);
    if (total_points <= 0)
    {
        _lines.assign(UMat(0,0,CV_32SC4));
        return true;
    }

    UMat accum;
    if (!ocl_fillAccum(pointsList, accum, total_points, rho, theta, numrho, numangle))
        return false;

    ocl::Kernel getLinesKernel("get_lines", ocl::imgproc::hough_lines_oclsrc,
                               format("-D GET_LINES_PROBABOLISTIC"));
    if (getLinesKernel.empty())
        return false;

    int linesMax = threshold > 0 ? min(total_points*numangle/threshold, OCL_MAX_LINES) : OCL_MAX_LINES;
    UMat lines(linesMax, 1, CV_32SC4);

    getLinesKernel.args(ocl::KernelArg::ReadOnly(accum), ocl::KernelArg::ReadOnly(src),
                        ocl::KernelArg::WriteOnlyNoSize(lines), ocl::KernelArg::PtrWriteOnly(counters),
                        linesMax, threshold, (int) minLineLength, (int) maxGap, (float) rho, (float) theta);

    size_t globalThreads[2] = { numrho, numangle };
    if (!getLinesKernel.run(2, globalThreads, NULL, false))
        return false;

    int total_lines = min(counters.getMat(ACCESS_READ).at<int>(0, 1), linesMax);
    if (total_lines > 0)
        _lines.assign(lines.rowRange(Range(0, total_lines)));
    else
        _lines.assign(UMat(0,0,CV_32SC4));

    return true;
}

#endif /* HAVE_OPENCL */

}

namespace cv
{

const int STORAGE_SIZE = 1 << 12;

static void seqToMat(const CvSeq* seq, OutputArray _arr)
{
    if( seq && seq->total > 0 )
    {
        _arr.create(1, seq->total, seq->flags, -1, true);
        Mat arr = _arr.getMat();
        cvCvtSeqToArray(seq, arr.ptr());
    }
    else
        _arr.release();
}

}

void cv::HoughCircles( InputArray _image, OutputArray _circles,
                       int method, double dp, double min_dist,
                       double param1, double param2,
                       int minRadius, int maxRadius )
{
    Ptr<CvMemStorage> storage(cvCreateMemStorage(STORAGE_SIZE));
    Mat image = _image.getMat();
    CvMat c_image = image;
    CvSeq* seq = cvHoughCircles( &c_image, storage, method,
                    dp, min_dist, param1, param2, minRadius, maxRadius );
    seqToMat(seq, _circles);
}

/* End of file. */
