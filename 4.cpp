/*
  encoding: utf-8
  by: qiαnmu
 */
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

// 不得不说cout是真的方便啊，去他娘的运行速率和双字支持，我就要用cout
#include<iostream>
#include<string>
using namespace std;

/*
  目录：
  应用题2.
  应用题4.
  算法设计题1.
 */
// 这是一个KMP算法的题目。
//计算next数组
void getNext(string T, int *next) {
    long long unsigned int i = 0; //模式串指针
	int j = -1; //前缀指针
	next[0] = -1; //初始化第一个元素为-1
	while (i < T.length()) { //遍历模式串
		if (j == -1 || T[i] == T[j]) { //如果前缀指针为-1或者当前字符相等
			i++; //模式串指针后移一位
			j++; //前缀指针后移一位
			next[i] = j; //更新next数组
		} else { //如果当前字符不相等
			j = next[j]; //前缀指针回溯到next[j]
		}
	}
}

//进行匹配
int KMP(string S, string T) {
	long long unsigned int i = 0; //主串指针
	int j = 0; //模式串指针
	int next[T.length()]; //定义next数组
	getNext(T, next); //计算next数组
	
	// 要强转为int是因为原本的长度是long long unsigned int
	while (i < S.length() && j < int(T.length())) { //遍历主串和模式串
		if (j == -1 || S[i] == T[j]) { //如果模式串指针为-1或者当前字符相等
			i++; //主串指针后移一位
			j++; //模式串指针后移一位
		} else { //如果当前字符不相等
			j = next[j]; //模式串指针回溯到next[j]
		}
	}
	
	if (j == int(T.length())) { //如果匹配成功，返回匹配位置的起始下标（从0开始）
		return i - j;
	} else { //如果匹配失败，返回-1 
		return -1;
	}
}
// 进行测试
void getKMPAnswer()
{
	//定义主串和模式串
	string S = "abcaabbcaaabababaabca";
	string T = "babab";
	
	//调用KMP函数
	int result = KMP(S, T);
	
	//输出结果
	if (result == -1) {
		cout << "没有匹配成功" << endl;
	} else {
		cout << "匹配成功，起始位置为：" << result << endl;
	}
}

// ----------------------------------------------------------------------------
// 这是一个三元组问题。实现起来有点复杂
//定义三元组结构体
struct Triple {
	int row; //行号
	int col; //列号
	int val; //值
};

//定义稀疏矩阵类
class SparseMatrix {
private:
	Triple *data; //存储非零元素的数组
	int rows; //行数
	int cols; //列数
	int nums; //非零元素个数
	
public:
	SparseMatrix(int r, int c, int n); //构造函数，初始化稀疏矩阵
	~SparseMatrix(); //析构函数，释放内存空间
	void input(); //输入非零元素的信息
	void output(); //输出稀疏矩阵的信息
	SparseMatrix transpose(); //转置稀疏矩阵，并返回转置后的新对象
	
};

//构造函数，初始化稀疏矩阵
SparseMatrix::SparseMatrix(int r, int c, int n) {
	rows = r;
	cols = c;
	nums = n;
	data = new Triple[nums]; //动态分配数组空间
}

//析构函数，释放内存空间
SparseMatrix::~SparseMatrix() {
	delete[] data;
}

//输入非零元素的信息
void SparseMatrix::input() {
	cout << "请输入" << nums << "个非零元素的行号、列号和值：" << endl;
	
	for (int i = 0; i < nums; i++) { 
		cin >> data[i].row >> data[i].col >> data[i].val;
		
		if (data[i].row < 0 || data[i].row >= rows || data[i].col < 0 || data[i].col >= cols) { 
			cout << "输入错误，请重新输入：" << endl;
			i--;
		}
		
		else if (data[i].val == 0) { 
			cout << "值不能为0，请重新输入：" << endl;
			i--;
		}
		
		else { 
			for (int j = 0; j < i; j++) { 
				if (data[j].row == data[i].row && data[j].col == data[i].col) { 
					cout << "位置重复，请重新输入：" << endl;
					i--;
					break;
				}
			}
		}
		
	}
}

//输出稀疏矩阵的信息

void SparseMatrix::output() {
	
	cout << "该稀疏矩阵共有" << rows << "行" << cols << "列" << nums <<"个非零元素" <<
	endl;
	
	cout <<
	"行号\t列号\t值\n";
	
	for (int i = 0; i < nums; i++) {
		
		cout <<
		data[i].row <<
		"\t" <<
		data[i].col <<
		"\t" <<
		data[i].val <<
		endl;
		
	}
}

//转置稀疏矩阵，并返回转置后的新对象

SparseMatrix SparseMatrix::transpose() {
	
	SparseMatrix B(cols, rows, nums); 
	
	int *num = new int[cols]; 
	
	int *cpot = new int[cols]; 
	
	for (int col = 0; col < cols; col++) {
		
		num[col] = 0;
		
	} 
	
	for (int t = 0; t < nums; t++) {
		
		num[data[t].col]++;
		
	} 
	
	cpot[0] = 0;
	
	for (int col = 1; col < cols; col++) {
		
		cpot[col] =
		cpot[col - 1] + num[col - 1];
		
	} 
	
	for (int p = 0; p < nums;p++) {
		
		int col = data[p].col;
		
		int q = cpot[col];
		
		B.data[q].val = data[p].val; //将原矩阵的值赋给转置后的矩阵
		cpot[col]++; //更新cpot数组
	}
	delete[] num; //释放num数组
	delete[] cpot; //释放cpot数组
	return B; //返回转置后的新对象
}

// 测试一下
void SparseMatrixTest()
{
	int r, c, n;
	cout << "请输入稀疏矩阵的行数、列数和非零元素个数：" << endl;
	cin >> r >> c >> n;
	SparseMatrix A(r, c, n); //创建稀疏矩阵对象A
	A.input(); //输入A的信息
	cout << "原稀疏矩阵为：" << endl;
	A.output(); //输出A的信息
	SparseMatrix B = A.transpose(); //调用转置函数，得到新对象B
	cout << "转置后的稀疏矩阵为：" << endl;
	B.output(); //输出B的信息
}
// ----------------------------------------------------------------------------
/*
  假设A是一个从左到右递增，从上到下递增的矩阵，并且给定了要搜索的子矩阵的范围（a到b行，c到d列）。
  它采用了一种从右上角开始向左下角搜索的方法，每次比较当前元素与x的大小关系，并根据结果调整行号或列号。
  如果找到了等于x的元素，则将flag置为1并结束循环；如果没有找到，则返回0。
  
 */
// 判断算法
int ifIn(int** A, int x) //定义一个函数，参数是一个二维整型数组A和一个整型变量x，返回值是一个整型变量
{
	int a,b,c,d; //定义四个局部整型变量a,b,c,d
	cin>>a>>b>>c>>d; //从标准输入读取四个数，赋值给a,b,c,d
	int i=a,j=d-1,flag=0; //定义三个局部整型变量i,j,flag，并初始化为a,d-1,0
	while(i<=b&&j>=c&&!flag){ //当i不大于b，j不小于c，且flag为0时，循环执行以下语句
		if(A[i][j]==x) flag=1; //如果A[i][j]等于x，则将flag赋值为1
		else if(A[i][j]>x){ //否则，如果A[i][j]大于x，则执行以下语句
			j--; //将j减一
		}
		else i++; //否则，将i加一
	}
	return flag; //返回flag的值
}


int _tmain(int argc, _TCHAR* argv[], _TCHAR* envp[]) {
	getKMPAnswer();
	SparseMatrixTest();
	return 0;
}
