//https://www.cnblogs.com/msymm/p/9756298.html
//https://blog.csdn.net/lady_killer9/article/details/86762495
//https://blog.csdn.net/wp1603710463/article/details/50933102

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<set>
#include<list>
#include<vector>
#include<map>
#include<iterator>
#include<algorithm>
#include<iostream>
#define MAX 1000 //哈夫曼树最大结点个数
#define MAXW 1000 //权值最大
using namespace std;
//哈夫曼树结点结构
typedef struct HNode
{
    char data; //数据,非叶节点为NULL
    double weight;//权重
    int parent;//双亲，-1表示没有双亲，即根节点
    int lchild;//左孩子，数组下标,-1表示无左孩子，即叶节点
    int rchild;//右孩子
}Hnode;
//编码结构
typedef struct HCNode
{
    char data; //数据
    string code;//该字符编码
}Hcnode;
//两个最小结点下标
struct minnodes
{
    int m1;//两者更小权值结点下标
    int m2;
    bool flag;//若找到则为true,否则为false，false说明仅有一个结点
};
//辅助标志数组 标记该结点为根的树是否已加入哈夫曼树
bool flag[MAX] = { false };
Hnode HT[MAX];//哈夫曼树
Hcnode HC[MAX];//哈夫曼编码数组

//选择两棵最小权值的树 参数max，当前有权值结点下标+1
minnodes Select(int max)
{
    double min = MAXW;
    minnodes mins = {-1, -1, false};
    //查找第一个最小权值的结点下标
    for (int i = 0; i < max; i++)
    {
        if (!flag[i] && HT[i].weight < min)//未加入哈夫曼树,权值更小
        {
            if(mins.m2 == -1 || min < HT[mins.m2].weight)
            {
                mins.m2 = mins.m1;
            }
            min = HT[i].weight;//更新最小权值
            mins.m1 = i;
        }
        else if(!flag[i] && (mins.m2 == -1 || HT[i].weight < HT[mins.m2].weight ))
        {
            mins.m2 = i;
        }

    }
    flag[mins.m1] = true;//将结点加入哈夫曼树
    min = MAXW;
    if(!(mins.m2 < 0))
    {
        mins.flag = true;
    }
    else
        mins.flag = false;
    flag[mins.m2] = true;

    //查找第二个最小权值结点下标，可能不存在
    /*
    for (int i = 0; i < max; i++)
    {
        if (!flag[i] && HT[i].weight < min)//未加入哈夫曼树,权值更小
        {
            min = HT[i].weight;//更新最小权值
            mins.m2 = i;
        }
    }
    flag[mins.m2] = true;//将结点加入哈夫曼树
    if (-1 == mins.m2)//仅剩余一个结点未加入哈夫曼树
    {
        mins.flag = false;//未找到两棵最小权值树
    }
    else
    {
        mins.flag = true;
    }
     */
    return mins;
}
//打印哈夫曼树
void PrintHT(int max)
{
    cout << "下标\t" << "数据\t" << "权重\t" << "双亲\t" << "左孩子\t" << "右孩子" << endl;
    for (int i = 0; i<max; i++)
    {
        cout << i << "\t" << HT[i].data << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
    }
}
//打印编码
void PrintHC(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << HC[i].data << ":" << HC[i].code << endl;;
    }
}
//创建哈夫曼树
void CreateHT()
{
    int n = 6;//字符个数，即哈夫曼树叶节点个数
    int a[] = {45, 13, 12, 16, 9, 5};
    char b[] = {'a', 'b', 'c', 'd', 'e', 'f', 'e'};

    minnodes mins;
    //cout << "请输入字符个数：" << endl;
    //cin >> n;

    //cout << "请输入字符及权值：" << endl;
    for (int i = 0; i < n; i++)
    {

        HT[i].data = b[i];
        HT[i].weight = a[i];
        HT[i].lchild = -1; HT[i].rchild = -1;
    }

    /*
    HT[0].data = 'a';HT[0].weight = 45;HT[0].lchild = -1;HT[0].rchild = -1;
    HT[1].data = 'b';HT[1].weight = 13;HT[1].lchild = -1;HT[1].rchild = -1;
    HT[2].data = 'c';HT[2].weight = 12;HT[2].lchild = -1;HT[2].rchild = -1;
    HT[3].data = 'd';HT[3].weight = 16;HT[3].lchild = -1;HT[3].rchild = -1;
    HT[4].data = 'e';HT[4].weight = 9; HT[4].lchild = -1;HT[4].rchild = -1;
    HT[5].data = 'f';HT[5].weight = 5; HT[5].lchild = -1;HT[5].rchild = -1;
     */
    int i = n;
    for (;; i++)
    {
        mins = Select(i);//找到两棵根权值最小的树
        if (mins.flag == false)//仅剩余一棵树时跳出
        {
            HT[mins.m1].parent = -1;
            break;
        }
        HT[i].weight = HT[mins.m1].weight + HT[mins.m2].weight;//新加入哈夫曼树结点为两个结点权值之和
        HT[i].data = ' ';
        HT[mins.m1].parent = i;                                //两个权值最小结点双亲为新加入结点
        HT[mins.m2].parent = i;
        HT[i].lchild = mins.m1;//左小又大
        HT[i].rchild = mins.m2;
    }
    PrintHT(i);//打印哈夫曼树
}
//哈夫曼树编码
void Code()
{
    int i = 0;
    for (;; i++)//给所有叶子结点编码
    {
        int j = i;
        string str = "";
        HC[i].data = HT[i].data;//复制数据
        while (-1 != HT[j].parent)//从叶节点找到根
        {
            if (HT[HT[j].parent].lchild == j)//左0右1
            {
                str += '0';
            }
            else
            {
                str += '1';
            }
            j = HT[j].parent;
        }
        reverse(str.begin(), str.end());//逆序
        HC[i].code = str;              //保存至编码
        if (HT[i].lchild == -1 && HT[i].rchild == -1)continue;//非叶子不编码
        else break;
    }
    PrintHC(i);
}
//哈夫曼树解码 从根开始，左0右1，直至叶节点
void Encode()
{
    string s;
    int root = 0;//记录根节点的下标
    cout << "请输入01字符串:" << endl;
    cin >> s;
    while (HT[root].parent != -1) root++;
    int j = root;
    for (int i = 0; i<s.length(); i++)//遍历输入的01串
    {
        if ('0' == s[i])
        {
            j = HT[j].lchild;
        }
        else
        {
            j = HT[j].rchild;
        }
        if (HT[j].lchild == -1 && HT[j].rchild == -1)//到达叶节点
        {
            cout << HT[j].data;
            j = root;//返回根节点继续
        }
    }
    cout << endl;
}
//计算WPL
void WPL()
{
    double WPL = 0;
    for (int i = 0;; i++)
    {
        if (HT[i].lchild != -1 || HT[i].rchild != -1)break;
        WPL += HT[i].weight*HC[i].code.length();//权值×路径长度（编码长度）
    }
    cout << "WPL:" << WPL << endl;
}
//菜单
void menu()
{
    cout << "************1.创建哈夫曼树   2.编码************" << endl;
    cout << "************3.解码           4.计算wpl*********" << endl;
    cout << "************5.退出" << endl;
}
//主函数
int main()
{
    int choice = 0;
    while (true)
    {
        menu();
        printf("请输入菜单序号：\n");
        scanf("%d", &choice);
        if (5 == choice) break;
        switch (choice)
        {
            case 1:CreateHT(); break;
            case 2:Code(); break;
            case 3:Encode(); break;
            case 4:WPL(); break;
            default:printf("输入错误！！！\n"); break;
        }
    }
    return 0;
}