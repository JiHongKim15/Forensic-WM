
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void ExtractWatermark(Mat& marked_img);                  // extract
void Extract(Mat& Marked_Image);

void   WT(Mat& img, Mat& dst, int NIter);
void   IWT(Mat& dst, Mat& idst, int NIter);



// SVD
void calculate_SVD(Mat& src, Mat& U, Mat& S, Mat& V);
