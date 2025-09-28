#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

typedef struct TreeNode{
    char data;
    char l;
    char r;
}TreeNode;

typedef TreeNode* BiTree;

int creatTree(TreeNode *T){
    int n;
    scanf("%d\n", &n);
    
    for (int i = 0; i < n; i++){
        scanf("%c %c %c\n",&T[i].data, &T[i].l, &T[i].r);
    }

    int check[n];
    for (int i = 0; i<n; i++) check[i] = 0;
    for (int i = 0; i < n; i++){
        if (T[i].l != '-'){
            T[i].l -= '0';
            check[(int)T[i].l] = 1;
        }else{
            T[i].l = -1;
        }
        if (T[i].r != '-'){
            T[i].r -= '0';
            check[(int)T[i].r] = 1;
        }else{
            T[i].r = -1;
        }
    }

    int root = -1;
    for (int i = 0; i < n; i++){
        if (check[i] == 0){
            root = i;
        }
    }
    
    return root;
}

int isSame(int R1, int R2, TreeNode* T1, TreeNode* T2){
    if (R1==-1 && R2==-1) return 1;
    if ((R1==-1 && R2!=-1) || (R1!=-1 && R2==-1) ) return 0;
    if (T1[R1].data != T2[R2].data) return 0;
    if (isSame(T1[R1].l, T2[R2].l, T1, T2) && isSame(T1[R1].r, T2[R2].r, T1, T2)) return 1;
    if (isSame(T1[R1].l, T2[R2].r, T1, T2) && isSame(T1[R1].r, T2[R2].l, T1, T2)) return 1;

    return 0;
}

int main(){
    // 创建两个树
    TreeNode T1[MAXSIZE],T2[MAXSIZE];

    int R1, R2;
    R1 = creatTree(T1);
    R2 = creatTree(T2);
    
    // 判断同构
    if (isSame(R1, R2, T1, T2)){
        printf("Yes");
    }else{
        printf("No");
    }
}
