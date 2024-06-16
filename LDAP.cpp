#include<bits/stdc++.h>
using namespace std;
//LDAP 原子表达式与复杂表达式 集合交集并集
const int N = 2510, M = 510;
int n, m;//用户的个数 属性的个数
vector<map<int, int>>user; //下标索引用户 ，map 用来映射 属性编号和值
vector<int>t; //t[i]表示在 user 中索引为 i 的用户真实编号
/*
纯模拟 40分 TLE 把vector换成set还是不好使
最简单的思路，对每个条件让每个用户都去判断，符合放入vector
对于非原子表达式，通过vector的交并运算得到符合的用户vector
*/

//记忆化：有可能一些原子表达式之前处理过，但是每次都要新调用
//这次我们用 映射记忆下来

//B3 modify 3
map<string, vector<int> >memory;//不好使

//对于一个原子表达式来说，如果它保留的是真正的要求而不是符合的用户列表，应该更好一点
vector<int>atom(string s)
{
	if (memory.count(s))
		return memory[s];
	//原子表达式，只需要处理 BASE_EXPR 中的 OPERATOR ：":" / "~"
	//返回 user 中符合条件的 用户
	int attr = 0; int num = 0;// 接收 BASE_EXPR 中的 属性 和 值 
	bool match = true;
	int index = 0;
	if (s.find(":") == string::npos)
	{
		match = false;
		index = s.find("~");
	}
	else index = s.find(":");
	//因此从 0 到 index-1 是attr, 从index+1 到 s.size()-1 是 num:
	string attrs = s.substr(0, index); //s.substr(start_index,length)
	string nums = s.substr(index + 1, s.size() - (index + 1));
	attr = atoi(attrs.c_str());
	num = atoi(nums.c_str());
	vector<int>res;
	if (match)
	{
		//如果 op = : 该属性存在且值相等
		for (int i = 0; i < user.size(); i++)
		{
			//这个循环让每个用户都被这个原子表达式判断过了
			//因而，对于所有原子表达式都让所有用户遍历一遍，显然复杂度较高
			map<int, int>t = user[i];
			if (t.count(attr) && t[attr] == num)
				res.push_back(i);
		}
	}
	else
	{
		//如果 op = ~ 该属性存在且 值不相等
		for (int i = 0; i < user.size(); i++)
		{
			map<int, int>t = user[i];
			if (t.count(attr) && t[attr] != num)
				res.push_back(i);
		}
	}
	memory[s]=res;
	return res;
}

vector<int>expr(string s)
{
	//一般表达式：如果开头不是 LOGIC =  "&" / "|" 则转入原子表达式
	//否则分别获取 logic ,expr1 和 expr2 
	if (s[0] != '&' && s[0] != '|')
	{
		//首字母不是 logic:
		vector<int>t = atom(s);
		return t;
	}
	else
	{
		//先获取 logic ="&" / "|",在获取括号内的两个 string,递归调用 返回两个vector<int>
		//通过logic符号确定对两个向量求并交
		//eg:&(1:2)(2:3)
		bool u = (s[0] == '&') ? 1 : 0; // u=1 两个条件都要符合 交集

		//需要得到里面两个 expr 的位置，怎么找括号（关键）
		int grade = 0; int index = 1;
		for (; index < s.size(); index++)
		{
			if (s[index] == '(')
				grade++;
			if (s[index] == ')')
				grade--;
			if (grade == 0)
				break;
		}
		//我们知道 expr1 的前括号一定是 s[1] ，通过上述循环找到 expr1 的尾括号 下标为 index
		//则 expr1:2--(index-1)    expr2:index+2--(s.size()-2)
		string expr1 = s.substr(2, index - 2);
		string expr2 = s.substr(index + 2, (s.size() - 2) - (index + 2) + 1);
		vector<int>v1 = expr(expr1);
		vector<int>v2 = expr(expr2);
		vector<int> res;

		if (u)
		{
			//求v1,v2的交集
			set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), inserter(res, res.begin()));
		}
		else {
			//求v1,v2的并集
			set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), inserter(res, res.begin()));
		}
		return res;
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int id; cin >> id;
		t.push_back(id);
		int cnt; cin >> cnt;
		map<int, int>m;
		for (int i = 0; i < cnt; i++)
		{
			int num, val; //属性编号 和 值
			cin >> num >> val;
			m[num] = val;
		}
		user.push_back(m);
	}
	int optime; cin >> optime;
	for (int i = 0; i < optime; i++)
	{
		string s; cin >> s;
		vector<int>r = expr(s);
		vector<int>res;
		for (int i = 0; i < r.size(); i++)
			res.push_back(t[r[i]]); //r[i]表示符合要求的用户在 user 中的索引 没排序
		sort(res.begin(), res.end());
		for (auto i : res)
			cout << i << " ";
		cout << endl;
	}
}