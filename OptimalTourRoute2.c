#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define INF 999

int n = 7;
int g[20][20] = { {0,4,INF,INF,INF,10,INF},{3,0,INF,18,INF,INF,INF},{INF,6,0,INF,INF,INF,INF},{INF,5,15,0,2,19,5},{INF,INF,12,1,0,INF,INF},{INF,INF,INF,INF,INF,0,10},{INF,INF,INF,8,INF,INF,0} };
int d[16][1 << 16];

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
        if (!(c & (1 << i)) && g[from][i])
            *ret = min(*ret, travel(i, c | (1 << i)) + g[from][i]);
    }
    return *ret;
}

int main()
{
    printf("%d\n", travel(0, 1));
    return 0;
}