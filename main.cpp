#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<string>
using namespace std;

void Show(int **a, int R , int C )
{
    int i, j;
    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
            printf("%7d", a[i][j]);
        printf("\n");
    }
}
// ham rut gon mot hang " row "
int ReduceRow(int** a, int C , int row )
{
	int j, sum ;
    int minR = 10000;
	for (j = 0 ; j < C ; j++){
			if (a[row][j] < minR) minR = a[row][j] ; 
		}
	for (j = 0 ; j < C ; j++){
			if (a[row][j] == 10000) continue;
			a[row][j]  = a[row][j] - minR; 
     	}
	    sum += minR;
	    return sum;
}
// ham rut gon mot cot "col"
int ReduceCol(int** a, int R , int col )
{
	int i, sum ;
    int minC= 10000;
	for (i = 0 ; i < R ; i++){
			if (a[i][col] < minC) minC = a[i][col] ; 
		}
	for (i = 0 ;i  < R ; i++){
			if (a[i][col] == 10000) continue;
			a[i][col]  = a[i][col] - minC; 
    }
	    sum += minC;
	    return sum;
}
// Ham rut gon ma tran
int Reduce(int** a, int R, int C ){
	int i,j, sum ;
	//rut gon tung hang
	for (i = 0 ; i < R ; i++ ){
		int minR = 10000;
		for (j = 0 ; j < C ; j++){
			if (a[i][j] < minR) minR = a[i][j] ; 
		}
		for (j = 0 ; j < C ; j++){
			if (a[i][j] == 10000) continue;
			a[i][j]  = a[i][j] - minR; 
		}
	    sum += minR;
	}
	//rut gon tung cot
    for (j = 0 ; j < C ; j++ ){
    	int minC = 1000;
		for (i = 0 ; i < R ; i++){
			if (a[i][j] < minC) minC = a[i][j] ; 
		}
		for (i = 0 ; i < R ; i++){
			if (a[i][j] == 10000) continue;
			a[i][j] -= minC; 
		}
	    sum += minC;
	}
	return sum;
}
int minR(int **a, int R, int C,int i,int j){
	int k,minR = 10000;
	for (k = 0 ; k < C ; k++){
		if (k != j) {
			if (a[i][k] < minR) minR = a[i][k];
		}
	}
	return minR;
}
int minC(int **a, int R, int C, int i, int j){
	int k,minC = 10000;
	for (k = 0 ; k < R ; k++){
		if (k != i) {
			if (a[k][j] < minC) minC = a[k][j];
		}
	}
	return minC;
}
void BestEdge(int** a, int R, int C,int* row , int* col, int *beta){
 int i,j,total;
 *beta = -1 ;
 for (i = 0; i<R; i++){
  for (j = 0; j<C; j++) {
   if (a[i][j] == 0){
     total = minR(a,R,C,i,j) + minC(a,R,C,i,j);
    if (total > *beta) {
     *beta = total;
     *row = i; 
     *col = j; 
    }
   }
  }
 }
}
void DelRow(int **a, int *R,int C, int row)
{
    int i,j;
	for( i=row; i < *R-1;i++){
	  for( j=0;j<C;j++){
 a[i][j]=a[i+1][j];
    }
  }
  *R = *R - 1;    
}
void DelCol(int** a,int R, int *C, int col)
{
 int i,j;
 for( i=0; i<R; i++){
   for( j=col ; j<*C-1; j++)
 {
 a[i][j]=a[i][j+1];
  }
} 
 *C = *C -1 ;
}
void Copy(int **a , int **b, int R , int C){
	int i,j;
	for (i=0 ; i<R; i++){
		for ( j = 0 ; j < C ; j++){
			b[i][j] = a [i][j];
		}
	}
}
/*
LowerBound = Reduce(a, R, C );
void TSP(int **a, int *R, int *C, int *LowerBound ,int *Edges) {
  While (*Edges >= R-2){ 
	if (*Edges == R-2){ // So canh da di duoc = R-2 ;
         if (a[1][1] == 10000) 
          // Ket nap 2 canh cuoi cung(chua lam)
		   <(u, x), (v, w)> 
         else 
            <  (u, w), ( v, x) >;
          MinCost = cost;
        }
    else {
        BestEdge( a, R , C  &row , &col , &beta )
        int** b = NULL ,R ,C ;
		b = (int **)malloc(R * sizeof(int *));
        int i,j;
	    for (i = 0; i < R ; i++)
          {
             b[i] = (int *)malloc(C * sizeof(int));
          }
        Copy(a,b,R,C);
        int** c = NULL ,R-1 ,C-1 ;
		b = (int **)malloc((R-1) * sizeof(int *));
        int i,j;
	    for (i = 0; i < R-1 ; i++)
          {
             b[i] = (int *)malloc((C-1) * sizeof(int));
          }
        // Di theo nhanh trai
		// Ket nap canh row-col (chua lam)
        a[col][row] = 10000 ;
        int** b = NULL ,R ,C ;
        DelRow(a,&R,C,row);
        DelCol(a,R,&C,col);
        // Ngan chan hanh trinh con neu co (chua lam)
		int LeftLB = *LowerBound + Reduce(a,R,C);
		copy(a,c,R,C);
		// xong di theo nhanh trai
		*R = *R +1;
		*C = *C +1;
		Copy(b,a,R,C);
		//Di theo nhanh phai
		a[row][col] = 10000;
        int RightLB = *LowerBound + ReduceRow(a ,C, row) + ReduceCol(a,R,col);
        if (LeftLB < RightLB) 	{
        	*R = *R - 1;
		    *C = *C -1 ;
		    copy(c,aR,C);
		   *LowerBound = LeftLB; 
            TSP(a,&R,&C, &LowerBound , &Edges);
			}
        else {
		   *LowerBound = RightLB; 
            TSP(a, &R, &C, &LowerBound , &Edges);
			}    
        }
    }
  
*/
void Input(int **a, int R , int C,FILE *f)
{
    int i, j;
    for (i = 0; i < R; i++)
        for (j = 0; j < C; j++)
        {
            fscanf(f,"%d",&a[i][j]);
        }
}

int main() {
	int row , col, beta=0 ;
    int** a = NULL ,R ,C ;
	// printf("Enter the number of cities : "); scanf("%d",&R);	
	int Edges = 0, cost=0;
	
	char select[50];
    printf("Enter your select : ");
    gets(select);

	FILE *f = fopen(select,"r");
			fscanf(f,"%d",&R);
	// Cap phat bo nho cho mang 2 chieu a
	a = (int **)malloc(R * sizeof(int *));
    int i,j;
	for (i = 0; i < R ; i++)
    {
        a[i] = (int *)malloc(C * sizeof(int));
    }
    C=R;
	//printf("Enter cost of traveling from city x to city y  \n"); 
     for (i = 0; i < R; i++)
        for (j = 0; j < C; j++)
        {
            fscanf(f,"%d",&a[i][j]);
        }
	printf("The cost matrix of the TSP : \n");
	Show(a,R,C);
    int MinCost = Reduce(a ,R,C);
    printf("\n");
	Show(a,R,C);
    BestEdge(a ,R, C , &row , &col , &beta);
    printf("%d %d %d ", beta, row ,col);
    DelRow(a,&R,C,row);
    DelCol(a,R,&C,col);
    printf("\n");
	Show(a,R,C);
	

}
