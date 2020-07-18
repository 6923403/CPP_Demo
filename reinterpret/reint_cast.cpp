#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    int error;
    try {   
    using Byte = std::uint8_t;
    string path = "Super.nes";
    error = 1;
    ifstream romFile (path, std::ios_base::binary | std::ios_base::in);
    if(!romFile.is_open())
    {
        return 0;
    }

    error = 2;
    vector<Byte> header;
    header.resize(0x10);
    if (!romFile.read(reinterpret_cast<char*>(&header[0]), 0x10))
    {
        cout << "Reading iNES header failed." << endl;
    }

    error = 3;
    cout << header[0] << endl;
    cout << header[1] << endl;
    cout << header[2] << endl;

    cout << endl;
    error = 4;
    } 
    catch(...)
    {
        cout << "Error = " << error << endl;
    }

    return 0;
}
