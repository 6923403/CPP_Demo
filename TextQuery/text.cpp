#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <fstream>

#include "text.h"
using namespace std;

Text::Pushline(const string line)
{
    ++book.push_back(line)
}

void Text::ShowLine(int n)
{
    book[n]->second;
}
