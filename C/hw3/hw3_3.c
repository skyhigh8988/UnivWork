/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲 
 * 編譯   : gcc -o hw3_3 hw3_3.c
 * 執行   : ./hw3_3 
 * 功能   : 計算自然對數e (Chapter 4 Exercise 39) 
 * 日期   : 2008/10/27 
 */

#include <stdio.h> 
#include <stdlib.h>

int main(void){

    int n, i;
    double X0, X1, t;
 
    //計算e之值 
    for(X1 = 1, n = 1; X0 != X1; n++){
        
        X0 = X1;
        
        //計算 n! 之值 
        for(i = n, t = 1; i > 0; i--){
            t *= i;
        }
        
        X1 += 1.0 / t;
    
        //印出目前次數及值
        printf("%d\n%.16lf\n\n", n, X1);
    }

    return 0;
}
