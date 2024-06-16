#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
//LDAP 原子表达式与复杂表达式 集合交集并集
const int N = 2510, M = 510;
int n, m;//用户的个数 属性的个数
//思路：因为 Expr 有交并两种情况，不能通过vector适当存储，
//我们最后采用 每个 user 遍历一遍表达式树 来获取答案
//正当的来想，这种遍历是必要的，同时比前一种方法好
//wrong answer 有不符合要求的混进来了
struct user
{
	int id;
	map<int,int>s; //属性编号 值
}users[N];

struct base_expr
{
	int attr;
	int num;
	bool b; //1 为需要相等 0 为不等
	
};
map<string, base_expr>atom_map;//通过 string 映射，不用重复计算，应该只放原子级的
				
bool atom(user u,string s)
{
	//判断对于user u,是否满足 由 s 表达的base_expr
	if (atom_map.count(s))
	{
		base_expr res = atom_map[s];
		int a = res.attr, b = res.num;bool c = res.b;//属性、值、是否需要和该值相等

		//如果该字符串之前处理过，直接进入对user的检验
		if (u.s.count(a)) //如果存在该属性
		{
			if (u.s[a] == b && c) //如果该属性值 和原子表达式值相等 且 要求相等
				return true;
			if (u.s[a] != b && !c) //如果该属性值 和 原子表达式值 不相等 且 要求不相等
				return true;
		}
		return false;
	}

	bool match = true;
	int index = 0;
	if (s.find(":") == string::npos)
	{
		match = false;
		index = s.find("~");
	}
	else index = s.find(":");
	//因此从 0 到 index-1 是attr, 从index+1 到 s.size()-1 是 num:
	string attrs = s.substr(0, index);
	string nums = s.substr(index + 1, s.size() - (index + 1));
	base_expr res;
	res.attr= atoi(attrs.c_str()) ;
	res.num=atoi(nums.c_str());
	res.b = match;
	atom_map[s] = res;//记录进map中，记忆化
	
	//下面进行 base_expr 对user的检验
	int a = res.attr, b = res.num ; bool  c = res.b;//属性、值、是否需要和该值相等
	if (u.s.count(a)) //如果存在该属性
	{
		if (u.s[a] == b && c) //如果该属性值 和原子表达式值相等 且 要求相等
			return true;
		if (u.s[a] != b && !c) //如果该属性值 和 原子表达式值 不相等 且 要求不相等
			return true;
	}
	return false;

}
bool judge(user u,string s) //对 user u 进行 expr 判断
{
	//这里也是，会重复分割总表达式，需要遍历strlen(s)
	//如果是原子，进入atom调用，如果是非原子，通过两个 Expr 得到一个新 Expr
	if (s[0] != '&' && s[0] != '|')
	{
		//首字母不是 logic:
		bool res = atom(u,s);
		return res;
	}
	else
	{
		//先获取 logic ="&" / "|",在获取括号内的两个 string,递归调用 返回两个vector<int>
		//通过logic 符号确定对两个判断做 && /||
		//eg:&(1:2)(2:3)
		bool flag = (s[0] == '&') ? 1 : 0; // flag =1 两个条件都要符合 交集

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

		bool r1 = judge(u,expr1);
		if (r1 == false && flag)
			return false; //剪枝：该情况不用判断另一个子树，直接返回false

		bool r2 = judge(u,expr2);
		if (r2 == false && flag) return false;//如果为 false 两个条件都不符合，否则返回true

		return true;
	}
}
int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int t; cin >> t;
		users[i].id = t;
		int cnt; cin >> cnt;
		for (int i = 0; i < cnt; i++)
		{
			int name, val; cin >> name >> val;
			users[i].s[name] = val;
		}
	}
	int optime; cin >> optime;
	for (int j = 0; j < optime; j++)
	{
		string s; cin >> s;
		vector<int>res;
		for (int i = 0; i < n; i++)
		{
			if (judge(users[i], s))
				res.push_back(users[i].id);
		}
		sort(res.begin(), res.end());
		for (auto i : res)
			cout << i << " ";
		cout << endl;
	}
}