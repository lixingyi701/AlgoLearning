//这里有个错误，没有考虑子树里的边，导致同级比较的时候错误
int dfs(int root)
{
	//两个参数分别为 根节点 层级
	//一开始层级是 0，表示需要经过 0 条边就能到达 根结点
	//随着 dfs 在树中的深入，level 逐渐递增，表示经过 level 条边能到达根节点

	node* t = v[root]; 
	int res = t->weight;
	t->visited = true;
	vector<pair<int,int>> dparr; //存储 (dp值，子节点编号) pair
	for(auto i:t->childs)
		if (!v[i]->visited)
		{
			//如果有叶子节点的话
			dparr.push_back({ dfs(i),i });
		}
	if (dparr.empty())
	{
		//如果没有子节点，直接返回
		return res;
	}
	else
	{
		sort(dparr.begin(), dparr.end());
		reverse(dparr.begin(), dparr.end());
		//从大到小得到 dparr 数组 (或正常sort后reverse(v.begin().v,end())
		int m = -1;
		for (int i = 0; i < dparr.size(); i++)
		{
			pair<int, int>&p = dparr[i];
			p.first += i * 2  + 1;//关键错误
			m = max(m, p.first);//加上路径权重后获取最大值
		}
		m = max(m,res);
		return m;
	}
}

