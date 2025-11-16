#include <bits/stdc++.h>

using namespace std;

const int N=1e5+4;

struct seg_tree{
	int n;
	vector<int>st;

	seg_tree(){};
	seg_tree(int _n): n(_n), st(4*n+2) {};

	void update(int id,int l,int r,int i,int value){
		if(i<l||r<i)return;
		if(l==r){
			st[id]+=value;
			return;
		}
		int mid=(l+r)>>1;
		update(id*2,l,mid,i,value);
		update(id*2+1,mid+1,r,i,value);
		st[id]=st[id*2]+st[id*2+1];
	}

	int get(int id,int l,int r,int u,int v){
		if(v<l||r<u)return 0;
		if(u<=l&&r<=v)return st[id];
		int mid=(l+r)>>1;
		return get(id*2,l,mid,u,v)+get(id*2+1,mid+1,r,u,v);
	}

	void update(int i,int value){
		update(1,1,n,i,value);
	}

	int get(int i){
		return get(1,1,n,1,i);
	}
};

int n;
set<int>s[N];
set<int>::iterator it;

void solve(){
	cin>>n;

	seg_tree st(N);
	int maxValue=0;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		maxValue=max(maxValue,a);
		s[a].insert(i);
		st.update(i,1);
	}

	int curr=0,x=0;
	long long res=0;
	for(int i=1;i<=maxValue;i++){
		while(!s[i].empty()){
			it=s[i].lower_bound(curr);
			if(it!=s[i].end()){
				x=*it;
				s[i].erase(x);
				res+=st.get(x)-st.get(curr);
				curr=x;
				st.update(x,-1);
			}
			else{
				x=*s[i].begin();
				s[i].erase(x);
				res+=st.get(n)+st.get(x)-st.get(curr);
				curr=x;
				st.update(x,-1);
			}
		}
	}
	cout<<res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}
