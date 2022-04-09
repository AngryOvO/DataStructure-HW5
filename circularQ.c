/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; //ĳ���� �ڷ����� element��� ������
// �迭�� ũ�Ⱑ 4�� ť�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

//�Լ� ������Ÿ�� ���𱸰�
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();
// �����Լ� ����
int main(void)
{
	// ����ü ������ ���� cQ�� ����� ���ÿ� createQueue �Լ��� �ʱ�ȭ 
	QueueType *cQ = createQueue();
	// element ���� data ����
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");
		printf("---------[2018038025] ---------[���Ͽ�]----------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}
// ť�� �����ϴ� �Լ�
QueueType *createQueue()
{
	// ����ü ������ ���� ����
	QueueType *cQ;
	// �����Ҵ� ũ��� ������ ����ü�� ũ�⸸ŭ �Ҵ�
	cQ = (QueueType *)malloc(sizeof(QueueType));
	// front�� rear�� ���� 0���� �ʱ�ȭ ��
	// �̴� ť�� ����״ٴ� �ǹ̿� ����
	cQ->front = 0;
	cQ->rear = 0;
	// ť�� �ּ� ����
	return cQ;
}
// �����Ҵ��� ť�� �Ҵ� �����ϴ� �Լ�
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}
// item ������ ���ڸ� �Է¹޾� �������ִ� �Լ�
element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(QueueType *cQ)
{
	// ť�� front�� rear�� �������
    if(cQ->front == cQ->rear)
    {
		//ť�� ����ִٴ� �޽����� ����ϰ� 1�� ����
        printf("Queue is Empty!!\n");
        return 1;
    }
	// ť�� front�� rear�� �ٸ����
    else
        return 0; //0�� ���� ��, ������� �ʴ�.
}

// ť�� ���� ���ִ��� Ȯ���ϴ� �Լ�
int isFull(QueueType *cQ)
{
	// rear�� ���� �ε����� ť�� ��ü ũ��� ������ ������ ���� �� �� ���� front�� ���ٸ�
    if((cQ->rear+1)%MAX_QUEUE_SIZE == cQ->front)
    {
		//������ ����á�ٶ�� �޽����� ����ϰ� 1�� ����
        printf("Queue is Full!!\n");
        return 1;
    }
	// ���� �ʴٸ� �̴� ť�� ���������� �����Ƿ� 0�� ����
    else
        return 0;
   
}


// ť�� �����͸� �ִ� �Լ�
void enQueue(QueueType *cQ, element item)
{
	//�����͸� �ֱ����� ť�� ���� ���ִ��� Ȯ��
    if(isFull(cQ))
        return; // ���� ���ִٸ� �Լ��� ����
    else // ť�� ������� �ִٸ�
    {
		//rear�� ���� ��ġ�� �̵���Ŵ
		// rear�� �迭�� ���� ���� ��� rear�� ��ġ�� 0���� ����
       cQ->rear = (cQ->rear+1) % MAX_QUEUE_SIZE;
	   // rear�� ��ġ�� item�� ���� �Ҵ�
       cQ->queue[cQ->rear] = item;
    }
}
// ť���� �����͸� ���� �Լ�
void deQueue(QueueType *cQ, element *item)
{
	// ť�� ����ִ����� �˻�
    if(isEmpty(cQ))
        return; //ť�� ��������� �Լ� ����
    else // ť�� �� �� �ִ� �����Ͱ� �����ϴ� ���
    {
		// front�� ���� ��ġ�� �̵���Ŵ
		// front�� �迭�� ���� ���� ��� front�� ��ġ�� 0���� ����
        cQ->front = (cQ->front+1)% MAX_QUEUE_SIZE;
		// front�� ��ġ�� �ִ� �����͸� item���� �ű�
        *item = cQ->queue[cQ->front];
    }
}

// ť ���� �����͸� ����ϴ� �Լ�
void printQ(QueueType *cQ)
{
	int i, first, last;
	// ó���� ���� ����ť���� front�� rear�� �̵��ϴ� ������� �Ҵ�
	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	// first���� last���� �ݺ�
	while(i != last){
		printf("%3c", cQ->queue[i]); // ť ���� ���� ���
		i = (i+1)%MAX_QUEUE_SIZE; //i�� front�� �̵�������� �Ҵ�

	}
	printf(" ]\n");
}

// ť ���� ������ ����ϴ� �Լ� ť�� front�� rear�� ��ġ�� Ȯ�� ����
// ������ �ε����� ��� �����Ͱ� ����ִ��� Ȯ�� ����
void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

