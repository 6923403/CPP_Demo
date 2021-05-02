#include<cstdio>
#include<cstring>
#include<set>
#include<list>
#include<queue>
#include<iostream>

const int MaxVerNum = 100; //顶点最大数目值
using VexType = char; //顶点数据类型
using EdgeType = int; //边数据类型,无向图时邻接矩阵对称，有权值时表示权值，没有时1连0不连
using namespace std;

//图的数据结构
struct Graph
{
    VexType Vex[MaxVerNum];//顶点表
    EdgeType Edge[MaxVerNum][MaxVerNum];//边表
    int vexnum, arcnum;//顶点数、边数
};
//*********************************************基本操作函数*****************************************//
//初始化函数 参数：图G 作用：初始化图的顶点表，邻接矩阵等
void InitGraph(Graph &G)
{
    memset(G.Vex,'#',sizeof(G.Vex));//初始化顶点表
    memset(G.Edge, 0, sizeof(G.Edge));//初始化边表
    G.arcnum = G.vexnum = 0;          //初始化顶点数、边数
}

//插入点函数 参数：图G,顶点v 作用：在图G中插入顶点v,即改变顶点表
bool InsertNode(Graph &G,VexType v)
{
    if (G.vexnum < MaxVerNum)
    {
        G.Vex[G.vexnum++] = v;
        return true;
    }
    return false;
}
//插入边函数 参数：图G,某边两端点v和w 作用：在图G两点v,w之间加入边，即改变邻接矩阵
bool InsertEdge(Graph &G,VexType v,VexType w)
{
    int p1,p2;//v,w两点下标
    p1 = p2 = -1;//初始化
    for (int i=0;i<G.vexnum;i++)//寻找顶点下标
    {
        if (G.Vex[i] == v)p1 = i;
        if (G.Vex[i] == w)p2 = i;
    }
    if (-1 != p1&&-1 != p2)//两点均可在图中找到
    {
        G.Edge[p1][p2] = G.Edge[p2][p1] = 1;//无向图邻接矩阵对称
        G.arcnum++;
        return true;
    }
    return false;
}
//判断是否存在边(v,w)函数 参数：图G，某边两端点v和w 作用：判断是否存在边(v,w)
bool Adjancent(Graph G,VexType v,VexType w)
{
    int p1, p2;//v,w两点下标
    p1 = p2 = -1;//初始化
    for (int i = 0;i<G.vexnum;i++)//寻找顶点下标
    {
        if (G.Vex[i] == v)p1 = i;
        if (G.Vex[i] == w)p2 = i;
    }
    if (-1 != p1&&-1 != p2)//两点均可在图中找到
    {
        if (G.Edge[p1][p2] == 1)//存在边
        {
            return true;
        }
        return false;
    }
    return false;
}
bool visited[MaxVerNum];//访问标记数组，用于遍历时的标记
//广度遍历函数 参数：图G,开始结点下标start 作用：宽度遍历
void BFS(Graph G, int start)
{
    queue<int> Q;//辅助队列
    cout << G.Vex[start];//访问结点
    visited[start] = true;
    Q.push(start);//入队
    while (!Q.empty())//队列非空
    {
        int v = Q.front();//得到队头元素
        Q.pop();//出队
        for (int j=0;j<G.vexnum;j++)//邻接点
        {
            if (G.Edge[v][j] == 1 && !visited[j])//是邻接点且未访问
            {
                cout << "->";
                cout << G.Vex[j];//访问结点
                visited[j] = true;
                Q.push(j);//入队
            }
        }
    }//while
    cout << endl;
}
//深度遍历函数（递归形式）参数：图G,开始结点下标start 作用：深度遍历
void DFS(Graph G, int start)
{
    cout << G.Vex[start];//访问
    visited[start] = true;
    for (int j = 0;j < G.vexnum;j++)
    {
        if (G.Edge[start][j]==1&&!visited[j])//是邻接点且未访问
        {
            cout << "->";
            DFS(G,j);//递归深度遍历
        }
    }
}
//**********************************************功能实现函数*****************************************//
//打印图的顶点表
void PrintVex(Graph G)
{
    return;
    for (int i = 0;i < G.vexnum;i++)
    {
    }
    cout << endl;
}
//打印图的边矩阵
void PrintEdge(Graph G)
{
    for (int i = 0;i < G.vexnum;i++)
    {
        cout << G.Vex[i] << " ";
        for (int j = 0;j < G.vexnum;j++)
        {
            cout << G.Edge[i][j] << " ";
        }
        cout << endl;
    }
}
//创建图功能实现函数 参数：图G  InsertNode 作用：创建图
void CreateGraph(Graph &G)
{
    VexType v,w;
    int vn, an;//顶点数，边数
    vn = 10;
    an = 9;
    char a[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    for (int i=0;i<vn;i++)
    {
        if (InsertNode(G, a[i])) continue;//插入点
        else {
            cout << "输入错误！" << endl;break;
        }
    }

    char b[] = {'A', 'A', 'B', 'C', 'D', 'I', 'G', 'F', 'G'};
    char c[] = {'B', 'C', 'E', 'D', 'E', 'J', 'F', 'H', 'H'};
    for (int j=0;j<an;j++)
    {
        if (InsertEdge(G, b[j], c[j])) continue;//插入边
        else {
            cout << "输入错误！"<<endl;break;
        }
    }
    PrintVex(G);
    PrintEdge(G);
}
//广度遍历功能实现函数 参数：图G 作用：宽度遍历
void BFSTraverse(Graph G)
{
    for (int i = 0;i<MaxVerNum;i++)//初始化访问标记数组
    {
        visited[i] = false;
    }
    for (int i = 0;i < G.vexnum;i++)//对每个连通分量进行遍历
    {
        if (!visited[i])BFS(G,i);
    }
}
//深度遍历功能实现函数 参数：图G 作用：深度遍历
void DFSTraverse(Graph G)
{
    for (int i = 0;i<MaxVerNum;i++)//初始化访问标记数组
    {
        visited[i] = false;
    }
    for (int i = 0;i < G.vexnum;i++)//对每个连通分量进行遍历
    {
        if (!visited[i])
        {
            DFS(G, i);cout << endl;
        }
    }
}
//菜单
void menu()
{
    cout << "************1.创建图       2.广度遍历************" << endl;
    cout << "************3.深度遍历     4.退出****************" << endl;
}
//主函数
int main()
{
    int choice = 0;
    Graph G;
    InitGraph(G);
    while (1)
    {
        menu();
        printf("请输入菜单序号：\n");
        scanf("%d", &choice);
        if (4 == choice) break;
        switch (choice)
        {
            case 1:CreateGraph(G);break;
            case 2:BFSTraverse(G);break;
            case 3:DFSTraverse(G);break;
            default:printf("输入错误！！！\n");break;
        }
    }
    return 0;
}