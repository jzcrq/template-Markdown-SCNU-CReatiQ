template <class T>
struct BIT
{
	int n;
	vector<T> a;

	BIT(int n_=0) { init(n_); }

	void init(int n_)
	{
		n=n_;
		a.assign(n,T{});
	}

	void add(int x,const T &v)
	{
		for (int i=x+1;i<=n;i+=i&-i)
			a[i-1]=a[i-1]+v;
	}

	//查询区间[0,x)
	T sum(int x)
	{
		T ans{};
		for (int i=x;i>0;i-=i&-i)
			ans=ans+a[i-1];
		return ans;
	}

	//查询区间[l,r)
	T rangeSum(int l,int r) { return sum(r)-sum(l); }

	int select(const T &k)
	{
		int x=0;
		T cur{};
		for (int i=1<<__lg(n);i;i>>=1)
		{
			if (x+i<=n&&cur+a[x+i-1]<=k)
			{
				x+=i;
				cur=cur+a[x-1];
			}
		}
		return x;
	}
};
