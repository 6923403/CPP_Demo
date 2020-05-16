#include <list>
#include <queue>

using std::cout;
using std::vector;
using std::string;
using std::endl;

void te1()
{
    list<deque<int>> st;

    vector<int> v1(10, 0);
    const vector<int> v2(10, 0);
    /*
     * vector<int>::iterator; const vector<int>::iterator;
     */
    auto it1 = v1.begin(), it2 = v2.begin();

    /*
     * vector<int>::const_iterator; const vector<int>::const_iterator; 
     */
    auto ie3 = v1.cbegin(), it4 = v2.cbegin();
}


int main(int argc, char **argv)
{
    te1();
}
