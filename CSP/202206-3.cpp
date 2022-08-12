#include<cstdio>
#include<math.h>
#include<utility>
#define ls (rt<<1)
#define rs (rt<<1|1)
#define MAXN 500001

using namespace std;

int n,q;
int L[MAXN<<2], R[MAXN<<2];
double sumx[MAXN<<2], sumy[MAXN<<2], sumxx[MAXN<<2], sumyy[MAXN<<2];
//lazy tag
//矩阵matrix运算
double addv[MAXN<<2][2];//(x, y)
double mulv[MAXN<<2][4];//init: ((1,0); (0,1))

void push_up(int rt){
    sumx[rt] = sumx[ls] + sumx[rs];
    sumy[rt] = sumy[ls] + sumy[rs];
    sumxx[rt] = sumxx[ls] + sumxx[rs];
    sumyy[rt] = sumyy[ls] + sumyy[rs];
}

//人为规定顺序
//x = t*x + s
//而不是 x = t*(x+s)
//从而对后续程序也有影响
void push_down(int rt){
}

void update(int rt){
    int m = R[rt]-L[rt]+1;
    sumxx[rt] = mx*mx*sumxx[rt] + 2*ax*mx*sumx[rt] + ax*ax*m;
    sumyy[rt] = my*my*sumyy[rt] + 2*ay*my*sumy[rt] + ay*ay*m;
    sumx[rt] = sumx[rt] *mx + ax;
    sumy[rt] = sumy[rt] * my + ay;
}

void build(int rt, int l, int r){
    if(l==r){
        scanf("%lf %lf", sumx+rt, sumy+rt);
        sumxx[rt] = sumx[rt]*sumx[rt];
        sumyy[rt] = sumy[rt]*sumy[rt];
    }
    int mi = l + (r-l)>>1;
    build(ls, l, mi);
    build(ls, mi+1, r);
    push_up(rt);
}

void op1(int rt, int  l, int r, double a, double b){
    if(L[rt]>r||R[rt]<l) return;
    if(L[rt]==l&&R[rt]==r){
        addx[rt] += a;
        addy[rt] += b;
        update(rt);
        return;
    }
    push_down(rt);
    int mi = L[rt] + (R[rt]-L[rt])>>1;
    if(r<=mi) op1(ls, l, r, a, b);
    else if(mi<l) op1(rs, l, r, a, b);
    else op1(ls, l, mi, a, b), op1(rs, mi+1, r, a, b);
    push_up(rt);
}

void op2(int rt, int l, int r, double a, double b, double t){
    if(L[rt]>r||R[rt]<l) return;
    if(l==L[rt]&&r==R[rt]){
        double tx = (1-cos(t)+sin(t));
        double ty = (1-cos(t)-sin(t));
        addx[rt] += tx*a;
        addy[rt] += ty*b;
        mulx[rt] *= tx;
        muly[rt] *= ty;
        update(rt);
    }
    push_down(rt);
    int mi = L[rt] + (R[rt]-L[rt])>>1;
    if(r<=mi) op2(ls, l, r, a, b, t);
    else if(mi<l) op2(rs, l, r, a, b, t);
    else op2(ls, l, mi, a, b, t), op2(rs, mi+1, r, a, b, t);
    push_up(rt);
}

void op3(int rt, int l, int r, double a,  double b, double t){
    if(L[rt]>r||R[rt]<l) return;
    if(l==L[rt]&&r==R[rt]){
        addx[rt] += (1-t)*a;
        addy[rt] += (1-t)*b;
        mulx[rt] *= t;
        muly[rt] *= t;
        update(rt);
    }
    push_down(rt);
    int mi = L[rt] + (R[rt]-L[rt])>>1;
    if(r<=mi) op3(ls, l, r, a, b, t);
    else if(mi<l) op3(rs, l, r, a, b, t);
    else op3(ls, l, mi, a, b, t), op3(rs, mi+1, r, a, b, t);
    push_up(rt);
}

double deltax(double k, double y0){
    return 0;
}

void op4(int rt, int l, int r, double t, double y){
    if(L[rt]>r||R[rt]<l) return;
    if(l==L[rt]&&r==R[rt]){
        update(rt);
    }
    push_down(rt);
    int mi = L[rt] + (R[rt]-L[rt])>>1;
    if(r<=mi) op4(ls, l, r, t, y);
    else if(mi<l) op4(rs, l, r, t, y);
    else op4(ls, l, mi, t, y), op4(rs, mi+1, r, t, y);
    push_up(rt);
}

void op5(int rt, int l, int r, double t, double y){
    if(L[rt]>r||R[rt]<l) return;
    if(l==L[rt]&&r==R[rt]){
    }
    push_down(rt);
    int mi = L[rt] + (R[rt]-L[rt])>>1;
    if(r<=mi) op5(ls, l, r, t, y);
    else if(mi<l) op5(rs, l, r, t, y);
    else op5(ls, l, mi, t, y), op5(rs, mi+1, r, t, y);
    push_up(rt);
}

pair<double, double> op6(int rt, int l, int r){
    if(L[rt]>r||R[rt]<l) return make_pair(0, 0);
    if(l==L[rt]&&r==R[rt]){
        return make_pair(sumx[rt], sumy[rt]);
    }
    push_down(rt);
    pair<double, double> t;
    int mi = L[rt] + (R[rt]-L[rt])>>1;
    if(r<=mi) t = op6(ls, l, r);
    else if(mi<l) t = op6(rs, l, r);
    else {
        pair<double, double> t1 = op6(ls, l, mi), t2 = op6(rs, mi+1, r);
        t = make_pair(t1.first+t2.first, t1.second + t2.second);
    }
    push_up(rt);
    return t;
}

double op7(int rt, int l, int r, double a, double b){
    if(L[rt]>r||R[rt]<l) return 0;
    if(l==L[rt]&&r==R[rt]){
        return sumxx[rt]+sumyy[rt]+sumx[rt]*a*2+sumy[rt]*b*2+(r-l+1)*(a*a+b*b);
    }
    
    double t;
    int mi = L[rt] + (R[rt]-L[rt])>>1;
    if(r<=mi) t = op7(ls, l, r, a, b);
    else if(mi<l) t = op7(rs, l, r, a, b);
    else t = op7(ls, l, mi, a, b) + op7(rs, mi+1, r, a, b);
    push_up(rt);
    return t;
}

int main(){
    scanf("%d %d", &n, &q);
    build(1, 1, n);
    int op, l, r;
    double a, b, theta, lambda, y0;
    pair<double, double> t;
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
            t = op6(1, l ,r);
            printf("%lf, %lf\n", t.first/(r-l+1), t.second/(r-l+1));
            break;
        case 7:
            scanf("%lf %lf", &a, &b);
            printf("%lf\n", op7(1, l, r, a, b));
            break;
        default:
            break;
        }
    }
}