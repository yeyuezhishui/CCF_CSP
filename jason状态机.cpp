/* CCF201709-3 JSON²éÑ¯ */
 
#include <iostream>
#include <string>
#include <map>
 
using namespace std;
 
int n, m;
string s, key;
map<string, string> json;
int state;
 
void handle(string& s)
{
    for(int i = 0; s[i]; i++) {
        if(s[i] == '{') {
            if(state == 0) {
                key = "";
            } else {
//                cout << "map: " << t << " " << "OBJECT" << endl;
                json[key] = "OBJECT";
            }
            state = 1;
        } else if(s[i] == '}') {
            int j;
            for(j = (int)key.size() - 1; j >= 0; j--) {
                if(key[j] == '.')
                    break;
            }
            if(j >= 0)
                key = key.substr(0, j);
            else
                key = "";
        } if(s[i] == ':') {
            state = 2;
        } if(s[i] == ',') {
            state = 1;
        } if(s[i] == '"') {  // Ë«ÒýºÅ
            string tmp;
            for(i++; s[i]; i++) {
                if(s[i] == '\\')
                    tmp += s[++i];
                else if(s[i] == '"')    // Ë«ÒýºÅ
                    break;
                else
                    tmp += s[i];
            }
            if(state == 1) {
                if(key == "")
                    key = tmp;
                else
                    key += '.' + tmp;
                state = 2;
            } else if(state == 2) {
//                cout << "map: " << t << " " << "STRING " + tmp << endl;
                json[key] = "STRING " + tmp;
                int j;
                for(j = (int)key.size() - 1; j >= 0; j--) {
                    if(key[j] == '.')
                        break;
                }
                if(j >= 0)
                    key = key.substr(0, j);
                else
                    key = "";
                state = 1;
            }
        }
    }
}
 
int main()
{
    cin >> n >> m;
    getline(cin, s);
 
    state = 0;
    while(n--) {
        getline(cin, s);
        handle(s);
    }
 
    while(m--) {
        cin >> s;
        cout << (json[s] == "" ? "NOTEXIST" : json[s]) << endl;
    }
 
    return 0;
}
 
