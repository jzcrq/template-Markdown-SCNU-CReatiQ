struct SAM
{
	static constexpr int ALPHABET=26;
	struct Node
	{
		int len;
		int link;
		array<int,ALPHABET> next;
		Node():len{},link{},next{} {}
	};

	vector<Node> t;

	SAM() { init(); }

	void init()
	{
		t.assign(2,Node());
		t[0].next.fill(1);
		t[0].len=-1;
	}

	int newNode()
	{
		t.emplace_back();
		return t.size()-1;
	}

	int extend(int lst,int c)
	{
		if (t[lst].next[c]&&t[t[lst].next[c]].len==t[lst].len+1)
			return t[lst].next[c];
		int p=lst,np=newNode(),flag=0;
		t[np].len=t[p].len+1;
		while (!t[p].next[c])
		{
			t[p].next[c]=np;
			p=t[p].link;
		}
		if (!p)
		{
			t[np].link=1;
			return np;
		}
		int q=t[p].next[c];
		if (t[q].len==t[p].len+1)
		{
			t[np].link=q;
			return np;
		}
		if (p==lst) flag=1,np=0,t.pop_back();
		int nq=newNode();
		t[nq].link=t[q].link;
		t[nq].next=t[q].next;
		t[nq].len=t[p].len+1;
		t[q].link=t[np].link=nq;
		while (p&&t[p].next[c]==q)
		{
			t[p].next[c]=nq;
			p=t[p].link;
		}
		return flag?nq:np;
	}

	int add(const string &a)
	{
		int p=1;
		for (auto c:a) p=extend(p,c-'a');
		return p;
	}

	int next(int p,int x) { return t[p].next[x]; }

	int link(int p) { return t[p].link; }

	int len(int p) { return t[p].len; }

	int size() { return t.size(); }
};
