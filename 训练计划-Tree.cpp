#include<bits/stdc++.h>
using namespace std;
//训练计划：建树、遍历
//一定要先想数据结构 不要着急上手
//报错1 没考虑 题目索引[1 -m] 和vector的 0 base
//报错2 问[第几天]真是恶心
class subject {
public:
	int id;
	int cost;
	int e;
	int l;
	bool flag;
	vector<int>childs;//存放依赖该科目的其他科目
	subject(int i) { id = i; e = 1; flag = false; };
};

const int N = 370, M = 110;
int n,m; //n天内完成所有训练 m 科目数量
vector<subject>v;

void early(int root)
{
	//找出 结点 root 的 最早开始时间
	//因为 满足 依赖科目的编号 小于自己，所以处理自己和 自己的子树 即可
	for (auto i:v[root].childs)
	{
		v[i].e = v[root].e + v[root].cost;
		//子树的最早开始时间 = 父节点的最早开始时间 + 父节点 cost
	}
}

int late(int root)
{
	//深度搜索 得到 root 的最晚开始时间
	//因为父节点是被依赖的，最晚开始该科目的时间 取决于 子节点的 最晚开始时间 和 子节点cost
	if (v[root].flag)
		return v[root].l;
	if (v[root].childs.empty())
	{
		//如果不被依赖
		v[root].l = n - v[root].cost ;
		v[root].flag = true; //flag 保证根节点不被 重复计算 导致错误
		return v[root].l;
	}
	int res = n;
	for (auto i : v[root].childs)
	{
		int t = late(i);
		res = min(res, t);
	}
	v[root].l = res - v[root].cost ;
	v[root].flag = true;
	return v[root].l;
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i <= m; i++)
	{
		v.push_back(subject(i));//下标从1-n,v[0]为填充
		v[i].l = n;
	}
	
	for (int i = 1; i <= m; i++)
	{
		int t; cin >> t;
		if (t != 0)
			v[t].childs.push_back(i);
	}
	for (int i = 1; i <= m; i++)
		cin >> v[i].cost;
		
	//分别求出 最早开始时间 和 最晚开始时间
	for (int i = 1; i <= m; i++)
	{
		early(i);
		late(i);
	}

	for (int i = 1; i <= m; i++)
		cout << v[i].e << " ";
	bool c = true;
	for (int i = 1; i <= m; i++)
		if (v[i].l < 1)
			c = false;//因为最晚开始时间最少是 第一天 如果小于说明不存在
	if (c)
	{
		cout << endl;
		for (int i = 1; i <= m; i++)
			cout << v[i].l + 1 << " ";//[第几天]真是恶心，把消耗的所有天数减去后加上1 因为这天也干活了
	}
}