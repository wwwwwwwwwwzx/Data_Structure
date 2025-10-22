#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// define
#define INFINITY 2147483647

// global variables
int num, jumpDistance; // 鳄鱼数 跳跃距离

// typedef
typedef struct Vertex
{
    int x;
    int y;
}Vertex;


// following are functions

float getDistance(Vertex V1, Vertex V2)
{
    return sqrt(pow(V2.y - V1.y, 2) + pow(V2.x - V1.x, 2));
}

int firstJump(Vertex V, int jumpDistance)
{
    Vertex O;
    O.x = 0;
    O.y = 0;

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
    for (int i = 1; i < num+2; i++)
    {
        if (firstJump(G[i], jumpDistance))
        {
            D[0][i] = 1;
            D[i][0] = 1;
        }
        
    }

    // 补充D的边缘那一行&列
    for (int i = 0; i < num+1; i++)
    {
        if (isSafe(G[i], jumpDistance))
        {
            D[i][num] = 1;
            D[num][i] = 1;
        }
        
    }
    
    // path[i][j]保存从i到j的最短路径，走出的第一步经过的顶点的idx
    int path[num+1][num+1];
    for (int i = 0; i < num+1; i++)
    {
        for (int j = 0; j < num+1; j++)
        {
            path[i][j] = (D[i][j] == 1) ? j : -1;
        }
        
    }

    // Floyd
    for (int i = 0; i < num+2; i++)
    {
        for (int j = 0; j < num+2; j++)
        {
            for (int k = 0; k < num+2; k++)
            {
                if (D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = path[i][k];
                }
                
            }
            
        }
        
    }

    // 把D[0-(num+1)][num+2]的最小值找出来
    //      如果只有一个->直接输出
    //      如果有多个  ->找第一步最短的输出

    // 先找最短路径minDistance
    // 把等于最最短路径的最后一个元素的idx放进数组minFinal
    // 把数组minFinal里的元素第一个跳到的点找出来 放进数组firstJumpPoint
    // 找数组B里面第一步最小的idx返回出来
}

int main()
{
    save();
}