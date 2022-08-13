#include <math.h>
#include <cstdio>
#include <utility>

#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define MAXN 500002

using namespace std;

int n, q;
int L[MAXN << 2], R[MAXN << 2];
double sumx[MAXN << 2], sumy[MAXN << 2], sumxx[MAXN << 2], sumyy[MAXN << 2],
    sumxy[MAXN << 2];
// lazy tag
//矩阵matrix运算
double addv[MAXN << 2][2]; //(x, y)
double mulv[MAXN << 2][4]; // init: ((1,0); (0,1))

void update(int rt, const double& m0, const double& m1, const double& m2, const double& m3, const double& v0, const double& v1){//right
    int m = R[rt] - L[rt] + 1;
    double sumxyt = sumxy[rt], sumxxt = sumxx[rt], sumxt = sumx[rt];
    sumxy[rt] = m0 * m2 * sumxx[rt] + m1 * m3 * sumyy[rt] +
                (m0 * m3 + m1 * m2) * sumxy[rt] +
                (m0 * v1 + m2 * v0) * sumx[rt] +
                (m1 * v1 + m3 * v0) * sumy[rt] +
                m * v0 * v1;
    sumxx[rt] = m0 * m0 * sumxx[rt] + m1 * m1 * sumyy[rt] +
                2 * m0 * v0 * sumx[rt] + 2 * m1 * v0 * sumy[rt] +
                2 * m0 * m1 * sumxyt + m * v0 * v0;
    sumyy[rt] = m2 * m2 * sumxxt + m3 * m3 * sumyy[rt] +
                2 * m2 * v1 * sumx[rt] + 2 * m3 * v1 * sumy[rt] +
                2 * m2 * m3 * sumxyt + m * v1 * v1;
    sumx[rt] = sumx[rt] * m0 + sumy[rt] * m1 + v0 * m;
    sumy[rt] = sumxt * m2 + sumy[rt] * m3 + v1 * m;
    double mt0 = mulv[rt][0], mt1 = mulv[rt][1], mt2 = mulv[rt][2],
            mt3 = mulv[rt][3], vt0 = addv[rt][0], vt1 = addv[rt][1];
    mulv[rt][0] = m0 * mt0 + m1 * mt2;
    mulv[rt][1] = m0 * mt1 + m1 * mt3;
    mulv[rt][2] = m2 * mt0 + m3 * mt2;
    mulv[rt][3] = m2 * mt1 + m3 * mt3;
    addv[rt][0] = m0 * vt0 + m1 * vt1 + v0;
    addv[rt][1] = m2 * vt0 + m3 * vt1 + v1;
}

void push_up(int rt){
    sumx[rt] = sumx[ls] + sumx[rs];
    sumy[rt] = sumy[ls] + sumy[rs];
    sumxx[rt] = sumxx[ls] + sumxx[rs];
    sumyy[rt] = sumyy[ls] + sumyy[rs];
    sumxy[rt] = sumxy[ls] + sumxy[rs];
}

//人为规定顺序
// x = t*x + s
//而不是 x = t*(x+s)
//从而对后续程序也有影响
void push_down(int rt){
    // update tag of sons
    int m = R[rt] - L[rt] + 1;
    double(&mat)[4] = mulv[rt], (&vec)[2] = addv[rt];
    update(ls, mat[0], mat[1], mat[2], mat[3], vec[0], vec[1]);
    update(rs, mat[0], mat[1], mat[2], mat[3], vec[0], vec[1]);
    mat[0] = 1, mat[1] = 0, mat[2] = 0, mat[3] = 1, vec[0] = 0, vec[1] = 0;
}

void build(int rt, int l, int r){
    L[rt] = l, R[rt] = r;
    mulv[rt][0]=mulv[rt][3]=1;
    mulv[rt][1]=mulv[rt][2]=addv[rt][0]=addv[rt][1]=0;
    if (l == r){
        scanf("%lf %lf", sumx + rt, sumy + rt);
        sumxx[rt] = sumx[rt] * sumx[rt];
        sumyy[rt] = sumy[rt] * sumy[rt];
        sumxy[rt] = sumx[rt] * sumy[rt];
        return;
    }
    int mi = l + ((r - l) >> 1);//>>低于+ 
    build(ls, l, mi);
    build(rs, mi + 1, r);
    push_up(rt);
}

void op1(int rt, int l, int r, double a, double b){
    if (L[rt] > r || R[rt] < l) return;
    if (L[rt] == l && R[rt] == r){
        update(rt, 1, 0, 0, 1, a, b);
        return;
    }
    push_down(rt);
    int mi = L[rt] + ((R[rt] - L[rt]) >> 1);
    if (r <= mi) op1(ls, l, r, a, b);
    else if (mi < l) op1(rs, l, r, a, b);
    else op1(ls, l, mi, a, b), op1(rs, mi + 1, r, a, b);
    push_up(rt);
}

void op2(int rt, int l, int r, double a, double b, double t){
    if (L[rt] > r || R[rt] < l) return;
    if (l == L[rt] && r == R[rt]) {
        const double& cost = cos(t), &sint = sin(t);
        update(rt, cost, -sint, sint, cost, a-a*cost +sint*b, b-sint*a - cost*b);
    }
    push_down(rt);
    int mi = L[rt] + ((R[rt] - L[rt]) >> 1);
    if (r <= mi) op2(ls, l, r, a, b, t);
    else if (mi < l) op2(rs, l, r, a, b, t);
    else op2(ls, l, mi, a, b, t), op2(rs, mi + 1, r, a, b, t);
    push_up(rt);
}

void op3(int rt, int l, int r, double a, double b, double t){
    if (L[rt] > r || R[rt] < l) return;
    if (l == L[rt] && r == R[rt]){
        update(rt, t, 0, t, 0, (1-t)*a, (1-t)*b);
    }
    push_down(rt);
    int mi = L[rt] + ((R[rt] - L[rt]) >> 1);
    if (r <= mi) op3(ls, l, r, a, b, t);
    else if (mi < l) op3(rs, l, r, a, b, t);
    else op3(ls, l, mi, a, b, t), op3(rs, mi + 1, r, a, b, t);
    push_up(rt);
}

void op4(int rt, int l, int r, double t, double y){
    if (L[rt] > r || R[rt] < l) return;
    if (l == L[rt] && r == R[rt]){
        const double& _2t = 2*atan(atan(t)), cos2t = cos(_2t), sin2t = sin(_2t);
        update(rt, cos2t, sin2t, sin2t, -cos2t, -sin2t*y, (1+cos2t)*y);
    }
    push_down(rt);
    int mi = L[rt] + ((R[rt] - L[rt]) >> 1);
    if (r <= mi) op4(ls, l, r, t, y);
    else if (mi < l) op4(rs, l, r, t, y);
    else op4(ls, l, mi, t, y), op4(rs, mi + 1, r, t, y);
    push_up(rt);
}

void op5(int rt, int l, int r, double t, double y){
    if (L[rt] > r || R[rt] < l) return;
    if (l == L[rt] && r == R[rt]){
        const double& cost = cos(atan(atan(t))), sint = sin(atan(atan(t)));
        update(rt, cost*cost, sint*cost, sint*cost, sint*sint, -sint*cost*y, (1 - sint*sint)*y);
    }
    push_down(rt);
    int mi = L[rt] + ((R[rt] - L[rt]) >> 1);
    if (r <= mi) op5(ls, l, r, t, y);
    else if (mi < l) op5(rs, l, r, t, y);
    else op5(ls, l, mi, t, y), op5(rs, mi + 1, r, t, y);
    push_up(rt);
}

pair<double, double> op6(int rt, int l, int r){
    if (L[rt] > r || R[rt] < l) return make_pair(0, 0);
    if (l == L[rt] && r == R[rt]) {
        return make_pair(sumx[rt], sumy[rt]);
    }
    push_down(rt);
    int mi = L[rt] + ((R[rt] - L[rt]) >> 1);
    if (r <= mi) return op6(ls, l, r);
    else if (mi < l) return op6(rs, l, r);
    else {
        const pair<double, double>& t1 = op6(ls, l, mi), t2 = op6(rs, mi + 1, r);
        return make_pair(t1.first + t2.first, t1.second + t2.second);
    }
}

double op7(int rt, int l, int r, double a, double b){
    if (L[rt] > r || R[rt] < l) return 0;
    if (l == L[rt] && r == R[rt]){
        return sumxx[rt] + sumyy[rt] - sumx[rt] * a * 2 - sumy[rt] * b * 2 +
               (r - l + 1) * (a * a + b * b);
    }
    push_down(rt);
    int mi = L[rt] + ((R[rt] - L[rt]) >> 1);
    if (r <= mi) return op7(ls, l, r, a, b);
    else if (mi < l) return op7(rs, l, r, a, b);
    else return op7(ls, l, mi, a, b) + op7(rs, mi + 1, r, a, b);
}

int main(){
    scanf("%d %d", &n, &q);
    build(1, 1, n);
    int op, l, r;
    double a, b, theta, lambda, y0;
    pair<double, double> t;
    while (q--){
        scanf("%d %d %d", &op, &l, &r);
        switch (op){
        case 1:
            scanf("%lf %lf", &a, &b);
            op1(1, l, r, a, b);
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
            t = op6(1, l, r);
            printf("%lf, %lf\n", t.first / (r - l + 1), t.second / (r - l + 1));
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