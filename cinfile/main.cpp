#include <fstream>
#include <iostream>
using namespace std;

void test1()
{
    char data[100];

    ofstream outfile;
    outfile.open("afile.tk", ios::out);

    cin.getline(data, 100);
    outfile << data << endl;
    cout << "Age: " ;
    cin >> data;
    cin.ignore();

    outfile << data << endl;
    outfile.close();

    ifstream infile;
    infile.open("afile.tk");
    
    cout << "Read file" << endl;
    infile >> data;
    cout << data << endl;
    infile >> data;
    cout << data << endl;

    infile.close();
}

int main(int argc, char **argv)
{
    test1();
}
