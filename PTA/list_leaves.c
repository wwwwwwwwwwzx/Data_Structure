# include<stdio.h>
# include<stdlib.h>

# define MAXSIZE 10

typedef struct TreeNode{
    int data;
    int l;
    int r;
}TreeNode;

int M = 0;

int read(TreeNode *T){
    int n;

    scanf("%d", &n);
    getchar();

    int check[n];
    for (int i=0; i<n; i++) check[i] = 0;

    for (int i = 0; i<n; i++){
        T[i].data = i;
        char cl, cr;
        scanf("%c %c", &cl, &cr);
        if (cl != '-'){
            T[i].l = cl - '0';
        }else{
            T[i].l = -1;
        }
        if (cr != '-'){
            T[i].r = cr - '0';
        }else{
            T[i].r = -1;
        }
        getchar();
        if (T[i].l==-1 && T[i].r==-1) M++;
    }

    for (int i =0; i<n; i++){
        if (T[i].l!=-1) check[T[i].l] = 1;
        if (T[i].r!=-1) check[T[i].r] = 1;
    }

    int root;
    for (int i = 0; i<n; i++){
        if (check[i]==0){
            root = i;
            break;
        }
    }
    return root;
}

int main(){
    TreeNode T[MAXSIZE];
    int R;
    R = read(T);

    int queue[MAXSIZE], front = 0, rear = 0;
    queue[rear++] = T[R].data;

    while (front!=rear)
    {
        int deQueue = queue[front];
        front++;
        if (T[deQueue].l!=-1){
            queue[rear++] = T[deQueue].l;
        }
        if (T[deQueue].r!=-1){
            queue[rear++] = T[deQueue].r;
        }
        if (T[deQueue].r==-1 && T[deQueue].l==-1){
            printf("%d", T[deQueue].data);
            M--;
            if (M) printf(" ");
        }
    }
}
