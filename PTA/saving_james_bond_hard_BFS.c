#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// define (不需要INFINITY了)

// typedef
typedef struct Vertex
{
    int x;
    int y;
    int index; // 增加一个字段来记录原始索引，方便排序
}Vertex;

// global variables
int num, jumpDistance; // 鳄鱼数 跳跃距离
Vertex O;
Vertex G[101]; // 把G也设为全局，方便qsort的比较函数访问

// 函数声明
float getDistance(Vertex V1, Vertex V2);
int firstJump(Vertex V, int jumpDistance);
int isSafe(Vertex V, int jumpDistance);
int compareFirstJumps(const void* a, const void* b);
void solve_with_bfs();

int main()
{
    O.x = O.y = 0;
    solve_with_bfs();
    return 0;
}

// 你的辅助函数，无需改动
float getDistance(Vertex V1, Vertex V2)
{
    return sqrt(pow((double)V2.y - V1.y, 2) + pow((double)V2.x - V1.x, 2));
}

int firstJump(Vertex V, int jumpDistance)
{
    // 岛屿半径7.5
    return (getDistance(O, V) <= 7.5 + jumpDistance);
}

int isSafe(Vertex V, int jumpDistance)
{
    return (abs(V.x) + jumpDistance >= 50 || abs(V.y) + jumpDistance >= 50);
}

// qsort需要的比较函数，用于给第一跳的鳄鱼排序
int compareFirstJumps(const void* a, const void* b)
{
    Vertex* v1 = (Vertex*)a;
    Vertex* v2 = (Vertex*)b;
    float dist1 = getDistance(O, *v1);
    float dist2 = getDistance(O, *v2);
    if (dist1 < dist2) return -1;
    if (dist1 > dist2) return 1;
    return 0;
}


void solve_with_bfs()
{
    scanf("%d %d", &num, &jumpDistance);

    // 特殊情况：一步就能上岸
    if (jumpDistance >= 42.5)
    {
        printf("1\n");
        return;
    }

    for (int i = 1; i <= num; i++)
    {
        scanf("%d %d", &G[i].x, &G[i].y);
        G[i].index = i; // 记录原始索引
    }

    // --- BFS 数据结构 ---
    int queue[101]; // 队列，存储鳄鱼的索引
    int head = 0, tail = 0;

    int visited[101] = {0}; // 访问标记数组
    int path[101] = {0};    // path[i] 记录跳到i之前的那个鳄鱼的索引
    int dist[101] = {0};    // dist[i] 记录从岛屿到i的跳跃次数

    // --- 步骤1: 处理第一跳，并排序 ---
    Vertex first_jump_crocs[100];
    int first_jump_count = 0;
    for (int i = 1; i <= num; i++)
    {
        if (firstJump(G[i], jumpDistance))
        {
            first_jump_crocs[first_jump_count++] = G[i];
        }
    }
    
    // 按距离排序
    qsort(first_jump_crocs, first_jump_count, sizeof(Vertex), compareFirstJumps);

    // 将排好序的第一跳鳄鱼入队
    for (int i = 0; i < first_jump_count; i++)
    {
        int croc_index = first_jump_crocs[i].index;
        if (!visited[croc_index])
        {
            visited[croc_index] = 1;
            dist[croc_index] = 1;
            path[croc_index] = 0; // 0代表从岛屿跳过来的
            queue[tail++] = croc_index;
        }
    }

    // --- 步骤2: BFS 主循环 ---
    int final_croc_index = -1; // 记录最后跳上岸的那只鳄鱼

    while(head < tail)
    {
        int curr_index = queue[head++]; // 出队

        // 检查是否能从当前鳄鱼上岸
        if (isSafe(G[curr_index], jumpDistance))
        {
            final_croc_index = curr_index;
            break; // 找到了！由于是BFS且第一跳已排序，这一定是满足条件的最短路径
        }

        // 遍历所有其他鳄鱼，寻找下一步
        for (int next_index = 1; next_index <= num; next_index++)
        {
            if (!visited[next_index] && getDistance(G[curr_index], G[next_index]) <= jumpDistance)
            {
                visited[next_index] = 1;
                dist[next_index] = dist[curr_index] + 1;
                path[next_index] = curr_index;
                queue[tail++] = next_index; // 新鳄鱼入队
            }
        }
    }

    // --- 步骤3: 输出结果 ---
    if (final_croc_index == -1)
    {
        printf("0\n"); // 无法上岸
    }
    else
    {
        // 输出跳跃次数
        printf("%d\n", dist[final_croc_index] + 1);

        // 回溯路径并存储
        int path_to_print[101];
        int count = 0;
        int curr = final_croc_index;
        while(curr != 0)
        {
            path_to_print[count++] = curr;
            curr = path[curr];
        }

        // 反向输出路径
        for (int i = count - 1; i >= 0; i--)
        {
            int index = path_to_print[i];
            printf("%d %d\n", G[index].x, G[index].y);
        }
    }
}