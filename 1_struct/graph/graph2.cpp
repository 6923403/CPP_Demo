#include <iostream>
#include <queue>

const int Max = 100;
const int g_num = 100;

struct Graph
{
    char Vertex[g_num];
    int Edge[g_num][g_num];
    int v_num;
    int e_num;
};

void Init(Graph& graph)
{
    memset(graph.Vertex, '#', g_num);
    memset(graph.Edge, 0, sizeof(graph.Edge));
    graph.e_num = 0;
    graph.v_num = 0;
}

void InsertV(Graph& graph, char a)
{
    if(graph.v_num > Max) {
        std::cout << "Max " << std::endl;
        exit(0);
    }
    graph.Vertex[graph.v_num++] = a;
}

void InsertE(Graph& graph, char b, char c)
{
    int p1, p2;
    p1 = p2 = -1;

    int i = 0;
    for(i = 0; i < graph.v_num; i++)
    {
        if(graph.Vertex[i] == b)
        {
            p1 = i;
        }

        if(graph.Vertex[i] == c)
        {
            p2 = i;
        }
    }

    if(p1 != -1 && p2 != -1)
    {
        graph.Edge[p1][p2] = 1;
        graph.Edge[p2][p1] = 1;
        graph.e_num++;
    }
}

void Create(Graph& graph)
{
    int vn, an;//顶点数，边数
    vn = 10; //顶点
    an = 9; //边数目

    char a[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    char b[] = {'A', 'A', 'B', 'C', 'D', 'I', 'G', 'F', 'G'};
    char c[] = {'B', 'C', 'E', 'D', 'E', 'J', 'F', 'H', 'H'};

    int i = 0;
    for(i = 0; i < vn; i++)
    {
        InsertV(graph, a[i]);
    }
    for(i = 0; i < an; i++)
    {
        InsertE(graph, b[i], c[i]);
    }
}

void Show(Graph& graph)
{
    int i = 0;
    std::cout << " ";
    for(i = 0; i < graph.v_num; i++)
    {
        std::cout << " " << graph.Vertex[i];
    }
    std::cout << std::endl;

    for(i = 0; i < graph.v_num; i++)
    {
        std::cout << graph.Vertex[i] << " ";
        for(int j = 0; j < graph.v_num; j++)
        {
            std::cout << graph.Edge[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void test()
{
    Graph graph;
    Init(graph);
    Create(graph);
    Show(graph);
    //DFS(graph);
    //BFS(graph);
}

int main(int argc, char** argv)
{
    test();
    return 0;
}
