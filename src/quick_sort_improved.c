#include <stdio.h>

//フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
    int lf,rt,pn,pivot;
    if(n<=1) return;
    lf=0;
    rt=n-1;
    pn=0;
    pivot=A[0];

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

        quick_sort(A,lf-pn);
        quick_sort(A+lf,n-lf);

}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }
}
