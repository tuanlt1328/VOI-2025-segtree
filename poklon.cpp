#include<bits/stdc++.h>
using namespace std;	
const int maxn=5e5+7;
int n,q,a[maxn];
int st[maxn*4],pre[maxn],lst[maxn];
vector<int> G;

void Update(int id,int l,int r,int pos,int val){
	if(l>pos||r<pos) return;
	if(l==r){
		st[id]+=val;
		return;
	}
	int mid=(l+r)/2,id1=(id<<1),id2=(id1+1);
	Update(id1,l,mid,pos,val);
	Update(id2,mid+1,r,pos,val);
	st[id]=st[id1]+st[id2];
}

int Get(int id,int l,int r,int u,int v){
	if(l>v||r<u) return 0;
	if(l>=u&&r<=v) return st[id];
	int mid=(l+r)/2,id1=(id<<1),id2=(id1+1);
	return Get(id1,l,mid,u,v)+Get(id2,mid+1,r,u,v);
}

vector<pair<int, int> > Gz[maxn];
int ans[maxn];

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	
	G.push_back(0);
	for(int i=1;i<=n;++i) cin>>a[i],G.push_back(a[i]);
	sort(G.begin(),G.end());
	
	for(int i=1;i<=q;++i){
		int u,v;
		cin>>u>>v;
		Gz[v].push_back({u,i});
	}
	
	for(int i=1;i<=n;++i){
		a[i]=lower_bound(G.begin(),G.end(),a[i])-G.begin();
		pre[i]=lst[a[i]];
		lst[a[i]]=i;
		int pos3=0, pos4=0;
		if(pre[i]){
			Update(1,0,n,pre[i],1);
			pos3=pre[pre[i]];
			Update(1,0,n,pos3,-2);
			pos4=pre[pos3];
			Update(1,0,n,pos4,1);
		}
		for(auto K : Gz[i])	ans[K.second]=Get(1,0,n,K.first,i);
	}
	
	for(int i=1;i<=q;++i) cout<<ans[i]<<"\n";
	return 0;
}
