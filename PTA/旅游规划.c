#include<stdio.h>
#include<stdlib.h>


// def
#define INFINITY 2147483647


// global
int n, m, s, d; //n城市数 m公路数 s起点 e终点


// function
void travel()
{
    scanf("%d %d %d %d", &n, &m, &s, &d);

    // 图创建-初始化
    int gLength[n][n];
    int gCost  [n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            gLength[i][j] = INFINITY;
            gCost[i][j] = INFINITY;
        }
    }
    

    // 读入
    for (int i = 0; i < m; i++)
    {
        int c1, c2, length, cost;
        scanf("%d %d %d %d", &c1, &c2, &length, &cost);
        gLength[c1][c2] = length;
        gLength[c2][c1] = length;
        gCost  [c1][c2] = cost;
        gCost  [c2][c1] = cost;
    }
    
    // Dijikstra
    int Dist[n];
    int Path[n];
    int visited[n];
    int Cost[n];

    for (int i = 0; i < n; i++)
    {
        Dist[i] = INFINITY;
        Path[i] = -1;
        visited[i] = 0;
        Cost[i] = INFINITY;
    }
    
    Dist[s] = 0;
    Cost[s] = 0;
    
    // main
    while (1)
    {
        // 找未访问过且Dist最小的V
        int i;
        int V = -1;
        int minDist = INFINITY;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && Dist[i] < minDist)
            {
                minDist = Dist[i];
                V = i;
            }
            
        }

        // 如果没找到
        if (V == -1)
        {
            break;
        }
        
        // 收录
        visited[V] = 1;

        // 对V的所有邻接点W
        for (int W = 0; W < n; W++)
        {
            if (gLength[V][W] != INFINITY)
            {
                if (Dist[W] > Dist[V] + gLength[V][W])
                {
                    Dist[W] = Dist[V] + gLength[V][W];
                    Cost[W] = Cost[V] + gCost[V][W];
                    Path[W] = V;
                }

                if (Dist[W] == Dist[V] + gLength[V][W] && Cost[W] > Cost[V] + gCost[V][W])
                {
                    Cost[W] = Cost[V] + gCost[V][W];
                    Path[W] = V;
                }
                
            }
            
        }
        
    }
    
    // 计算路径长度和收费总额
    // int curr = d;
    // int prev = Path[curr];
    // int totalLength = 0, totalCost = Cost;

    // while (prev != -1)
    // {
    //     totalLength += gLength[prev][curr];
    //     curr = prev;
    //     prev = Path[curr];
    // }
    printf("%d %d", Dist[d], Cost[d]);
}

int main()
{
    travel();
}