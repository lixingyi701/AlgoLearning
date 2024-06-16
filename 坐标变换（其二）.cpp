//前缀和->fixed setprecision精度限定
//一开始是把总体的输出长度限定了导致大数的精度较低，所以90
#include<iostream>
#include<algorithm>
#include<vector>
#include<iomanip>
#include <cmath> 
using namespace std;
const int N = 100010;
double k[N];
double theta[N];
int main()
{
	int n, m; cin >> n >> m;

	vector<pair<int, double>> v; 
	//存储操作类型和对应 k/角度
	//vector的下标表示 其在操作序列中的位置

	for (int i = 1; i <= n; i++)
	{
		int type; double op;
		cin >> type >> op;
		v.push_back({ type,op });//从 0 开始计数
	}

	//计算前缀和，首先初始化
	k[0] = 1.0, theta[0] = 0.0;
	for (int i = 0; i < v.size(); i++)
	{
		pair<int,double> temp = v[i];
		if (temp.first == 1)
		{
			k[i + 1] = k[i] * temp.second;
			theta[i + 1] = theta[i];
		}
		else
		{
			k[i + 1] = k[i];
			theta[i + 1] = theta[i] + temp.second;
		}
	}


	for (int t = 1; t <= m; t++)
	{
		int i,j; double x, y;
		cin >> i >> j >> x >> y;
		double beishu = k[j]/k[i-1]; double jiaodu = theta[j]-theta[i-1];

		double resX, resY;
		x *= beishu; y *= beishu;
		resX = x * cos(jiaodu) - y * sin(jiaodu);
		resY = x * sin(jiaodu) + y * cos(jiaodu);
		
		cout << fixed<< setprecision(4) << resX << " " << resY << endl;
	}
}

//基础算法（80）
#include<iostream>
#include<algorithm>
#include<vector>
#include<iomanip>

#include <math.h> 
using namespace std;
int main()
{
	int n, m; cin >> n >> m;

	vector<pair<int, double>>v; 
	//存储操作类型和对应 k/角度
	//vector的下标表示 其在操作序列中的位置

	for (int i = 1; i <= n; i++)
	{
		int type; double op;
		cin >> type >> op;
		v.push_back({ type,op });//从 0 开始计数
	}

	for (int t = 1; t <= m; t++)
	{
		int i,j; double x, y;
		cin >> i >> j >> x >> y;
		double k = 1.0; double theta = 0.0;
		for (int p = i - 1; p <= j - 1; p++)
		{
			pair<int, double> temp = v[p];
			if (temp.first == 1) 
				k *= temp.second;
			else 
				theta += temp.second;
		}
		//统计出操作部分的放缩倍数和旋转角度
		//先旋转后放缩
		double resX, resY;

		resX = x * cos(theta) - y * sin(theta);
		resY = x * sin(theta) + y * cos(theta);
		//应该用之前的坐标算，之前y用了更新后的坐标
		resX *= k; resY *= k;
		cout << setprecision(10) << resX << " " << resY << endl;
	}
}