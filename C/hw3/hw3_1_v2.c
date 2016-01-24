#include <stdlib.h>
#include <stdio.h>

double X0,X1,a,n;
int i;

int main()
{
    X1=1;
    scanf("%lf",&a);
    for(i=1;X1!=X0;i++)
    {
      X0=X1;
      X1=0.5*(X1+a/X1);
      n=a-X1*X1;
      printf("%d %lf %lf\n",i,X1,n);                 
    } 
system("pause");
return 0;       
}
