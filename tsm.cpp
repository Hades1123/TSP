#include "tsm.h"
#include<bitset>
const int INF = 1e9;
const int MAXN = 20;

int dist[MAXN][MAXN];
int dp[MAXN][1 << MAXN]; 
int parent[MAXN][1 << MAXN];

void init(int G[20][20], int numVertice)
{
    for (int i = 0 ; i < MAXN ; ++ i)
    {
        for (int j = 0 ; j < (1 << MAXN); ++ j)
        {
            parent[i][j] = -1;
            dp[i][j] = -1;
        }
    }

    for (int i = 0 ; i < numVertice; ++ i)
    {
        for (int j = 0 ; j < numVertice ; ++ j)
        {
            if (i == j)
            {
                dist[i][j] = 0;
            }
            else
            {
                if (G[i][j] == 0)
                {
                    dist[i][j] = INF;
                }
                else
                {
                    dist[i][j] = G[i][j];
                }
            }
        }
    }
}

int solve(int pos, int mask, int n, int start) 
{
    if (__builtin_popcount(mask) == n)
    {
        parent[pos][mask] = start;
        return dist[pos][start]; 
    }
        
    if (dp[pos][mask] != -1)
        return dp[pos][mask];

    int ans = INF;
    for (int city = 0; city < n; city++) 
    {
        if ((mask & (1 << city)) == 0) 
        {
            int newAns = dist[pos][city] + solve(city, mask | (1 << city), n, start);
            if (newAns < ans) 
            {
                ans = newAns;
                parent[pos][mask] = city;
            }
        }
    }

    return dp[pos][mask] = ans;
}

char numToChar(int n)
{
    return (n + 'A');
}

string Traveling(int G[20][20], int n, char start) 
{

    init(G, n);
    int startIdx = start - 'A';
    int minCost = solve(startIdx, 1 << startIdx, n, startIdx);
    int mask = 1 << startIdx;
    int pos = startIdx;
    string path = "";
    path.push_back(numToChar(pos));
    path += " ";
    cout << "parent[" << pos << "][" << bitset<14>(mask) << "] :  " << parent[pos][mask] << endl; 
    do
    {
        pos = parent[pos][mask];
        mask = mask | (1 << pos);
        cout << "parent[" << pos << "][" << bitset<14>(mask) << "] :  " << parent[pos][mask] << endl;
        path.push_back(numToChar(pos));
        path += " ";
    
    }
    while (mask != (1 << n) - 1); 
    path.push_back(numToChar(startIdx));
    return path;
}

