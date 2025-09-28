#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *l;
    struct TreeNode *r;
}TreeNode;

int pre[] = {1, 2, 3, 4, 5, 6, };
int in[] = {3, 2, 4, 1, 6, 5, };

TreeNode* creatTree(int preL, int inL, int n)
{
    if (n==0) return NULL;
    if (n==1)
    {
        TreeNode *T;
        T = (TreeNode*)malloc(sizeof(TreeNode));
        T->data = in[inL];
        T->l = NULL;
        T->r = NULL;

        return T;
    }

    TreeNode *T = (TreeNode*)malloc(sizeof(TreeNode));
    int root = pre[preL];
    T->data = root;

    int i;
    for (i = 0; i < n; i++)
    {
        if (in[inL + i] == root)
        {
            break;
        }
        
    }
    int L = i;
    int R = n - L - 1;
    T->l = creatTree(preL+1, inL, L);
    T->r = creatTree(preL+L+1, inL+L+1, R);

    return T;
}

void postOrder(TreeNode *T)
{
    if (T == NULL) return;
    postOrder(T->l);
    postOrder(T->r);
    printf("%d", T->data);
    return;
}

int main()
{
    TreeNode *T;
    T = creatTree(0, 0, 6);

    postOrder(T);
}