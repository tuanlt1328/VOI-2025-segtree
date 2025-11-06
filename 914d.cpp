#include <bits/stdc++.h>

using namespace std;

const int N=5e5+4;

int n,q,a[N],st[N<<2];

void build(int id,int l,int r){
    if(l==r){
        st[id]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    st[id]=__gcd(st[id*2],st[id*2+1]);
}

void update(int id,int l,int r,int i,int value){
    if(i<l||r<i)return;
    if(l==r){
        st[id]=value;
        return;
    }
    int mid=(l+r)>>1;
    update(id*2,l,mid,i,value);
    update(id*2+1,mid+1,r,i,value);
    st[id]=__gcd(st[id*2],st[id*2+1]);
}

void down(int id,int l,int r,int x,int &ans){
    if(l==r){
        if(st[id]%x!=0)++ans;
        return;
    }

    int mid=(l+r)>>1;
    if(st[id*2]%x!=0){
        if(st[id*2+1]%x!=0){
            ans+=2;
            return;
        }
        down(id*2,l,mid,x,ans);
        // return;
    }
    else down(id*2+1,mid+1,r,x,ans);
}

void get(int id,int l,int r,int x,int u,int v,int &ans){
    if(v<l||r<u)return;
    else if(u<=l&&r<=v){
        if(st[id]%x==0)return;
        down(id,l,r,x,ans);
        return;
    }

    int mid=(l+r)>>1;
    get(id*2,l,mid,x,u,v,ans);
    if(ans>1)return;
    get(id*2+1,mid+1,r,x,u,v,ans);
}

void input(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
}

void solve(){
    build(1,1,n);

    cin>>q;
    while(q--){
        int type,i,l,r,x;
        cin>>type;
        if(type==1){
            cin>>l>>r>>x;
            int res=0;
            get(1,1,n,x,l,r,res);
            cout<<(res<2?"YES\n":"NO\n");
        }
        else{
            cin>>i>>x;
            update(1,1,n,i,x);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    input();
    solve();
    return 0;
}
