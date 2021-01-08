#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    cv::Mat src1, src2, dst;
    src1 = cv::imread(argv[1]);
    src2 = cv::imread(argv[2]);
    if(!src1.data && !src2.data)
    {
        std::cout << "cound not load image..." << std::endl;
    }
    if(src1.rows != src2.rows || src1.cols != src2.cols || src1.type() != src2.type())
    {
        cv::resize(src1, src1, cv::Size(300, 300));
        cv::resize(src2, src2, cv::Size(300, 300));
    }
    double alpha = 0.5;
    cv::addWeighted(src1, alpha, src2, 0.6, 0.0, dst);
    cv::imshow("src1", src1);
    cv::imshow("src2", src2);
    cv::imshow("dst", dst);

    cv::waitKey();
    return 0;
}