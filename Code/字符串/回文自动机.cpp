struct PAM
{
	static constexpr int ALPHABET_SIZE=28;
	struct Node
	{
		int len,link,cnt;
		array<int,ALPHABET_SIZE> next;
		Node():len{},link{},cnt{},next{}{}
	};
	vector<Node> t;
	int suff;
	string s;

	PAM() { init(); }

	void init()
	{
		t.assign(2,Node());
		t[0].len=-1;
		suff=1;
		s.clear();
	}

	int newNode()
	{
		t.emplace_back();
		return t.size()-1;
	}

	bool add(char c,char offset='a')
	{
		int pos=s.size();
		s+=c;
		int let=c-offset;
		int cur=suff,curlen=0;
		while (1)
		{
			curlen=t[cur].len;
			if (pos-curlen-1>=0&&s[pos-curlen-1]==s[pos]) break;
			cur=t[cur].link;
		}
		if (t[cur].next[let])
		{
			suff=t[cur].next[let];
			return 0;
		}
		int num=newNode();
		suff=num;
		t[num].len=t[cur].len+2;
		t[cur].next[let]=num;
		if (t[num].len==1)
		{
			t[num].link=t[num].cnt=1;
			return 1;
		}
		while (1)
		{
			cur=t[cur].link;
			curlen=t[cur].len;
			if (pos-curlen-1>=0&&s[pos-curlen-1]==s[pos])
			{
				t[num].link=t[cur].next[let];
				break;
			}
		}
		t[num].cnt=t[t[num].link].cnt+1;
		return 1;
	}
};
