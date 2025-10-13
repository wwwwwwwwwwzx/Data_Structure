#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXCHARNUM 64

int N, frequence[MAXCHARNUM];
// N:需要编码的字符个数 frequence:字符的频率

char ch[MAXCHARNUM];
// ch储存需要编码的字符

int bestLength;
// 最优编码长度

typedef struct Tree
{
    int weight;
    struct Tree *left, *right;
}Tree;

typedef Tree* Huffman;

typedef struct Heap
{
    int size;
    Huffman *element;
}Heap;

Tree* creatTree()
{
    Tree *T = (Tree*)malloc(sizeof(Tree));
    T->left = T->right = NULL;
    T->weight = -1;

    return T;
}

Heap* creatHeap(int n)
{
    // Heap *H = (Heap*)malloc(sizeof(Heap));
    // H->size = 0;
    // H->data = (int*)malloc(sizeof(int) * (n+1));
    // H->data[0] = MAXDATA;

    // return H;

    Heap *H = (Heap*)malloc(sizeof(Heap));
    H->size = 0;
    H->element = (Huffman*)malloc(sizeof(Huffman) * (n + 1));
    H->element[0] = (Tree*)malloc(sizeof(Tree));
    H->element[0]->left = H->element[0]->right = NULL;
    H->element[0]->weight = -1;

    return H;
}

// 最小堆
// void insert(Heap *H, int value)
void insert(Heap *H, Huffman T)
{
    // if (H->size == 0)
    // {
    //     H->data[++H->size] = value;
    //     return;
    // }

    if (H->size == 0)
    {
        H->element[++H->size] = T;
        return;
    }
    
    H->size++;

    // 上滤
    // int i;
    // for (i = H->size; value < H->data[i/2]; i /= 2)
    // {
    //     H->data[i] = H->data[i/2];
    // }
    // H->data[i] = value;

    int i;
    for (i = H->size; T->weight < H->element[i/2]->weight; i /= 2)
    {
        H->element[i] = H->element[i/2];
    }
    H->element[i] = T;
}

Huffman delete(Heap *H)
{
    // int min = H->data[1];
    // H->data[1] = H->data[H->size--];

    // int tmp = H->data[1];

    // int parent, child;
    // for (int parent = 1; parent*2 <= H->size; parent = child)
    // {
    //     // 找到最小孩子
    //     child = parent * 2;
    //     if (child + 1 <= H->size)
    //     {
    //         child = H->data[child]<H->data[child+1]?child:child+1;
    //     }

    //     // 下滤
    //     if (tmp >= H->data[child])
    //     {
    //         H->data[parent] = H->data[child];
    //     }
    //     else
    //     {
    //         break;
    //     }
        
    // }
    // H->data[parent] = tmp;


    Huffman min = H->element[1];
    Huffman tmp = H->element[H->size--];

    int parent, child;
    for (parent = 1; parent*2 <= H->size; parent = child)
    {
        // 找到最小孩子
        child = parent * 2;
        if (child + 1 <= H->size)
        {
            child = H->element[child]->weight<H->element[child+1]->weight?child:child+1;
        }

        // 下滤
        if (tmp->weight >= H->element[child]->weight)
        {
            H->element[parent] = H->element[child];
        }
        else
        {
            break;
        }
        
    }
    H->element[parent] = tmp;

    return min;

    // 有问题的地方：

    // parent*2 <= H->size
    // ~~~~~~~~~~~~~~~~~~~

    // tmp >= H->data[child
    // ~~~

    // else{break;}
    // ~~~~~~~~~~~~
}



Tree* huffmanTree(int num, int *frequence)
{
    Heap *H = creatHeap(num);
    for (int i = 0; i < num; i++)
    {
        Tree *T = (Tree*)malloc(sizeof(Tree));
        T->weight = frequence[i];
        insert(H, T);
    }

    while (H->size != 1)
    {
        Tree *T = (Tree*)malloc(sizeof(Tree));
        T->left = delete(H);
        T->right = delete(H);
        T->weight = T->left->weight+T->right->weight;

        insert(H, T);
    }
    
    return delete(H);
}

int WPL(Huffman T, int depth)
{
    // 只有叶子节点需要算入WPL
    if (T->left==NULL && T->right==NULL)
    {
        return T->weight * depth;
    }

    return (WPL(T->left, depth+1) + WPL(T->right, depth+1));
}

// judge()一次只判断 *一个人* 的答案
int judge()
{
    int flag = 1;
    char chl, code[MAXCHARNUM];
    int totalLength = 0;

    Tree *T = creatTree();
    Tree *p;

    int i, j, weight;

    for (i = 0; i < N; i++)
    {
        p = T;
        scanf(" %c %s", &chl, code);
        int len = strlen(code);
        if (len > N-1)
        {
            flag = 0;
        }
        else
        {
            for (j = 0; chl != ch[j]; j++);
            weight = frequence[j];
            totalLength += (len * weight);

            for (j = 0; j < len; j++)
            {
                // 每放一个字符(0/1)都要检查一下当前这个有没有权值
                if (code[j] == '0')
                {
                    if (p->left == NULL)
                    {
                        p->left = creatTree();
                    }

                    if (p->left->weight != -1)
                    {
                        flag = 0;
                        break;
                    }
                    
                    p = p->left;
                }
                else if (code[j] == '1')
                {
                    if (p->right == NULL)
                    {
                        p->right = creatTree();
                    }

                    if (p->right->weight != -1)
                    {
                        flag = 0;
                        break;
                    }
                    
                    p = p->right;
                }
            } // 到此为止读完了一个字符的编码
            p->weight = weight;
            if (p->left != NULL || p->right != NULL)
            {
                flag = 0;
            }
            
            
        }
    }
    // 到此为止读完了当前学生的答案
    if (totalLength != bestLength)
    {
        flag = 0;
    }
    
    return flag;
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf(" %c %d", &ch[i], &frequence[i]);
    }

    Huffman Huff = huffmanTree(N, frequence);
    bestLength = WPL(Huff, 0);

    // 接下来可以开始判断学生答案了
    int numOfAnswer;
    scanf("%d", &numOfAnswer);

    for (int i = 0; i < numOfAnswer; i++)
    {
        if (judge())
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
        
    }
    
}