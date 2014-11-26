    #include <cstring>  
    #include <cstdio>  
    #include <algorithm>  
    #include <map>  
    #include <string>  
    #include <queue>  
    using namespace std;  
      
    #define SIGMA_SIZE 26 //文本串字符内容  
    #define MAXNODE 20000 //节点数量  
    #define TEXT_SIZE 1000005 //文本串长度  
    #define P_SIZE 100 //模式串长度  
    #define P_NUM 200 //模式串数量  
      
    map <string, int> mp;  
      
    struct AhoCorasickAutomata  
    {  
        int cnt[P_NUM];  
        int sz;  
        int ch[MAXNODE][SIGMA_SIZE];  
        int f[MAXNODE];  
        int val[MAXNODE];  
        int last[MAXNODE];  
      
        void Init() {  
            sz = 1;  
            memset(ch[0],0,sizeof(ch[0]));  
            memset(cnt,0,sizeof(cnt));  
            mp.clear();  
        }  
      
        int idx(char c) {  
            return c - 'a';  
        }  
      
        void Insert(char *s,int v) {  
            int u = 0, n = strlen(s);  
            for(int i = 0; i < n; i++) {  
                int c = idx(s[i]);  
                if(!ch[u][c]) {  
                    memset(ch[sz], 0, sizeof(ch[sz]));  
                    val[sz] = 0;  
                    ch[u][c] = sz++;  
                }  
                u = ch[u][c];  
            }  
            val[u] = v;  
            mp[string(s)] = v;  
        }  
      
        void print(int j) {  
            if(j) {  
                cnt[val[j]]++;  
                print(last[j]);  
            }  
        }  
      
        void Find(char *T) {  
            int n = strlen(T);  
            int j = 0;  
            for(int i = 0; i < n; i++) {  
                int c = idx(T[i]);  
                while(j && !ch[j][c]) j = f[j];  
                j = ch[j][c];  
                if(val[j]) print(j);  
                else if(last[j]) print(last[j]);  
            }  
        }  
      
        void Get_Fail() {  
            queue<int> q;  
            f[0] = 0;  
            for(int c = 0; c<SIGMA_SIZE; c++) {  
                int u = ch[0][c];  
                if(u) {  
                    f[u] = 0;  
                    q.push(u);  
                    last[u] = 0;  
                }  
            }  
            while(!q.empty()) {  
                int r = q.front();  
                q.pop();  
                for(int c = 0; c<SIGMA_SIZE; c++) {  
                    int u = ch[r][c];  
                    if(!u) continue;  
                    q.push(u);  
                    int v = f[r];  
                    while(v && !ch[v][c]) v = f[v];  
                    f[u] = ch[v][c];  
                    last[u] = val[f[u]] ? f[u] : last[f[u]];  
                }  
            }  
        }  
    };  
      
    char text[TEXT_SIZE];  
    char P[P_NUM][P_SIZE];  
    AhoCorasickAutomata ac;  
    int n, T;  
      
    int main() {  
        scanf("%d", &T);  
        int cas = 0;  
        while(T--) {  
            scanf("%d", &n);  
            ac.Init();  
            for(int i = 1; i <= n; i++) {  
                scanf("%s", P[i]);  
                ac.Insert(P[i], i);  
            }  
            ac.Get_Fail();  
            scanf("%s", text);  
            ac.Find(text);  
            int Max_cnt = -1;  
            for(int i = 1; i <= n; i++)  
                if(ac.cnt[i] > Max_cnt)  
                    Max_cnt = ac.cnt[i];  
            printf("%d\n", Max_cnt);  
            for(int i = 1; i <= n; i++)  
                if(ac.cnt[mp[string(P[i])]] == Max_cnt)  
                    printf("%s\n", P[i]);  
        }  
        return 0;  
    }  
