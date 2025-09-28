#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10

typedef struct stack
{
	int data;
	struct stack *next;
}Stack;

Stack* initStack()
{
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->data = 0;
	s->next = NULL;
	return s;
}

int push(Stack *s, int e)
{
	Stack *p = (Stack*)malloc(sizeof(Stack));
	p->data = e;
	p->next = s->next;
	s->next = p;
	return 1;
}

int pop(Stack *s, int *e)
{
	if(s->next == NULL)
	{
		printf("绌虹殑\n");
		return 0;
	}
	*e = s->next->data;
	Stack *q = s->next;
	s->next = q->next;
	free(q);
	return 1;
}



// 根据前序中序解决后续遍历的函数
void solve(int preL, int inL, int postL, int n, int *pre, int *in, int *post)
{   
    if (n == 0) return;
    if (n == 1)
    {
        post[postL] = pre[preL];
        return;
    }

    // 每次前序的第一个节点都是根节点
    int root = pre[preL];
    // 把根节点放到每次的后序遍历的末端
    // 在程序中不会改变preL inL postL的值，只会改变传入函数的参数的值，所以要这样计算末端的值
    post[postL + n - 1] = root;

    // 做一个循环 找到本次根节点位于中序遍历的位置，这样可以求出左子树的长度和右子树的长度
    int i;
    for (i = 0; i < n; i++)
    {
        if (in[inL + i] == root)
        {
            break;
        }
    }
    // 求左子树右子树长度L&R
    int L = i;
    int R = n - L - 1;

    // 递归地解决左子树和右子树
    solve(preL + 1, inL, postL, L, pre, in, post);
    solve(preL + L + 1, inL + L + 1, postL + L, R, pre, in, post);
}

int main()
{
    Stack *S = initStack();

    int n;
    scanf("%d\n", &n);

    char s[2*n][MAXSIZE];
    for (int i = 0; i < 2*n; i++)
    {
        fgets(s[i], MAXSIZE, stdin);
    }

    int preI = 0, inI = 0;
    int pre[n], in[n], post[n];
    for (int i = 0; i<2*n; i++)
    {
        if (s[i][1] == 'u')
        {
            if (s[i][6] == '\n')
            {
                pre[preI++] = s[i][5] - '0';
                push(S, s[i][5] - '0');
            }
            else
            {
                pre[preI++] = (s[i][5] - '0') * 10 + (s[i][6] - '0');
                push(S, (s[i][5] - '0') * 10 + (s[i][6] - '0'));
            }
        }
        else
        {
            int popValue;
            pop(S, &popValue);
            in[inI++] = popValue;
        }
    }

    solve(0, 0, 0, n, pre, in, post);
    int M = n;
    for (int i = 0; i < n; i++)
    {
        printf("%d", post[i]);
        M--;
        if (M) printf(" ");
    }
    
}