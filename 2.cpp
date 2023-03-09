/*
  encoding: utf-8
  by: qiαnmu
 */
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

// 单链表的定义
// 如果您已经熟练掌握，请忽略以下一大堆定义，直接前往Union函数和主函数
typedef struct _NODE_
{
	int data;
	_NODE_* next;
}NODE, *PNODE;

// 定义单链表类
class LinkList {

public:
	// 无参构造函数，创建一个空链表
	LinkList() {
		head = NULL;
	}
	PNODE& getHead()
	{
		return head;
	}
	
	// 有参构造函数，根据给定数组和长度创建链表
	LinkList(int a[], int n) {
		if (n <= 0) return; // 如果长度不合法，直接返回
		head = new NODE(); // 创建头节点并分配内存空间
		head->data = a[0]; // 将头节点的数据域赋值为数组第一个元素
		head->next = NULL; // 将头节点的指针域置空
		PNODE p = head; // 创建一个临时指针p指向头节点
		for (int i = 1; i < n; i++) { // 遍历数组中剩余的元素
			PNODE q = new NODE(); // 创建新节点并分配内存空间
			q->data = a[i]; // 将新节点的数据域赋值为数组当前元素
			q->next = NULL; // 将新节点的指针域置空 
			p->next = q; // 将p所指向的节点（即上一个节点）与q连接起来 
			p = q; // 将p移动到q所指向的位置（即当前最后一个节点）
		}
	}
	
	// 析构函数，释放链表占用的内存空间 
	~LinkList() {
		PNODE p = head; // 创建一个临时指针p指向头节点 
		while (p != NULL) { 
			PNODE q = p->next; // 创建另一个临时指针q指向p所指向节点（即当前要删除的节点）的下一个节点 
			delete p; // 删除p所指向的节点并释放内存空间 
			p = q;  // 将p移动到q所指向的位置（即下一个要删除的位置）
		}
	}
	
	// 求顺序表长度，返回链表中元素个数 
	int getLength() {
		int len = 0; // 初始化长度为0 
		PNODE p = head;  
		
		// 创建一个临时指针p指向头节点
		while (p != NULL) { // 遍历链表
			len++; // 每遍历一 个节点，长度加一
			p = p->next; // 将p移动到下一个节点
		}
		return len; // 返回长度
	}
	
	// 按位查找，返回第i个位置的元素值，如果i不合法，返回-1 
	int getItem(int i) {
		if (i < 1 || i > getLength()) return -1; // 如果i不在有效范围内，返回-1 
		PNODE p = head; // 创建一个临时指针p指向头节点 
		int j = 1; // 初始化计数器为1 
		while (j < i) { // 遍历链表直到第i个位置 
			p = p->next; // 将p移动到下一个节点 
			j++; // 计数器加一 
		}
		return p->data; // 返回p所指向节点的数据域 
	}
	
	// 按值查找，返回第一个等于x的元素的位置，如果没有找到，返回0 
	int locate(int x) {
		PNODE p = head; // 创建一个临时指针p指向头节点 
		int i = 1; // 初始化计数器为1 
		while (p != NULL && p->data != x) {  // 遍历链表直到找到x或者到达尾部
			p = p->next; // 将p移动到下一个节点
			i++; // 计数器加一
		}
		if (p == NULL) return 0; // 如果没有找到x，返回0
		else return i; // 否则返回当前位置i
	}
	
	// 在第i个位置插入x，如果成功插入，返回true；否则返回false
	bool insert(int i, int x) {
		if (i < 1 || i > getLength() + 1) return false; // 如果i不在有效范围内，返回false
		PNODE s = new NODE(); // 创建新节点并分配内存空间
		s->data = x; // 将新节点的数据域赋值为x
		s->next = NULL; // 将新节点的指针域置空
	// 创建一个临时指针p指向头节点 while (p != NULL) { // 遍历链表 len++; // 每遍历一个节点，长度加一 p = p->next; // 将p移动到下一个节点 } return len; // 返回长度 } // 按位查找，返回第i个位置的元素值，如果i不合法，返回-1 int getItem(int i) { if (i < 1 || i > getLength()) return -1; // 如果i不在有效范围内，返回-1 PNODE p = head; // 创建一个临时指针p指向头节点 int j = 1; // 初始化计数器为1 while (j < i) { // 遍历链表直到第i个位置 p = p->next; // 将p移动到下一个节点 j++; // 计数器加一 } return p->data; // 返回p所指向节点的数据域 } // 按值查找，返回第一个等于x的元素的位置，如果没有找到，返回0 int locate(int x) { PNODE p = head; // 创建一个临时指针p指向头节点 int i = 1; // 初始化计数器为1 while (p != NULL && p->data != x) { // 遍历链表直到找到x或者到达尾部 p = p->next; // 将p移动到下一个节点 i++; // 计数器加一 } if (p == NULL) return 0; // 如果没有找到x，返回0 else return i; // 否则返回当前位置i } // 在第i个位置插入x，如果成功插入，返回true；否则返回false bool insert(int i, int x) { if (i < 1 || i > getLength() + 1) return false; // 如果i不在有效范围内，返回false PNODE s = new NODE(); // 创建新节点并分配内存空间 s->data = x; // 将新节点的数据域赋值为x s->next = NULL; // 将新节点的指针域置空

		
		if (i == 1) { // 如果插入位置为第一个
			s->next = head; // 将新节点与头节点连接起来
			head = s; // 将头节点指向新节点
		}
		else { // 如果插入位置不是第一个
			PNODE p = head; // 创建一个临时指针p指向头节点
			int j = 1; // 初始化计数器为1
			while (j < i - 1) { // 遍历链表直到第i-1个位置
				p = p->next; // 将p移动到下一个节点
				j++; // 计数器加一
			}
			s->next = p->next; // 将新节点与p所指向节点的下一个节点连接起来 
			p->next = s; // 将p所指向的节点与新节点连接起来 
		}
		return true; // 返回true表示成功插入 
	}
	
	// 删除第i个位置的元素，如果成功删除，返回被删除的元素值；否则返回-1 
	int remove(int i) {
		if (i < 1 || i > getLength()) return -1; // 如果i不在有效范围内，返回-1 
		PNODE p = head; // 创建一个临时指针p指向头节点 
		int x; // 定义一个变量x用于存储被删除的元素值 
		if (i == 1) { // 如果删除位置为第一个 
			head = head->next; // 将头节点指向原来头节点的下一个节点 
			x = p->data; // 将被删除的元素值赋给x 
			delete p; // 删除原来的头节点并释放内存空间 
		}
		else { // 如果删除位置不是第一个 
			int j = 1; // 初始化计数器为1 
			while (j < i - 1) { // 遍历链表直到第i-1个位置 
				p = p->next; // 将p移动到下一个节点 
				j++; // 计数器加一  
			}
			if (i == 1) { // 如果插入位置为第一个 s->next = head; // 将新节点与头节点连接起来 head = s; // 将头节点指向新节点 } else { // 如果插入位置不是第一个 PNODE p = head; // 创建一个临时指针p指向头节点 int j = 1; // 初始化计数器为1 while (j < i - 1) { // 遍历链表直到第i-1个位置 p = p->next; // 将p移动到下一个节点 j++; // 计数器加一 } s->next = p->next; // 将新节点与p所指向节点的下一个节点连接起来 p->next = s; // 将p所指向的节点与新节点连接起来 } return true; // 返回true表示成功插入 } // 删除第i个位置的元素，如果成功删除，返回被删除的元素值；否则返回-1 int remove(int i) { if (i < 1 || i > getLength()) return -1; // 如果i不在有效范围内，返回-1 PNODE p = head; // 创建一个临时指针p指向头节点 int x; // 定义一个变量x用于存储被删除的元素值 if (i == 1) { // 如果删除位置为第一个 head = head->next; // 将头节点指向原来头节点的下一个节点 x = p->data; // 将被删除的元素值赋给x delete p; // 删除原来的头节点并释放内存空间 } else { // 如果删除位置不是第一个 int j = 1; // 初始化计数器为1 while (j < i - 1) { // 遍历链表直到第i-1个位置 p = p->next; // 将p移动到下一个节点 j++; // 计数器加一 }
			
				
				PNODE q = p->next; // 创建另一个临时指针q指向p所指向节点（即第i-1个节点）的下一个节点（即第i个节点）
				x = q->data; // 将被删除的元素值赋给x 
				p->next = q->next; // 将p所指向节点与q所指向节点的下一个节点连接起来 
				delete q; // 删除q所指向的节点并释放内存空间 
			}
			return x; // 返回被删除的元素值 
		}
		
	}
		
	// 判空，如果链表为空，返回true；否则返回false 
	bool empty() {
		return head == NULL; // 如果头节点为空，表示链表为空 
	}
	
	// 遍历，打印出链表中所有元素值 
	void printList() {
		PNODE p = head; // 创建一个临时指针p指向头节点 
		while (p != NULL) { // 遍历链表
			_tprintf(_T("%d->>"), p->data); // 打印当前节点的数据域
			p = p->next; // 将p移动到下一个节点
		}
		_tprintf(_T("\r\n")); // 换行
	}
private:
		PNODE head;
};

PNODE Union(PNODE &LA,PNODE LB){
	if(LA->next ==NULL || LB->next ==NULL) return nullptr; //空链表
	
	PNODE p = LA->next;
	PNODE q = LB->next;
	PNODE pre = LA;   //A表中，指向*p节点的指针；
	PNODE qre = LB;   //B表中，指向*q节点的指针；
	
	while(p!=NULL && q!=NULL){
		if(p->data > q->data){//B中元素的值较小，删除该结点,B中的指针右移；
			qre->next = q->next;
			q=q->next;
			if(q->data){
				delete q;
			}
			
		}else if(p->data < q->data){ //A中元素的值较小，删除该结点，并将指针右移；
			pre->next = p->next;
			p = p->next;
			if(p->data){
				delete p;
			}
			
		}else if(p->data == q->data){ 
			//发现相同元素，A中保留该结点，B中删除该结点，A、B指针同时右移；
			PNODE temp = qre; //暂存B中需要删除的结点的指针；
			
			pre = p;
			p = p->next;
			qre =q;
			q=q->next;
			
			delete temp;
		}
	}
	
	while(p==NULL && q!=NULL){ //B链表中还有元素未被遍历；
		PNODE temp = q->next;
		q->next = NULL;
		q = q->next;
		delete temp;
	}
	
	while(p !=NULL && q==NULL){ //A链表中还有元素未被遍历；
		PNODE temp = p->next;
		p->next = NULL;
		p = p->next;
		delete temp;
	}
	
	return LA;
}


int _tmain(int argc, _TCHAR* argv[], _TCHAR* envp[]) {
	_tsetlocale(LC_ALL, TEXT("chs"));
	int l1[] = {1, 2, 3, 4, 5};
	int l2[] = {1, 2, 3, 5, 6};
	LinkList list1(l1, 5);
	LinkList list2(l2, 5);
	
	Union(list1.getHead(), list2.getHead());
	list1.printList();
}
