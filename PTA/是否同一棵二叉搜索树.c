// 二叉排序树 BST

#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *l;
    struct TreeNode *r;
    int tag;
}TreeNode;

#define NOT_FOUND 0
#define SUCCESS 1
#define LOSE 2

int find(TreeNode *T, int value, TreeNode *parent, TreeNode **pos)
{
    if (T == NULL)
    {
        *pos = parent;
        return NOT_FOUND;
    }
    
    if (value < T->data)
    {
        return find(T->l, value, T, pos);
    }
    else if (value > T->data)
    {
        return find(T->r, value, T, pos);
    }
    else
    {
        *pos = T;
        return SUCCESS;
    }
}

int check(TreeNode *T, int value)
{
    if (T == NULL)
    {
        return NOT_FOUND;
    }
    
    if (value < T->data)
    {
        if (T->tag == 0)
        {
            return LOSE;
        }
        
        return check(T->l, value);
    }
    else if (value > T->data)
    {
        if (T->tag == 0)
        {
            return LOSE;
        }
        
        return check(T->r, value);
    }
    else
    {
        T->tag = 1;
        return SUCCESS;
    }
}

int insert(TreeNode **T, int value)
{
    TreeNode *curr = (TreeNode*)malloc(sizeof(TreeNode));
    curr->data = value;
    curr->l = NULL;
    curr->r = NULL;
    curr->tag = 0;

    if (*T == NULL)
    {
        *T = curr;
        return 1;
    }

    TreeNode *pos;
    int s = find(*T, value, NULL, &pos);
    if (s == NOT_FOUND)
    {
        if (value < pos->data)
        {
            pos->l = curr;
        }
        else
        {
            pos->r = curr;
        }
    }
    else
    {
        free(curr);
        return 0;
    }
    
    return 1;
    
}

TreeNode* makeTree(int N)
{
    TreeNode *T = NULL;
    int num;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num);
        insert(&T, num);
    }

    return T;
}

int judge(TreeNode *T, int N)
{
    /*      N
            4 2 读完了
        3 1 4 2 读完了
        3 4 1 2 现在要处理的
        3 2 4 1
    */
    int num;
    int ok = 1;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num);
        if (check(T, num) != SUCCESS)
        {
            ok = 0;
        }
    }

    return ok;

}

void freeTree(TreeNode *T)
{
    // 最小case
    if (T == NULL) return;

    // 递归
    freeTree(T->l);
    freeTree(T->r);

    // 正常逻辑
    free(T);
}

void reset(TreeNode* T)
{
    if (T == NULL) return;

    T->tag = 0;

    reset(T->l);
    reset(T->r);
}

int main(int argc, char const *argv[])
{
    int N, L, i;
    TreeNode *T;

    scanf("%d", &N);
    while (N != 0)
    {
        scanf("%d", &L);

        T = makeTree(N);

        for (i = 0; i < L; i++)
        {
            if (judge(T, N))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
            reset(T);
        }
        freeTree(T);
        scanf("%d", &N);
    }
    
    return 0;
}
