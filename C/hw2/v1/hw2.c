/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲 
 * 編譯   : gcc -o hw2 hw2.c
 * 執行   : ./hw2 hw2_input.txt hw2_output.txt (./hw2 hw2_input.txt) 
 * 功能   : 左右對齊 
 * 日期   : 2008/10/15 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *ipf, *opf;
    int n, i , j, spc, sp[80], nlc, nl[80], m, r, x, y;
    char c[81];
    
    //檢測傳入參數數量 (2:僅輸出至螢幕; 3:輸出至螢幕及檔案)
    if(argc < 2 || argc > 3){
        printf("Argument count error!\n");
        exit(1);
    }
    
    ipf = fopen(argv[1], "r");
    if(argc == 3) opf = fopen(argv[2], "w");
    
    //檢測檔案是否存在 
    if(ipf == NULL){
        printf("Open file error!\n");
        exit(1);
    }
    
    while((n = fread(c, sizeof(char), 81, ipf)) > 0){
        spc = nlc = 0;    //計數用變數歸零 
        
        //計錄空白字元及換行字元之數量及位置 
        for(i = 0; i < n; i++){
            switch(c[i]){
                case ' ':
                    sp[spc] = i;
                    spc++;
                    break;
                case '\n':
                    nl[nlc] = i;
                    nlc++;
            }
        }
        
        //檔尾程序 
        if(getc(ipf) == EOF){
                     
            //依序列印字元到螢幕直到結束 
            for(i = 0; i < n; i++){
                putchar(c[i]);
                if(argc == 3) putc(c[i], opf);
            }
        
        //段末程序 
        }else if(nlc > 0){
            m = nl[nlc-1] - 82;    //計算檔案之位置修正量  
            
            //依序列印字元到螢幕直到換行 
            for(i = 0; i <= nl[0]; i++){
                putchar(c[i]);
                if(argc == 3) putc(c[i], opf);
            }
        
        //一般程序 
        }else{
        
            m = sp[spc-1] - 82;    //計算檔案之位置修正量         
            r = 80 - sp[spc-1];    //計算多餘的空白字元 
            x = r / spc;           //計算每間隔最低增加寬度 
            y = r % spc;           //計算需額外增加寬度之數量 
        
            //依序列印字元到螢幕直到最後一個空白字元 
            for(i = 0; i < sp[spc-1]; i++){
                putchar(c[i]);
                if(argc == 3) putc(c[i], opf);
                
                //分配多餘的空白字元 
                if(c[i] == ' '){
                    for(j = 0; j < x; j++){
                        putchar(' ');
                        if(argc == 3) putc(' ', opf);
                    }
                    if(y > 0){
                        putchar(' ');
                        if(argc == 3) putc(' ', opf);
                        y--;
                    }
                }
            }
        }
        putchar('\n');
        if(argc == 3) putc('\n', opf);
        
        //修正位置 
        if(getc(ipf) != EOF) fseek(ipf, m, SEEK_CUR);
    }
    
    fclose(ipf);
    if(argc == 3) fclose(opf); 
    return 0;
}
