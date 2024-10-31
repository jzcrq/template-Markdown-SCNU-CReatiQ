struct HLD
{
	int n;
	vector<int> siz,top,dep,pa,in,out,seq;
	vector<vector<int>> adj;
	int cur;

	HLD(){}
	HLD(int n) { init(n); }

	void init(int n)
	{
		this->n=n;
		siz.resize(n);
		top.resize(n);
		dep.resize(n);
		pa.resize(n);
		in.resize(n);
		out.resize(n);
		seq.resize(n);
		cur=0;
		adj.assign(n,{});
	}

	void addEdge(int u,int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void work(int rt=0)
	{
		top[rt]=rt;
		dep[rt]=0;
		pa[rt]=-1;
		dfs1(rt);
		dfs2(rt);
	}

	void dfs1(int u)
	{
		if (pa[u]!=-1) adj[u].erase(find(adj[u].begin(),adj[u].end(),pa[u]));
		siz[u]=1;
		for (auto &v:adj[u])
		{
			pa[v]=u;
			dep[v]=dep[u]+1;
			dfs1(v);
			siz[u]+=siz[v];
			if (siz[v]>siz[adj[u][0]])
				swap(v,adj[u][0]);
		}
	}

	void dfs2(int u)
	{
		in[u]=cur++;
		seq[in[u]]=u;
		for (auto v:adj[u])
		{
			top[v]=(v==adj[u][0])?top[u]:v;
			dfs2(v);
		}
		out[u]=cur;
	}

	int lca(int u,int v)
	{
		while (top[u]!=top[v])
		{
			if (dep[top[u]]>dep[top[v]]) u=pa[top[u]];
			else v=pa[top[v]];
		}
		return dep[u]<dep[v]?u:v;
	}

	int dist(int u,int v) { return dep[u]+dep[v]-(dep[lca(u,v)]<<1); }

	int jump(int u,int k)
	{
		if (dep[u]<k) return -1;
		int d=dep[u]-k;
		while (dep[top[u]]>d) u=pa[top[u]];
		return seq[in[u]-dep[u]+d];
	}

	bool isAncester(int u,int v) { return in[u]<=in[v]&&in[v]<out[u]; }

	int rootedParent(int u,int v)//u->root,v->point
	{
		if (u==v) return u;
		if (!isAncester(v,u)) return pa[v];
		auto it=upper_bound(adj[v].begin(),adj[v].end(),u,[&](int x,int y){ return in[x]<in[y]; })-1;
		return *it;
	}

	int rootedSize(int u,int v)//same as rootedParent
	{
		if (u==v) return n;
		if (!isAncester(v,u)) return siz[v];
		return n-siz[rootedParent(u,v)];
	}

	int rootedLca(int a,int b,int c) { return lca(a,b)^lca(b,c)^lca(c,a); }
};
