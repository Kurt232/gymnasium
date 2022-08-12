#include<iostream>
#include<math.h>

using namespace std;

int n, a[1001];
double _a, d;

int main(){
    cin>>n;
    for(int i=1; i<=n; i++){
        cin>>a[i];
        _a+=a[i];
    }
    _a/=n;
    for(int i=1; i<=n; i++){
        d+=pow(a[i]-_a, 2);
    }
    d/=n;
    for (int i = 1; i <=n; i++){
        cout<<(a[i]-_a)/sqrt(d)<<endl;
    }
}

//AC