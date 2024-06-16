#include<bits/stdc++.h>
using namespace std;
//大模拟 读入数据 数学库调用
//错误：填入蛇形数组的时候没有看清真正的走势
//原因：测试样例 填入蛇形数组的时候 没有填满
//其他模块正确
int q[8][8];
int m[8][8];
double cosm[8][8];
void print_int(int name[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << name[i][j] << " ";
        cout << endl;
    }
}
//void mul(int m[8][8], int q[8][8] )
//二维数组乘法函数怎么不好使
int main()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            cin >> q[i][j];
    int cnt; cin >> cnt;
    int mission; cin >> mission;
    //读入扫描矩阵 
    vector<pair<int, int>>dir = { {0,1} ,{1,-1},{1,0},{-1,1} };
    //方向走势：右 左下 下 右上 
    // 右 下 每次走一格
    //其中 左下 右上 （下标为 1 3 ）每次都走一格 下次还要走该方向 直到不能走为止
    pair<int, int>xy = { 0,0 };
    int dir_index = 0;
    for (int i = 0; i < cnt; i++)
    {
        int scan; cin >> scan;
        m[xy.first][xy.second] = scan;
        bool inrange = true;
        if (xy.first + dir[dir_index].first >= 0 && xy.first + dir[dir_index].first < 8
            && xy.second + dir[dir_index].second >= 0 && xy.second + dir[dir_index].second < 8)
        {
            //如果在界内
            xy.first += dir[dir_index].first;
            xy.second += dir[dir_index].second;
        }
        else inrange = false;

        if (dir_index % 2 == 0)
        {
            //如果是 右 下 的话 走完一定在界内【错误】
            dir_index = (dir_index + 1) % 4;
        }
        if (!inrange)
        {
            //如果是 左下 右上 的话，走完可能在界内，也可能在界外
            //但是如果在界外 就需要切换到下一个方向（右 下 ）
            dir_index = (dir_index + 1) % 4;
            xy.first += dir[dir_index].first;
            xy.second += dir[dir_index].second;
            dir_index = (dir_index + 1) % 4;// 右 下 走完一步立刻切方向
        }

    }
    if (mission ==0)
    {
        print_int(q);
    }
    if (mission == 1)
    {
        //将矩阵 M 中的每个元素都乘以量化矩阵 Q 中的对应元素
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                m[i][j] *= q[i][j];
        print_int(m);
    }
    if (mission == 2)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                m[i][j] *= q[i][j];
        //对 m 进行离散余弦变换
        double pi = acos(-1);
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                cosm[i][j] = 0.0;
                for (int u = 0; u < 8; u++)
                {
                    double alpha_u = ((u == 0) ? sqrt(0.5) : 1);
                    double t1 = pi * (i + 0.5) * u / 8.0;
                    double cos1 = cos(t1);
                    for (int v = 0; v < 8; v++)
                    {
                        double alpha_v = ((v == 0) ? sqrt(0.5) : 1);
                        //为什么sqrt(0.5)就好使，sqrt(1/2)就不行
                        
                        double t2 = pi * (j + 0.5) * v / 8.0;
                        double cos2 = cos(t2);

                        cosm[i][j] += 0.25 * alpha_u * alpha_v * double(m[u][v]) * cos1 * cos2;
                    }
                    
                }
            }
        
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cosm[i][j] += 128;
                cosm[i][j] = round(cosm[i][j]);
                if (cosm[i][j] > 255)
                    cosm[i][j] = 255;
                else if (cosm[i][j] < 0)
                    cosm[i][j] = 0;
                cout << cosm[i][j] << " ";
            }
            cout << endl;
        }
    }

}
