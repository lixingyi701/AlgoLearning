#include<bits/stdc++.h>
using namespace std;
/*
老朋友，树上搜索
60分 后来加了个记忆化搜索没啥效果 (可能没有抵消,dfs消耗太大)
发现dfs 不用每次都走，在删掉某个子树后 可以往父节点遍历更新，删掉其他部分 可以改变根节点
这两种操作 避免了每次的dfs(),需要对 Node 类增添 father 成员
但是没改对啊，还多错了一个，逆天
*/
const int N = 2010, M = 110;
int n, m;//结点个数	测试类别个数
class Node
{
public:
	int id;
	long long w;
	long long total;//本结点 和其全部后代类别 权重之和
	bool vaild;//是否被删掉
	vector<int>childs;
	Node(int i) { id = i; vaild = true; total = 0; }
};
vector<Node>v;
//记忆二叉树：从第1次询问相同结点开始，之后每次询问只有yes no导致不同的删除方式
//感觉应该挺有用，但是一点效果都没有
class memory {
public:
	int p; //选择的点
	memory* left; //在子树内，yes
	memory* right; //不在,out
	memory() { p = -1, left = right = NULL; }
};

int dfs(Node &root)
{
	if (!root.vaild)
		return 0; //被删除
	long long& r = root.total;//引用竟然不好使？因为函数参数传的不是引用
	r = root.w;
	if (root.childs.empty())
		return r;
	for (auto i : root.childs)
	{
		if (v[i].vaild)
			r += dfs(v[i]);
	}
	return r;
	// dfs 返回以 root 为根的子树的权重之和
}

pair<int,int> quest(Node root, int all) //return (abs_min,index)
{
	//在获得以 root 为根的子树的全体节点的权重 和 全部结点的权重和 all 后
	//遍历树得到需要询问的结点（可以选择循环或者dfs,dfs能剪枝）
	if (root.vaild)
	{
		long long& r = root.total;
		if (2 * r - all < 0)
		{
			//随着子树权值由大变小， 2 * r - all 从大于 0 变为小于 0
			//因而其绝对值先变小后变大
			//对于一个节点来说，如果其 2 * r - all小于 0，则其子树没有必要计算
			//这时只需要返回它的 abs( 2 * r - all)即可
			return { abs(2 * r - all),root.id };
		}

		int res = abs(2 * r - all);
		int index = root.id;
		for (auto i : root.childs)
		{
			//对于其子树来说：
			pair<int, int> p = quest(v[i], all);
			if (p.first < res)
			{
				res = p.first;
				index = p.second;
			}
			else if (p.first == res)
			{
				if(index < p.second)
					continue;
				else
				{
					res = p.first;
					index = p.second;
				}
			}
		}
		return { res,index };
	}
	else return { 0x3f3f3f3f,-1 };

}

bool dfind(int target, int root)
{
	//以 root 为根的子树中找 target,找到返回true
	if (v[root].id == target)
		return true;
	else 
	{
		bool f = false;
		for (auto i : v[root].childs)
		{
			f = dfind(target, i);
			if (f)
				break;
		}
		return f;
	}
}

void del(int root)
{
	v[root].vaild = false;
	if (!v[root].childs.empty())
		for (auto i : v[root].childs)
			del(i);
}

bool check(Node root)
{
	//检查以 root 为根的子树是否只剩一个类别
	for (auto i : root.childs)
		if (v[i].vaild)
			return true;
	return false;
}

int main()
{
	memory* b=new  memory;//起始记忆

	ios::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	v.push_back(Node(0));
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		v.push_back(Node(i));
		cin >> v[i].w;
	}// v下标 1-n
	
	for (int i = 2; i <= n; i++)
	{
		//结点 1 是根节点
		int t; cin >> t;
		v[t].childs.push_back(i);
	}
	for (int i = 0; i < m; i++)
	{
		vector<int>ans;
		int res; cin >> res;
		//输入询问类别后，进入循环
		Node root = v[1];//初始根节点

		memory* walk = b; //在每次询问中更新 b

		while (check(root))
		{
			
			//计算以 root 为根节点的 子树中 各个点权值
			//确定出需要询问的点
			//根据 res 进行判断，如果在询问点所在后代类别，保留->将 root 变为询问点
			//如果不在，删除询问点及其子树，

			int index;
			if (walk->p != -1)
				index = walk->p;
			else
			{
				int all = dfs(root);
				pair<int, int> p = quest(root, all);
				index = p.second;//询问点

				walk->p = index;
			}

			ans.push_back(index);
			bool in = dfind(res, index);

			if (in)
			{
				//保留->将 root 变为询问点
				//这样好像下一轮不用 dfs 更新权值了
				if (walk->left != NULL)
					walk = walk->left;
				else
				{
					memory* temp = new memory;
					walk->left = temp;
					walk = walk->left;
				}
				root = v[index];
			}
			else
			{
				//删除询问点及其子树
				if (walk->right != NULL)
					walk = walk->right;
				else
				{
					memory* temp = new memory;
					walk->right = temp;
					walk = walk->right;
				}
				del(index);
			}
		}
		for (auto t : ans)
			cout << t << " ";
		cout << endl;

		for (int i = 1; i <= n; i++)
		{
			v[i].vaild = true; 
			v[i].total = 0;
		}
		
	}

}