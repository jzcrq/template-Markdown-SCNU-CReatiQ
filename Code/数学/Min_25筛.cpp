void prime(ll n){
	for(ll i=2;i<=n;i++){
		if(!vis[i]) p[++cnt]=i;
		for(ll j=1;j<=cnt&&p[j]<=n/i;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}

ll qz1(ll x){return x%=mod,x*(x+1)%mod*inv2%mod;}
ll qz2(ll x){return x%=mod,x*(x+1)%mod*(2*x+1)%mod*inv6%mod;}
ll get(ll x){return x<N?id1[x]:id2[n/x];}
ll sq(ll x) {return x%=mod,x*x%mod;}
ll F(ll x)  {return x%=mod,(sq(x)+mod-x)%mod;}

void getg(){
	for(ll l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		v[++m]=n/l;
		if(v[m]<N) id1[v[m]]=m;
		else id2[n/v[m]]=m;
		g1[m]=(qz1(v[m])-1+mod)%mod;
		g2[m]=(qz2(v[m])-1+mod)%mod;
	}
	for(ll j=1;j<=cnt;j++){
		for(ll i=1;i<=m&&p[j]<=v[i]/p[j];i++){
			g1[i]=(g1[i]-p[j]*(g1[get(v[i]/p[j])]-g1[get(p[j-1])])%mod+mod)%mod;
			g1[i]=(g1[i]+mod)%mod;
			g2[i]=(g2[i]-sq(p[j])*(g2[get(v[i]/p[j])]-g2[get(p[j-1])])%mod+mod)%mod;
			g2[i]=(g2[i]+mod)%mod;
		}
	}
}

ll S(ll x,ll y){
	if(p[y]>=x) return 0;
	ll res=(g2[get(x)]-g1[get(x)]-g2[get(p[y])]+g1[get(p[y])]+mod)%mod;//g(n);
	for(ll i=y+1;i<=cnt&&p[i]<=x/p[i];i++){
		ll P=p[i];
		for(ll j=1;P<=x/p[i];j++,P*=p[i]){//p^e
			res=(res+F(P)*S(x/P,i)%mod+F(P*p[i]))%mod;
		}
	}
	return res;
}

ll qpow(ll x,ll y){
	if(y==1) return x;
	ll res=qpow(x,y>>1);
	if(y&1) return (((res*res)%mod)*x)%mod;
	return (res*res)%mod;
}ll inv(ll x){return qpow(x,mod-2);}

int main(){
	inv2=inv(2),inv6=inv(6);
	n=read();
	ll T=sqrt(n)+1;
	prime(T);
	getg();
	ll ans=(S(n,0)+1+mod)%mod;
	cout<<ans;
	return 0;
}
