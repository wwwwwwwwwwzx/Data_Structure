#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1000

#define IDX(i,j) ((i) * (vertexNum + 1) + (j))
// 首先我确定 要用BFS 因为要求最短距离
// 图的表示方式？邻接矩阵/邻接表？
// 邻接矩阵吧 好写一点

/*
    实现逻辑是？

    // sdos
    
    int success_time = 0;
    for (each person in Graph:按顺序遍历数组就好)
    {
        for (each target_person in Graph:也是按顺序遍历数组,不过不要遍历当前下标)
        {
            time = 0;
            BFS(this_person, target_person, &time);
            if (time < 6)
            {
                success_time++;
            }
        }
        
        printf("百分比形式输出噢!", success_time/总人数);
    }



    // BFS   不是递归!!! DFS才是递归!!!
    sdos = 0;
    break_time = 0;

    eQueue(当前结点X);
    while (!isEmpty(Q) || 还有节点没访问过)
    {
        deQueue(Q, &X);
        for (当前结点X的每一个邻接点Y)
        {
            visited[Y] = 1;
            if (Y != target_person)
            {
                equeue(Y);
            }
            else
            {
                break_time++;
                break;
            }
        }
        if (break_time == 0)
        {
            *time++;
        }
        else
        {
            break;
        }
    }


    30 min
*/

int Q[MAXSIZE];
int front = 0;
int rear = 0;

int isEmpty()
{
    return front==rear?1:0;
}

int eQueue(int e)
{
    if ((rear + 1) % MAXSIZE == front)
    {
        return 0;
    }
    else
    {
        Q[rear] = e;
        rear = (rear + 1) % MAXSIZE;

        return 1;
    }
}

int deQueue(int *d)
{
    if (isEmpty())
    {
        return 0;
    }
    else
    {
        *d = Q[front];
        front = (front + 1) % MAXSIZE;

        return 1;
    }
    
}

int BFS(int *metirx, int this_person, int vertexNum)
{
    front = rear = 0;

    int visited[vertexNum+1];
    int level  [vertexNum+1];
    int cnt = 0;

    for (int i = 0; i < vertexNum+1; i++)
    {
        visited[i] = 0;
        level  [i] = 0;
    }

    eQueue(this_person);
    visited[this_person] = 1;
    cnt++;

    while (!isEmpty())
    {        
        int u;
        deQueue(&u);

        if (level[u] == 6)
        {
            continue;
        }
        

        for (int v = 1; v < vertexNum+1; v++)
        {
            if (metirx[IDX(u,v)] == 1 && !visited[v])
            {
                visited[v] = 1;
                cnt++;
                level[v] = level[u] + 1;
                eQueue(v);
            }            
        }
        

    }
    return cnt;
}

void SDOS()
{

    // 从1开始编号的数组
    // 第i,j个元素是第几个::i(i-1)/2+j

    // read data
    int vertexNum, edgeNum;
    scanf("%d %d", &vertexNum, &edgeNum);

    int metrix[(vertexNum + 1) * (vertexNum + 1)];

    for (int i = 0; i < vertexNum + 1; i++)
    {
        for (int j = 0; j < vertexNum + 1; j++)
        {
            metrix[IDX(i,j)] = 0;
        }
        
    }
    
    // read data
    for (int i = 1; i < edgeNum + 1; i++)
    {
        int p1, p2;
        scanf("%d %d", &p1, &p2);
        metrix[IDX(p1,p2)] = 1;
        metrix[IDX(p2,p1)] = 1;
    }
    

    // sdos
    
    // for (each person in Graph:按顺序遍历数组就好)
    for (int this_person = 1; this_person < vertexNum + 1; this_person++)
    {
        // 对每个人做一次层级BFS
        int reachable = BFS(metrix, this_person, vertexNum);
        printf("%d: %.2f%%\n", this_person, (reachable * 100.0 / vertexNum) );
    }

}

/*
void BFS(int metrix[][MAXSIZE], int this_person, int target_person, int *sdos_time, int vertexNum)
{
    // BFS   不是递归!!! DFS才是递归!!!
    front = rear = 0;
    int break_time = 0;
    int visited[vertexNum + 1]; // 1 -> vtx+1
    for (int i = 0; i < vertexNum + 1; i++)
    {
        visited[i] = 0;
    }
    

    eQueue(this_person);
    // while (!isEmpty(Q) || 还有节点没访问过)
    while (!isEmpty())
    {
        int d;
        deQueue(&d);

        for (int link = 1; link < vertexNum + 1; link++)
        {
            if (metrix[d][link] == 1 && visited[link] != 1)
            {
                visited[link] = 1;
                if (link != target_person)
                {
                    eQueue(link);
                }
                else
                {
                    break_time++;
                    break;
                }
            }
            
        }
        if (break_time == 0)
        {
            (*sdos_time)++;
        }
        else
        {
            break;
        }
    }
}
*/

int main()
{
    SDOS();
}