/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

//함수 프로토타입 선언 구간
void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

//메인함수 시작
int main()
{
	char command;

	do 
	{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");
		printf("---------[2018038025] ---------[정하용]-------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}
// 후위표기 스택 푸시
void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}
//후위표기 스택 팝
char postfixPop()
{
	char x;
	if (postfixStackTop == -1) //스택의 top이 -1인 경우는 스택이 비어있는 경우이므로 팝x
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}
//후위표기식의 계산 스택 푸시
void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}
//후위표기식의 계산 스택 팝
int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}
//각 연산자를 그에 해당하는 우선순위 값으로 변환해주는 함수
precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0') //infixExp의 길이만큼 반복
	{
		/* 필요한 로직 완성 */
		//만약 추출한 문자가 연산자가 아닌 상수일경우
		if (getPriority(*exp) == operand)
		// 그대로 출력할 후위표기 문자열(postfixExp)로 전달
			charCat(exp);
		//추출한 문자가 왼쪽 소괄호인 경우 '('
		else if (getPriority(*exp) == lparen)
			postfixPush(*exp); // 출력하지는 않고 푸시만함

		//추출한 문자가 오른쪽 소괄호인 경우 ')'
		else if (getPriority(*exp) == rparen)
		{
			// 스택의 탑이 왼쪽 소괄호를 만날 때까지
			while (getPriority(postfixStack[postfixStackTop]) != lparen)
			{
				//스택안의 데이터 pop
				x = postfixPop();
				// pop한 데이터를 출력할 후위표기 문자열(postfixExp)로 전달
				charCat(&x);
			}
			// 왼쪽 소괄호는 후위표기 문자열로 넘기지 않고 데이터 pop
			x = postfixPop();
		}
		else // 상수와 괄호가 아닌 다른 연산자들일 경우
		{
			/* 스택 안의 연산자가 스택으로 들어갈 연산자보다 우선순위가 높은 경우
			   스택 안의 연산자의 우선순위가 들어갈 연산자의 우선순위보다 작을때까지 pop */
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
			{
				//pop한 데이터는 출력할 문자열로 전달
				x = postfixPop();
				charCat(&x);
			}
			// 스택 안의 연산자의 우선순위보다 스택으로 들어갈 연산자보다 작으면
			postfixPush(*exp); // 스택 안으로 연산자를 푸시
		}


		exp++; // 다음 infixExp의 원소로
	}
	//위의 과정을 다 마치고 나서도 postfixStack에 데이터가 남아있는 경우에
	// 그 데이터들을 전부 pop하고 postfixExp배열로 전달
	while (postfixStackTop != -1)
	{
		x = postfixPop();
		charCat(&x);
	}

	/* 필요한 로직 완성 */

}
//전체 내용을 출력하는 함수
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset() //리셋 함수
{
	// 문자열 널문자로 초기화
	infixExp[0] = '\0'; 
	postfixExp[0] = '\0'; 

    // 포스트픽스 스택도 초기화
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
	// 포스트픽스 스택과 계산스택의 top도 -1로 초기화 해서 스택을 비워둠
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() // 왼성된 postfixExp 스택을 계산하는 함수
{
	char *exp = postfixExp; //포인터 변수 exp에 postfixExp 주소 할당
	int x1, x2; // 정수형 변수 x1 x2 선언

	while (*exp != '\0') // postfixExp의 길이만큼 반복
	{
		// 만약 exp의 값이 '+'일 경우
		if (*exp == '+')
		{
			// 연산자 앞의 두 상수를 계산 스택에서 추출해서 더함
			x2 = evalPop(); 
			x1 = evalPop();
			// 계산한 결과를 계산 스택으로 푸시
			evalPush(x1 + x2);
		}
		// 만약 exp의 값이 '-'일 경우
		else if (*exp == '-')
		{
			// 연산자 앞의 두 상수 추출
			x2 = evalPop();
			x1 = evalPop();
			// 계산한 결과를 계산 스택으로 푸시
			evalPush(x1 - x2);
		}
		// 만약 exp의 값이 '*'일 경우
		else if (*exp == '*')
		{
			// 연산자 앞의 두 상수 추출
			x2 = evalPop();
			x1 = evalPop();
			// 계산한 결과를 계산 스택으로 푸시
			evalPush(x1 * x2);
		}
		// 만약 exp의 값이 '/'일 경우
		else if (*exp == '/')
		{
			// 연산자 앞의 두 상수 추출
			x2 = evalPop();
			x1 = evalPop();
			// 계산한 결과를 계산 스택으로 푸시
			evalPush(x1 / x2);
		}
		// 만약 추출한 문자가 상수일 경우
		// 아스키코드에서 상수의 값에 '0'의 값을 뺌
		// 이는 문자로 표현한 숫자를 int 형 배열인 evalStack에서 실제 숫자값으로 사용
		else if(getPriority(exp) == operand)
			evalPush(*exp - '0');
		else
			break;
		exp++;// 문자열 다음 원소로
	}
	//위 루프를 모두 수행한뒤 evalStack의 top에 위치한 데이터가 후위 표기식의 총 연산 결과
	evalResult = evalPop(); 
}

