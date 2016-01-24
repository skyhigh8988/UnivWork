/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲
 * 編譯   : gcc -o hw7 hw7.c
 * 執行   : ./hw7 method_code data_type value
            (method_code : 1 pointer / 2 union )
            (data_type   : int(i) / double(d) / float(f) )
            (Example     : ./hw7 1 double 5.64 )
 * 功能   : 印出指定數值之位元圖樣
 * 日期   : 2008/01/06
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void method_1(char, char[]);    //利用「pointer」處理浮點數的方法 
void method_2(char, char[]);    //利用「union」處理浮點數的方法 
void bitprint(int);

//Union 
union fdi{
    float f;
    double d;
    int i[2];
};

int main(int argc, char *argv[]){

    //檢測傳入參數數量是否正確
    if(argc != 4){
        printf("Argument count error!\n");
        exit(1);
    }

    //檢測「method_code」是否合理
    if(argv[1][0] < '1' || argv[1][0] > '2' || argv[1][1] != '\0'){
        printf("Method code error!\n");
        exit(1);
    }

    //檢測「data_type_code」是否合理
    if(argv[2][0] != 'i' && argv[2][0] != 'f' && argv[2][0] != 'd'){
        printf("Data type code error!\n");
        exit(1);
    }

    //依據「method_code」選擇方法並呼叫之 
    switch(argv[1][0]){
        case '1':
            method_1(argv[2][0], argv[3]);
            break;
        case '2':
            method_2(argv[2][0], argv[3]);
    }

    getch();
    putchar('\n');
    return 0;
}


void method_1(char type, char value[]){

    int *i;
    double d;
    float f;

    //依據「data_type_code」分別處理
    switch(type){
        case 'i':
            i = calloc(1, sizeof(int));       //分配記憶體空間
            i[0] = atoi(value);               //將傳入參數轉為整數
            bitprint(i[0]);                   //呼叫「bitprint」印出位元圖樣
            break;
        case 'd':
            d = atof(value);                  //將傳入參數轉為浮點數
            i = (int*)&d;                     //將i指向d所在位址
            bitprint(i[1]);                   //呼叫「bitprint」印出位元圖樣
            bitprint(i[0]);                   //呼叫「bitprint」印出位元圖樣
            break;
        case 'f':
            f = atof(value);                  //將傳入參數轉為浮點數
            i = (int*)&f;                     //將i指向f所在位址
            bitprint(i[0]);                   //呼叫「bitprint」印出位元圖樣
    }

    return;
}


void method_2(char type, char value[]){

    union fdi u;

    //依據「data_type_code」分別處理
    switch(type){
        case 'i':
            u.i[0] = atoi(value);             //將傳入參數轉為整數
            bitprint(u.i[0]);                 //呼叫「bitprint」印出位元圖樣
            break;
        case 'd':
            u.d = atof(value);                //將傳入參數轉為浮點數
            bitprint(u.i[1]);                 //呼叫「bitprint」印出位元圖樣
            bitprint(u.i[0]);                 //呼叫「bitprint」印出位元圖樣
            break;
        case 'f':
            u.f = atof(value);                //將傳入參數轉為浮點數
            bitprint(u.i[0]);                 //呼叫「bitprint」印出位元圖樣
    }

    return;
}


void bitprint(int value){

    int i;
    int n = sizeof(int) * CHAR_BIT;           //計算長度 

    //印出位元圖樣 
    for(i = n - 1; i >= 0; i--){
        printf("%1d", (value >> i) & 0x00000001);
        if(i % CHAR_BIT == 0) putchar(' ');
    }

    return;
}
