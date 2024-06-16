#include<bits/stdc++.h>
using namespace std;
const int N = 366, M = 110;
int n, m;//n 天内完成所有训练  训练科目的数量
int depend[M];//如果科目 i 依赖科目 j 则 depend[i]=j; 
int cost[M];//需要天数
bool solved[M]; //已经完成的科目
int early[M], late[M]; //最早结束时间 最晚结束时间
//失败 70 没有数据结构

bool check()
{
	for (int i = 1; i <= m; i++)
		if (solved[i] == false)
			return true;
	return false;
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int t; cin >> t;
		depend[i] = t;
	}
		
	for (int i = 1; i <= m; i++)
		cin >> cost[i];

	for (int i = 1; i <= m; i++)
		early[i] = 1;
	for (int i = 1; i <= m; i++)
		late[i] = n; //late先统计总耗时，在计算最晚开始时间


	while (check())
	{
		for (int i = 1; i <= m; i++)
		{
			//没有考虑到 题中 满足 依赖科目的编号小于自己，外面的while没有用
			if (depend[i] == 0)
			{
				solved[i] = true;//先处理没有依赖的
			}
			else if (solved[depend[i]])
			{
				//depend[i]表示依赖项 如果其已经被处理掉
				early[i] = early[depend[i]] + cost[depend[i]];
				solved[i] = true;
			}
		}
	}
	for (int i = 1; i <= m; i++)
		cout << early[i] << " ";//得到最早开始时间
	cout << endl;

}
