struct LB
{
	static constexpr int L=60;
	array<i64,L+1> a{};
	
	LB(){}
	
	LB(const vector<i64> &v) { init(v); }
	
	bool insert(i64 t)
	{
		for (int i=L;i>=0;i--)
			if (t&(1ll<<i))
			{
				if (!a[i])
				{
					a[i]=t;
					return 1;
				}
				else t^=a[i];
			}
		return 0;
	}
	
	void init(const vector<i64> &v) { for (auto x:v) insert(x); }
	
	bool check(i64 t)
	{
		for (int i=L;i>=0;i--)
			if (t&(1ll<<i))
				if (!a[i]) return 0;
				else t^=a[i];
		return 1;
	}
	
	i64 QueryMax()
	{
		i64 res=0;
		for (int i=L;i>=0;i--)
			res=max(res,res^a[i]);
		return res;
	}
	
	i64 QueryMin()
	{
		for (int i=0;i<=L;i++)
			if (a[i]) return a[i];
		return 0;
	}
	
	i64 QueryKth(int k)
	{
		i64 res=0;
		int cnt=0;
		array<i64,L+1> tmp{};
		for (int i=0;i<=L;i++)
		{
			for (int j=i-1;j>=0;j--)
				if (a[i]&(1ll<<j)) a[i]^=a[j];
			if (a[i]) tmp[cnt++]=a[i];
		}
		if (k>=(1ll<<cnt)) return -1;
		for (int i=0;i<cnt;i++)
			if (k&(1ll<<i)) res^=tmp[i];
		return res;
	}
};
