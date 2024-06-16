#include<bits/stdc++.h>
using namespace std;
//星际网络II:字符串处理，链表维护 字符串区间合并【不会】
//字符串比较： "0000ffff"> "00000000"
/*
合并情况：在区间 id 相同情况下：
eg1:0001:8000--0001:ffff 和 0001:c000--0003:ffff 应该合为 0001:8000:0003:ffff ez
eg2:0001:8000--0001:ffff 和 0002:0000--0002:ffff 可以看到 range1.end.next == range2.begin
这种情况也需要合并，但是怎么实现呢（还需要考虑到n数值）
*/
//25分，有 wa 和 tle 不好改啊
class Node
{
public:
	pair<string, string>range;
	int belonger;
	//Node* left;
	//Node* right;
	Node(int id, string a, string b) { belonger = id; range = { a,b }; }
};
int n, q;//地址二进制长度  q次操作
list<Node>l;
int main()
{
	cin >> n >> q;
	for (int i = 0; i < q; i++)
	{
		int opcode; cin >> opcode;
		if (opcode == 1)
		{
			//1 id l r：表示用户 id 申请地址在 l-r 范围内（包含l 和 r，下同）的一段连续地址块。
			//特殊：申请地址 含有 本人之前已申请地址
			int id; cin >> id;
			string b; cin >> b;
			string e; cin >> e;//输入 起始 和 终止 位置
			Node t = {id, b,e };
			if (l.empty())
			{
				l.push_back(t);
				cout << "YES" << endl;
			}
			else
			{
				bool accept = true;
				for (auto i : l)
				{
					string tb = i.range.first;
					string te = i.range.second;
					if (b > te || e < tb)
					{
						//如果申请的 新开始 大于旧的结尾 或者 新结尾 小于 旧的开始
						//完全不重合
						continue;
					}
					else if ( (b<te && e>te) || (b<tb&& e>tb) )
					{
						//申请的新位置与原位置有 交集，但新位置不是 原位置的子集
						//这里有问题：如果不合并区间的话，会导致 3个原区间分别都是新区间的子集
						//但是 3 个原区间本应合并，合并后是新区间的超集
						if (i.belonger == id)
							continue;
						else
							accept = false;
					}
					else {
						//不满足以上两种情况
						//新位置 是 原位置 的子集 直接否决
						accept = false;
					}
				}
				if (accept)
				{
					l.push_back(t);
					cout << "YES" << endl;
				}
				else cout << "NO" << endl;
			}
		}
		else if (opcode == 2)
		{
			//2 s：检查地址 s 被分配给了哪个用户。若未被分配，则结果为 0。
			string s; cin >> s;
			bool accept = false;
			for (auto i : l)
			{
				string tb = i.range.first;
				string te = i.range.second;
				if (s >= tb && s <= te)
				{
					accept = true;
					cout << i.belonger << endl;
					break;
				}
			}
			if (!accept)
				cout << "0" << endl;
		}
		else if (opcode == 3)
		{
			//3 l r：检查 l-r 范围内的所有地址是否完整地分配给了某个用户。若是，回答该用户的编号；若否，回答 0。
			string b; cin >> b;
			string e; cin >> e;
			bool accept = false;
			for (auto i : l)
			{
				string tb = i.range.first;
				string te = i.range.second;
				if (b >= tb && e <= te)
				{
					accept = true;
					cout << i.belonger << endl;
					break;
				}
			}
			if (!accept)
				cout << "0" << endl;
		}
	}
}