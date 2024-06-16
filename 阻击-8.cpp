#include<bits/stdc++.h>
using namespace std;
//阻击 8分 实现的不是标准的树型dp 对每个结点都 dfs 相当于暴力

const int N = 1e5 + 10, M = 1e5 + 10;
int n, m;//城市数 和 修改次数

struct path
{
	int id;
	int s, e;   //起点，终点
	long long loss, earn; //损失、收益
	bool visited;
}p[N];
map<int, vector<int>>pmap; //记录以 pmap.first 为起点的 边的id（如果是边的话不能和path数组同步）
long long dfs(int root)
{
	//深度搜索 得到 以 结点 i 为起点的所有路径中，损失最大的
	long long r = 0;
	vector<int> v = pmap[root]; 
	for (auto i : v)
		if (!p[i].visited)
		{
			p[i].visited = true;
			if (root == p[i].e)
				r = max(r, p[i].loss - p[i].earn + dfs(p[i].s));
			else // root == i.s
				r = max( r, p[i].loss -p[i].earn + dfs(p[i].e));
		}
	//如果都是收益大于损失，最后会返回 r = 0
	return r;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i < n; i++)
	{
		//有 n-1 条边,索引从 1到 n-1
		p[i].id = i;
		cin >> p[i].s >> p[i].e;       // 起点、终点
		cin >> p[i].earn >> p[i].loss; // 收益、损失
		p[i].visited = false;
		pmap[p[i].s].push_back(i);
		pmap[p[i].e].push_back(i);

	}
	long long res = -1;
	for (int i = 1; i <= n; i++)
	{
		res = max(res,dfs(i));
		for (int j = 1; j <= n; j++)
			p[j].visited = false;
	}
	cout << res << endl;
    //复杂度 m*n*n 太高了
	while (m--)
	{
		int num, c;
		cin >> num >> c;
		p[num].earn = c;
		long long res = -1;
		for (int i = 1; i <= n; i++)
		{
			res = max(res, dfs(i));
			for (int j = 1; j <= n; j++)
				p[j].visited = false;
		}
		cout << res << endl;
	}
}