#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

typedef struct
{
    int data;
    int next;
}n;



// 函数会把头结点储存到hair, 并反转head往后的k个链表
void reverse(Node *head, int k, Node **newHead)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next;

    int cnt = 0;
    while (cnt < k)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;

        cnt++;
    }
    *newHead = prev;
}

Node* reverseKGroup(Node* head, int k)
{
    // 分成不同的组
    //     如果组内个数是k -> 反转
    //     不是 -> 不用管
    // 反转时需要保存hair 当下一组反转完之后 要把上一组的hair指向这一组的head
    

    Node *ret;
    

    int t = 0;
    Node* hair = NULL;
    Node* newHead = NULL;
    Node *nextHead = head;
    while (head != NULL)
    {
        // 先看够不够k个
        int i;
        Node *p = head;
        for (i = 0; i < k && p != NULL; i++, p = p->next);
        if (i == k)
        {
            // 如果够->执行对应逻辑

            // 1. 先保存下一组的第一个
            
            for (i = 0; i < k; i++)
            {
                if(nextHead) nextHead = nextHead->next;
            }

            // 2. 先更新newHead
            reverse(head, k, &newHead);
            
            // 3. 把hair和newHead接上
            if (hair && newHead && t!= 0)
            {
                hair->next = newHead;
            }

            // 4. 再更新hair
            hair = head;
            
            if (t == 0)
            {
                ret = newHead;
            }
        }
        else
        {
            // 不够
            if (hair) hair->next = head;
            break;
        }
    
        // head往后移动k个
        head = nextHead;
        t++;
    }

    return ret;
}

void read(Node **head)
{
    n node[100000];
    int head_address, num, k;
    scanf("%d %d %d", &head_address, &num, &k);
    for (int i = 0; i < num; i++)
    {
        int address, data, next;
        scanf("%d %d %d", &address, &data, &next);
        node[address].data = data;
        node[address].next = next;
    }

    // 构建链表
    int curr_adress = head_address;
    for (int i = 0; i < num; i++)
    {
        Node *p = (Node*)malloc(sizeof(Node));
        p->data = node[curr_adress].data;
    }
    
    
}

int main()
{
    Node *head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    read(head);
}