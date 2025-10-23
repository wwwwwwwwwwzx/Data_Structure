#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// define
#define INFINITY 2147483647

// typedef
typedef struct Vertex
{
    int x;
    int y;
}Vertex;

// global variables
int num, jumpDistance; // 鳄鱼数 跳跃距离
Vertex O;


// following are functions

float getDistance(Vertex V1, Vertex V2)
{
    return sqrt(pow(V2.y - V1.y, 2) + pow(V2.x - V1.x, 2));
}

int firstJump(Vertex V, int jumpDistance)
{
    return (getDistance(O, V) <= 7.5 + jumpDistance) ? 1 : 0;
}

int isSafe(Vertex V, int jumpDistance)
{
    return (50-V.x <= jumpDistance || V.x+50 <= jumpDistance || 50-V.y <= jumpDistance || V.y+50 <= jumpDistance) ? 1 : 0;
}

void save()
{
    // read and create metrix
    scanf("%d %d", &num, &jumpDistance);

    // 只需要一步
    if (jumpDistance >= 42.5)
    {
        printf("1\n");
        return;
    }

    // G储存所有顶点 包括原点
    Vertex G[num+1];
    G[0].x = G[0].y = 0; // 原点

    for (int i = 1; i < num+1; i++)
    {
        scanf("%d %d", &G[i].x, &G[i].y);
    }

    // 根据顶点创建D^-1
    int D[num+2][num+2]; // 0是原点 1-num是顶点 num+1是边缘

    // 初始化D
    for (int i = 0; i < num+2; i++)
    {
        for (int j = 0; j < num+2; j++)
        {
            D[i][j] = i==j ? 0 : INFINITY;
        }
        
    }
    
    // 把图的信息读入D
    for (int i = 1; i < num+1; i++)
    {
        for (int j = 1; j < num+1; j++)
        {
            if (i != j && getDistance(G[i], G[j]) <= jumpDistance)
            {
                // 说明这两个点联通
                D[i][j] = 1;
                D[j][i] = 1;
            }
            
        }
        
    }

    // 补充D的原点那一行&列
    for (int i = 1; i < num+1; i++)
    {
        if (firstJump(G[i], jumpDistance))
        {
            D[0][i] = 1;
            D[i][0] = 1;
        }
        
    }
    D[0][num+1] = INFINITY;
    D[num+1][0] = INFINITY;

    // 补充D的边缘那一行&列
    for (int i = 0; i < num+1; i++)
    {
        if (isSafe(G[i], jumpDistance))
        {
            D[i][num+1] = 1;
            D[num+1][i] = 1;
        }
        
    }
    
    // path[i][j]保存从i到j的最短路径，走出的第一步经过的顶点的idx
    int path[num+2][num+2];
    for (int i = 0; i < num+2; i++)
    {
        for (int j = 0; j < num+2; j++)
        {
            path[i][j] = (D[i][j] == 1) ? j : -1;
        }
        
    }

    // Floyd
    for (int k = 0; k < num+2; k++)
    {
        for (int i = 0; i < num+2; i++)
        {
            for (int j = 0; j < num+2; j++)
            {
                if (D[i][k] != INFINITY && D[k][j] != INFINITY && D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = path[i][k];
                }
                
            }
            
        }
        
    }

    int minDistance = D[0][num+1];
    if (minDistance == INFINITY)
    {
        printf("0\n");
        return;
    }
    else
    {
        // 用minFirst记录:以这个点为第一个到达的点为起点到边缘
        int minFirst[num];
        int minFirstIdx = 0;

        for (int i = 1; i < num+1; i++)
        {
            if (firstJump(G[i], jumpDistance) && D[i][num+1] == minDistance-1)
            {
                minFirst[minFirstIdx++] = i;
            }
            
        }

        // best保存minFirst中 需要输出的那个的下标
        int best = 0;
        for (int i = 1; i < minFirstIdx; i++)
        {
            if (getDistance(O, G[minFirst[i]]) < getDistance(O, G[minFirst[best]]))
            {
                best = i;
            }
        }
        
        // 输出最短跳跃次数
        printf("%d\n", minDistance);

        // 输出各个顶点
        int curr = minFirst[best];
        while (curr != num+1)
        {
            printf("%d %d\n", G[curr].x, G[curr].y);
            curr = path[curr][num+1];
        }
        
        
    }
    
}

int main()
{
    O.x = O.y = 0;
    save();
}