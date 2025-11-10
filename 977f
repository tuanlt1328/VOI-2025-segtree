#include <bits/stdc++.h>
using namespace std;

const int maxn=6e5+7;
vector<int> compressor;
int n,a[maxn];

class segmentTree{
public:
	segmentTree(int n){
		st.resize(4*n+7,0);
		size=n;
	}
	void update(int pos, int val){
		update_uth(1,1,size,pos,val);
	}
	long long query(int l, int r){
		return query_uth(1,1,size,l,r);
	}
private:
	vector<long long> st;
	int size;
	void update_uth(int id, int l, int r, int pos, int val){
		if(l>pos||r<pos) return;
		if(l==r){
			st[id]=val;
			return;
		}
		int m=(l+r)>>1;
		update_uth(id*2, l, m, pos, val);
		update_uth(id*2+1, m+1, r, pos, val);
		st[id]=st[id*2]+st[id*2+1];
	}
	long long query_uth(int id, int l, int r, int u, int v){
		if(l>v||r<u) return 0;
		if(l>=u&&r<=v) return st[id];
		int m=(l+r)>>1;
		return query_uth(id*2, l, m, u, v) + query_uth(id*2+1, m+1, r, u, v);
	}
};

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        compressor.push_back(a[i]-1);
        compressor.push_back(a[i]);
        compressor.push_back(a[i]+1);
    }
    
    sort(compressor.begin(),compressor.end());
    compressor.erase(unique(compressor.begin(),compressor.end()),compressor.end());
    long long len=compressor.size()+5;
    long long resLength=0;
    segmentTree tree(len);
    pair<int, int> trace=make_pair(0,0);
    
    for(int i=1; i<=n; i++){
    	long long currentPosition = lower_bound(compressor.begin(), compressor.end(), a[i])-compressor.begin()+1;
		long long currentValue = tree.query(currentPosition-1, currentPosition-1);
		tree.update(currentPosition, currentValue+1);
		if(resLength < currentValue+1){
			resLength = currentValue+1;
			trace = make_pair(a[i],i);
		}
	}
	cout << resLength << '\n';
	int pos=trace.first-resLength+1;
	for(int i=1; i<=n; ++i){
		if(pos>trace.first) break;
		if(a[i]==pos) {
			cout << i << " ";
			pos++;
		}
	}
	return 0;
}
