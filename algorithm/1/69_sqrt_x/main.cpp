class Solution {
public:
    int mySqrt(int x) {
        if(x == 0 || x == 1)
        {
            return x;
        }
        int left = 0;
        int right = x;
        int mid = 0;
        while(left < right)
        {
            mid = left + ((right - left) / 2);
            if(x / mid == mid)
                return mid;
            else if(x / mid < mid)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return right - 1;
    }
};