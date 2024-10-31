struct TwoSat
{
	int n;
	vector<vector<int>> e;
	vector<bool> ans;

	TwoSat(int n):n(n),e(n<<1),ans(n){}

	void addClause(int u,bool f,int v,bool g)
	{
		e[u*2+!f].push_back(v*2+g);
		e[v*2+!g].push_back(u*2+f);
	}

	bool satisfiable()
	{
		vector<int> id(n*2,-1),dfn(n*2,-1),low(n*2,-1),stk;
		int now=0,cnt=0;
		function<void(int)> tarjan=[&](int u)
		{
			stk.push_back(u);
			dfn[u]=low[u]=now++;
			for (auto v:e[u])
			{
				if (dfn[v]==-1)
				{
					tarjan(v);
					low[u]=min(low[u],low[v]);
				}
				else if (id[v]==-1)
					low[u]=min(low[u],dfn[v]);
			}
			if (dfn[u]==low[u])
			{
				int v;
				do
				{
					v=stk.back();
					stk.pop_back();
					id[v]=cnt;
				} while (v!=u);
				cnt++;
			}
		};
		for (int i=0;i<n*2;i++)
			if (dfn[i]==-1)
				tarjan(i);
		for (int i=0;i<n;i++)
		{
			if (id[i*2]==id[i*2+1]) return 0;
			ans[i]=id[i*2]>id[i*2+1];
		}
		return 1;
	}
	vector<bool> answer() { return ans; }
};
