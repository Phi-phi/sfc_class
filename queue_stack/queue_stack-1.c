#include <io.h>
#include <stdio.h>

struct queue{
	int data[1024];
	int start;
	int end;
};

struct stack{
	int data[1024];
	int now;
};

void selectmode();

void initialize_q(struct queue *queue){
	queue -> start = 0;
	queue -> end = 0;
	int i = 0;
	for(i = 0; i < 1024; i++){
		queue -> data[i] = 0;
	}
	printf("Initialized.\n");
}

void initialize_s(struct stack *stack){
	stack -> now = 0;
	int i = 0;
	for(i = 0; i < 1024; i++){
		stack -> data[i] = 0;
	}
	printf("Initialized.\n");
}

void stackset(struct stack *stack){
	int data;
	printf("Stack: Please set data.\n");
	scanf("%d", &data);
	stack -> data[stack -> now] = data;
	stack -> now++;
}

void stackout(struct stack *stack){
	int data;
	if(stack -> now == 0) printf("Error, Stack is empty.\n");
	else{
		data = stack -> data[stack -> now - 1];
		printf("%d\n", data);
		stack -> now--;
	}
}

void queueset(struct queue *queue){
	int data;
	printf("Queue: Plese set data.\n");
	scanf("%d",&data);
	queue -> data[queue -> end] = data;
	queue -> end++;
}

void queueout(struct queue *queue){
	int data;
	if(queue -> start == queue -> end)	printf("Error.Queue is empty.\n");
	else{
		data = queue -> data[queue -> start];
		printf("%d\n",data);
		queue -> start++;
	}
}

void Queue_mode(struct queue *q){
	int data;
	while(1){
		printf("1->setdata\n2->initialize \n3->output\n4->back\nWhich?: ");
		scanf("%d",&data);
		if(data == 1){
			queueset(q);
		}else if(data == 2){
			initialize_q(q);
		}else if(data == 3){
			queueout(q);
		}else if(data == 4){
			selectmode();
		}else{
			printf("error.\n");
		}
	}
}

void Stack_mode(struct stack *s){
	int data;
	while(1){
		printf("1->setdata\n2->initialize \n3->output\n4->back\nWhich?: ");
		scanf("%d", &data);
		if(data == 1){
			stackset(s);
		}else if(data == 2){
			initialize_s(s);
		}else if(data == 3){
			stackout(s);
		}else if(data == 4){
			selectmode();
		}else{
			printf("error.\n");
		}
	}
}

void selectmode(){
	int which;
	struct queue q;
	initialize_q(&q);
	struct stack s;
	initialize_s(&s);
	while(1){
		printf("Queue? - 1  Stack? - 2\n");
		scanf("%d",&which); 
		if(which == 1){
			Queue_mode(&q);
		}else if(which == 2){
			Stack_mode(&s);
		}else{
			printf("error.\n");
		}
	}
}

int main(){
	selectmode();
}
