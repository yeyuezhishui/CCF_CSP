#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <string.h>
#include <queue>
typedef long long int ll;
using namespace std;
const long long int N = 500+20;
const long long int INF = 1e18;
long long int g1[N][N],g2[N][N];//大边邻接矩阵，小边邻接矩阵
long long int d1[N],d2[N];//d1:最后一条边是大边的最短距离
                          //d2:最后一条边是小边的最短距离


long long int vis[N];//标记是否在队列里
void SPFA(long long int start,long long int n)
{
//    memset(d1,INF,sizeof(d1));
//    memset(d2,INF,sizeof(d2));
    for(ll i = 0; i<N ; i++)
    {
        d1[i] = INF;
        d2[i] = INF;
    }
    memset(vis,0,sizeof(vis));
    d1[start] = 0;
    d2[start] = 0;
    queue<ll> q;
    q.push(start);
    vis[start] = 1;
    while(!q.empty())
    {
        ll u = q.front();
        q.pop();
        vis[u] = 0;
        for(ll i = 1; i<=n ; i++)
        {
            bool flag = false;
            //优化最后一条边是小边
            if(g2[u][i]<INF)
            {
                if(d1[u]+g2[u][i]*g2[u][i]<d2[i])
                {
                d2[i] = d1[u]+g2[u][i]*g2[u][i];
                flag = true;
                }
            }

            //优化最后一条边是大边
            if(g1[u][i]<INF)
            {
                if(d1[u]+g1[u][i]<d1[i] || d2[u]+g1[u][i]<d1[i])
                {
                d1[i] = min(d1[u]+g1[u][i],d2[u]+g1[u][i]);
                flag = true;
                }
            }

            if(!vis[i]&&flag)
            {
                q.push(i);
                vis[i] = 1;
            }
        }
    }
}

int m, n;
int main(void)
{
    //初始化邻接矩阵
//    memset(g1,INF,sizeof(g1));
//    memset(g2,INF,sizeof(g2));
    for(ll i = 0; i<N ; i++)
    {
        for(ll j = 0; j<N ; j++)
        {
           g1[i][j] = INF;
           g2[i][j] = INF;
        }

    }
    cin >> n >> m;
    //写入邻接矩阵数据
    for(int i = 0; i<m; i++)
    {
        long long t,a,b,c;
        cin >> t >> a >> b >> c;
        if(t==1) g2[a][b]=g2[b][a]=c;
        else g1[a][b]=g1[b][a]=c;
    }
    //floyd算法求各个小路间的最小路
    for(int i = 1; i<=n ; i++)
    {
        for(int j = i+1; j<=n ; j++)
        {
            for(int k = 1; k <=n ;k++)
            {
                if(k==i||k==j) continue;
                else
                {
                    g2[i][j] = min(g2[i][j],g2[i][k]+g2[k][j]);
                }
            }
        }
    }
    SPFA(1,n);
    cout << min(d1[n],d2[n]);
    return 0;
}
