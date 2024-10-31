void prime(){
	u[1]=1;v[1]=1;phi[1]=1;
	for(ll i=2;i<=N;i++){
		if(!v[i]) {u[i]=-1;p[++cnt]=i;phi[i]=i-1;}
		for(ll j=1;j<=cnt&&p[j]*i<=N;j++){
			v[p[j]*i]=1;
			if(!(i%p[j])) {phi[i*p[j]]=phi[i]*p[j];break;}
			else u[i*p[j]]=-u[i],phi[i*p[j]]=phi[i]*phi[p[j]];
		}
	}
	for(ll i=1;i<=N;i++) u[i]+=u[i-1],phi[i]+=phi[i-1];
}

ll sumu(ll n) {
	if(n<=N) return u[n];
	if(M[n]) return M[n];
	ll res=1;
	for(ll l=2,r=0;l<=n;l=r+1){
		r=n/(n/l);
		res-=1ll*sumu(n/l)*(r-l+1);
	}
	M[n]=res;
	return M[n];
}
