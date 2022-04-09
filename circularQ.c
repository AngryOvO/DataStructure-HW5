/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; //캐릭터 자료형을 element라고 정의함
// 배열의 크기가 4인 큐를 생성
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

//함수 프로토타입 선언구간
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();
// 메인함수 시작
int main(void)
{
	// 구조체 포인터 변수 cQ를 선언과 동시에 createQueue 함수로 초기화 
	QueueType *cQ = createQueue();
	// element 변수 data 선언
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");
		printf("---------[2018038025] ---------[정하용]----------------\n");

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
// 큐를 생성하는 함수
QueueType *createQueue()
{
	// 구조체 포인터 변수 선언
	QueueType *cQ;
	// 동적할당 크기는 선언한 구조체의 크기만큼 할당
	cQ = (QueueType *)malloc(sizeof(QueueType));
	// front와 rear의 값을 0으로 초기화 함
	// 이는 큐를 비워뒀다는 의미와 같음
	cQ->front = 0;
	cQ->rear = 0;
	// 큐의 주소 리턴
	return cQ;
}
// 동적할당한 큐를 할당 해제하는 함수
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}
// item 변수에 문자를 입력받아 리턴해주는 함수
element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


// 큐가 비어있는지 확인하는 함수
int isEmpty(QueueType *cQ)
{
	// 큐의 front와 rear가 같을경우
    if(cQ->front == cQ->rear)
    {
		//큐가 비어있다는 메시지를 출력하고 1을 리턴
        printf("Queue is Empty!!\n");
        return 1;
    }
	// 큐의 front와 rear가 다를경우
    else
        return 0; //0을 리턴 즉, 비어있지 않다.
}

// 큐가 가득 차있는지 확인하는 함수
int isFull(QueueType *cQ)
{
	// rear의 다음 인덱스를 큐의 전체 크기로 나머지 연산을 했을 때 이 값이 front와 같다면
    if((cQ->rear+1)%MAX_QUEUE_SIZE == cQ->front)
    {
		//스택이 가득찼다라는 메시지를 출력하고 1을 리턴
        printf("Queue is Full!!\n");
        return 1;
    }
	// 같지 않다면 이는 큐가 가득차있지 않으므로 0을 리턴
    else
        return 0;
   
}


// 큐에 데이터를 넣는 함수
void enQueue(QueueType *cQ, element item)
{
	//데이터를 넣기전에 큐가 가득 차있는지 확인
    if(isFull(cQ))
        return; // 가득 차있다면 함수를 끝냄
    else // 큐에 빈공간이 있다면
    {
		//rear를 다음 위치로 이동시킴
		// rear가 배열의 끝에 있을 경우 rear의 위치를 0으로 보냄
       cQ->rear = (cQ->rear+1) % MAX_QUEUE_SIZE;
	   // rear의 위치에 item의 값을 할당
       cQ->queue[cQ->rear] = item;
    }
}
// 큐에서 데이터를 빼는 함수
void deQueue(QueueType *cQ, element *item)
{
	// 큐가 비어있는지를 검사
    if(isEmpty(cQ))
        return; //큐가 비어있으면 함수 종료
    else // 큐에 뺄 수 있는 데이터가 존재하는 경우
    {
		// front를 다음 위치로 이동시킴
		// front가 배열의 끝에 있을 경우 front의 위치를 0으로 보냄
        cQ->front = (cQ->front+1)% MAX_QUEUE_SIZE;
		// front의 위치에 있는 데이터를 item으로 옮김
        *item = cQ->queue[cQ->front];
    }
}

// 큐 안의 데이터를 출력하는 함수
void printQ(QueueType *cQ)
{
	int i, first, last;
	// 처음과 끝을 원형큐에서 front와 rear가 이동하는 방식으로 할당
	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	// first부터 last까지 반복
	while(i != last){
		printf("%3c", cQ->queue[i]); // 큐 안의 값을 출력
		i = (i+1)%MAX_QUEUE_SIZE; //i는 front의 이동방식으로 할당

	}
	printf(" ]\n");
}

// 큐 안의 정보를 출력하는 함수 큐의 front와 rear의 위치를 확인 가능
// 각각의 인덱스에 어떠한 데이터가 들어있는지 확인 가능
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

