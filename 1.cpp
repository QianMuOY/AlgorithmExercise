/*
  encoding: utf-8
  by: qiαnmu
 */
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

int f(int m, int n)
{
	if(m == 1)// 如果m等于1,1只能分解为1,也即表示方式只有一种
		return 1;
	if(n == 1)// 如果n等于1,无论m多大,n为1时只能表示为m个1之和,也即表示方式只有一种
		return 1;
	if(m == n)// 如果m等于n,此时分为m=n这一种情况和其余最大加数为n-1的情况
		return (1 + f(m, n-1));
	else if(m < n)// 当m小于n时，最大加数实际上不超过m
		return f(m, m);
		else	// 当m大于n时，可以拆分为最大加数包不包含n的两种情况。
			// 当最大加数包含n时，剩余加数之和必为m-n，即f(m-n, n)。
			// 当最大加数不包含n时，那么不超过n-1的加数之和为m，即f(m, n-1)
			// 实际上是让函数递归到上述四种情况去。
			return (f(m - n, n) + f(m, n - 1));
}

int _tmain(int argc, _TCHAR* argv[], _TCHAR* envp[]) {
	_tsetlocale(LC_ALL, TEXT("chs"));
	// 输入，输出结果
	// 6 4 9
	int m,n,ans;
	_tscanf(_T("%d%d"),&m,&n);
	ans = f(m,n);
	_tprintf(_T("%d\n"),ans);
}
