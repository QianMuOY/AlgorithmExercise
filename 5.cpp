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
// 在本节，定义各种类是没有意义的。我们集中看几种算法的实现即可。如果想测试，直接加入定义即可。若对这些还有疑问的同学，请读课本。

/*
  目录：
  填空题12.
  算法设计题1.
  算法设计题2.
 */

// 求二叉树深度的递归算法
int depth(BiTree* bt) {
	int h1, hr; //定义两个变量分别存储左右子树的高度
	if (bt == NULL) return 0; //如果当前节点为空，返回零
	h1 = depth(bt->lchild); //递归计算左子树的高度
	hr = depth(bt->rchild); //递归计算右子树的高度
	if (h1 > hr) { //如果左子树高度大于右子树高度
		h1++; //将左子树高度加一
	}
	return (hr + 1); //返回右子树高度加一（注意：这里假设h1 <= hr）
}
// ----------------------------------------------------------------------------
/*
  不使用递归或栈的方法 返回后序遍历第一个节点
  Morris遍历的方法，它可以在O(1)的空间复杂度下遍历二叉树。
  
  Morris遍历的思想是利用二叉树中的空指针，将当前节点的前驱节点（左子树中最右边的节点）的右指针指向当前节点，从而实现线索化。
  
  具体的算法步骤如下：
  
  初始化p指向根节点。
  如果p不为空，执行以下操作：
	  如果p没有左孩子，那么输出p的值，并将p指向其右孩子。
	  如果p有左孩子，那么找到其左子树中最右边的节点q，并判断q的右指针是否为空或者指向p。
		  如果q的右指针为空，那么将其右指针指向p，并将p指向其左孩子。
		  如果q的右指针指向p，那么将其右指针置空，并逆序输出从q到p路径上所有节点的值，并将p指向其右孩子。
  重复步骤2直到p为空。
  这样就可以得到二叉树后序遍历的第一个节点。
  
 */
//后序遍历Morris
void postOrderMorris(TreeNode* root) {
	if (root == NULL) return;
	TreeNode* p = root;
	while (p) {
		if (p->left == NULL) { //如果没有左孩子，直接指向右孩子
			p = p->right;
		} else { //如果有左孩子，找到其前驱节点
			TreeNode* q = p->left;
			while (q->right && q->right != p) { //找到左子树中最右边的节点
				q = q->right;
			}
			if (q->right == NULL) { //如果前驱节点的右指针为空，将其指向p，并将p指向其左孩子
				q->right = p;
				p = p->left;
			} else { //如果前驱节点的右指针指向p，将其置空，并逆序输出从q到p路径上所有节点的值，并将p指向其右孩子
				q->right = NULL;
				reversePrint(p->left);
				p = p->right;
			}
		}
	}
	reversePrint(root); //最后逆序输出从根节点到最右边节点的值
}

//逆序输出从start到end路径上所有节点的值
void reversePrint(TreeNode* start, TreeNode* end = NULL) {
	if (start == end) return; //如果起点和终点相同或者为空，直接返回
	TreeNode* prev = NULL; //记录前一个节点
	TreeNode* cur = start; //记录当前节点
	TreeNode* next; //记录下一个节点
	while (cur != end) { //反转链表，直到遇到终点或者空指针为止
		next = cur->right; 
		cur->right = prev; 
		prev = cur; 
		cur = next; 
	}
	cur = prev; //此时cur为反转后的头结点，即原来的尾结点
	while (cur) { //输出反转后链表中所有节点的值，并恢复原来的链表结构
		cout << cur->val << " ";
		next = cur->right;
		cur->right = prev;
		prev = cur;
		cur = next;
	}
}
// ----------------------------------------------------------------------------

//判断二叉树是否为完全二叉树
bool isCompleteTree(TreeNode* root) {
	if (root == NULL) return true; //空树是完全二叉树
	queue<TreeNode*> q; //创建一个队列
	q.push(root); //将根节点入队
	bool flag = false; //标记是否遇到了不饱和节点
	while (!q.empty()) { //当队列不为空时循环
		TreeNode* p = q.front(); //取出队首节点
		q.pop(); //将队首节点出队
		if (p == NULL) { //如果当前节点为空，说明遇到了不饱和节点
			flag = true;
		} else { //如果当前节点不为空，判断其左右孩子情况
			if (flag) return false; //如果之前已经遇到过不饱和节点，那么当前节点必须为空，否则返回false
			q.push(p->left); //将左孩子入队（可能为空）
			q.push(p->right); //将右孩子入队（可能为空）
		}
	}
	return true; //当队列为空时，说明没有发现矛盾的情况，返回true
}

int _tmain(int argc, _TCHAR* argv[], _TCHAR* envp[]) {
	_tsetlocale(LC_ALL, TEXT("chs"));
	
}
