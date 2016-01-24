#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<time.h>
int main()
{
 int n,m,i,j,**a,**b,d,total;
       
/*      if(argc!=4)
        {
                printf("%s%s%s", "Usage: ", argv[0], "which way do you want to show, row, column");
                exit(1);
        }*/
       
//      option=atoi(argv[1]);
   n=3;
   m=7;
 
        srand(time(NULL));

        a=calloc(m, sizeof(int));
        for(j=0; j<m; j++)
         a[j]=calloc(n, sizeof(int));
        printf("Array_a:\n");
        for(i=0; i<m; i++)
        {
                for(j=0; j<n; j++)
                {
                        do 
                        a[i][j]=rand();
			            while(a[i][j]>=100);
			            printf("%5d", a[i][j]);
		}

                printf("\n\n");
        }

        printf("\n\n");
        //system("pause");

        b=calloc(n, sizeof(int));
        for(j=0; j<n; j++)
         b[j]=calloc(m, sizeof(int));
        printf("Array_b:\n");
        for(i=0; i<n; i++)
        {
                for(j=0; j<m; j++)
                {
                        do
	                    b[i][j]=rand();
	                    while(b[i][j]>=100);
	                    printf("%5d", b[i][j]);

                }
                printf("\n\n");
        }
        printf("\n\n");

//      switch(option)
//      {
//            case 1 :
//                  matrix_multiplication(m, n, a[m][n], b[n][m]);
//      }
system("pause");


        return 0;
}
 
