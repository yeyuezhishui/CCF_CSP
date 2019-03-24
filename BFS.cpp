#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int  N=1000+10;
vector<int> vfront[N];
vector<int> vback[N];
bool can_front[N];
bool can_back[N];
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    int u,v;
    int ans = 0;
    //创建邻接节点表
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d",&u,&v);
        vfront[u].push_back(v);
        vback[v].push_back(u);
    }
    //开始bfs
    //queue<int> temp;
    //int len = 0;
    for(int i = 1; i <= n ; i++)
    {
        queue<int> temp;
        memset(can_front,false,sizeof(can_front));
        memset(can_back,false,sizeof(can_back));
        temp.push(i);
        can_front[i] = true;
        while(!temp.empty())
        {
            int head = temp.front();
            temp.pop();
            int len = vfront[head].size();
            for(int j = 0; j<len ; j++)
            {
                if(!can_front[vfront[head][j]])
                {
                     temp.push(vfront[head][j]);
                     can_front[vfront[head][j]] = true;/*!!!!!!!
                     !!!!!!!!!!!!!一定记得在入队的时候访问!!!!!!!!!!!!!*/
                }
            }
        }
        temp.push(i);
        can_back[i] = true;
        while(!temp.empty())
        {
            int head = temp.front();
            temp.pop();
            int len = vback[head].size();
            for(int j = 0; j<len ; j++)
            {
                if(!can_back[vback[head][j]])
                {
                     temp.push(vback[head][j]);
                     can_back[vback[head][j]] = true;
                }
            }
        }

        int cn = 0;
        for(int j = 1;j <=n;j++)
        {
            if(j == i) continue;
            if(can_back[j] || can_front[j])
            {
                cn++;
            }
        }
        if(cn == n-1) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
