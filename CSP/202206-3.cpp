#include<cstdio>
#include<math.h>
#define ls (rt<<1)
#define rs (rt<<1|1)
#define MAXN 500000+1

using namespace std;

int n,q;
int L[MAXN<<2], R[MAXN<<2];
double sumx[MAXN<<2], sumy[MAXN<<2], sum2[MAXN<<2];
//lazy

void push_up(int rt){
    sumx[rt] = sumx[ls] + sumx[rs];
    sumy[rt] = sumy[ls] + sumy[rs];
    sum2[rt] = sum2[ls] + sum2[rs];
}

void build(int rt, int l, int r){
    if(l==r){
        scanf("%lf %lf", sumx+rt, sumy+rt);
        sum2[rt] = pow(sumx[rt],2) + pow(sumy[rt], 2);
    }
    int mi = l + (r-l)>>1;
    build(ls, l, mi);
    build(ls, mi+1, r);
    push_up(rt);
}

void op1(int rt, int  l, int r, double a, double b){

}

void op2(int rt, int l, int r, double a, double b, double t){

}

void op3(int rt, int l, int r, double a,  double b, double t){

}

void op4(int rt, int l, int r, double t, double y){

}

void op5(int rt, int l, int r, double t, double y){

}

void op6(int rt, int l, int r){

}

void op7(int rt, int l, int r){

}

int main(){
    scanf("%d %d", &n, &q);
    build(1, 1, n);
    int op, l, r;
    double a, b, theta, lambda, y0;
    while(q--){
        scanf("%d %d %d", &op, &l, &r);
        switch (op)
        {
        case 1:
            scanf("%lf %lf", &a, &b);
            op1(1, l ,r ,a ,b);
            break;
        case 2:
            scanf("%lf %lf %lf", &a, &b, &theta);
            op2(1, l, r, a, b, theta);
            break;
        case 3:
            scanf("%lf %lf %lf", &a, &b, &lambda);
            op3(1, l, r, a, b, theta);
            break;
        case 4:
            scanf("%lf %lf", &theta, &y0);
            op4(1, l, r, theta, y0);
            break;
        case 5:
            scanf("%lf %lf", &theta, &y0);
            op5(1, l, r, theta, y0);
            break;
        case 6:
            op6(1, l ,r);
            break;
        case 7:
            scanf("%lf %lf", &a, &b);
            op7(1, l, r, a, b);
            break;
        default:
            break;
        }
    }
}