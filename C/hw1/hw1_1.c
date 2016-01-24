/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲 
 * 編譯   : gcc -o hw1_1 hw1_1.c
 * 執行   : ./hw1_1 (./hw1_1 < data)
 * 功能   : 計算平均值 (Chapter 1 Exercise 15) 
 * 日期   : 2008/10/07 
 */
 
/*
 * 程式執行原理:
 *  
 * avg_ori=原平均 ; avg_new=新平均
 * sum_ori=原總和 ; sum_new=新總和
 * 
 * avg_new = avg_ori + (x - avg_ori) / i
 *         = (avg_ori * i + (x - avg_ori)) / i
 *         = (avg_ori * (i - 1) + x) / i
 *         = (sum_ori + x) / i
 *         = sum_new / i
 *
 * avg = avg + (x - avg) / i = sum / i = navg 
 * 
 */ 

#include <stdio.h>

int main(void)
{
    int i;
    double x,avg = 0.0, navg, sum = 0.0;
    
    //列印表頭至螢幕 
    printf("%5s%17s%17s%17s\n%5s%17s%17s%17s\n\n", "Count", "Item", "Average", 
        "Naive avg", "-----", "----", "-------", "---------");
    
    //將輸入值計算總和及平均並列印至螢幕直到輸入值不是數字 
    for (i = 1; scanf("%lf", &x) == 1; i++) {
        avg += (x - avg) / i;
        sum += x;
        navg = sum / i;
        printf("%5d%17e%17e%17e\n", i, x, avg, navg);
    }
    
    return 0;
}
