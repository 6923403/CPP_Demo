#include <iostream>
#include <string>
using namespace std;

string version1(const string & s1, const string & s2);
const string & version2(string & s1, const string & s2);
//const string & version3(string & s1, const string & s2);

int main(int argc, char **argv)
{
    string input;
    string copy;
    string result;

    cout << "A string" << endl;

    getline(cin, input);
    copy = input;
    result = version1(input, "***");
    cout << "version1_result: " << result << endl;
    cout << "version1_input: " << input << endl;

    result = version2(input, "###");
    cout << "version2_result: " << result << endl;
    cout << "version2_input: " << input << endl;

    return 0;
}

string version1(const string & s1, const string & s2)
{
    string temp;
    temp = s2 + s1 + s2;
    return temp;

}

const string & version2(string & s1, const string & s2)
{
    s1 = s2 + s1 + s2;
    return s1;
}

const string &version3(string & s1, const string & s2)
{
    string temp;
    temp = s2 + s1 + s2;

    /*
     * unsafe
     */
    return temp;
}



