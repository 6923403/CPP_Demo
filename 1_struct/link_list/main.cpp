#include "list.h"

int main(int argc, char** argv)
{
    List list;

    list.init();
    list.Insert();
    list.head_Insert();
    list.Delete();
    list.show();

    return 0;
}