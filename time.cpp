#include <iostream>
#include <ctime>

int main(int argc, char **argv)
{
    using namespace std;

    time_t result = time(nullptr);

    cout << asctime(localtime(&result)) << result << "  seconds since the Epoch" << endl;
}
