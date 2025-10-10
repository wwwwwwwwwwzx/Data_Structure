#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int compare(void *a, void *b)
{
    return *(int*)a-*(int*)b;
}

double min(double a, double b)
{
    return a<b?a:b;
}

int getLeftLength(int N)
{
    int H = floor(log2(N));
    int X = N - pow(2, H) + 1;
    X = min(X, pow(2, H - 1));
    return (pow(2, H-1) - 1 + X);
}

void solve(int Aleft, int Aright, int Troot, int *A, int *T)
{
    int n = Aright - Aleft + 1;

    if (n == 0)
    {
        return;
    }

    int L = getLeftLength(n);
    T[Troot] = A[Aleft + L];

    int leftTRoot = Troot * 2 + 1;
    int rightTRoot = leftTRoot + 1;
    solve(Aleft, Aleft+L-1, leftTRoot, A, T);
    solve(Aleft+L+1, Aright, rightTRoot, A, T);
}

int main()
{
    int num;
    scanf("%d", &num);
    int A[num];
    int T[num];

    for (int i = 0; i < num; i++)
    {
        scanf("%d", &A[i]);
    }

    qsort(A, num, sizeof(int), compare);
    
    solve(0, num-1, 0, A, T);

    int cnt = num;
    for (int i = 0; i < num; i++)
    {
        printf("%d", T[i]);
        cnt--;
        if (cnt > 0)
        {
            printf(" ");
        }
        
    }
    
}