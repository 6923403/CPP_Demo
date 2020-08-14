#include <iostream>
using namespace std;

int main()
{
    auto except = []()throw(int){
        throw 10;
    };
    try {
        except();
    }
    catch(int) {
        cout << "Capture ok" << endl;
    }

    return 0;
}

/*
 *#include <iostream>
using namespace std;
int main()
{
    auto except1 = []()noexcept{
        throw 100;
    };
    auto except2 = []()throw(char){
        throw 10;
    };
    try{
        except1();
        except2();
    }catch(int){
        cout << "捕获到了整形异常"<< endl;
    }
    return 0;
}
*/
