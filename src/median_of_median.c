#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];


//配列のk＋１番目の値を返す関数
int median(int a[],int n,int k){
    int i,j,tmp;

    for(i=0;i<n-1;i++){
        for(j=0;j<n-1;j++){
            if(a[j+1]<a[j]){
                tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
    }
    return a[k];
}




/*
 A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
 ただし、Aの中身は書き換えてしまう。
 */
int quick_select(int A[], int n, int k){
    int i, pivot;
    int B[(N+4)/5];

    if(n<=5){
        return median(A,n,k);  //配列が５以下なら計算して中央値を出力
    }

    for(i=0;i<n/5;i++){
        B[i]=median(A+i*5,5,2);
    }

    if(n%5!=0){
        B[i]=median(A+i*5,n%5,(n%5)/2);
    }

    pivot=quick_select(B,(n+4)/5,((n+4)/5)/2);


    int lf,rt,pn;
    lf=0;
    rt=n-1;
    pn=0;

    while(rt-lf>=0){
        int z;
        if(A[lf]<pivot){
            z=A[lf];
            A[lf]=A[lf-pn];
            A[lf-pn]=z;
            lf+=1;
        }else if(A[lf]>pivot){
            z=A[lf];
            A[lf]=A[rt];
            A[rt]=z;
            rt-=1;
        }else{

            pn+=1;
            lf+=1;
        }
    }
    if(lf-pn>=k+1) return quick_select(A, lf-pn, k);  //pivotより小さい部分を探索
    else if(lf < k+1){ return quick_select(A+lf, n-lf, k-lf);}  // pivotより大きい領域を探索
    else {return pivot;}  //pivotを出力
}

int main(){
    int i;
    A[0] = 0;
    A[1] = 3; //原始元
    for(i=2;i<N;i++){
        A[i] = (long long int) A[i-1] * A[1] % N;
    }
    for(i=0;i<N;i++){
        if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
        //    printf("%d th element is %d\n", i, quick_select(A, N, i));
    }
}
