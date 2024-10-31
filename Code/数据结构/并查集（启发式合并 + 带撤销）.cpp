struct DSU
{
	int n=0;
	vector<int> fa,siz;
	stack<int> s;

	DSU(int n) { init(n); }

	void init(int n)
	{
		fa.resize(n);
		iota(fa.begin(),fa.end(),0);
		siz.assign(n,1);
		while (!s.empty()) s.pop();
	}

	int get(int x) { return fa[x]==x?x:get(fa[x]); }

	void merge(int x,int y)
	{
		x=get(x),y=get(y);
		if (x==y) return;
		if (siz[x]<siz[y]) swap(x,y);
		s.push(y),fa[y]=x,siz[x]+=siz[y];
	}

	void undo()
	{
		if (s.empty()) return;
		int y=s.top();
		s.pop();
		siz[fa[y]]-=siz[y];
		fa[y]=y;
	}

	void back(int t=0) { while (s.size()>t) undo(); }
};
