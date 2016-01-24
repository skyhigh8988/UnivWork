/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲 
 * 編譯   : gcc -o hw5 hw5.c -lm 
 * 執行   : ./hw5 method_code array_size (EX: ./hw5 3 16) 
 * 功能   : 陣列排序 
 * 日期   : 2008/12/10 
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void merge(int [], int [], int [], int, int);
void mergesort_1(int [], int);
void mergesort_2(int [], int);
void mergesort_3(int [], int);
void mergesort_4(int [], int);
void wrt(int [], int);

int main(int argc, char *argv[]){
       
    //檢測傳入參數數量是否正確
    if(argc != 3){
        printf("Argument count error!\n");
        exit(1);
    } 
    
    int i, n = 0;
    
    //將傳入參數「array_size」轉為整數 
    for(i = 0; argv[2][i] >= '0' && argv[2][i] <= '9'; i++)
        n = 10 * n + (argv[2][i] - '0');

    //檢測「array_size」是否合理 
    if(n == 0){
        printf("Array size error!\n");
        exit(1);
    }
    
    //檢測「method_code」是否合理 
    if(argv[1][0] < '0' || argv[1][0] > '4' || argv[1][1] != '\0'){ 
        printf("Method code error!\n");
        exit(1);
    }
    
    int sz, key[n];
    
    //亂數產生值為 -99 至 +99 之陣列 
    srand(time(NULL));
    for(i = 0; i < n; i++){
        key[i] = rand() % 199 - 99;
    }
    
    //計算陣列大小 
    sz = sizeof(key) / sizeof(int);
    
    //列印排序前陣列至螢幕 
    printf("Before mergesort:\n");
    wrt(key, sz);
    
    //依據「method_code」決定使用之排序方法並呼叫之 
    switch(*argv[1]){
        case '1':
            mergesort_1(key, sz);
            break;
        case '2':
            mergesort_2(key, sz);
            break;
        case '3':
            mergesort_3(key, sz);
            break;
        case '4':
            mergesort_4(key, sz);
    }
    
    //列印排序後陣列至螢幕 
    printf("After mergesort:\n");
    wrt(key, sz);

    return 0;
}

void merge(int keya[], int keyb[], int keyc[], int sza, int szb){

    int i = 0, j = 0, k = 0;
    
    //比較AB兩陣列個別的最小值，並將較小者放入C陣列 
    while(i < sza && j < szb)
        if(keya[i] < keyb[j]) keyc[k++] = keya[i++];
        else keyc[k++] = keyb[j++];

    //將剩餘之值放入C 
    while(i < sza) keyc[k++] = keya[i++];
    while(j < szb) keyc[k++] = keyb[j++];

    return;
}

void mergesort_1(int key[], int sz){

    int j, k, m, *w;
    
    //檢測陣列大小是否為2的次方 
    for(m = 1; m < sz; m *= 2);
    if(sz < m){
        printf("Array size error!\n");
        exit(1);
    }
    
    //分配W之空間並檢測 
    w = calloc(sz, sizeof(int));
    assert(w != NULL);
    
    //決定要傳入merge之長度，從1開始
    for(k = 1; k < sz; k *= 2){
          
        //決定要傳入merge之起始位址，從0開始 
        for(j = 0; j < sz - k; j += 2 * k)
            merge(key + j, key + j + k, w + j, k, k);
            
        //將W中之值放回Key中 
        for(j = 0; j < sz; j++) key[j] = w[j];
    }
    
    return;
}

void mergesort_2(int key[], int sz){

    int i, j, k , m = 0, *w;
    int q = sz, r[sz], d = 0;
    
    //將原陣列大小拆成皆為2之次方 
    while(q != 0){
        r[d++] = q % 2;
        q = q / 2;
    }

    //分配W之空間並檢測 
    w = calloc(sz, sizeof(int));
    assert(w != NULL);
    
    //決定次方要處理的次方，從0開始 
    for(i = 0; i < d; i++){
          
        //若陣列沒有分割到此大小則不做處理 
        if(r[i] == 1){
            
            //決定要傳入merge之長度，從1開始
            for(k = 1; k < pow(2, i); k *= 2){
                  
                //決定要傳入merge之起始位址，從0開始 
                for(j = 0; j < pow(2, i) - k; j += 2 * k)
                    merge(key + m + j, key + m + j + k, w + m + j, k, k);
                    
                //將W中之值放回Key中
                for(j = m; j < m + pow(2, i); j++) key[j] = w[j];
            }
            
            //將剛處理完之陣列與之前之陣列合併並排序 
            merge(key, key + m, w, m, pow(2, i));
            for(k = 0; k < m + pow(2, i); k++) key[k] = w[k];
            
            //計算已處理完成之長度 
            m += pow(2, i);
        }
    }
    
    return;
}

void mergesort_3(int key[], int sz){
     
    int j, k, *w, d = 0;
    
    //分配W之空間並檢測 
    w = calloc(sz, sizeof(int));
    assert(w != NULL);

    //決定要傳入merge之長度，從1開始
    for(k = 1; k < sz; k *= 2){

        //決定要傳入merge之起始位址，從0開始 
        for(j = 0; j < sz - k; j += 2 * k)
            merge(key + j, key + j + k, w + j, (sz - j >= k ? k : sz - j)
                         , (sz - j - k >= k ? k :sz - j - k));

        //非2之次方時處理程序 
        if(sz % 2 != 0){
            if(d == 0) w[j] = key[j];
            d = 1;
        }

        //將W中之值放回Key中 
        for(j = 0; j < sz; j++) key[j] = w[j];
    }
}

void mergesort_4(int key[], int sz){
    
    int tmp, i, j, k, *w;
   
    //陣列大小為1則不進行處理 
    if(sz == 1) return;
    
    //陣列大小為2則直接排序 
    if(sz == 2){
        if(key[0] > key[1]){
            tmp = key[0];
            key[0] = key[1];
            key[1] = tmp;
        }
        return;
    }
    
    //計算將陣列分成兩部分之個別長度 
    j = sz / 2;
    k = sz - j;
    
    //將分割的兩部分再傳入此Function 
    mergesort_4(key, j);
    mergesort_4(key + j, k);
    
    //分配W之空間並檢測 
    w = calloc(sz, sizeof(int));
    assert(w != NULL);
    
    //合併並排序陣列 
    merge(key, key + j, w, j, k);
    for(i = 0; i < sz; i++) key[i] = w[i];
    
    return;
}

void wrt(int key[], int sz){
    
    int i;
    
    //依序將陣列印至螢幕 
    for(i = 0; i < sz; i++)
        printf("%4d%s", key[i], ((i < sz - 1) ? "" : "\n")); 
        
    return;
} 
