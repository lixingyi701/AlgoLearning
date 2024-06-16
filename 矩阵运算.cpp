//100分 注意二维数组的new初始化操作
//将结果数组用long long存储
//注意n和d的关系，将矩阵往小了算
#include<iostream>
#include<cstring>
using namespace std;

int n, d;

int main()
{
	cin >> n >> d;

	int(*q)[20] = new int[n][20];//n*d

	int** k = new int* [20];
	for (int i = 0; i < 20; ++i) //这里按行遍历，应该是20而非n
		k[i] = new int[n];//d*n

	int(*v)[20] = new int[n][20];//n*d
	int* w = new int[n];

	long long res1[20][20];
	long long ** res2 = new long long * [n];
	for (int i = 0; i < n; i++)
		res2[i] = new long long [d]; //n*d

	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			cin >> q[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			cin >> k[j][i];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			cin >> v[i][j];

	for (int i = 0; i < n; i++)
		cin >> w[i]; 
		//输入结束
	memset(res1,0, sizeof res1);
	for (int i = 0; i < d; i++)
		for (int j = 0; j < d; j++)
			for (int t = 0; t < n; t++)
				res1[i][j] += k[i][t] * v[t][j];
		

	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
		{
			res2[i][j] = 0;
			for (int t = 0; t < d; t++)
				res2[i][j] += q[i][t] * res1[t][j];
		}

		


	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			res2[i][j] *= w[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++)
			cout << res2[i][j] << " ";
		cout << endl;
	}

}


//70分，最基础做法
#include<iostream>
using namespace std;
const int N = 1010;
int q[N][N], k[N][N], v[N][N];
int res[N][N], f[N][N];
int w[N];
int n, d;

int main()
{
	cin >> n >> d;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			cin >> q[i][j];//n*d
	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			cin >> k[j][i];//d*n

	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			cin >> v[i][j];//n*d
	for (int i = 0; i < n; i++)
		cin >> w[i];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int t = 0; t < d; t++)
				res[i][j] += q[i][t] * k[t][j];//n*n

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res[i][j] *= w[i];//n*n

	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			for (int t = 0; t < n; t++)
				f[i][j] += res[i][t] * v[t][j];//n*d

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++)
			cout << f[i][j] << " ";
		cout << endl;
	}
	return 0;
}