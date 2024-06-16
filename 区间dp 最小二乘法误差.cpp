#include<bits/stdc++.h>
using namespace std;
//分段直线拟合 区间dp 最小二乘法

vector<pair<int, int>>pointArr;
int n, c;//点数、新直线权重

const int N = 1010;
double dp[N][N]; //dp[i][j]表示从点 i 到点 j 的最小罚分

double cal(int start, int end)
{
	//计算从start到end的拟合直线并计算罚分:

	int cnt = end - start + 1;
	double  xbar = 0.0, ybar = 0.0; //计算平均值
	int up = 0, down = 0; //计算拟合直线的斜率 分子 分母
	for (int i = start; i <= end; i++)
	{
		int x = pointArr[i].first, y = pointArr[i].second;
		xbar += x;
		ybar += y;
		up += x * y;
		down += x * x;
	}
	xbar /= cnt, ybar /= cnt;

	double k = 0;//斜率
	k = (up - cnt * xbar * ybar) / (down - cnt * xbar * xbar);
	double b = ybar - k * xbar;

	double loss = 0;
	for (int i = start; i <= end; i++)
	{
		loss += pow(pointArr[i].second - (k * pointArr[i].first + b), 2);
	}
	return loss;
}

int main()
{
	cin >> n >> c;
	for (int i = 0; i < n; i++)
	{
		int x, y; cin >> x >> y;
		pair<int, int>t = { x,y };
		pointArr.push_back(t);
	}

	//dp数组初始化:应该全部初始化为单个直线拟合的罚分，这样在后面的转移方程中就可以直接考虑新建直线导致罚分的了

	for (int i = 0; i < n; i++)
		dp[i][i] = c; //单个结点 因为不与其他结点构成直线，所以也是新出来的直线
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			dp[i][j] = cal(i, j)+c;

	for (int gap = 2; gap < n; gap++)
	{
		//区间跨度 gap = 0,1 已经初始化，这里从 2 开始遍历
		for (int i = 0; i + gap < n; i++)
		{
			//对于以点 i 开始的顶点
			int end = i + gap;  //确定终点
			for (int k = i + 1; k < end; k++)
			{
				//不要在dp内部进行单条罚分计算，不仅会造成大量重复，还会造成数值重置
				dp[i][end] = min(dp[i][end], dp[i][k] + dp[k + 1][end]);
				//一定要注意动态规划问题种初始化与转移方程之间的关系
				// dp[i][j]表示从点 i 到点 j 的最小罚分 则在初始化的时候一定要cal(i,j) + c;
				//在此基础上，转移方程中一定是 其本身 和 dp[i][k] + dp[k + 1][end] 的比较，
				//后者不用 +c，因为 两项分别就是 两个最小罚分，在初始化时已经考虑到了 +c
			}
		}
	}

	cout << fixed << setprecision(2) << dp[0][n - 1];
}
