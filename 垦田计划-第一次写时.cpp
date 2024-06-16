//满分，排序后操作
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<limits>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int, int>>v;
bool compare(pair<int,int> a, pair<int,int> b)
{
	return a.first > b.first;
}

int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		int t, c;
		scanf("%d %d", &t, &c);
		v.push_back({ t,c });
	}
	sort(v.begin(), v.end(), compare);

	//按花费时间从大到小排序
	int s = v.size();
	int mint = v[s - 1].first;//保存最短时间
	int maxt = v[0].first;
	long long costSum = 0;//将所有区域的开垦耗时统一的cost
	long long cost_for_one = 0;
	for (int i = 0; i < s; i++)
	{
		costSum += (v[i].first - mint) * v[i].second;
		cost_for_one += v[i].second; //O(N)
	}
	if (costSum <= m)
	{
		//统一消耗小于等于总消耗，说明资源足够统一到最短天数
		long long leftcost = m - costSum;
		if (leftcost == 0)
			cout << mint;

		int day = leftcost / cost_for_one;//还能减少的天数
		if (mint - day <= k)
			cout << k;
		else cout << mint - day;
	}
	else
	{
		//按排序，时间依次递减
		int day = maxt;
		int i = 0;
		while(1)
		{
			if (v[i].first == day)
			{
				if (m - v[i].second < 0)
					break;//减完之后大于等于0才能减

				m -= v[i].second;
				v[i].first -= 1;
				i++;
 			}
			else
			{
				//v[i].first != day,需要将 day 递减 并 将 i 重新赋值为 0
				day--;
				i = 0;
			}
		}
		int maxt = - 1;
		for (int i = 0; i < n; i++)
			maxt = max(maxt, v[i].first);
		cout << maxt;
	}



}


//1.超时，70分
#include<iostream>
#include<cmath>
#include<limits>
#include<algorithm>
using namespace std;
const int N = 100010;
long long t[N];//耗时
long long c[N];//缩短1天所需资源数


int main()
{
	//子问题1：使用一部分资源，将所有区域的开垦耗时统一到输入中的最短耗时
	//如果资源不够用，需要再求一遍 最短耗时
	//如果资源够用，之后根据缩短一天消耗资源综合和k值限定继续求解
	int n, m, k; 
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &t[i], &c[i]);
	}

	long long mint = INT_MAX;
	for (int i = 1; i <= n; i++)
	{
		mint = min(mint, t[i]);
	}//找到区域中最短耗时,    O(N)

	long long costSum = 0;//将所有区域的开垦耗时统一的cost
	long long cost_for_one = 0;
	for (int i = 1; i <= n; i++)
	{
		costSum += (t[i] - mint) * c[i];
		cost_for_one += c[i]; //O(N)
	}
	if (costSum <= m)
	{
		//统一消耗小于等于总消耗，说明资源足够统一到最短天数
		long long leftcost = m - costSum;
		if (leftcost == 0) 
			cout << mint;

		int day = leftcost / cost_for_one;//还能减少的天数
		if (mint - day <= k)
			cout << k;
		else cout << mint - day;
	}
	else 
	{
		//costSum > m  说明资源不够统一到最短天数
		//第一种办法，尝试天数，复杂度较高
		for (int day = mint + 1; ; day++)
		{
			//因为不能统一到 mint ,所以试着统一到 mint+1 或者更大
			long long sum = 0;
			for (int i = 1; i <= n; i++)
			{
				if (t[i] <= day)
					continue;
				else
					sum += (t[i] - day)* c[i];
			}
			if (sum <= m)
			{
				cout << day;
				break;
			}
		}//需要减少复杂度
	
		//第二种办法，（建最大堆），从最大时长开始逐天减少 但是时长也不理想
	
		//final:排序，然后易如反掌



	}
}