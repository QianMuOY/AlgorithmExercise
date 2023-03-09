/*
  encoding: utf-8
  by: qiαnmu
 */
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

#include<iostream>
#include<string>

#define maxsize 1000
using namespace std;

/*
  目录：
  应用题2.
  应用题3.
  算法设计题2.
  
 */

// 栈的定义
// 如果您已经熟练掌握，请忽略以下一大堆定义。

// 定义一个最大容量为100的数组
const int MAX = 100;

// 定义一个类Stack，包含一个数组和一个指针
class Stack {
	int arr[MAX];
	int top;
	
public:
	// 构造函数，初始化指针为-1
	Stack() {
		top = -1;
	}
	
	// push操作，如果栈不满，就把元素放到数组中，并更新指针
	void push(int x) {
		if (top < MAX - 1) {
			top++;
			arr[top] = x;
		}
		else {
			_tprintf(_T("Stack overflow in push \r\n"));
		}
	}
	
	// pop操作，如果栈不空，就返回并删除数组中的最后一个元素，并更新指针
	int pop() {
		if (top >= 0) {
			int x = arr[top];
			top--;
			return x;
		}
		else {
			_tprintf(_T("Stack underflow in pop \r\n"));
			return -1;
		}
	}
	
	// peek操作，如果栈不空，就返回数组中的最后一个元素，不改变指针
	int peek() {
		if (top >= 0) {
			return arr[top];
		}
		else {
			_tprintf(_T("Stack is empty \r\n"));
			return -1;
		}
	}
	
	// 定义一个函数，判断栈是否为空
	bool isEmpty() {
		return top == -1;
	}
	
};
// ----------------------------------------------------------------------------
/*
  将中缀表达式转化为后缀表达式的步骤如下：
  
	  从左到右扫描中缀表达式。
	  如果遇到操作数，直接输出到后缀表达式。
	  如果遇到左括号，压入栈中。
	  如果遇到右括号，弹出栈中的运算符并输出到后缀表达式，直到遇到左括号为止，并丢弃左括号。
	  如果遇到运算符，比较它与栈顶运算符的优先级和结合性。如果它的优先级和结合性高于栈顶运算符
  （或者栈为空或者栈顶为左括号），则压入栈中。否则，弹出并输出栈顶运算符，并重复这一步骤。
	  如果扫描完毕，弹出并输出栈中剩余的运算符（如果有）。
  
 */

// 定义一个函数，判断一个字符是否是操作数
bool isOperand(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// 定义一个函数，返回一个运算符的优先级
int precedence(char c) {
	if (c == '^') return 3;
	if (c == '*' || c == '/') return 2;
	if (c == '+' || c == '-') return 1;
	return -1;
}

// 定义一个函数，将中缀表达式转化为后缀表达式
string infixToPostfix(string infix) {
	// 创建一个空字符串用于存储后缀表达式
	string postfix = "";
	// 创建一个空栈用于存储运算符和括号
	Stack s;
	// 从左到右扫描中缀表达式
	for (long long unsigned int i = 0; i < infix.length(); i++) {
		// 获取当前字符
		char c = infix[i];
		// 如果是操作数，则直接输出到后缀表达式
		if (isOperand(c)) {
			postfix += c;
		}
		// 如果是左括号，则压入栈中
		else if (c == '(') {
			s.push(c);
		}
		// 如果是右括号，则弹出并输出栈中的运算符直到遇到左括号，并丢弃左括号
		else if (c == ')') {
			while (!s.isEmpty() && s.peek() != '(') {
				postfix += s.pop();
			}
			if (!s.isEmpty() && s.peek() == '(') {
				s.pop();
			}
		}
		// 如果是运算符，则比较它与栈顶运算符的优先级和结合性，并按照相应规则处理
		else {
			while (!s.isEmpty() && precedence(c) <= precedence(s.peek())) {
				postfix += s.pop();
			}
			s.push(c);
		}
	}
	// 扫描完毕后，弹出并输出栈中剩余的运算符（如果有）
	while (!s.isEmpty()) {
		postfix += s.pop();
	}
	// 返回后缀表达式
	return postfix;
}

void changeExpression()
{
	// 创建一个中缀表达式
	// 一个复杂的测试，要求课本上的结果，可以直接换成自己想要的字符串。
	string infix = "a+b*(c^d-e)^(f+g*h)-i";
	// 调用函数将其转化为后缀表达式，并输出结果
	// std::string类用printf输出非常麻烦，这里简单输出一下，请大家谅解。以下输出均用cout代替。
	cout << "Infix: " << infix << endl;
	cout << "Postfix: " << infixToPostfix(infix) << endl;
}
// ----------------------------------------------------------------------------
// 应用题3.是一个循环队列
/*
  初始化一个大小为n的数组queue，其中n是队列能够容纳的最大元素个数。
  初始化两个变量front和rear为-1，分别表示队首和队尾的索引。
  入队一个元素x时，执行以下操作：
  rear加1。如果rear等于n，将rear设为0。
  如果front等于-1，将front设为0。
  将x赋值给queue[rear]。
  出队一个元素时，执行以下操作：
  如果front等于-1，说明队列为空，返回错误信息。
  将queue[front]赋值给一个变量y，并返回y。
  如果front等于rear，说明只有一个元素在队列中，将front和rear都设为-1。
  否则，front加1。如果front等于n，将front设为0。
  
 */
// 定义循环队列类
class CircularQueue {
	// 定义私有成员变量
private:
	int *queue; // 队列数组
	int front; // 队首索引
	int rear; // 队尾索引
	int size; // 队列大小
	
	// 定义公有成员函数
public:
	// 构造函数
	CircularQueue(int n) {
		queue = new int[n]; // 动态分配数组空间
		front = -1; // 初始化为-1
		rear = -1; // 初始化为-1
		size = n; // 记录大小
	}
	
	// 析构函数
	~CircularQueue() {
		delete[] queue; // 释放数组空间
	}
	
	// 入队函数
	void enqueue(int x) {
		if (isFull()) { // 判断是否满了
			cout << "Queue is full." << endl;
			return;
		}
		rear++; // rear加1
		if (rear == size) { // 如果到达边界
			rear = 0; // 设为0
		}
		if (front == -1) { 
			front = 0; // 如果队列为空，设front为0
		}
		queue[rear] = x; // 将x赋值给queue[rear]
		cout << "Enqueued " << x << " to the queue." << endl;
	}
	
	// 出队函数
	int dequeue() {
		if (isEmpty()) { // 判断是否为空
			cout << "Queue is empty." << endl;
			return -1;
		}
		int y = queue[front]; // 将queue[front]赋值给y
		cout << "Dequeued " << y << " from the queue." << endl;
		if (front == rear) { // 如果只有一个元素
			front = -1; // 设front为-1
			rear = -1; // 设rear为-1
		} else {
			front++; // 否则，front加1
			if (front == size) { // 如果到达边界
				front = 0; // 设为0
			}
		}
		return y; // 返回y
	}
	
	// 判断空函数
	bool isEmpty() {
		return front == -1; // 如果front等于-1，返回true，否则返回false
	}
	
	// 判断满函数
	bool isFull() {
		return (rear + 1) % size == front; 
		// 如果rear加1后取模size等于front，返回true，否则返回false
	}
	
	// 打印函数
	void print() {
		if (isEmpty()) { 
			// 判断是否为空
			cout << "Queue is empty." << endl;
			return;
		}
		cout << "Queue: ";
		// 输出队列元素，从front到rear，注意处理边界情况
		front = 0; // 如果队列为空，设front为0 } queue[rear] = x; // 将x赋值给queue[rear] cout << "Enqueued " << x << " to the queue." << endl; } // 出队函数 int dequeue() { if (isEmpty()) { // 判断是否为空 cout << "Queue is empty." << endl; return -1; } int y = queue[front]; // 将queue[front]赋值给y cout << "Dequeued " << y << " from the queue." << endl; if (front == rear) { // 如果只有一个元素 front = -1; // 设front为-1 rear = -1; // 设rear为-1 } else { front++; // 否则，front加1 if (front == size) { // 如果到达边界 front = 0; // 设为0 } } return y; // 返回y } // 判断空函数 bool isEmpty() { return front == -1; // 如果front等于-1，返回true，否则返回false } // 判断满函数 bool isFull() { return (rear + 1) % size == front; // 如果rear加1后取模size等于front，返回true，否则返回false } // 打印函数 void print() { if (isEmpty()) { // 判断是否为空 cout << "Queue is empty." << endl; return; } cout << "Queue: "; // 输出队列元素，从front到rear，注意处理边界情况
		int i = front; // 用一个变量i记录当前索引
		while (i != rear) { // 当i不等于rear时
			cout << queue[i] << " "; // 输出queue[i]
			i++; // i加1
			if (i == size) { // 如果到达边界
				i = 0; // 设为0
			}
		}
		cout << queue[rear] << endl; // 输出queue[rear]
	}
};
// ----------------------------------------------------------------------------
// 算法设计题2. 两栈共享空间。我们这里用结构体来实现。
//定义一个结构体表示两个栈
typedef struct {
	int data[maxsize]; //定义一个数组作为存储区
	int top1; //定义一个指针表示S1的栈顶
	int top2; //定义另一个指针表示S2的栈顶
}DoubleStack;

//初始化两个栈
void InitStack(DoubleStack *S) {
	S->top1 = -1; //让S1的栈顶指向-1
	S->top2 = maxsize; //让S2的栈顶指向maxsize
}

//判断两个栈是否为空
bool IsEmpty(DoubleStack *S) {
	if (S->top1 == -1 && S->top2 == maxsize) { //如果两个指针都没有移动过，说明两个栈都为空
		return true;
	} else {
		return false;
	}
}

//判断两个栈是否满
bool IsFull(DoubleStack *S) {
	if (S->top1 + 1 == S->top2) { //如果两个指针相邻，说明两个栈都满了
		return true;
	} else {
		return false;
	}
}

//入栈操作
bool Push(DoubleStack *S, int x, int i) { //x是要入栈的元素，i是要选择哪个栈（0代表S1，非0代表S2）
	if (IsFull(S)) { //如果满了就不能入栈了
		return false;
	}
	if (i == 0) { //如果选择了S1
		S->data[++(S->top1)] = x; //先让top1加一再赋值给data数组（相当于从左往右入）
	} else { //如果选择了S2
		S->data[--(S->top2)] = x; //先让top2减一再赋值给data数组（相当于从右往左入）
	}
	return true;
}

//出栈操作
bool Pop(DoubleStack *S, int *x, int i) { //*x用来存储出栈的元素，i用来选择哪个栈（同上）
	if (IsEmpty(S)) { //如果空了就不能出站了 
		return false;
	}
	if (i == 0) { //如果选择了s1 
		*x = S->data[(S->top1)--];  //先把data数组赋值给*x再让top减一（相当于从右往左出） 
	} else {  // 如果选择了s2 
		*x = S -> data[(S ->top2) ++];  // 入把data数组赋值给*x再让top加一（相当于从左往右出） 
	} 
	return true; 
}
//查看栈顶元素
bool Peek(DoubleStack *S, int *x, int i) { //x用来存储查看到的元素，i用来选择哪个栈（同上）
	if (IsEmpty(S)) { //如果空了就没有元素可以查看了
		return false;
	}
	if (i == 0) { //如果选择了S1
		*x = S->data[S->top1]; //直接把data数组赋值给*x，不改变top1的值（相当于只看不动）
	} else { //如果选择了S2
		*x = S->data[S->top2]; //直接把data数组赋值给*x，不改变top2的值（相当于只看不动）
	}
	return true;
}


int _tmain(int argc, _TCHAR* argv[], _TCHAR* envp[]) {
	changeExpression();
	return 0;
}
