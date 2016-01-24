/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲 
 * 編譯   : gcc -o hw1_2 hw1_2.c
 * 執行   : ./hw1_2 
 * 功能   : 使用 putchar() 將字串列印至螢幕 (Chapter 1 Exercise 25) 
 * 日期   : 2008/10/07 
 */

#include <stdio.h>
#include <string.h>

#define MAXSTRING 100

void prn_string(char *); 

int main(void)
{
    char s1[MAXSTRING], s2[MAXSTRING];
    
    //字串存入字元陣列並呼叫 prn_string() 列印之 
    strcpy(s1, "Mary, Mary, quite contrary, \n");
    strcpy(s2, "how does your garden grow?\n");
    prn_string(s1);
    prn_string(s2);
    
    //合併兩字元陣列並呼叫 prn_string() 列印之 
    strcat(s1, s2);
    prn_string(s1);
    
    return 0;
}

//將傳入之字元陣列列印至螢幕
void prn_string(char *s)
{
    int i;
    
    //將傳入之字元陣列從頭開始列印至螢幕直到字元為'\0'為止 
    for(i = 0; s[i] != '\0'; i++) {
        putchar(s[i]);
    }
    
    return;
}
