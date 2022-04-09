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

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

//�Լ� ������Ÿ�� ���� ����
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

//�����Լ� ����
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
		printf("---------[2018038025] ---------[���Ͽ�]-------------------------\n");

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
// ����ǥ�� ���� Ǫ��
void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}
//����ǥ�� ���� ��
char postfixPop()
{
	char x;
	if (postfixStackTop == -1) //������ top�� -1�� ���� ������ ����ִ� ����̹Ƿ� ��x
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}
//����ǥ����� ��� ���� Ǫ��
void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}
//����ǥ����� ��� ���� ��
int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}
//�� �����ڸ� �׿� �ش��ϴ� �켱���� ������ ��ȯ���ִ� �Լ�
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
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while (*exp != '\0') //infixExp�� ���̸�ŭ �ݺ�
	{
		/* �ʿ��� ���� �ϼ� */
		//���� ������ ���ڰ� �����ڰ� �ƴ� ����ϰ��
		if (getPriority(*exp) == operand)
		// �״�� ����� ����ǥ�� ���ڿ�(postfixExp)�� ����
			charCat(exp);
		//������ ���ڰ� ���� �Ұ�ȣ�� ��� '('
		else if (getPriority(*exp) == lparen)
			postfixPush(*exp); // ��������� �ʰ� Ǫ�ø���

		//������ ���ڰ� ������ �Ұ�ȣ�� ��� ')'
		else if (getPriority(*exp) == rparen)
		{
			// ������ ž�� ���� �Ұ�ȣ�� ���� ������
			while (getPriority(postfixStack[postfixStackTop]) != lparen)
			{
				//���þ��� ������ pop
				x = postfixPop();
				// pop�� �����͸� ����� ����ǥ�� ���ڿ�(postfixExp)�� ����
				charCat(&x);
			}
			// ���� �Ұ�ȣ�� ����ǥ�� ���ڿ��� �ѱ��� �ʰ� ������ pop
			x = postfixPop();
		}
		else // ����� ��ȣ�� �ƴ� �ٸ� �����ڵ��� ���
		{
			/* ���� ���� �����ڰ� �������� �� �����ں��� �켱������ ���� ���
			   ���� ���� �������� �켱������ �� �������� �켱�������� ���������� pop */
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
			{
				//pop�� �����ʹ� ����� ���ڿ��� ����
				x = postfixPop();
				charCat(&x);
			}
			// ���� ���� �������� �켱�������� �������� �� �����ں��� ������
			postfixPush(*exp); // ���� ������ �����ڸ� Ǫ��
		}


		exp++; // ���� infixExp�� ���ҷ�
	}
	//���� ������ �� ��ġ�� ������ postfixStack�� �����Ͱ� �����ִ� ��쿡
	// �� �����͵��� ���� pop�ϰ� postfixExp�迭�� ����
	while (postfixStackTop != -1)
	{
		x = postfixPop();
		charCat(&x);
	}

	/* �ʿ��� ���� �ϼ� */

}
//��ü ������ ����ϴ� �Լ�
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

void reset() //���� �Լ�
{
	// ���ڿ� �ι��ڷ� �ʱ�ȭ
	infixExp[0] = '\0'; 
	postfixExp[0] = '\0'; 

    // ����Ʈ�Ƚ� ���õ� �ʱ�ȭ
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
	// ����Ʈ�Ƚ� ���ð� ��꽺���� top�� -1�� �ʱ�ȭ �ؼ� ������ �����
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() // �޼��� postfixExp ������ ����ϴ� �Լ�
{
	char *exp = postfixExp; //������ ���� exp�� postfixExp �ּ� �Ҵ�
	int x1, x2; // ������ ���� x1 x2 ����

	while (*exp != '\0') // postfixExp�� ���̸�ŭ �ݺ�
	{
		// ���� exp�� ���� '+'�� ���
		if (*exp == '+')
		{
			// ������ ���� �� ����� ��� ���ÿ��� �����ؼ� ����
			x2 = evalPop(); 
			x1 = evalPop();
			// ����� ����� ��� �������� Ǫ��
			evalPush(x1 + x2);
		}
		// ���� exp�� ���� '-'�� ���
		else if (*exp == '-')
		{
			// ������ ���� �� ��� ����
			x2 = evalPop();
			x1 = evalPop();
			// ����� ����� ��� �������� Ǫ��
			evalPush(x1 - x2);
		}
		// ���� exp�� ���� '*'�� ���
		else if (*exp == '*')
		{
			// ������ ���� �� ��� ����
			x2 = evalPop();
			x1 = evalPop();
			// ����� ����� ��� �������� Ǫ��
			evalPush(x1 * x2);
		}
		// ���� exp�� ���� '/'�� ���
		else if (*exp == '/')
		{
			// ������ ���� �� ��� ����
			x2 = evalPop();
			x1 = evalPop();
			// ����� ����� ��� �������� Ǫ��
			evalPush(x1 / x2);
		}
		// ���� ������ ���ڰ� ����� ���
		// �ƽ�Ű�ڵ忡�� ����� ���� '0'�� ���� ��
		// �̴� ���ڷ� ǥ���� ���ڸ� int �� �迭�� evalStack���� ���� ���ڰ����� ���
		else if(getPriority(exp) == operand)
			evalPush(*exp - '0');
		else
			break;
		exp++;// ���ڿ� ���� ���ҷ�
	}
	//�� ������ ��� �����ѵ� evalStack�� top�� ��ġ�� �����Ͱ� ���� ǥ����� �� ���� ���
	evalResult = evalPop(); 
}

