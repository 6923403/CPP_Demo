#include "Strblob.h"

StrBlob::StrBlob() : data(make_shared<std::vector<std::string>>())
{

}

StrBlob::StrBlob(initializer_list<string> il) : 
                data(,ake_shared<vector<string>> (il))
{}

void StrBlob::check(size_type i, const string &msg) const
{
    if(i >= data->size())
        throw out_of_range(msg);
}

string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
