#define ll long long
const ll inf=(ll)(1e16);
#define MAXN (int)(2e3+233)
#define MAXM (int)(6e3+233)
struct qwq
{
	int nex,to;
	ll w;
}e[MAXM];
int h[MAXN],tot=0;
int n,m;
inline void add(int x,int y,ll z)
{
	e[++tot].to=y;
	e[tot].nex=h[x];
	e[tot].w=z;
	h[x]=tot;
}
ll dis[MAXN];
int cnt[MAXN];
bool vis[MAXN];
queue<int> q;
inline void INIT()
{
	for (int i=1;i<=n;i++) h[i]=0,dis[i]=inf,cnt[i]=0,vis[i]=false; tot=0;
	while (!q.empty()) q.pop();
	return;
}

inline bool spfa(int s)
{
	dis[s]=0; q.push(s); vis[s]=true;
	int x;
	while (!q.empty())
	{
		x=q.front(); q.pop(); vis[x]=false;
		for (int i=h[x],y;i;i=e[i].nex)
		{
			y=e[i].to;
			if (dis[y]>dis[x]+e[i].w)
			{
				dis[y]=dis[x]+e[i].w;
				if (!vis[y])
				{
					cnt[y]++;
					if (cnt[y]>=n) return false;
					q.push(y); vis[y]=true;
				}
			}
		}
	}
	return true;
}
inline bool bellman_ford(int s)
{
	dis[s]=0;
	for (int k=1;k<n;k++)
		for (int x=1;x<=n;x++)
		{
			if (dis[x]==inf) continue;
			for (int i=h[x],y;i;i=e[i].nex)
			{
				y=e[i].to;
				if (dis[y]>dis[x]+e[i].w)
					dis[y]=dis[x]+e[i].w;
			}
		}
	for (int x=1;x<=n;x++)
	{
		if (dis[x]==inf) continue;
		for (int i=h[x],y;i;i=e[i].nex)
		{
			y=e[i].to;
			if (dis[y]>dis[x]+e[i].w) return false;
		}
	}
	return true;
}

inline void R()
{
	scanf("%d%d",&n,&m);
	INIT();
	for (int i=1,x,y;i<=m;i++)
	{
		ll z;
		scanf("%d%d%lld",&x,&y,&z);
		if (z>=0) add(x,y,z),add(y,x,z);
		else add(x,y,z);
	}
	puts(spfa(1)?"NO":"YES"); /*or*/ puts(bellman_ford(1)?"NO":"YES");
	return;
}
