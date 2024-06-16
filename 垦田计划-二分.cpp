//垦田计划：二分
//在acwing上测试的时候得把int改成long long 才能AC，否则超int
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

const int N = 100010;
map<int, int, greater<int>>mp;
int n, m, k;

bool check(int mid)
{
	//判断资源 是否能满足缩减到 mid 天，满足返回true, 不满足返回false
	int res = 0;
	for (auto i : mp)
	{
		if (i.first > mid)
		{
			//如果 耗时 大于 mid,算出减少到 mid 所需要的资源
			res += (i.first - mid)* i.second;
		}
	}
	if (m >= res)
		return true;
	else return false;
}

int main()
{
	cin >> n >> m >> k;

	//map的排序 默认按照 key 从小到大
	//加入第三个参数 greater<int>, 使得 按照key 从大到小
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		if (!mp.count(a))
		{
			mp[a] = b;
		}
		else mp[a] += b;
	} 

	auto i = mp.begin();
	int maxt = (*i).first;

	int mint = k;

	while (mint < maxt)
	{
		int mid = (mint + maxt) / 2;
		bool i = check(mid);
		if (i) maxt = mid;
		else mint=mid+1;
		//这里的单调性是：天数越少，消耗的资源越多
		//所以如果 mid 天资源满足的话，应该 maxt=mid 将下一次的 mid 减少 
	}

	cout << mint;
}