struct EBCC
{
	int n;
	vector<vector<int>> adj;
	vector<int> stk,dfn,low,bel;
	int cur,cnt;

	EBCC() {}
	EBCC(int n) { init(n); }

	void init(int n)
	{
		this->n=n;
		adj.assign(n,{});
		dfn.assign(n,-1);
		low.resize(n);
		bel.assign(n,-1);
		stk.clear();
		cur=cnt=0;
	}

	void add(int u,int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void dfs(int x,int p)
	{
		dfn[x]=low[x]=cur++;
		stk.push_back(x);
		for (auto y:adj[x])
		{
			if (y==p) continue;
			if (dfn[y]==-1)
			{
				dfs(y,x);
				low[x]=min(low[x],low[y]);
			}
			else if (bel[y]==-1&&dfn[y]<dfn[x]) low[x]=min(low[x],dfn[y]);
		}
		if (dfn[x]==low[x])
		{
			int y;
			do
			{
				y=stk.back();
				bel[y]=cnt;
				stk.pop_back();
			} while (y!=x);
			cnt++;
		}
	}

	vector<int> work()
	{
		dfs(0,-1);
		return bel;
	}

	struct Graph
	{
		int n;
		vector<pair<int,int>> edges;
		vector<int> siz,cnte;
	};

	Graph compress()
	{
		Graph G;
		G.n=cnt;
		G.siz.resize(cnt);
		G.cnte.resize(cnt);
		for (int i=0;i<n;i++)
		{
			G.siz[bel[i]]++;
			for (auto j:adj[i])
			{
				if (bel[i]<bel[j]) G.edges.emplace_back(bel[i],bel[j]);
				else if (i<j) G.cnte[bel[i]]++;
			}
		}
		return G;
	};
};
