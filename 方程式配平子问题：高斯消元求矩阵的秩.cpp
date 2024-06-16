#include<bits/stdc++.h>
using namespace std;
//使用高斯消元法求矩阵的秩
//从首行开始遍历，如果主元存在，正常消元
//如果主元不存在，遍历寻找其下行同列元素，找到非零元素则置换两行
//以此类推，运算结束后检查主对角线元素，非零元素个数即为秩的个数
int n, m;
vector<vector<double>>v;
#define eps 1e-5;
void print()
{
	for (auto i : v)
	{
		for (auto j : i)
			cout << j << " ";
		cout << endl;
	}
	cout << endl;
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		vector<double>t;
		for (int j = 0; j < m; j++)
		{
			double temp; cin >> temp;
			t.push_back(temp);
		}
		v.push_back(t);
	}
	cout << endl;
	//print();

	int col = 0;
	for (int line = 0; line < n; )
	{
		if (v[line][col] != 0)
		{
			//如果主元不为0，直接消元
			
			for (int neline = line + 1; neline < n; neline++)
			{
				double factor = v[neline][col]/ v[line][col]  ;
				//削减因子为 以下行同列元素 除以 主元，保证减法后该列全为0
				for (int j = col; j < m; j++)				
					v[neline][j] -= v[line][j] * factor;
			}
			//顺利完成，目标行列往后移动
			line++,col++;
		}
		else
		{
			//该行主元为0，需要找其他行替换
			bool find = false;
			for (int neline = line + 1; neline < n; neline++)
			{
				if (v[neline][col] != 0)
				{
					//找到非零行，替换
					swap(v[line],v[neline]);
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
		if (col >= m)
			break;
	}

	print();

	//消元完成，检查主对角线元素确定秩
	int rank = 0;
	for (int line = 0; line < n; line++)
		if (line < m)
		{
			if (v[line][line] != 0)
				rank++;
		}
		else break;
	cout << rank << endl;
}