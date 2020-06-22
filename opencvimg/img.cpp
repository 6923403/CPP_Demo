#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
int main(int argc, char const *argv[])
{
	Mat src = imread("eagle.jpg");
	imshow("src", src);
	Mat src_gray;
	cvtColor(src, src_gray, COLOR_BGR2GRAY); // 注意，有的教程CV_BGR2GRAY，opencv4下会报错
	imshow("src_gray", src_gray);
	imwrite("eagle_gray.jpg", src_gray);
	waitKey(0);
	return 0;
}

