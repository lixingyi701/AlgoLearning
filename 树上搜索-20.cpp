//20，简单模拟
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<cstring>
#include<cmath>
#include <climits>
using namespace std;

const int N = 2010;
int father[N], val[N]; long long delta[N];
bool isValid[N]; //如果被去除，则在本轮中置为false;

//father是父亲数组，其中值为自己的父亲下标
//val是权重数组

int h[N], e[N], ne[N];
int idx;//用数组邻接表存储孩子

void setFather(int s, int f)
{
	e[idx] = s; ne[idx] = h[f], h[f] = idx++;
}
vector<int> showSon(int f, bool all)
{
	vector<int>res;
	if (all == false) //只返回 isValid = true 的
	{
		for (int i = h[f]; i != -1; i = ne[i])
			if (isValid[e[i]])
				res.push_back(e[i]);
	}
	else //返回 所有直接相连的子节点
	{
		for (int i = h[f]; i != -1; i = ne[i])
			res.push_back(e[i]);
	}
	return res;
}
vector<int>showFather(int s)
{
	vector<int>res;
	while (father[s] != s)
	{
		if (isValid[father[s]])
		{
			res.push_back(father[s]);
			s = father[s];
		}
		else break;
	}
	return res;
}
//如果有father,返回所有fathers,否则返回空vector


vector<int>allSons(int index)
{
	stack<int>temp;  vector<int>res;
	temp.push(index);
	while (!temp.empty())
	{
		int t = temp.top();
		temp.pop();
		res.push_back(t);
		vector<int>t_child = showSon(t, false);
		if (t_child.empty())
			continue;

		for (auto it = t_child.begin(); it != t_child.end(); it++)
			temp.push(*it);
	}
	return res;
}

int bottom_top(int root)
{
	//从树底部走向树的根节点，算出每个子树的权重总和

	int res = val[root]; //根节点也是有权重的
	vector<int>v = showSon(root, false);
	if (!v.empty())
		for (auto it = v.begin(); it != v.end(); it++)
			res += bottom_top(*it);

	//如果非空，加上他的子树delta值，  如果空说明为叶节点，跳过即可
	delta[root] = res;

	return res;
}

void top_end(int root, int sum)
{
	//从 树顶走向树底，按delta的定义重新计算delta
	vector<int> v = showSon(root, false);
	if (v.empty()) //为空，说明走到了叶节点
		return;
	else
	{
		for (auto it = v.begin(); it != v.end(); it++)
		{
			delta[*it] = abs(2 * delta[*it] - sum);
			top_end(*it, sum);
		}
	}

}

void setInvalid(int index)
{
	//将index及其子树全部设为 isValid= false;
	vector<int> v = showSon(index, false);
	isValid[index] = false;
	if (v.empty())
		return;
	else
		for (auto it = v.begin(); it != v.end(); it++)
			setInvalid(*it);
}



int main()
{
	int n, m; cin >> n >> m;

	memset(isValid, 1, sizeof isValid);
	memset(h, -1, sizeof h);

	for (int i = 1; i <= n; i++)
		cin >> val[i];

	father[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		cin >> father[i];
		setFather(i, father[i]);
	}


	while (m--)
	{
		int target; cin >> target;
		vector<int>finalRes;
		while (1)
		{
			//找有效的根节点
			int root = 1;
			if (!isValid[root]) {
				vector<int>sons = showSon(root, true);

				for (auto it = sons.begin(); it != sons.end(); it++) {
					vector<int>v = showSon(*it, true);
					//对于根节点的子节点，如果已被删除，则将其子节点放入vector中
					//如果没被删除，说明它就是 有效的 root
					if (isValid[*it] == false)
					{
						while (!v.empty())
						{
							sons.push_back(v.back());
							v.pop_back();
						}
					}
					else
					{
						//找到一个root之后直接停止
						root = *it;
						break;
					}
				}
			}
			//在每次正确删除后，推理出树的上层每层中只有一个isValid节点，找到他之后

			bottom_top(root);
			//从树底部走向树的根节点，算出每个子树的权重总和（包括它和它的子树）

			int sum = delta[root];
			//全部类别的权重总和 就是 根节点的权重

			top_end(root, sum);
			//计算当前树上的每个节点w_delta值

			int minW = INT_MAX, index = 0;
			for (int i = 1; i <= n; i++)
				if (delta[i] < minW && isValid[i])
				{
					minW = delta[i];//最小值更新
					index = i;
				}

			//在上面，找到minW是什么不重要，重要的是它的下标 index
			finalRes.push_back(index); //记录在最终结果里

			bool isSon = false;
			//看一下target是否在选取的类别
			vector<int>fs = showFather(target);
			if (target == index)
				isSon = true;

			else if (!fs.empty())
				for (auto it = fs.begin(); it != fs.end(); it++)
					if (*it == index)
					{
						isSon = true;
						break;
					}


			//如果 isSon=true 仅保留该类别及其后代类别 根类别的编号为 index
			//否则 仅保留其余类别
			if (isSon)
			{
				vector<int>a = allSons(index);
				//收集到了所有 isValid =true 的子树
				memset(isValid, 0, sizeof isValid);
				for (auto it = a.begin(); it != a.end(); it++)
				{
					isValid[*it] = true;
				}
			}

			else
				setInvalid(index);

			int cnt = 0; 
			for (int i = 1; i <= n; i++)
			{
				if (isValid[i] == true)
					cnt++;
				if (cnt > 1) break;
			}


			if (cnt == 1) //结束
			{
				for (auto it = finalRes.begin(); it != finalRes.end(); it++)
					cout << *it << " ";
				cout << endl;
				memset(isValid, 1, sizeof isValid);//重置Valid数组
				finalRes.clear();
				break;
			}
		}

	}
}