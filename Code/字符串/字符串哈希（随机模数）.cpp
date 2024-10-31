bool isPrime(int n)
{
	if (n<=1) return 0;
	for (int i=2;i*i<=n;i++)
		if (n%i==0) return 0;
	return 1;
}

int findPrime(int n)
{
	while (!isPrime(n)) n++;
	return n;
}

mt19937 rng(time(0));
const int P=findPrime(rng()%900000000+100000000);
struct StrHash
{
	int n;
	vector<int> h,p;

	StrHash(const string &s){ init(s); }
	
	void init(const string &s)
	{
		n=s.size();
		h.resize(n+1);
		p.resize(n+1);
		p[0]=1;
		for (int i=0;i<n;i++) h[i+1]=(10ll*h[i]+s[i]-'a')%P;
		for (int i=0;i<n;i++) p[i+1]=10ll*p[i]%P;
	}

	//查询[l,r)的区间哈希
	int get(int l,int r) { return (h[r]+1ll*(P-h[l])*p[r-l])%P; }
};
