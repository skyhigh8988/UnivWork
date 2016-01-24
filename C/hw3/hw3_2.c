/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲 
 * 編譯   : gcc -o hw3_2 hw3_2.c -lm 
 * 執行   : ./hw3_2 
 * 功能   : 計算自然對數e (Chapter 4 Exercise 38) 
 * 日期   : 2008/10/27 
 */

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

int main(void){

    int n;
    double X0, X1;

    //計算e之值 
    for(X1 = 1, n = 1; X0 != X1; n++){
        
        X0 = X1;
        X1 = pow(1.0 + 1.0 / n, n);
    
        //印出目前次數及值(會造成執行速度大幅降低) 
        //printf("n = %d\ne = %.16lf\n\n", n, X1);
    }
    
    //印出總共之次數及最後之e值
    printf("n\t= %d\ne\t= %.16lf\n\n", n, X1);

    return 0;
}
