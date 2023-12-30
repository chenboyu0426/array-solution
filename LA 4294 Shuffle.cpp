#include <cstdio>
#include <cstring>

using namespace std;
const int N = 200000 + 5;

int s, len;
bool back[N], forw[N];
int cnt[N], seq[N];

void solve()
{
    memset(cnt, 0, sizeof(cnt));
    memset(back, 0, sizeof(back));
    memset(forw, 0, sizeof(forw));

    int diff = 0, ans = 0;
    for(int i = 0; i < len + s; i++){
        if(i >= s-1 && diff == s){
            back[i-s] = true;// 超過循環歌數
        }
        // 滑動視窗 cnt 要移去播放紀錄 seq[i] 數字統計
        if(i > s-1){
            cnt[seq[i-s]]--;
            if(cnt[seq[i-s]] == 0) diff--;                       
        }
        // 位置 i 在滑動式窗內多一位數字(seq[i])
        if(i >= len) diff++;
        else{
            if(cnt[seq[i]] == 0) diff++;
            cnt[seq[i]]++;
        }
        if(i < s && diff == i+1) forw[i] = true;
    }
    for(int i = 0; i < s; i++){ // 滑動視窗檢驗 reshuffle 點
        int ok = 1;
        // 所有前面的數字都不一樣
        if(i != 0 && !forw[i-1]) continue;
        // 播放紀錄從位置 i 起有幾段的重播循環
        for(int j = i; j < len && ok; j += s){
            if(!back[j]) ok = 0;            
        }
        ans += ok;
    }
    printf("%d\n", ans);
}

int main()
{
    int cas;
    scanf("%d", &cas);

    while(cas--)
    {
        scanf("%d %d", &s, &len);
        for(int i = 0; i < len; i++){
            scanf("%d", &seq[i]);
        }
        solve();
    }
}
