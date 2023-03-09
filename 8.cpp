/*
  encoding: utf-8
  by: qiαnmu
 */
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

#include<iostream>
using namespace std;
/*
  目录
  应用题2，5
  算法设计题1，2
 */
//针对应用题2，这是一个每次划分都会输出关键码序列的快排，可以试试复制出去运行试试理解。
//定义划分函数，参数为数组指针，起始下标和终止下标
int partition(int* arr, int low, int high) {
	int pivot = arr[high]; //选择最后一个元素作为基准元素
	int i = low - 1; //定义一个变量i，表示小于等于基准元素的区域的右边界，初始为low-1
	for (int j = low; j < high; j++) { //遍历从low到high-1的所有元素
		if (arr[j] <= pivot) { //如果当前元素小于等于基准元素
			i++; //将i加一，扩大小于等于基准元素的区域
			swap(arr[i], arr[j]); //交换i和j位置上的元素，使得i位置上的元素小于等于基准元素，j位置上的元素大于基准元素（或者是原来就在那里）
		}
	}
	swap(arr[i + 1], arr[high]); //最后交换i+1和high位置上的元素，使得i+1位置上是基准元素，左边都是小于等于它的，右边都是大于它的
	return i + 1; //返回基准元素的位置
}

//定义打印数组函数，参数为数组指针，起始下标和终止下标
void printArray(int* arr, int low, int high) {
	for (int i = low; i <= high; i++) { //遍历从low到high的所有元素
		cout << arr[i] << " "; //打印当前元素，并用空格隔开
	}
	cout << endl; //打印换行符
}
//定义快速排序函数，参数为数组指针，起始下标和终止下标
void quickSort(int* arr, int low, int high) {
	if (low < high) { //如果起始下标小于终止下标，说明还有元素需要排序
		int pivot = partition(arr, low, high); //调用划分函数，返回基准元素的位置
		printArray(arr, low, high); //打印每次划分结束后的数组状态
		quickSort(arr, low, pivot - 1); //对基准元素左边的子数组进行快速排序
		quickSort(arr, pivot + 1, high); //对基准元素右边的子数组进行快速排序
	}
}
// ----------------------------------------------------------------------------



//针对应用题5，这是一个每次划分都会输出关键码序列的堆排，可以试试复制出去运行试试理解。
//定义调整最大堆函数，参数为数组指针，当前节点下标和堆大小
void maxHeapify(int* arr, int i, int n) {
	int left = 2 * i + 1; //计算左孩子节点的下标
	int right = 2 * i + 2; //计算右孩子节点的下标
	int largest = i; //假设当前节点是最大的
	if (left < n && arr[left] > arr[largest]) { //如果左孩子存在且比当前节点大，则更新最大值下标为左孩子下标
		largest = left;
	}
	if (right < n && arr[right] > arr[largest]) { //如果右孩子存在且比当前节点或左孩子大，则更新最大值下标为右孩子下标
		largest = right;
	}
	if (largest != i) { //如果最大值下标不是当前节点，则说明需要交换位置，并继续向下调整
		swap(arr[i], arr[largest]); //交换当前节点和最大值节点的位置
		maxHeapify(arr, largest, n); //递归地对交换后的子树进行调整，使其满足最大堆性质
	}
}
//定义构建最大堆函数，参数为数组指针和数组长度
void buildMaxHeap(int* arr, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) { //从最后一个非叶子节点开始，到根节点结束，逆序遍历所有节点
		maxHeapify(arr, i, n); //对每个节点进行调整，使其满足最大堆性质
	}
}

//定义堆排序函数，参数为数组指针和数组长度
void heapSort(int* arr, int n) {
	buildMaxHeap(arr, n); //构建最大堆
	for (int i = n - 1; i > 0; i--) { //从最后一个元素开始，到第二个元素结束，循环执行以下操作
		swap(arr[0], arr[i]); //交换堆顶元素和当前元素，使得当前元素是最大的
		printArray(arr, n); //打印每趟排序后的结果
		maxHeapify(arr, 0, i); //对剩余的i个元素进行调整，使其满足最大堆性质
	}
}
//定义打印数组函数，参数为数组指针和数组长度
void printArray(int* arr, int n) {
	for (int i = 0; i < n; i++) { //遍历所有元素
		cout << arr[i] << " "; //打印当前元素，并用空格隔开
	}
	cout << endl; //打印换行符
}


// ----------------------------------------------------------------------------

// 实际上，算法设计题1这个有趣的算法叫做鸡尾酒算法。它可以减少交换次数，并降为两个一重循环。
//定义交换函数
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

//定义鸡尾酒排序函数
void cocktailSort(int arr[], int n) {
	int left = 0; //左边界
	int right = n - 1; //右边界
	bool swapped = true; //标记是否发生交换
	while (left < right && swapped) { //当左右边界未相遇且有交换时继续循环
		swapped = false; //每轮开始前重置交换标记为false
		for (int i = left; i < right; i++) { //从左到右进行冒泡排序
			if (arr[i] > arr[i + 1]) { //如果当前元素大于后一个元素，交换位置
				swap(arr[i], arr[i + 1]);
				swapped = true; //更新交换标记为true
			}
		}
		right--; //缩小右边界
		for (int i = right; i > left; i--) { //从右到左进行冒泡排序
			if (arr[i] < arr[i - 1]) { //如果当前元素小于前一个元素，交换位置
				swap(arr[i], arr[i - 1]);
				swapped = true; //更新交换标记为true
			}
		}
		left++; //缩小左边界
	}
}

// ----------------------------------------------------------------------------
/*
  单链表排序是指对一个由节点组成的线性表进行排序，使得节点按照某种规则排列。常用的单链表排序算法有直接插入排序、简单选择排序和归并排序。
  
  直接插入排序是一种稳定的排序算法，它的思想是将每个节点插入到已经排好序的链表中，使得新链表仍然有序。它的时间复杂度为O(n^2)，空间复杂度为O(1)。
  
  简单选择排序是一种不稳定的排序算法，它的思想是每次从原链表中找出最小（或最大）的节点，放到新链表的末尾，使得新链表逐渐有序。它的时间复杂度为O(n^2)，空间复杂度为O(1)。
  
  归并排序是一种稳定的排序算法，它的思想是将原链表分成两个子链表，分别对子链表进行归并排序，然后将两个有序子链表合并成一个有序链表。它的时间复杂度为O(nlogn)，空间复杂度为O(1)
  
 */
// 单链表排序的实现比较麻烦。这里仅展示直接插入排序。
// 假设链表节点为ListNode
void insertionSort(ListNode* head) {
	if (head == nullptr || head->next == nullptr) return; //如果链表为空或只有一个节点，直接返回
	ListNode* sorted = head; //已排序部分的尾节点，初始为头节点
	ListNode* curr = head->next; //待排序部分的头节点，初始为第二个节点
	while (curr != nullptr) { //当待排序部分不为空时循环
		if (curr->val >= sorted->val) { //如果待排序节点大于等于已排序尾节点，无需插入，直接更新指针
			sorted = curr;
			curr = curr->next;
		} else { //否则，需要在已排序部分找到合适的位置插入
			ListNode* prev = nullptr; //用于记录已排序部分的前驱节点，初始为空
			ListNode* temp = head; //用于遍历已排序部分的临时指针，初始为头节点
			while (temp != curr && temp->val < curr->val) { //从头开始找到第一个大于等于待排序节点的位置，或者到达待排序头节点（说明待排序头节点是最小的）
				prev = temp;
				temp = temp->next;
			}
			if (prev == nullptr) { //如果前驱为空，说明待排序头节点应该插入到链表头部
				sorted->next = curr->next; //将待排序头节点从原链表中断开
				curr->next = head; //将待排序头节点连接到链表头部
				head = curr; //更新链表头指针为待排序头节点
				curr = sorted->next; //更新待排序头指针为下一个待排元素（即原来的sorted后面那个）
			} else {
				//否则，说明找到了合适的位置在中间插入（不会是尾部）
				sorted->next = curr->next; //将待排序头节点从原链表中断开
				curr->next = temp; //将待排序头节点连接到找到的位置后面
				prev->next = curr; //将前驱节点连接到待排序头节点前面
				curr = sorted->next; //更新待排序头指针为下一个待排元素（即原来的sorted后面那个）
			}
		}
	}

int _tmain(int argc, _TCHAR* argv[], _TCHAR* envp[]) {
	_tsetlocale(LC_ALL, TEXT("chs"));
	
}
