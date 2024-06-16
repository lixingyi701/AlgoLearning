#include<bits/stdc++.h>
using namespace std;
/*
十滴水：离散化 + 链表 + 优先级队列（或递归）
在1 * c的网格内 m 个格子中有 1-4 滴水，其余格子中没有水
c <= 1e9, m <= 3*1e5 说明需要离散化，将有水的格子通过 map 集中并映射
因为在之后的 n 次操作中，每次对原始的 p 格操作，需要映射到 集中后的格子

每次水爆开对其临近左、右格子水滴 +1 ，因此需要把映射后的格子连成链表（用数组模拟）
爆炸处理使用循环，先处理该格子及其左边格子，再处理右边格子
爆炸后也要更新链表，防止影响 [原来有水，现在没水] 的格子
*/
const int N = 3 * 1e5 + 10;
int c, m, n; //网格宽度 有水的格子个数  操作次数
map<int, int>init_water; //原始位置-水滴个数映射
map<int, int>re_vir;//原始位置-虚拟位置映射
priority_queue<int, vector<int>, greater<int>>q; //小值优先，对应先爆左后爆右
struct vit {
	bool used; //标记，防止重复放入优先级队列
	int water; //水滴数
	int l, r;//左右邻接结点
}w[N];//虚拟位置
void print(vit v)
{
	cout << v.water << " " << v.l << " " << v.r << " " <<v.used<< endl;
}
int main()
{
	cin >> c >> m >> n;
	for (int i = 0; i < m; i++)
	{
		int x, w; cin >> x >> w;
		init_water[x] = w;
	}
	int index = 0;
	for (auto i : init_water)
	{
		//map 按照 key 大小映射 直接遍历
		re_vir[i.first] = index; //将 原始位置 映射到 虚拟位置
		w[index].water = i.second;
		w[index].l = index - 1, w[index].r = index + 1;
		index++;
	}
	//for (int i = 0; i < m; i++)
	//	print(w[i]);
	int res = m; //有水的格子初始为 m
	for (int i = 0; i < n; i++)
	{
		int p; cin >> p;//对第 p 格进行操作
		int v = re_vir[p];//原始->虚拟
		w[v].water++;
		if (w[v].water >= 5)
		{
			w[v].used = true;
			q.push(v);
		}
		while (!q.empty())
		{
			int v = q.top();
			q.pop();
			w[v].water = 0;
			res--;
			// 虚拟 v 点 水滴爆开，对其左右邻接结点作用
			int left = w[v].l, right = w[v].r;
			//更新左右邻接结点
			w[left].r = right;
			w[right].l = left;
			if (left >= 0 && w[left].water != 0)
			{
				w[left].water++;
				if (w[left].water >= 5 && !w[left].used) {
					q.push(left);
					w[left].used = true;
				}
				
			}
			if (right < m && w[right].water != 0)
			{
				w[right].water++;
				if (w[right].water >= 5 && !w[right].used) {
					q.push(right);
					w[right].used = true;
				}
			}
		}
		/*for (int i = 0; i < m; i++)
			print(w[i]);*/
		cout << res << endl;
	}
}
