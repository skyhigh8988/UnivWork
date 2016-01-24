/*
 * Server : B2
 * 學號   : F74976120
 * 姓名   : 李睿哲 
 * 編譯   : gcc -o hw4 hw4.c
 * 執行   : ./hw4 hw4_input.txt hw4_output.txt (./hw4 hw4_input.txt) 
 * 功能   : 左右對齊 
 * 日期   : 2008/11/12 
 */

#include <stdio.h>
#include <stdlib.h>

void Argument_Check(int);
void File_Open(char *[]);
int File_Input(void);
void File_Process(int);
void File_Output(void);
void File_Close(void);

int output_to_file;
char line_input[81], line_output[81];
FILE *input_file, *output_file;

int main(int argc, char *argv[]){

    int n = 81;

    Argument_Check(argc);
    File_Open(argv);
    
    while(n == 81){
            
        n = File_Input();
        File_Process(n);
        File_Output();
        
    }
    
    File_Close();
    printf("\n\n");
    return 0;
}

void Argument_Check(int argc){
    
    //檢測傳入參數數量 (2:僅輸出至螢幕; 3:輸出至螢幕及檔案)
    if(argc == 2){
        output_to_file = 0;
    }else if(argc == 3){
        output_to_file = 1;
    }else{
        printf("Argument count error!\n");
        exit(1);
    }

    return;
    
}

void File_Open(char *argv[]){
    
    //開啟檔案   
    input_file = fopen(argv[1], "r");
    if(output_to_file == 1) output_file = fopen(argv[2], "w");
    
    //檢測檔案是否存在 
    if(input_file == NULL){
        printf("Open file error!\n");
        exit(1);
    }

    return;

}

int File_Input(void){
    
    //嘗試從檔案讀取81字元並回傳成功讀取字元數 
    return fread(line_input, sizeof(char), 81, input_file);

}

void File_Process(int n){
     
    int space_count, space, newline_count, newline;
    int i, j, k, seek, space_remain, space_least, space_plus;

    space_count = newline_count = 0;                    //計數用變數歸零 
        
    //計錄空白字元及換行字元之數量及位置 
    for(i = 0; i < n; i++){
        switch(line_input[i]){
            case ' ':
                space = i;
                space_count++;
                break;
            case '\n':
                newline = i;
                newline_count++;
        }
    }

    //檔尾程序 
    if(n < 81){
                     
        //依序列印字元到螢幕直到結束 
        for(i = 0; i < n; i++){
            line_output[i] = line_input[i];
        }
        line_output[i] = '\0';

    //段末程序 
    }else if(newline_count > 0){

        seek = newline - 80;                          //計算檔案之位置修正量  
            
        //依序列印字元到螢幕直到換行 
        for(i = 0; i <= newline; i++){
            line_output[i] = line_input[i];
        }
        line_output[i] = '\0';
        
    //一般程序 
    }else{
        
        seek = space - 80;                            //計算檔案之位置修正量         
        space_remain = 80 - space;                    //計算多餘的空白字元 
        space_least = space_remain / space_count;     //計算每間隔最低增加寬度 
        space_plus = space_remain % space_count;      //計算需額外增加寬度之數量 
        
        //依序列印字元到螢幕直到最後一個空白字元 
        for(i = 0, k = 0; i < space; i++){
            line_output[k++] = line_input[i];
                
            //分配多餘的空白字元 
            if(line_input[i] == ' '){
                for(j = 0; j < space_least; j++){
                    line_output[k++] = ' ';
                }
                if(space_plus > 0){
                    line_output[k++] = ' ';
                    space_plus--;
                }
            }
        }
        line_output[k] = '\n';
    }
        
    //修正位置 
    fseek(input_file, seek, SEEK_CUR);
    
    return;

}

void File_Output(void){

    //將處理完成之行輸出 
    printf("%s", line_output);
    if(output_to_file == 1) fprintf(output_file, "%s", line_output);

    return;
    
}

void File_Close(void){

    //關閉檔案 
    fclose(input_file);
    if(output_to_file == 1) fclose(output_file);
    
    return;

}
