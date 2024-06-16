#include<bits/stdc++.h>
using namespace std;
//使用 dfs 对树进行深搜，返回值记录并求出最大值
//未作出
const int N = 1e5 * 5 + 10;
int n;
class node
{
public:
	int id;
	bool visited;
	int weight;
	vector<int>childs; //邻接结点，通过 visited判断是根节点还是子节点
	int edges;//以该节点为根的子树一共有多少条边
	node(int i) {
		id = i;
	}
};
vector<node*>v;

//以 v[1]为根节点，开始 dfs
//更新思路如下：
//如果该节点为叶子节点，直接返回自身的 weight 值
//否则，遍历其子节点，调用 dfs() 返回 以其子节点为根的子树总消耗最小时间
// （这里这个返回值需要做优化或者补充，不然后面会很难处理）
//对消耗时间从大到小排序，走边时先走高消耗的边再走低消耗的边，
//以达到所有中最大值最小
//考虑走边的消耗：最高时间子树 + 1，次高 + 3，以此类推（该想法是错误的）
//处理完该数组后选出其中最大值，加上该节点本身的 weight 返回
//考虑子树经过边的数量
int dfs(int root,int &edge)
{
	node* t = v[root];
	int res = t->weight;
	t->visited = true;
	vector<pair<int,int> >subtrees; //记录各个子树的权值 和 边

	for (auto i : t->childs)
		if (!v[i]->visited)
		{
			//如果有叶子节点的话
			int e = 0;
			int w = dfs(i, e);
			subtrees.push_back({w,e});
		}
	if (subtrees.empty())
	{
		//如果没有子节点，直接返回
		edge = 0;
		return res;
	}
	else
	{
		for (auto i : subtrees)
			edge += i.second;// 获得 以root为根 的子树边数
		//根据subtree中各个子树的 最长时间 和 边数 确定遍历的顺序
		//在计算先走哪个子树的时候非常复杂，不是简单的  i * 2  + 1;
	}



}
int main() 
{
	cin >> n;
	v.push_back(new node(0));
	for (int i = 1; i <= n; i++)
	{
		v.push_back(new node(i));
		int t; cin >> t;
		v[i]->weight = t;
	}
	for (int i = 1; i < n; i++)
	{
		int x, y; cin >> x >> y;
		v[x]->childs.push_back(y);
		v[y]->childs.push_back(x); //建立无向边
	}

	int edge = 0;
	// 2 * (n - 1) + v[1]->weight 表示 最后回到自己家安装软件 的总时间
	cout << max(dfs(1, edge), 2 * (n - 1) + v[1]->weight);
}