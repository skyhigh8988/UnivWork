#include <stdio.h>

typedef struct node{
    int prioirty;
    char name[50];
    struct node *next;
} NODE;

typedef struct queue{
    NODE *head;
    int size;
} QUEUE;

void addQueue(QUEUE *q, char *n, int p){
     
    NODE *current, *newnode, *previous;
    newnode = malloc(sizeof(NODE));

    if(isEmpty(q)){
        q -> head = newnode;
        strcpy(newnode -> name, n);
        newnode -> prioirty = p;
        newnode -> next = NULL;

    }else{
        current = q -> head;
        previous = NULL;

        while(current -> prioirty <= p){
            previous = current;
            current = current -> next;
            if(current == NULL) break;
        }

        if(previous == NULL) q -> head = newnode;
        else previous -> next = newnode;
        strcpy(newnode -> name, n);
        
        newnode -> prioirty = p;
        newnode -> next = current;
    }

    q -> size++;
    return;
}

char* getQueue(QUEUE *q){
      
    if(isEmpty(q)) return "null";
    
    NODE *current;

    current = q -> head;
    q -> head = current -> next;
    q -> size--;
    
    return current -> name;
}

int isEmpty(QUEUE *q){

    if(q -> size == 0) return 1;
    return 0;
}

int main(int argc, char *argv[]){
    
    if (argc != 2){
        printf("Usage: a.out inputfile.\n");
        return 1;
    }
    
    FILE * f = fopen(argv[1], "r");
    if (f == NULL){
        printf("Open file %s error.\n", argv[1]);
        return 1;
    }
    
    QUEUE *q;
    int i, p;
    char c;
    char w[4], n[50];

    q = malloc(sizeof(QUEUE));
    q -> size = 0;
    
    for(i = 0; 1; i++){

        c = fgetc(f);
        if(c != ' ' && c != '\n' && c != EOF){
            w[i] = c;

        }else{
            w[i] = '\0';

            if(strcmp(w, "add") == 0){
                
                for(i = 0; (c = fgetc(f)) != ' '; i++){
                    n[i] = c;
                }
                n[i] = '\0';
                
                for(i = 0; (c = fgetc(f)) != '\n'; i++){
                    w[i] = c;
                }
                w[i] = '\0';
                p = atoi(w);
                addQueue(q, n, p);
                
            }else if(strcmp(w, "get") == 0){
                printf("%s\n", getQueue(q));
            }else{
                printf("File format error.\n");
                return 1;
            }

            if(c == EOF) break;
            i = -1;
        }
    }

    return 0;
}
