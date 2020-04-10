#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void test1()
{
    multimap<string, string> vec;
    string auth = "Qs";
    vec.insert(make_pair(auth, "QQ"));
    vec.insert(make_pair(auth, "WW"));
    vec.insert(make_pair(auth, "EE"));
    
    auto it1 = vec.find(auth);
    auto it2 = vec.count(auth);

    while(it2)
    {
        if(it1->second == "EE")
        {
            vec.erase(it1);
            break;
        }

        ++it1;
        --it2;
    }

    multimap<string, string>::iterator it3 = vec.begin();
    for(it3; it3 != vec.end(); ++it3)
        cout << it3->first << "  " << it3->second << endl;
}

int main(int argc, char **argv)
{
    test1();
}
