/*********************************************
* Server代號: B1
* 學號: F74972281
* 姓名: 曾毓豪
* 編譯方式: gcc -o hw2_1 hw2_1.c
* 執行方式: ./hw2_1
* 程式功能: 左右對齊,一行八十字 
* 更新日期: 2008.10.20
*********************************************/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int i,j,k,a[81], e=0,m,d;
    
    
    FILE *ifp,*ofp;
    char ch[81];
    
    ifp = fopen("input.txt","r");  //讀取檔案 
    ofp = fopen("output.txt","w");//輸出檔案 
    while(e==0){                    
 
  j=0; 
  m=-1;
  
  for(i=0;i<81;++i){//從ifp讀取字元存到ch[i] 
   ch[i] = getc(ifp);
   if(ch[i]==' '){//當讀到"空格"存到a[j] 
    a[j]=i;
    j++;   
   }else if(ch[i]=='\n'){//當讀到"斷行"存到m 
    m=i;
   }else if(ch[i]==EOF){//檢查是否有讀到檔尾 
    e=1;
   }
  }
  
  if(m==-1){//讀到最後一個"空白" 
   k=81-a[j-1];
   d=a[j-1];
   for(i=0;i<a[j-1];++i){
    putc(ch[i],ofp);//輸出字元 
    if(ch[i]==' ' && k>0){//當兩條件成立時,輸出一個"空白" 
     putc(' ' ,ofp);
     k--;
    } 
   }
  }else if(m>=0){
   d=m;
   for(i=0;i<m;++i){//當讀取到斷行,跟著斷行 
    putc(ch[i],ofp);
   }
  }
  putc('\n',ofp);//輸出一個斷行 
  
  if(e==0)fseek(ifp,-(80-d),SEEK_CUR);//回復到未輸出的地方 
 }
 fclose(ofp);   //關掉輸出檔案 
 fclose(ifp);   //關掉讀取檔案 
 return 0;
}
