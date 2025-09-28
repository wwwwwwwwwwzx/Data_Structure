#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define YES 1
#define NO 0

typedef struct Vertex
{
    int x;
    int y;
}Vertex;

typedef Vertex *Graph;

float getDistance(Vertex V1, Vertex V2)
{
    return sqrt(pow(V2.y - V1.y, 2) + pow(V2.x - V1.x, 2));
}

int isSafe(Vertex V, int jumpDistance)
{
    if ( 50-V.x <= jumpDistance || V.x+50 <= jumpDistance || 50-V.y <= jumpDistance || V.y+50 <= jumpDistance  )
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
    
}

int firstJump(Vertex V, int jumpDistance)
{
    Vertex O;
    O.x = 0;
    O.y = 0;

    if (getDistance(O, V) <= 7.5 + jumpDistance)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int jump(Vertex V, Vertex W, int jumpDistance)
{
    if (getDistance(V, W) <= jumpDistance)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
    
}


int DFS(Graph G, int i, int *visited, int jumpDistance, int num)
{
    int answer = NO;
    Vertex V = G[i];

    visited[i] = 1;
    if (isSafe(V, jumpDistance))
    {
        answer = YES;
    }
    else
    {
        // for (each W in G)
        for (int j = 0; j < num; j++)
        {
            Vertex W = G[j];
            if (!visited[j] && jump(V, W, jumpDistance))
            {
                answer = DFS(G, j, visited, jumpDistance, num);
                if (answer == YES)
                {
                    break;
                }
                
            }
            
        }
    }
    return answer;
}

void save007()
{
    int num, jumpDistance;
    scanf("%d %d", &num, &jumpDistance);
    
    int visited[num];
    for (int i = 0; i < num; i++)visited[i] = 0;

    Vertex V[num];
    for (int i = 0; i < num; i++)
    {
        scanf("%d %d", &V[i].x, &V[i].y);
    }

    Graph G = V;
    int answer;
    // for (each V in G)
    for (int i = 0; i < num; i++)
    {
        if (!visited[i] && firstJump(G[i], jumpDistance))
        {
            answer = DFS(G, i, visited, jumpDistance, num);
            if (answer == YES)
            {
                break;
            }
            
        }
    }

    if (answer == YES)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}

int main()
{
    save007();
}