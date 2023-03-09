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
  算法设计题1.
  
 */
//定义二叉树节点结构
struct TreeNode {
	int val; //节点值
	TreeNode* left; //左子节点指针
	TreeNode* right; //右子节点指针
	TreeNode(int x) : val(x), left(NULL), right(NULL) {} //构造函数
};
//计算二叉树节点的高度
int height(TreeNode* node) {
	if (node == NULL) return 0; //空节点高度为0
	return max(height(node->left), height(node->right)) + 1; //非空节点高度为左右子树最大高度加1
}

//判断一棵二叉树是否为平衡二叉树
bool isBalanced(TreeNode* root) {
	if (root == NULL) return true; //空树是平衡的
	int balance = height(root->left) - height(root->right); //计算当前节点的平衡因子
	if (abs(balance) > 1) return false; //如果平衡因子绝对值大于1，说明不平衡
	return isBalanced(root->left) && isBalanced(root->right); //递归判断左右子树是否都平衡
}

int _tmain(int argc, _TCHAR* argv[], _TCHAR* envp[]) {
	_tsetlocale(LC_ALL, TEXT("chs"));
	
}
