#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char const *argv[])
{
    Mat data = (Mat_<double>(2, 2) << 1, 2, 2, 1);
    Mat eigen_values, eigen_vector;
    eigen(data, eigen_values, eigen_vector);
    for(int i = 0; i < eigen_values.rows; i++)
    {
        printf("eigen value %d: %.3f\n", i, eigen_values.at<double>(i));
    }
    cout << "eigen vector: " << endl << eigen_vector << endl;
    waitKey(0);
    return 0;
}
