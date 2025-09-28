#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1000
#define MAXDATA -10001

typedef struct Heap
{
    int *data;
    int size;
    int capacity;
}Heap;

Heap* initHeap()
{
    Heap *H = (Heap*)malloc(sizeof(Heap));
    H->data = (int*)malloc(sizeof(int) * MAXSIZE);
    H->data[0] = MAXDATA;
    H->size = 0;
    H->capacity = MAXSIZE;

    return H;
}

int insert(Heap *H, int value)
{
    if (H->size == H->capacity || H == NULL)
    {
        return 0;
    }

    int i;
    for (i = H->size + 1; value < H->data[i/2]; i /= 2)
    {
        H->data[i] = H->data[i/2];
    }
    H->data[i] = value;
    H->size++;
    
    return 1;
}

void read(Heap *H, int *time)
{
    int n;
    scanf("%d %d", &n, time);

    for (int i = 1; i <= n; i++)
    {
        int ist;
        scanf("%d", &ist);
        insert(H, ist);
    }

}

void print_heap(Heap *H, int time)
{
    for (int cnt = 0; cnt < time; cnt++)
    {
        int i;
        scanf("%d", &i);

        for ( ; i > 0; i /= 2)
        {
            printf("%d", H->data[i]);
            if (i != 1)
            {
                printf(" ");
            }
            
        }

        printf("\n");
    }
    
}

int main()
{
    // 初始化堆
    Heap *H = initHeap();

    // 创建最小堆，记录打印个数
    int time;
    read(H, &time);

    // 打印路径
    print_heap(H, time);


}