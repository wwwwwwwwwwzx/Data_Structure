#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10000

typedef struct TreeNode
{
    int data;
    int parent;
}TreeNode;

// 查找某个元素所在的集合
int find(TreeNode *T, int value)
{
    int i;
    int root;
    for (i = 0; i < MAXSIZE; i++)
    {
        if (T[i].data == value)
        {
            root = i;
            break;
        }
        
    }

    // 没找到
    if (i >= MAXSIZE)
    {
        return -1;
    }
    
    // 找到根
    while (T[root].parent >= 0)
    {
        root = T[root].parent;
    }


    // 路径压缩
    int curr = i;
    while (T[curr].parent >= 0)
    {
        int next = T[curr].parent;  // 记录下一个
        T[curr].parent = root;      // 压缩
        curr = next;                // 向前移动
    }
    
    
    return root;
}

int Union(TreeNode *T, int value1, int value2)
{
    int parent1, parent2;
    parent1 = find(T, value1);
    parent2 = find(T, value2);

    if (parent1 == -1 || parent2 == -1)
    {
        return 0;
    }
    if (parent1 == parent2)
    {
        return 0;
    }

    int size1, size2;
    size1 = -T[parent1].parent;
    size2 = -T[parent2].parent;

    if (size1 < size2)
    {
        T[parent1].parent = parent2;
        T[parent2].parent = -(size1 + size2);
    }
    else
    {
        T[parent2].parent = parent1;
        T[parent1].parent = -(size1 + size2);
    }
    
    return 1;
}

void isConnected(TreeNode *T, int value1, int value2)
{
    if (find(T, value1)==find(T, value2))
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
    int num;
    scanf("%d", &num);
    getchar();

    int components = num;

    TreeNode *T = (TreeNode*)malloc(sizeof(TreeNode) * MAXSIZE);

    for (int i = 0; i < num; i++)
    {
        T[i].data = i+1;
        T[i].parent = -1;
    }

    
    char op;
    int c1, c2;

    while (scanf(" %c", &op) == 1)
    {
        if (op == 'S')
        {
            break;
        }
        else if (op == 'I' || op == 'C')
        {
            scanf("%d %d", &c1, &c2);
            if (op == 'I')
            {
                int s = Union(T, c1, c2);
                if (s == 1)
                {
                    components--;
                }
                
            }
            if (op == 'C')
            {
                isConnected(T, c1, c2);
            }
        }

        
        
        
    }



 /*
    char str[7];
    fgets(str, 7, stdin);
    while (str[0] != 'S')
    {
        switch (str[0])
        {
            case 'C':
                isConnected(T, str[2] - '0', str[4] - '0');
                break;
            case 'I':
                Union(T, str[2] - '0', str[4] - '0');
                components--;
                break;
            default:
                break;
        }
        fgets(str, 7, stdin);
    }
*/




    if (components != 1)
    {
        printf("There are %d components.\n", components);
    }
    else
    {
        printf("The network is connected.\n");
    }
    
    

}

int main()
{
    solve();
}