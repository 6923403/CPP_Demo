#include<iostream>
#include<algorithm>

using namespace std;

struct var 
{
    char *name;
    int key;
    var(char *a,int k):name(a),key(k){}
};

bool comp(const var& l, const var& r) 
{
    return l.key < r.key;
}

int main() 
{
    var v1("var1", 2);
    var v2("var2", 3);
    cout << std::min(v1, v2, comp).name << endl;
    return 0;
}
