#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  int lf,rt,pn,pivot;
  lf=1;
  rt=n-1;
  pn=1;
  pivot=A[0];
// 先頭の要素をピボットとする

 while(rt-lf>=0){
     int z;
     if(A[lf]<pivot){
        z=A[lf];
        A[lf]=A[lf-pn+1];
        A[lf-pn+1]=z;
        lf+=1;
     }else if(A[lf]>pivot){
        z=A[lf];
        A[lf]=A[rt];
        A[rt]=z;
        rt-=1;
     }else if(A[lf]==pivot){
        pn+=1;
        lf+=1;


     }
 }

  if(lf-pn<k+1 && lf>=k+1) return pivot;//pivotを出力
  else if(lf < k+1) return quick_select(A+lf, n-lf, k-lf); // pivotより大きい領域を探索
  else return quick_select(A+1, lf-pn, k);//pivotより小さい部分を探索
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i+1));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
  printf("%d\n",1);
}
