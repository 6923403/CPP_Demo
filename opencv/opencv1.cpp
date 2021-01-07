#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

/*
 * g++ -W -Wall -g -O0 opencv1.cpp `pkg-config --cflags --libs opencv4`
 */

int main(int argc, char **argv)
{
    Mat image = imread("./ts.jpg");
    if(image.empty())
    {
        std::cout << "Not img" << std::endl;
    }
    imshow("img", image);
    waitKey(0);

    return 0;
}
