struct ACAM
{
	static constexpr int ALPHABET=26;
	struct Node
	{
		int len;
		int link;
		array<int,ALPHABET> next;
		Node():len{0},link{0},next{}{}
	};

	vector<Node> t;

	ACAM() { init(); }

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

	int add(const string &a)
	{
		int p=1;
		for (auto c:a)
		{
			int x=c-'a';
			if (t[p].next[x]==0)
			{
				t[p].next[x]=newNode();
				t[t[p].next[x]].len=t[p].len+1;
			}
			p=t[p].next[x];
		}
		return p;
	}

	void work()
	{
		queue<int> q;
		q.push(1);
		while (!q.empty())
		{
			int x=q.front();
			q.pop();
			for (int i=0;i<ALPHABET;i++)
			{
				if (t[x].next[i]==0) t[x].next[i]=t[t[x].link].next[i];
				else
				{
					t[t[x].next[i]].link=t[t[x].link].next[i];
					q.push(t[x].next[i]);
				}
			}
		}
	}

	int next(int p,int x) { return t[p].next[x]; }

	int link(int p) { return t[p].link; }

	int size() { return t.size(); }
};
