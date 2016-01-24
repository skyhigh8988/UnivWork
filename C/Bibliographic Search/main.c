#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYWORD 128

struct goto_list
{
	char input;
	struct state_list *target;
	struct goto_list *next;
};

struct output_list
{
	char* keyword;
	struct output_list *next;
};

struct state_list
{
	struct goto_list *ghead;
	struct state_list *fstate;
	struct output_list *ohead;
	struct state_list *next;
};

typedef struct goto_list GLIST;
typedef struct output_list OLIST;
typedef struct state_list STATE;

STATE *shead;

void match(const char*);
STATE* gfunc(STATE*, char);
void ofunc(STATE*, int);
void gcons(char**, int);
void fcons(void);

void test (void)
{
	STATE *stemp;
	stemp = shead;
	int x = 0;
	
	while (stemp != NULL)
    {
          printf("%d\t%d\t%d\n", x++, stemp, stemp->fstate);
          stemp = stemp->next;
    }
}

int main()
{
	char **key;
	key = (char**)malloc(4 * sizeof(char*));
	int i;
	for(i = 0; i < 4; i++) key[i] = (char*)malloc(MAX_KEYWORD * sizeof(char));
	
	strcpy(key[0], "he");
	strcpy(key[1], "she");
	strcpy(key[2], "his");
	strcpy(key[3], "hers");
	
	gcons(key, 4);
	fcons();
	match("hershe");
	
	return 0;
}

void match(const char *x)
{
	STATE *state;
	state = shead;
	int i, n = strlen(x);

	for (i = 0; i < n; i++)
	{
		while (gfunc(state, x[i]) == NULL)
		{
			state = state->fstate;
			if (state == shead) break;
		}
		state = gfunc(state, x[i]);
		if (state == NULL) state = shead;
		
		ofunc(state, i + 1);
	}
}

STATE* gfunc(STATE *state, char input)
{
       
	if (state->ghead == NULL) return NULL;
	GLIST *temp = state->ghead;
	
	while (1)
	{
		if (temp->input == input) return temp->target;
		else if (temp->next != NULL) temp = temp->next;
		else return NULL;
	}
}

void ofunc(STATE *state, int i)
{
	if (state->ohead == NULL) return;
	OLIST *temp;
	temp = state->ohead;
	
	printf("%d\t", i);
	while (1)
	{
		printf("%s\t", temp->keyword);
		if (temp->next != NULL) temp = temp->next;
		else
		{
			printf("\n");
			return;
		}
	}
}

void gcons(char **k, int n)
{
	STATE *snew, *slast;
	GLIST *gnew;
	OLIST *onew;
	shead = (STATE*)malloc(sizeof(STATE));
	shead->ghead = NULL;
	shead->ohead = NULL;
	shead->next = NULL;
	shead->fstate = shead;
	slast = shead;
	
	
	int i, j;
	
	
	for (i = 0; i < n; i++)
	{
        
		STATE *state;
		state = shead;
			
		for (j = 0; gfunc(state, k[i][j]) != NULL; j++) state = gfunc(state, k[i][j]);
		
		int m = strlen(k[i]);
		
		
		for (; j < m; j++)
		{
			snew = (STATE*)malloc(sizeof(STATE));
			snew->ghead = NULL;
			snew->ohead = NULL;
			snew->next = NULL;
			snew->fstate = NULL;
			slast->next = snew;
			slast = snew;
			
			gnew = (GLIST*)malloc(sizeof(GLIST));
			gnew->input = k[i][j];
			gnew->target = snew;
			gnew->next = NULL;
						
			if (state->ghead == NULL) state->ghead = gnew;
			else
			{
				GLIST *temp;
				temp = state->ghead;
				while (temp->next != NULL) temp = temp->next;
				temp->next = gnew;
			}
			state = snew;
			
		}
		
		
		onew = (OLIST*)malloc(sizeof(OLIST));
		
		onew->keyword = (char*)malloc(MAX_KEYWORD * sizeof(char));
		strcpy(onew->keyword, k[i]);
		
		onew->next = NULL;
		state->ohead = onew;
		
	}
}

void fcons(void)
{
	typedef struct queue
	{
		STATE *state;
		struct queue *next;
	} QUEUE;
	
	QUEUE *front, *rear, *qnew;
	front = NULL;
	rear = NULL;
	
	GLIST *temp;
	temp = shead->ghead;
	while (1)
	{
		qnew = (QUEUE*)malloc(sizeof(QUEUE));
		qnew->state = temp->target;
		qnew->next = NULL;
		if (rear == NULL) front = qnew;
		else rear->next = qnew;
		rear = qnew;
		temp->target->fstate = shead;
		
		if (temp->next != NULL) temp = temp->next;
		else break;
	}
	
	
	
	while (front != NULL)
	{
		STATE *state, *pop;
		pop = front->state;
		
		QUEUE *qtmp;
		if (front == rear) rear = NULL;
		qtmp = front;
		front = front->next;
		free(qtmp);
		
		if (pop->ghead != NULL)
		{
			temp = pop->ghead;
			while (1)
			{
				qnew = (QUEUE*)malloc(sizeof(QUEUE));
				qnew->state = temp->target;
				qnew->next = NULL;
				if (rear == NULL) front = qnew;
				else rear->next = qnew;
				rear = qnew;
				
				state = pop->fstate;
				while (gfunc(state, temp->input) == NULL)
				{
					state = state->fstate;
					if (state == shead) break;
				}
				temp->target->fstate = gfunc(state, temp->input);
				if (temp->target->fstate == NULL) temp->target->fstate = shead;
				
				if (temp->target->fstate->ohead != NULL)
					if (temp->target->ohead == NULL) temp->target->ohead = temp->target->fstate->ohead;
					else temp->target->ohead->next = temp->target->fstate->ohead;
				
				if (temp->next != NULL) temp = temp->next;
				else break;
				
				
			}
		}
		
		
	}
	
	
}
