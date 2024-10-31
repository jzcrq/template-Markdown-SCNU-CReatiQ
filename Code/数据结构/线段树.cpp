template <class Info,class Tag>
struct SGT
{
	int n;
	vector<Info> info;
	vector<Tag> tag;

	SGT():n(0) {}
	SGT(int n_,Info v_=Info()) { init(n_,v_); }

	template <class T>
	SGT(vector<T> init_) { init(init_); }

	void init(int n_,Info v_=Info()) { init(vector(n_,v_)); }

	template <class T>
	void init(vector<T> init_)
	{
		n=init_.size();
		info.assign(4<<__lg(n),Info());
		tag.assign(4<<__lg(n),Tag());
		function<void(int,int,int)> build=[&](int p,int l,int r)
		{
			if (r-l==1)
			{
				info[p]=init_[l];
				return;
			}
			int m=(l+r)>>1;
			build(p<<1,l,m);
			build(p<<1|1,m,r);
			pushup(p);
		};
		build(1,0,n);
	}

	void pushup(int p) { info[p]=info[p<<1]+info[p<<1|1]; }

	void apply(int p,const Tag &v)
	{
		info[p].apply(v);
		tag[p].apply(v);
	}

	void pushdown(int p)
	{
		apply(p<<1,tag[p]);
		apply(p<<1|1,tag[p]);
		tag[p]=Tag();
	}

	void modify(int p,int l,int r,int x,const Info &v)
	{
		if (r-l==1)
		{
			info[p]=v;
			return;
		}
		int m=(l+r)>>1;
		pushdown(p);
		if (x<m) modify(p<<1,l,m,x,v);
		else modify(p<<1|1,m,r,x,v);
		pushup(p);
	}

	//O(log n)单点修改
	void modify(int p,const Info &v) { modify(1,0,n,p,v); }

	Info rangeQuery(int p,int l,int r,int x,int y)
	{
		if (l>=y||r<=x) return Info();
		if (l>=x&&r<=y) return info[p];
		int m=(l+r)>>1;
		pushdown(p);
		return rangeQuery(p<<1,l,m,x,y)+rangeQuery(p<<1|1,m,r,x,y);
	}

	//O(log n)区间查询[l,r)
	Info rangeQuery(int l,int r) { rangeQuery(1,0,n,l,r); }

	void rangeApply(int p,int l,int r,int x,int y,const Tag &v)
	{
		if (l>=y||r<=x) return;
		if (l>=x&&r<=y)
		{
			apply(p,v);
			return;
		}
		int m=(l+r)>>1;
		pushdown(p);
		rangeApply(p<<1,l,m,x,y,v);
		rangeApply(p<<1|1,m,r,x,y,v);
		pushup(p);
	}

	//O(log n)区间操作[l,r)
	void rangeApply(int l,int r,const Tag &v) { rangeApply(1,0,n,l,r,v); }

	//O(log n)区间[l,r)内查找第一个合法位置
	template <class F>
	int findFirst(int p,int l,int r,int x,int y,F pred)
	{
		if (l>=y||r<=x||!pred(info[p])) return -1;
		if (r-l==1) return l;
		int m=(l+r)>>1;
		pushdown(p);
		int res=findFirst(p<<1,l,m,x,y,pred);
		if (res==-1) res=findFirst(p<<1|1,m,r,x,y,pred);
		return res;
	}

	template <class F>
	int findFirst(int l,int r,F pred) { return findFirst(1,0,n,l,r,pred); }

	template <class F>
	int findLast(int p,int l,int r,int x,int y,F pred)
	{
		if (l>=y||r<=x||!pred(info[p])) return -1;
		if (r-l==1) return l;
		int m=(l+r)>>1;
		pushdown(p);
		int res=findFirst(p<<1|1,m,r,x,y,pred);
		if (res==-1) res=findFirst(p<<1,l,m,x,y,pred);
		return res;
	}

	template <class F>
	int findLast(int l,int r,F pred) { return findLast(1,0,n,l,r,pred); }
};

//这里默认乘法优先 (x*a+b)*c+d=x*(a*c)+(b*c+d)
struct Tag
{
	i64 a=1,b=0;
	void apply(Tag t)
	{
		a*=t.a;
		b=b*t.a+t.b;
	}
};

struct Info
{
	i64 x=0,l=0,r=0;
	void apply(Tag t)
	{
		int len=r-l+1;
		x=x*t.a+len*t.b;
	}
};

Info operator + (Info a,Info b)
{
	return {a.x+b.x,min(a.l,b.l),max(a.r,b.r)};
}
