----------------
#include <iostream>  //输入输出流
#include <cstdlib>   //标准库
#include <unistd.h>  //延时函数要
#include <stdio.h>   //getchar()
#include <ctime>     //时间函数
#include <termios.h> //终端设置
using namespace std;

#define max_x 20      //高
#define max_y 30      //长
bool flag = false;    //构建地图 成功为true
bool slow = false;    //为true 慢速游戏
bool autogame = true; //更换游戏模式 true代表自动行走

int maze[max_x][max_y]; //高20 长30的地图

class stack_foot_maze
{

private:
    //code
    //记录迷宫坐标
    struct node
    {
        int x;
        int y;
        char direction; //上一步路径（如何来的）
        node *next;
    };
    node *head;

public:
    stack_foot_maze()
    {
        head = NULL; //初始化
    }

    ~stack_foot_maze()
    {
        node *p = head;

        while (head != NULL) //逐个删除
        {
            head = head->next;
            delete p;
            p = head;
        }
    }

    void push(int xx, int yy, char direction)
    {
        node *new_node = new node; //定义一个新节点
        if (new_node != NULL)
        {
            new_node->x = xx;
            new_node->y = yy;
            new_node->direction = direction;
            new_node->next = NULL;
            if (head == NULL) //判断栈是否为空，如果为空则直接把新节点赋值给栈，否则添加到栈顶
            {
                head = new_node;
            }
            else
                new_node->next = head;
            head = new_node;
        }
        else
        {
            cout << "内存分配失败" << endl;
        }
    }

    node *pop(int &xx, int &yy)
    {
        if (head != NULL)
        {
            node *p = head;
            head = head->next;
            xx = p->x;
            yy = p->y;
            delete p;
        }
        return head;
    }

    void print()
    {
        if (head != NULL)
        {
            node *p = head;
            while (p != NULL)
            {
                cout << " " << p->x << " " << p->y << " " << p->direction << endl;
                p = p->next;
            }
        }
        else
            cout << "栈为空，打印失败" << endl;
    }

};

void createMaze()
{
    int maxway = max_x * max_y;
    int x, y;

    //先填充迷宫
    for (x = 0; x < max_x; x++)
    {
        for (y = 0; y < max_y; y++)
        {
            maze[x][y] = 1;
        }
    }

    //随即函数种子 以时间为参数
    //srand(unsigned) time(NULL);
    srand((unsigned)time(NULL));

    //随机构建迷宫通路
    for (int i = 0; i < maxway; i++)
    {
        x = rand() % (max_x - 2) + 1;
        y = rand() % (max_y - 2) + 1;
        maze[x][y] = 0;
    }
    maze[1][1] = 0;                 //入口
    maze[max_x - 2][max_y - 2] = 0; //出口

    maze[0][1] = 3;
    maze[max_x - 1][max_y - 2] = 0; //出口
}

void printmaze()
{
    int x, y;

    //清屏
    system("clear"); //win下 cls

    //输出地图
    for (x = 0; x < max_x; x++)
    {
        for (y = 0; y < max_y; y++)
        {
            if (maze[x][y] == 0)
            {
                cout << "  ";
                continue;
            } //通路
            if (maze[x][y] == 1)
            {
                cout << "■ ";
                continue;
            } //墙
            if (maze[x][y] == 2)
            {
                cout << "× ";
                continue;
            } //死胡同
            if (maze[x][y] == 3)
            {
                cout << "↓ ";
                continue;
            } //向下走
            if (maze[x][y] == 4)
            {
                cout << "→ ";
                continue;
            }
            if (maze[x][y] == 5)
            {
                cout << "← ";
                continue;
            }
            if (maze[x][y] == 6)
            {
                cout << "↑ ";
                continue;
            }
            if (maze[x][y] == 7)
            {
                cout << "※ ";
                continue;
            } //当前站立位置
        }
        cout << endl;
    }

    //慢速游戏
    if (slow)
    {
        sleep(1);
    }
}

void check(stack_foot_maze &s)
{
    //备份地图
    int temp[max_x][max_y];
    for (int x = 0; x < max_x; x++)
        for (int y = 0; y < max_y; y++)
            temp[x][y] = maze[x][y];
    int x = 1, y = 1; //起点
    while (1)
    {
        temp[x][y] = 2;

        if (temp[x + 1][y] == 0) //向下
        {
            s.push(x, y, 'D');
            temp[x][y] = 3;
            x = x + 1;
            temp[x][y] = 7;                           //当前位置
            if ((x == max_x - 1) && (y == max_y - 2)) //判断是否到达出口
            {
                flag = true;
                return;
            }
            else
                continue;
        }

        if (temp[x][y + 1] == 0) //向右
        {
            s.push(x, y, 'R');
            temp[x][y] == 4;
            y = y + 1;
            temp[x][y] == 7;

            if ((x == max_x - 1) && (y == max_y - 2)) //判断是否到达出口
            {
                flag = true;
                return;
            }
            else
                continue;
        }

        if (temp[x - 1][y]) //向上
        {
            s.push(x, y, 'U');
            temp[x][y] == 6;
            x = x - 1;
            temp[x][y] == 7;
            if ((x == max_x - 1) && (y == max_y - 2)) //判断是否到达出口
            {
                flag = true;
                return;
            }
            else
                continue;
        }

        if (temp[x][y - 1]) //向左
        {
            s.push(x, y, 'L');
            temp[x][y] == 5;
            y = y - 1;
            temp[x][y] == 7;

            if ((x == max_x - 2) && (y == max_y - 1)) //判断是否到达出口
            {
                flag = true;
                return;
            }
            else
                continue;
        }

        //四个方向不通过 返回起点
        if (s.pop(x, y) == NULL && temp[x - 1][y] != 0 && temp[x][y - 1] != 0 && temp[x][y + 1] != 0 && temp[x + 1][y] != 0)
        {
            temp[0][1] = 7;
            if (temp[1][1] != 1)
                temp[1][1] = 2;
            return;
        }
    }
}

char getch() //在理解
{
    char ch;
    //保存原有终端属性和新设置的终端属性
    static struct termios oldt, newt;

    //获得终端原有属性并保存在结构体oldt
    tcgetattr(STDIN_FILENO, &oldt);

    //设置新的终端属性
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    //取消回显
    system("stty -echo");
    ch = getchar();
    system("stty echo");

    //让终端恢复为原有的属性
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void move()
{
    int x = 1, y = 1;

    //一直游戏 直到走出
    while (1)
    {
        //判断输入的命令
        switch (getch())
        {
        case 's': //向下
            if (maze[x + 1][y] == 0)
            {
                maze[x][y] == 0;
                x = x + 1;
                maze[x][y] == 7;
                printmaze();
                if ((x == max_x - 1) && (y == max_y - 2))
                {
                    cout << "\n \n         成功走出";
                    return;
                }
            }
            break;

        case 'w': //向上
            if (maze[x - 1][y] == 0)
            {
                maze[x][y] == 0;
                x = x - 1;
                maze[x][y] == 7;
                printmaze();
                if ((x == max_x - 1) && (y == max_y - 2))
                {
                    cout << "\n \n         成功走出";
                    return;
                }
            }
            break;

        case 'a': //向左
            if (maze[x][y - 1] == 0)
            {
                maze[x][y] == 0;
                y = y - 1;
                maze[x][y] == 7;
                printmaze();
                if ((x == max_x - 2) && (y == max_y - 1))
                {
                    cout << "\n \n         成功走出";
                    return;
                }
            }
            break;

        case 'd': //向右
            if (maze[x][y + 1] == 0)
            {
                maze[x][y] == 0;
                y = y + 1;
                maze[x][y] == 7;
                printmaze();
                if ((x == max_x - 1) && (y == max_y - 2))
                {
                    cout << "\n \n         成功走出";
                    return;
                }
            }
            break;
        }
    }
}

void automove(stack_foot_maze & s)
{
    int x = 1, y = 1;

    while(1)
    {
       maze[x][y] == 2;

       //左侧
       if(maze[x][y - 1])
       {
           s.push(x, y, 'L');
           maze[x][y] == 5;
           y = y - 1;
           maze[x][y] == 7;
           if(slow){
           printmaze();
           }
           if((x == max_x -1) && (y == max_y - 2))
           {
               s.push(x, y, '*');
               cout << "\n \n         成功走出";
               return;
           }
           else
           continue;
       }

       //向右
       if(maze[x][y + 1])
       {
           s.push(x, y, 'R');
           maze[x][y] == 4;
           y = y + 1;
           maze[x][y] == 7;
           if(slow){
           printmaze();
           }
           if((x == max_x -1) && (y == max_y - 2))
           {
               s.push(x, y, '*');
               cout << "\n \n         成功走出";
               return;
           }
           else
           continue;
       }
       
       //向上
       if(maze[x - 1][y])
       {
           s.push(x, y, 'U');
           maze[x][y] == 6;
           y = y - 1;
           maze[x][y] == 7;
           if(slow){
           printmaze();
           }
           if((x == max_x -1) && (y == max_y - 2))
           {
               s.push(x, y, '*');
               cout << "\n \n         成功走出";
               return;
           }
           else
           continue;
       }

        //向下 
       if(maze[x + 1][y])
       {
           s.push(x, y, 'D');
           maze[x][y] == 3;
           x = x + 1;
           maze[x][y] == 7;
           if(slow){
           printmaze(); 
           }
           if((x == max_x -1) && (y == max_y -2))
           {
               s.push(x, y, '*');
               cout << "\n \n         成功走出";
               return;
           }
           else
           continue;
       }

       //死路  回退
       if((s.pop(x, y) == NULL) && (maze[x + 1][y] != 0) && (maze[x - 1][y] != 0) && (maze[x][y + 1] != 0) && (maze[x][y - 1] != 0))
       {
           cout << "\n\n              没有找到合适的路径" << endl;
           maze[0][1] == 7;
           if(maze[1][1] != 1)
           maze[1][1] == 2;
           return;
       }

    }
}

void menu(); //回调 menu() 函数

void startgame()
{
    //初始化地图
    flag = false;
    while(!flag)
    {
        stack_foot_maze stack;
        createMaze(); //创建地图
        check(stack); //检测

        //模拟进度条
        system("clear");
        cout<<"\t*                loading.              *"<<endl;
        system("clear");
        cout<<"\t*                loading..             *"<<endl;
        system("clear");
        cout<<"\t*                loading...            *"<<endl;

    }
    //输出当前迷宫的初始状态
    printmaze();                       
    cout<<"\n\n              输入enter键继续"<<endl;
    getchar();
    //自行游戏
    if(!autogame){
        move();
        cout<<"\n\n              输入enter键继续"<<endl;
        getchar();
        menu();
    }
    //自动游戏
    else
    {
        stack_foot_maze stack1;
        automove(stack1); //自动移动
    }
    printmaze(); //输出迷宫最终状态
    cout<<"\n\n              输入enter键继续"<<endl;
    getchar();
    menu();
    
}

void menu(){
    system("clear");
    int num;
    cout<<"\t****************************************"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               1.查看路径             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               2.自动进行             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               3.自行游戏             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               4.退出游戏             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t****************************************"<<endl;
    slow = false;
    switch(getch()) //选择游戏模式
    {
        case '1': 
        autogame = true;
        startgame();
        break;

        case '2':
        autogame = true;
        slow = true;
        startgame();
        break;

        case '3':
        autogame = false;
        startgame();
        break;

        case '4':
        exit(1);
        break;

        default:
        cout<<"\n\n              错误操作，输入enter返回！"<<endl;
        getch();
        menu();
    }
    getchar();
}

int main(int argc, char **argv)
{
    menu();
    return 0;
}
