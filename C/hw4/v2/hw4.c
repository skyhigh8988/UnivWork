#include<stdio.h>
#include<stdlib.h>
 
void File_Open(void);
void File_Input(void);
//void File_Process(void);
void File_Output(void);
void File_Close(void);
 
int n = 81, i, j;
int output_to_file, space, space_count, newline, newline_count;
int seek, space_remain, space_least, space_plus;
char line_input[5000], line_output[81];
FILE *input_file, *output_file;

int  i,j,k,w[81],x=0,y,z,c;
char ll[81];
FILE *ifp, *ofp;
 
int main(int argc, char *argv[])
{

    File_Open();
    while(/*n > 80*/x==0){
     File_Input();
     File_Output();
  }
  File_Close();
  system("pause");
  return(0);
    }
 
 
 
  void File_Open(void)
  {
  ifp= fopen("input.txt","r");   
  ofp= fopen("output.txt","w");   
 
          if (ifp==NULL)
          {
          printf("error");
          system("Pause");
          exit(1);
          }
  }
 
 
  void File_Input(void)
  {

                     //c++;
                     //printf("%d\n",c);
          j=0;
          y=-1;
          for(i=0;i<81;++i)
                  {
                  ll[i] = getc(ifp);

          
           if(ll[i]==' ')
                     {
                      w[j]=i;
                      j++;
                     }
 
            else if(ll[i]=='\n')
                     {
                      y=i;
                     }
 
            else if(ll[i]==EOF)
                     {
                     x=1;
                     }
                  }
  }
 
 
  void File_Output(void)
  {
          if(y==-1)
          {
          k=80-w[j-1];
          z=w[j-1];
          for(i=0;i<w[j-1];++i)
                  {
                  putc(ll[i],ofp);
                  if(ll[i]==' ' && k>0)
                          {
                          putc(' ' ,ofp);
                          k--;
                          }
                   }
          }
 
          else if(y>=0)
          {
          z=y;
          for(i=0;i<y;++i)
                  {
                   putc(ll[i],ofp);
                  }
          }
 
  putc('\n',ofp);
  if(x==0) fseek(ifp,-(80-z),SEEK_CUR);
 
  }
 
 
 
  void File_Close(void)
  {
  fclose(ifp);
  fclose(ofp);
  }
 
