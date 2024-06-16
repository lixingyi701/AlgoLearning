#include<bits/stdc++.h>
using namespace std;
//彩色路径
//20: 有边数限制的 最长路径 BF算法[不好使，可能 bf 不能通过把 min 改 max 得到最长路]
//动态规划：记 dp[i][j] 表示经过了 i 条边 ，最后到达了 j 点的距离 最大值
//初始状态 dp[0][i] = 0 经过 0 条边，最后到达 i 点 的最长距离为 0
//转移方程： dp[i][j] = max(dp[i][j] , dp[i-1][k] + mar[k][j]) 
//50 是状态压缩 dp ，将结点的颜色压缩成二进制数，考虑怎么改进 存储方式
const int N = 110;
const int M = 5010;
const int L = 10;
int n, m, l, k;//图的节点数、边数、节点上限数、颜色标签范围

int mar[N][N];

int dp[L][N];
int f[M], t[M], w[M];
int main()
{
	cin >> n >> m >> l >> k;
	
	for (int i = 0; i < n; i++){
		int k; cin >> k;
	}

	for (int i = 0; i < m; i++) 
		cin >> f[i];
	for (int i = 0; i < m; i++) 
		cin >> t[i];
	for (int i = 0; i < m; i++)
		cin >> w[i];
	
	for (int i = 0; i < m; i++)	
		mar[f[i]][t[i]] = w[i];
	

	for (int i = 1; i <= l-1; i++)
		//遍历 经过边的个数,上限 为 节点上限数 - 1
		for (int j = 0; j < n; j++)
			//遍历所有结点
			for (int k = 0; k < n; k++)
				if (mar[k][j] != 0) //如果有从 k 到 j 的边
					dp[i][j] = max(dp[i][j], dp[i - 1][k] + mar[k][j]);
				

	int res = -1;
	for (int i = 0; i <= l - 1; i++)
		res = max(res, dp[i][n - 1]);
	
	cout << res;
}