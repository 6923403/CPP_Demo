#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename T>
class Bolb
{
    public:
        typedef T value_type;
        typedef typename vector<T>::size_type size_type;

        Blob();
        Blob(initializer_list<T> il);

        size_type size() const 
        {
            return data->size();
        }

        bool empty() const
        {
            return data->empty();
        }

        void push_back(const T &t)
        {
            data->push_back(t);
        }

        void push_back(T &&t)
        {
            data->push_back(move(t));
        }

        void pop_back();
        T& back();
        T &operator[](size_type i);

    private:
        shared_ptr<vector<T>> data;
        void check(size_type i, const string &msg) const;
};

int main(int argc, char **argv)
{
    Blob<int> ia;
    Blob<int> ia2 = {0, 1, 2, 3, 4};
    Blob<string> ia3;
    Blob<double> ia4;

    return 0;
}
