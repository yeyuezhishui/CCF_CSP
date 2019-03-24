#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=1e5+10;
struct Edge
{
    int u,v,c;
    bool operator < (const Edge &a) const
    {
        return c<a.c;
    }
}edge[N];

int uf[N];

//找最小生成树的巧妙方法 
int find(int x)
{
    if(uf[x]==-1) return x;
    return uf[x]=find(uf[x]); 
}


int main()
{
    int n,m,r;
    scanf("%d%d%d",&n,&m,&r);
    memset(uf,-1,sizeof(uf));
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].c);

//首先排序 
    sort(edge,edge+m);
    
    int cnt=0,ans=0;
    for(int i=0;i<m;i++)
    {
        int u=edge[i].u;
        int v=edge[i].v;
        int t=edge[i].c;
        int t1=find(u),t2=find(v);
        if(t1!=t2)
        {
            uf[t1]=t2;
            ans=max(ans,t);
            cnt++;
            if(cnt==n-1) break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
