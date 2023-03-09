/*
  encoding: utf-8
  by: qiαnmu
 */
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>
/*
  目录
  算法设计题1.2.
  
 */

/*
  我们遍历邻接矩阵matrix，将每个非零元素转换为邻接表中的一个结点。
  我们用两层循环来遍历matrix，外层循环变量i表示行号，内层循环变量j表示列号。
  如果matrix[i][j]不等于0，说明存在一条从顶点i到顶点j的边。
  因此，我们需要在adjList[i]中添加一个新的结点来表示这条边。我们用new关键字来动态分配内存空间给新结点，
	  并给它赋值vertex为j和next为NULL。然后，我们将新结点插入到adjList[i]的头部，即让新结点的next指向原来的头结点，
	  并让adjList[i]指向新结点。
  
 */
//我们这里同样不进行定义。假设图的顶点数为n，邻接矩阵为matrix[n][n]
//定义邻接表结点结构
struct Node {
	int vertex; //顶点编号
	Node* next; //指向下一个结点的指针
};
//定义邻接表数组
Node* adjList[n];
void changeToAdjList()
{
	//初始化邻接表数组为空
	for (int i = 0; i < n; i++) {
		adjList[i] = NULL;
	}
	//遍历邻接矩阵，将每个非零元素转换为邻接表结点
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) { //如果存在一条从i到j的边
				//创建一个新的结点
				Node* newNode = new Node;
				newNode->vertex = j;
				newNode->next = NULL;
				//将新结点插入到adjList[i]的头部
				newNode->next = adjList[i];
				adjList[i] = newNode;
			}
		}
	}
}
// ----------------------------------------------------------------------------
// 判断给定的有向图是否存在回路。假设邻接矩阵已确定
//假设图的顶点数为n，邻接矩阵为matrix[n][n]
//定义一个数组visited[n]，用来记录每个顶点的访问状态
//0表示未访问，1表示正在访问，2表示已访问
int visited[n];
//初始化visited数组为0
for (int i = 0; i < n; i++) {
	visited[i] = 0;
}
//定义一个函数dfs，用来进行深度优先搜索
//参数v表示当前访问的顶点编号
bool dfs(int v) {
	//将v标记为正在访问
	visited[v] = 1;
	//遍历v的所有邻接顶点
	for (int w = 0; w < n; w++) {
		if (matrix[v][w] != 0) { //如果存在一条从v到w的边
			if (visited[w] == 0) { //如果w未访问过，则递归调用dfs(w)
				if (dfs(w)) { //如果找到了回路，则返回true
					return true;
				}
			} else if (visited[w] == 1) { //如果w正在访问，则说明找到了回路
				return true;
			}
		}
	}
	//将v标记为已访问
	visited[v] = 2;
	//返回false表示没有找到回路
	return false;
}
//定义一个函数hasCycle，用来判断有向图是否存在回路
bool hasCycle() {
	//遍历所有顶点，对每个未访问过的顶点调用dfs函数
	for (int i = 0; i < n; i++) {
		if (visited[i] == 0) { //如果i未访问过，则调用dfs(i)
			if (dfs(i)) { //如果找到了回路，则返回true
				return true;
			}
		}
	}
	//返回false表示没有找到回路
	return false;
}


int _tmain(int argc, _TCHAR* argv[], _TCHAR* envp[]) {
	_tsetlocale(LC_ALL, TEXT("chs"));
	
}
