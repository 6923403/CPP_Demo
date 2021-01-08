/*
 * https://www.cnblogs.com/hyb221512/p/8975624.html
 * https://www.cnblogs.com/eczhou/p/5434996.html
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char const *argv[])
{
    Mat samples = (Mat_<double>(5, 3) << 90, 60, 90, 90, 90, 30, 60, 60, 60, 60, 60, 90, 30, 30, 30);
    Mat cov, mu; //mu：保存均值 //cov：保存协方差
    calcCovarMatrix(samples, cov, mu, CV_COVAR_NORMAL | CV_COVAR_ROWS);//CV_COVAR_COLS
    cout << "means : "<< endl;
    cout << mu << endl;
    cout << cov << endl;
    cout << "cov : " << endl;
    cout << cov/5 << endl;
    waitKey(0);
    return 0;
}
