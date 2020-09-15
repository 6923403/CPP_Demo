#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int findN(vector<int> &nums)
{
    unordered_set <int> hash_set;
    for (auto &s : nums)
    {
        if (hash_set.count(s) == 1)
            return s;
        else
            hash_set.insert(s);
    }
    return -1;
}


int main()
{
    vector<int> nums = {2, 3, 1, 0, 2, 5, 3};
    int q = findN(nums);

    cout << q << endl;

    return 0;
}
