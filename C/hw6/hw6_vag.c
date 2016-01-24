#include <stdio.h>
#include <stdlib.h>
//#include <iostream.h>
#include <time.h>

int i,j,m,n,p,q,r;

void method_1(int A[][], int B[][], int ,int );

int main()
{
 
  printf("請輸入列:");
  scanf("%d",&n);
  printf("請輸入行:");
  scanf("%d",&m);
 
 int A[n][m],B[m][n],C[n][n];
 
 
  srand(time(NULL));
  for(i=0;i<n;i++)
  {
     for(j=0;j<m;j++)
     {
        A[i][j]=rand()%10;
        B[j][i]=rand()%10;
     }               
  }
 
for(p=0;p<n;p++)
  {
     for(q=0;q<n;q++)
     {
        C[p][q]=0;
        for(r=0;r<n;r++)
        {
           C[p][q] += A[p][r] * B[r][q];                 
        }
     }
  }
 
 
method_1(A,B,n,m);

system("pause");
}



void method_1(int A[n][m], int B[m][n], int n,int m)
{
 int C[n][n];
 
  for(i=0;i<n;i++)
  {
     for(j=0;j<m;j++)
     {
        printf("%3d",A[i][j]);
     }               
     printf("\n");
  }
  printf("\n");
  for(i=0;i<m;i++)
  {
     for(j=0;j<n;j++)
     {
        printf("%3d",B[i][j]);
     }               
     printf("\n");
  }     
   
  printf("\n");
  for(i=0;i<n;i++)
  {
     for(j=0;j<n;j++)
     {
        printf("%4d",C[i][j]);
     }               
     printf("\n");
  }
}
