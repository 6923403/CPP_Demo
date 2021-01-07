#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void k1(const Mat& src, Mat& dst);
void k2(const Mat& src, Mat& dst);

int main(int argc, char **argv) {
    if (argc < 2)
        exit(1);
    Mat src, dst;
    src = imread(argv[1]);
    if (!src.data) {
        cout << "Not jpg" << endl;
        exit(0);
    }
    //k1(src, dst); //图片锐化
    k2(src, dst); //边缘处理
    imshow("img", src);
    imshow("image_process_ker", dst);
    waitKey(0);
    return 0;
}

void k1(const Mat& src, Mat& dst)
{
    Mat kernel(3,3,CV_32F,Scalar(0));
    kernel.at<float>(1,1) = 5;
    kernel.at<float>(0,1) = -1;
    kernel.at<float>(2,1) = -1;
    kernel.at<float>(1,0) = -1;
    kernel.at<float>(1,2) = -1;
    filter2D(src, dst, src.depth(), kernel);
    dst.row(0).setTo(Scalar(0,0,0));
    dst.row(dst.rows-1).setTo(Scalar(0,0,0));
    dst.col(0).setTo(Scalar(0,0,0));
    dst.col(dst.cols-1).setTo(Scalar(0,0,0));
}

void k2(const Mat& src, Mat& dst)
{
    Mat kernel(2, 2, CV_32F, Scalar(0));
    kernel.at<float>(0, 0) = 1;
    kernel.at<float>(0, 1) = 0;
    kernel.at<float>(1, 0) = 0;
    kernel.at<float>(1, 1) = -1;
    filter2D(src, dst, src.depth(), kernel);
    /*
    dst.row(0).setTo(Scalar(0, 0));
    dst.row(dst.).setTo(Scalar(0, 0));
    */
}
