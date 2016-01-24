/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲 
 * 編譯   : gcc -o hw3_1 hw3_1.c
 * 執行   : ./hw3_1 
 * 功能   : 計算輸入值a之平方根 (Chapter 4 Exercise 36) 
 * 日期   : 2008/10/27 
 */

#include <stdio.h> 
#include <stdlib.h>

int main(void){

    int a, i, f;
    double X0, X1 = 1;
    
    //要求輸入a值，當a值小於0時要求重新輸入 
    do{

        printf("Enter the number a : ");
        scanf("%d", &a);
    
    }while(a < 0);

    //計算a之平方根 
    for(X1 = 1, i = 1; X0 != X1; i++){
        
        X0 = X1;
        X1 = 0.5 * (X1 + a / X1);
    
        //印出目前次數、值及誤差 
        printf("\ni\t= %d\nX1\t= %.16lf\nd\t= %.16lf\n", i, X1, a - X1 * X1);
    }

    return 0;
}
