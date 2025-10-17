#include<stdio.h>
#include<stdlib.h>

// define
#define MAXSIZE 100
#define IFINITY 2147483647

// global_variable
int n, m; // 动物总数n 咒语条数m

// graph
typedef struct Graph
{
    int vertexNum;
    int egdeNum;
    // 邻接矩阵的下标的动物下标差1!!
    int metrix[MAXSIZE][MAXSIZE];
}Graph;

Graph* creatGraph(int n, int m)
{
    Graph *G = (Graph*)malloc(sizeof(Graph));
    G->vertexNum = n;
    G->egdeNum = m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            G->metrix[i][j] = IFINITY;
        }
        
    }

    // 读取m条咒语
    int i, j, length; // 两个动物编号 咒语长度
    for (int k = 0; k < m; k++)
    {
        scanf("%d %d %d", &i, &j, &length);
        G->metrix[i-1][j-1] = length;
        G->metrix[j-1][i-1] = length;
    }
    
    return G;
}

void Dijkstra(Graph *G, int start, int *Distance, int *visited)
{
    Distance[start] = 0;

    while (1)
    {
        int minDistance = IFINITY;
        
        // 未访问且Distance最小的V
        int i;
        int V = -1;
        for (i = 0; i < n; i++)
        {
            if (!visited[i] && Distance[i] < minDistance)
            {
                minDistance = Distance[i];
                V = i;
            }
            
        }

        // 如果没有这样的V,结束
        if (V == -1)
        {
            break;
        }

        // 标记了一处地点
        visited[V] = 1;
        

        // V所有邻接点W
        int W;
        for (W = 0; W < n; W++)
        {
            if (G->metrix[V][W] != IFINITY)
            {
                if (Distance[W] > Distance[V] + G->metrix[V][W])
                {
                    Distance[W] = Distance[V] + G->metrix[V][W];
                }
                
            }
            
        }
        
    }
    
}

int main()
{
    scanf("%d %d", &n, &m);
    Graph *G = creatGraph(n, m);

    // Distance保存从起始点到任一点的最短距离
    // visited访问/未访问
    int Distance[n], visited[n];

    // 每个点都要做一次Dijkstra,所有结果存在这个二维矩阵
    int dijkstraResult[n][n];

    // 遍历起始点
    for (int i = 0; i < n; i++)
    {
        // 初始化三个数组,下标与动物编号差1
        for (int j = 0; j < n; j++)
        {
            Distance[j] = IFINITY;
            visited[j] = 0;
        }

        Dijkstra(G, i, Distance, visited);

        // 把结果写入djikstraResult里
        for (int j = 0; j < n; j++)
        {
            dijkstraResult[i][j] = Distance[j];
        }
        
    }

    // 把每行的最大值找出来,存在max数组中
    int max[n];

    for (int i = 0; i < n; i++)
    {
        max[i] = dijkstraResult[i][0];
        for (int j = 0; j < n; j++)
        {
            if (dijkstraResult[i][j] > max[i])
            {
                max[i] = dijkstraResult[i][j];
            }
            
        }
        
    }

    int min = max[0];
    int minIdx;
    for (int i = 0; i < n; i++)
    {
        if (max[i] < min)
        {
            min = max[i];
            minIdx = i;
        }
        
    }
    
    if (min != IFINITY)
    {
        printf("%d %d", minIdx+1, max[minIdx]);
    }
    else
    {
        printf("0");
    }
    
    return 0;
}


// 忘记标记visited[V] = 1

// 判断V不存在的时候可以优化

// minDistance初始化错误 要初始化成IFINITY