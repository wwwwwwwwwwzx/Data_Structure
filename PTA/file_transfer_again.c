#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10000

typedef struct UnionFindSet
{
    int data;
    int parent;
}UFS;

int find(UFS *U, int value)
{
    int i;
    for (i = 0; i < MAXSIZE && U[i].data != value; i++);

    // 没找到
    if (i == MAXSIZE)
    {
        return -(MAXSIZE + 1);
    }
    
    // 找到了 -> 找根
    int root = i;
    while (U[root].parent > 0)
    {
        root = U[root].parent;
    }
    

    // 路径压缩
    int parent = U[i].parent;
    while (parent > 0)
    {
        U[i].parent = root;
        i = parent;
        parent = U[i].parent;
    }
    
    return root;
}

int Union(UFS *U, int value1, int value2)
{
    int parent1 = find(U, value1);
    int parent2 = find(U, value2);

    if (parent1 ==  -(MAXSIZE + 1) || parent2 == -(MAXSIZE + 1))
    {
        return 0;
    }

    if (parent1 == parent2)
    {
        return 2;
    }
    
    
    int size1 = -U[parent1].parent;
    int size2 = -U[parent2].parent;

    if (size1 < size2)
    {
        U[parent1].parent = parent2;
        U[parent2].parent = -(size1 + size2);
    }
    else
    {
        U[parent2].parent = parent1;
        U[parent1].parent = -(size1 + size2);
    }
    
    return 1;
}

void check(UFS *U, int c1, int c2)
{
    int root1 = find(U, c1);
    int root2 = find(U, c2);
    if (root1 == root2)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
}

void solve()
{
    //read
    int num;
    scanf("%d\n", &num);
    int components = num;

    // init
    UFS U[num+1];
    for (int i = 1; i <= num; i++)
    {
        U[i].data = i;
        U[i].parent = -1;
    }

    char status;
    scanf("%c", &status);
    while (status != 'S')
    {
        int c1, c2;
        scanf(" %d %d\n", &c1, &c2);
        switch (status)
        {
        case 'C':
            check(U, c1, c2);
            break;
        case 'I':
            if(Union(U, c1, c2) == 1)
            {
                components--;
            }
            break;
        default:
            break;
        }

        scanf("%c ", &status);
    }
    if (components == 1)
    {
        printf("The network is connected.\n");
    }
    else
    {
        printf("There are %d components.\n", components);
    }
    
    
}

int main()
{
    solve();
    
}