#include<iostream>
#include<algorithm>

using namespace std;

const int maxn=1010;
int n, l, s, num, ans; // num s 中 树的总数
pair<int, int> tree[maxn];

int ma[52][52];

int main(){
    cin>>n>>l>>s;
    for(int i=0; i<n ; i++){
        cin>>tree[i].first>>tree[i].second;
    }
    int x;

    for(int i=s; i>=0; i--){
        for(int j=0; j<=s; j++){
            cin>>x;
            ma[i][j] =x;
            if(x==1) num++;
        }
    }

    for(int i=0; i<n; i++){
        bool f= true;
        int cnt = 0;
        int x0 = tree[i].first;
        int y0 = tree[i].second;
        for(int j=0; j<n; j++){
            int x = tree[j].first - x0;
            int y = tree[j].second - y0;
            if(0<=x&&x<=s&& x0+s<=l && 0<=y&& y<=s&&y0+s<=l){
                if(ma[x][y]==0) f=0;
                if(ma[x][y]==1) cnt++;
            }
        }
        if(f&&cnt==num) ans++;
    }
    cout<<ans<<endl;
}

//AC