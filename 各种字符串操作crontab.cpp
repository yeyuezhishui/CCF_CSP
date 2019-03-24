/* CCF201712-3 Crontab */
 
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
using namespace std;
 
const char *months[]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const char *weeks[]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const int days[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
int leapyear(int year, int month)
{
    if(month == 2)
        return ( ((year%4==0) && (year%100!=0)) || (year%400==0) ) ? 1 : 0;
    else
        return 0;
}
 
const int N = 20;
 
struct Crontab {
    vector<pair<int, int> > mi;  // ����
    vector<pair<int, int> > h;  // Сʱ
    vector<pair<int, int> > d;  // ����
    vector<pair<int, int> > m;  // �·�
    vector<pair<int, int> > w;  // ����
    string cmd;
} cmd[N];
 
struct CMD {
    int id;
    long long time;
    string cmd;
    bool operator < (const CMD &a) const //Ҫ��ʱ����Ⱥ�˳���ź�
    {
        return (time == a.time) ? id > a.id : time > a.time;
    }
};
 
char buf[256];
 
int getval(char t[])
{
    int i;
 
    t[0] = toupper(t[0]);
    for(i = 1; t[i]; i++)
        t[i] = tolower(t[i]);
 
    for(i = 1; i <= 12; i++)
        if(strcmp(t, months[i]) == 0)
            break;
    if(i <= 12)
        return i;
    else {
        for(i = 0; i <= 6; i++)
            if(strcmp(t, weeks[i]) == 0)
                break;
        if(i <= 6)
            return i;
    }
 
    return -1;
}
 
void setsubval(char s[], vector<pair<int, int> >& v)
{
    int p1 = 0, p2 = 0;
    for(int i = 0; s[i]; i++)
        if(s[i] == '-') {
            s[i] = '\0';
            p2 = i + 1;
            break;
        }
 
    int val1, val2;
    if(p1 == p2) {
        if(isdigit(s[0]))
            val1 = atoi(s);
        else
            val1 = getval(s);
        v.push_back(make_pair(val1, val1));
    } else {
        if(isdigit(s[0]))
            val1 = atoi(s);
        else
            val1 = getval(s);
        if(isdigit(s[p2]))
            val2 = atoi(s + p2);
        else
            val2 = getval(s + p2);
        v.push_back(make_pair(val1, val2));
    }
}
 
void setval(char s[], vector<pair<int, int> >& v)
{
    if(s[0] == '*')
        v.push_back(make_pair(-1, -1));
    else {
        char *p = strtok(s, ",");
        while(p) {
            setsubval(p, v);
            p = strtok(NULL, ",");
        }
    }
}
 
int myatoi(char t[], int b, int e)
{
    int v = 0;
    for(int i = b; i <= e; i++)
        v = v * 10 + t[i] - '0';
    return v;
}
 
bool judge(int m, vector<pair<int, int> >& v)
{
    for(int i = 0; i < (int)v.size(); i++)
        if(v[i].first == -1 || (v[i].first <= m && m <= v[i].second))
            return true;
    return false;
}
 
bool end_time_check(int y, int m, int d, int h, int mi, int ey, int em, int ed, int eh, int emi)
{
    if(y < ey) return true;
    if(m > em) return false;
    if(m < em) return true;
    if(d > ed) return false;
    if(d < ed) return true;
    if(h > eh) return false;
    if(h < eh) return true;
    if(mi > emi) return false;
    if(mi < emi) return true;
    return false;
}
 
// ������1582��10��15��֮��, ��Ϊ����̻ʸ������ʮ��������һ������������
// ���չ�ʽ�����������գ��õ����������ڼ�
int weekday(int year,int month,int day)
{
    if(month == 1 || month == 2) {
        month += 12;
        year--;
    }
    int c = year / 100;
    int y = year % 100;
    int m = month;
    int d = day;
    int w = c / 4 - 2 * c + y + y / 4 + 26 * (m + 1) / 10 + d - 1;
    if(w < 0)
        return (w + (-w / 7 + 1) * 7) % 7;
    return w % 7;
}
 
int main()
{
    int n;
    string s, t;
    priority_queue<CMD> q;
 
    cin >> n >> s >> t;
 
    strcpy(buf, s.c_str());
    int sy = myatoi(buf, 0, 3);
    int sm = myatoi(buf, 4, 5);
    int sd = myatoi(buf, 6, 7);
    int sh = myatoi(buf, 8, 9);
    int smi = myatoi(buf, 10, 11);
    strcpy(buf, t.c_str());
    int ey = myatoi(buf, 0, 3);
    int em = myatoi(buf, 4, 5);
    int ed = myatoi(buf, 6, 7);
    int eh = myatoi(buf, 8, 9);
    int emi = myatoi(buf, 10, 11);
 
    for(int i = 0; i < n; i++) {
        string ss;
 
        // ����
        cin >> ss;
        strcpy(buf, ss.c_str());
        setval(buf, cmd[i].mi);
 
        // Сʱ
        cin >> ss;
        strcpy(buf, ss.c_str());
        setval(buf, cmd[i].h);
 
        // ����
        cin >> ss;
        strcpy(buf, ss.c_str());
        setval(buf, cmd[i].d);
 
        // �·�
        cin >> ss;
        strcpy(buf, ss.c_str());
        setval(buf, cmd[i].m);
 
        // ��
        cin >> ss;
        strcpy(buf, ss.c_str());
        setval(buf, cmd[i].w);
 
        // Command
        cin >> cmd[i].cmd;
 
        int k = sm, l = sd, m = sh, n = smi;
        for(int j = sy; j <= ey; j++, k=1)
            for(; k <= 12; k++, l = 1)
                if(judge(k, cmd[i].m))
                    for(; l <= days[k] + leapyear(j, k); l++, m = 0)
                        if(judge(l, cmd[i].d) && judge(weekday(j, k, l), cmd[i].w))
                            for(; m < 24; m++, n = 0)
                                if(judge(m, cmd[i].h))
                                    for(; n < 60; n++) {
                                        if(!end_time_check(j, k, l, m, n, ey, em, ed, eh, emi))
                                            break;
                                        if(judge(n, cmd[i].mi)) {
                                            CMD tmp;
                                            tmp.id = i;
                                            tmp.time = (long long)j * 100000000 + (long long)k * 1000000 + (long long)l * 10000 + (long long)m * 100 + n;
                                            tmp.cmd = cmd[i].cmd;
                                            q.push(tmp);
                                        }
                                    }
    }
 
    while(!q.empty()) {
        CMD tmp = q.top();
        q.pop();
        cout << tmp.time << " " << tmp.cmd << endl;
    }
 
    return 0;
}
 
