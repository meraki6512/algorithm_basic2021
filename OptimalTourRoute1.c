#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define INF 999

int n = 4;
int g[4][4] = { {0,2,9,INF},{1,0,6,4},{INF,7,0,8},{6,3,INF,0} };
int d[16][1 << 16];
int p[4][4] = { 0, };

int min(int a, int b)
{
    return a < b ? a : b;
}

int travel(int from, int c)
{
    int* ret = &d[from][c];
    if (c == (1 << n) - 1) {
        if (g[from][0]) {
            return g[from][0];
        }
        return 1e9;
    }
    if (*ret) 
        return *ret;
    *ret = 1e9;
    for (int i = 0; i < n; i++) {
        if (!(c & (1 << i)) && g[from][i]) {
            *ret = min(*ret, travel(i, c | (1 << i)) + g[from][i]);
        }
    }
    return *ret;
}

int main()
{
    printf("%d\n", travel(0, 1));
    return 0;
}