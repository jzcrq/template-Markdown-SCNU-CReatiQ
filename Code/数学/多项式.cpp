namespace polygone{
	//慎用！！！
    //需要根据实际情况来调整 函数 poly operator * (poly f,poly g) 
	//和 数据类型(变为int) 因为取模频繁 而且我这一块处理的不好导致常数很大
    //涵盖了 多项式 求导，积分，加减乘 ，快速幂，ln , exp ，开根
    //没有涵盖 除法 多点求值 复合运算 等复杂部分 （学艺不精呜呜呜）
    //带有模数 没有支持无模
	#define N 3000006
	#define ll long long
	long long read(){
		ll f=1,s=0;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
		while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
		return s*f;
	}
	
	long long reading(ll mod){
		ll f=1,s=0;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
		while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',s%=mod,ch=getchar();
		return s*f;
	}
	const double pi=acos(-1.0);
	const long long  mod = 998244353, g = 3, g1 = 332748118;
	ll add(ll x,ll y){x+=y;return x>=mod?x-mod:x;}
	ll rdu(ll x,ll y){x-=y;return x<0?x+mod:x;}
	ll mul(ll x,ll y){return 1ll*x*y%mod;}
	
	#define poly vector<ll>
	#define plen(x) ((int)x.size())
	
	ll finv[N],r[N],lim,lg;
	
	ll qpow(ll x,ll y){
		if(y==1) return x;
		ll res=qpow(x,y>>1);
		if(y&1) return (((res*res)%mod)*x)%mod;
		return (res*res)%mod;
	}ll ginv(ll x){return qpow(x,mod-2);}
	
	void init(ll n){
		for(lim=1,lg=0;lim<=n;lim<<=1,lg++);
		for(int i=0;i<lim;i++) r[i]=((r[i>>1]>>1)|((i&1)<<(lg-1)));
	}
	
	void cinv(ll n){
		finv[1]=1;
		for(int i=2;i<=n;i++) finv[i]=mul(mod-mod/i,finv[mod%i]);
	}
	
	poly operator - (ll x,poly f){ll len=plen(f);for(int i=0;i<len;i++) f[i]=mod-f[i];f[0]=add(f[0],x);return f;}
	poly operator - (poly f,ll x){f[0]=rdu(f[0],x);return f;}
	poly operator - (poly f,poly g){ll n=max(plen(f),plen(g));f.resize(n);g.resize(n);for(int i=0;i<n;i++) f[i]=rdu(f[i],g[i]);return f;}
	poly operator * (poly f,ll x){ll len=plen(f);for(int i=0;i<len;i++) f[i]=mul(f[i],x);return f;}
	poly operator + (poly f,poly g){ll n=max(plen(f),plen(g));f.resize(n);g.resize(n);for(int i=0;i<n;i++) f[i]=add(f[i],g[i]);return f;}
	
	void ntt(poly &f,int op){
		for(int i=0;i<lim;i++) if(i<r[i]) swap(f[i],f[r[i]]);
		for(int mid=1;mid<lim;mid<<=1){
			ll wn=qpow(op==1?g:g1,(mod-1)/(mid<<1));
			for(int j=0;j<lim;j+=(mid<<1)){
				ll w=1;
				for(int k=0;k<mid;k++,w=(w*wn)%mod){
					ll x=f[j+k],y=w*f[j+k+mid]%mod;
					f[j+k]=(x+y)%mod;
					f[j+k+mid]=(x-y+mod)%mod;
				}
			}
		}
		if(op==1) return;
		ll inv=qpow(lim,mod-2);
		for(int i=0;i<lim;i++) f[i]=1ll*f[i]*inv%mod;
	}
	
	poly operator * (poly f,poly g){
		ll n=plen(f)+plen(g)-1;
		init(n);
		f.resize(lim);g.resize(lim);
		ntt(f,1);ntt(g,1);
		for(int i=0;i<lim;i++) f[i]=mul(f[i],g[i]);
		ntt(f,-1);
		f.resize(min(n,1ll*100000)); 
		return f;
	}
	
	poly inv(poly f){
		poly g=poly(1,ginv(f[0]));
		ll len=plen(f);
		for(int i=2;i<(len<<1);i<<=1){
			poly A=f;
			A.resize(i);
			g=g*(2-(g*A));
		}
		g.resize(len);
		return g;
	}
	
	poly qiudao(poly f){
		ll len=plen(f);
		for(int i=0;i<len-1;i++) f[i]=mul(i+1,f[i+1]);
		f.resize(len-1);
		return f;
	}
	
	poly jifen(poly f){
		ll len=plen(f);
		f.resize(len+1);
		for(int i=len-1;i>=1;i--) f[i]=mul(f[i-1],finv[i]);
		f[0]=0;
		return f;
	}
	
	poly ln(poly f){
		poly g=jifen(qiudao(f)*inv(f));
		g.resize(plen(f));
		return g;
	}
	
	poly exp(poly f){
		poly g=poly(1,1);
		ll len=plen(f);
		for(int i=2;i<(len<<2);i<<=1){
			poly A=f;
			A.resize(i);
			g=g*((1-ln(g))+A);
		}
		g.resize(len);
		return g;
	}
	
	poly Pow(poly f,ll k){
		f=ln(f);f=f*k;f=exp(f);
		return f;
	}
	
	poly sqrt(poly f){
		poly g=poly(1,1);
		ll len=plen(f);
		ll inv2=ginv(2);
		for(int i=2;i<(len<<2);i<<=1){
			poly A=f;
			A.resize(i);
			g=(g+(A*inv(g)))*inv2;
		}
		g.resize(len);
		return g;
	}
}
using namespace polygone;
