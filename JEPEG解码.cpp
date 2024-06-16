#include<bits/stdc++.h>
using namespace std;
//大模拟 读入数据 数学库调用
//C4 modify 1
int q[8][8];
int m[8][8];
double cosm[8][8];

//一开始想通过按顺序切换方向移动，但是发现 走势只有阶段性周期 
//把 移动序列 记录在数组中， 共有 63 个
void print_int(int name[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << name[i][j] << " ";
		if(i!=7)
			cout << endl;
	}
}
//void mul(int m[8][8], int q[8][8] )
//二维数组乘法函数怎么不好使
int main()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			cin >> q[i][j];
	int cnt; cin >> cnt;
	int mission; cin >> mission;
	//方向走势：右 左下 下 右上 ；右 左下 下 右上 ；右 左下 下 右上 ；右 左下 ；
	//			右 右上 下 左下；  右 右上 下 左下；  右 右上 下 左下；右 
	//读入扫描矩阵  dir直接记录每次的移动方向
	vector<pair<int, int>>dir = 
	{	{0,1} ,{1,-1},  {1,0},  {-1,1},{-1,1}, //右 左下 下 右上
		{0,1} , {1,-1},{1,-1},{1,-1},   {1,0},  {-1,1},{-1,1},{-1,1},{-1,1}, //右 左下 下 右上
		{0,1} , {1,-1},{1,-1},{1,-1},{1,-1},{1,-1},  {1,0}, {-1,1},{-1,1},{-1,1},{-1,1},{-1,1},{-1,1},//右 左下 下 右上
		{0,1} , {1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},//右 左下 ；
		{0,1} ,  {-1,1},{-1,1},{-1,1},{-1,1},{-1,1},{-1,1},   {1,0},  {1,-1},{1,-1},{1,-1},{1,-1},{1,-1},//右 右上 下 左下；
		{0,1} ,  {-1,1},{-1,1},{-1,1},{-1,1},    {1,0},   {1,-1},{1,-1},{1,-1},//右 右上 下 左下；
		{0,1} ,  {-1,1},{-1,1},   {1,0},   {1,-1},				//右 右上 下 左下；
		{0,1} , //右
        //可以看到 对角线 的移动次数为 1-2-3-4-5-6-7-6-5-4-3-2-1
	};
	//cout << dir.size(); 63 没问题
	pair<int, int>xy = { 0,0 };
	int index = 0;
	for (int i = 0; i < cnt; i++)
	{
		int scan; cin >> scan;
		//cout << xy.first << " "  << xy.second << endl;
		m[xy.first][xy.second] = scan;
		bool inrange = true;

		xy.first += dir[index].first;
		xy.second += dir[index].second;
		
		index++;
	}

	if (mission ==0)
	{
		print_int(m);
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			m[i][j] *= q[i][j];
	if (mission == 1)
	{
		//将矩阵 M 中的每个元素都乘以量化矩阵 Q 中的对应元素
		
		print_int(m);
	}
	if (mission == 2)
	{
		//对 m 进行离散余弦变换
		double pi = acos(-1);
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				cosm[i][j] = 0.0;
				for (int u = 0; u < 8; u++)
				{
					double alpha_u = ((u == 0) ? sqrt(0.5) : 1);
					double t1 = pi * (i + 0.5) * u / 8.0;
					double cos1 = cos(t1);
					for (int v = 0; v < 8; v++)
					{
						double alpha_v = ((v == 0) ? sqrt(0.5) : 1);
						//为什么sqrt(0.5)就好使，sqrt(1/2)就不行
						
						double t2 = pi * (j + 0.5) * v / 8.0;
						double cos2 = cos(t2);

						cosm[i][j] += 0.25 * alpha_u * alpha_v * double(m[u][v]) * cos1 * cos2;
					}
					
				}
			}
		
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cosm[i][j] += 128;
				cosm[i][j] = round(cosm[i][j]);
				if (cosm[i][j] > 255)
					cosm[i][j] = 255;
				else if (cosm[i][j] < 0)
					cosm[i][j] = 0;
				cout << cosm[i][j] << " ";
			}
			if(i!=7)
				cout << endl;
		}
	}

}