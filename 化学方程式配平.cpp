#include<bits/stdc++.h>
using namespace std;
/*
100分：map处理字符串+数学
为了便于程序处理，我们用到的化学式，会被化简为只包含 小写字母 和 数字 的字符串，
不包含括号。 其中连续的字母表示一种元素，随后的数字表示原子个数。
原子个数为 1 时 不省略数字 ；一个化学式中包含的元素不重复。

将化学方程式转化为对应的邻接矩阵：
考虑一个共有 n 种元素，m 个化学物质的化学方程式
将其抽象成一个 n * m 的邻接矩阵，v[i][j]表示第 i 种元素在第 j 个化学物质中的量

每个方程中物质的个数不超过 40,每个方程中涉及的全部元素不超过 40 种；且有
需要判断的化学方程式  1 <= n <= 10
且化学式中各元素的原子个数不超过 50
*/
const int N = 52;
map<string, int>strmap;//元素和其标号之间的映射
double v[N][N];// v[i][j]表示第 i 种元素在第 j 个化学物质中的量
int n; //需要判断的化学方程式的个数

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int len; cin >> len;
		int index = 0;


		for (int col = 0; col < len; col++)
		{
			//读入并处理 每个化学物质，并转化成矩阵的第 col 列
			string t; cin >> t;

			string chem;  //化学元素
			double temp = 0.0; //元素个数,数据类型要和矩阵匹配 两个临时变量

			for (int k = 0; k < t.size(); k++)
			{
				if (t[k] >= 'a' && t[k] <= 'z')
				{
					//如果是字母
					if (temp != 0)
					{
						//不等于0 说明 需要处理前面的化学符号
						if (!strmap.count(chem))
							strmap[chem] = index++;
						v[strmap[chem]][col] = temp; //对矩阵赋值

						chem.clear(), temp = 0;
					}

					chem += t[k];
				}
				else
				{
					//如果是数字
					temp = temp * 10 + (t[k] - '0');
				}
			}
			//结尾是数字，说明得处理最后一个化学符号：
			if (!strmap.count(chem))
				strmap[chem] = index++;
			v[strmap[chem]][col] = temp;
		}

		//for (auto line : strmap)
		//{
		//	for (int col = 0; col < len; col++)
		//		cout << v[line.second][col] << " ";
		//	cout << endl;
		//}
		//cout << endl;

		int rowSum = strmap.size(), colSum = len;
		int col = 0;
		for (int line = 0; line < rowSum; )
		{
			if (v[line][col] != 0)
			{
				//如果主元不为0，直接消元

				for (int neline = line + 1; neline < rowSum; neline++)
				{
					double factor = v[neline][col] / v[line][col];
					//削减因子为 以下行同列元素 除以 主元，保证减法后该列全为0
					for (int j = col; j < colSum; j++)
						v[neline][j] -= v[line][j] * factor;
				}
				//顺利完成，目标行列往后移动
				line++, col++;
			}
			else
			{
				//该行主元为0，需要找其他行替换
				bool find = false;
				for (int neline = line + 1; neline < rowSum; neline++)
				{
					if (v[neline][col] != 0)
					{
						//找到非零行，替换
						swap(v[line], v[neline]);
						find = true;
						break;
					}
				}
				if (!find)
				{
					//如果没找到，说明该列全部为0，只能将目标列后移
					col++;
				}
			}
			if (col >= colSum)
				break;
		}
		//for (int i=0;i<rowSum;i++)
		//{
		//	for (int col = 0; col < colSum; col++)
		//		cout << v[i][col] << " ";
		//	cout << endl;
		//}
		//cout << endl;
		//输出和检查主元时一定要用 v[i][col]遍历而不是 for (auto line : strmap)，不然体现不出排序
		//消元完成，检查主对角线元素确定秩
		int rank = 0;
		for (int line = 0; line < rowSum; line++)
			if (line < colSum)
			{
				if (v[line][line] != 0)
					rank++;
			}
			else break;
		if (rank < len) cout << "Y" << endl;
		else cout << "N" << endl;


		//对每个化学方程式运算后，应该清空 strmap 和 v
		//注意清空的时机
		strmap.clear();
		memset(v, 0, sizeof v);
	}


}
