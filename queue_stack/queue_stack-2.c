#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct queue_box{
	int data;
	
	struct queue_box *next;
} queue;

typedef struct stack_box{
	int data;

	struct stack_box *next;
} stack;

void selectmode();

queue *create_q(){
	queue *q = NULL;
	q = (queue*)malloc(sizeof(queue));
	q -> next = NULL;

	return q;
}

stack *create_s(){
	stack *s = NULL;
	s = (stack*)malloc(sizeof(stack));
	s -> next = NULL;

	return s;
}

void initialize_q(queue *q){
	queue *del;
	while(q != NULL){
		del = q;
		q = q -> next;
		free(del);
	}
	printf("\nInitialized.\n\n");
}

void initialize_s(stack *s){
	stack *del;
	while(s != NULL){
		del = s;
		s = s -> next;
		free(del);
	}
	printf("\nInitialized.\n");
}

int stackset(stack *s){
	int input;
	int ret = 0;
	stack *new = (stack*)malloc(sizeof(stack));
	if(new != NULL){
		printf("\nStack: Please set data.\n\n");
		printf(">");
		scanf("%d",&input);
		new -> data = input;
		new -> next = s -> next;
		s -> next = new;
		int before = 0;
		if(s -> next -> next != NULL) before = s -> next -> next -> data;
		int data = s -> next -> data;
		printf("\nInput data is %d\nPrevious:%d\n",data,before);

		ret = 1;
	}
	return ret;
}

void stackout(stack *s){
	int data;
	stack *del;
	if(s -> next == NULL){
		printf("\nError.\nStack is empty.\n\n");
	}else{
		del = s -> next;
		data = del -> data;
		printf("\nOutput-> %d\n\n", data);
		s -> next = s -> next -> next;
		free(del);
	}
}

int queueset(queue *q){
	int ret = 0;
	int input;
	queue *new = (queue*)malloc(sizeof(queue));
	if(new != NULL){
		printf("\nQueue: Plese set data.\n");
		printf(">");
		scanf("%d",&input);
		new -> data = input;
		new -> next = q -> next;
		q -> next = new;
		int before = 0;
		if(q -> next -> next != NULL) before = q -> next -> next -> data;
		int data = q -> next -> data;
		printf("\nInput data is %d\nPrevious:%d\n",data,before);

		ret = 1;
	}
	return ret;
}

void queueout(queue *q){
	int data;
	queue *del;
	if(q -> next == NULL) printf("\nError.\nQueue is empty.\n\n");
	else{
			while(q -> next -> next != NULL){
				q = q -> next;
				printf("%d\n",q -> data);
			}
			del = q -> next;
			data = del -> data;
			printf("\nOutput -> %d\n\n", data);
			q -> next = q -> next -> next;
			free(del);
	}
}

void Queue_mode(queue *q){
	int queue_which;
	while(1){
		printf("\n1->setdata\n2->initialize \n3->output\n4->back\nWhich?: ");
		scanf("%d",&queue_which);
		switch(queue_which){
			case 1:
				if(queueset(q)){
					printf("\nAdded.\n\n");
				}else{
					perror("\nError.\n\n");
				}
				break;

			case 2:
				initialize_q(q);
				q = create_q();
				break;

			case 3:
				queueout(q);
				break;

			case 4:
				initialize_q(q);
				selectmode();
				break;

			default:
				printf("error.\n");
				break;
		}
	}
}

void Stack_mode(stack *s){
	int stack_which;
	while(1){
		printf("\n1->setdata\n2->initialize \n3->output\n4->back\nWhich?: ");
		scanf("%d", &stack_which);
		switch(stack_which){
			case 1:
				if(stackset(s)){
					printf("\nAdded.\n\n");
				}else{
					perror("\nError.\n\n");
				}
				break;

			case 2:
				initialize_s(s);
				s = create_s();
				break;

			case 3:
				stackout(s);
				break;

			case 4:
				initialize_s(s);
				selectmode();
				break;

			default:
				printf("error.\n");
				break;
		}
	}
}

void selectmode(){
	int which;
	queue *q = create_q();
	stack *s = create_s();

	while(1){
		printf("\nQueue? - 1  Stack? - 2\n");
		printf(">");
		scanf("%d",&which); 
		if(which == 1){
			Queue_mode(q);
		}else if(which == 2){
			Stack_mode(s);
		}else{
			printf("error.\n");
		}
	}
}

int main(){
	selectmode();
	return 0;
}
