#include "bellman.h"

void BF(int graph[][20], int num_vertices, char start_vertex, int BFVal[], int BFPrev[]) 
{
    if (BFVal[0] != 0)
        BFVal[start_vertex - 'A'] = 0;
    int prevVal[num_vertices + 1];
    for (int i = 0 ; i < num_vertices; ++ i)
    {
        if (BFVal[i] == -1)
        {
            prevVal[i] = INT_MAX;
        }
        else
        {
            prevVal[i] = BFVal[i];
        }
    }
    for (int u = 0; u < num_vertices; ++ u)
    {
        if (prevVal[u] == INT_MAX)
        {
            continue;
        }
        for (int v = 0; v < num_vertices; ++ v)
        {
            if (graph[u][v] > 0)
            {
                if (prevVal[u] + graph[u][v] < BFVal[v] || BFVal[v] == -1)
                {
                    BFVal[v] = prevVal[u] + graph[u][v];
                    BFPrev[v] = u;
                }
            }
        }
    }
}
string BF_Path(int graph[][20], int num_vertices, char start_char, char goal_char) 
{
   
    int BFVal[num_vertices + 1];
    int BFPrev[num_vertices + 1];
    for (int i = 0 ; i < num_vertices;  ++ i)
    {
        BFVal[i] = -1;
        BFPrev[i] = -1;
    }
    for (int i = 1 ; i <= num_vertices - 1 ; ++ i)
    {
        BF(graph,num_vertices,start_char,BFVal,BFPrev);
    }

    string path = "";
    int t = BFPrev[goal_char - 65];
    path.push_back(goal_char);
    while(t != int(start_char))
    {
        if (t == -1)
            break;
        path.push_back(char(t + 65));
        t = BFPrev[t];
    }
    string res = "";
    for (int i = path.size() - 1 ; i >= 0; --i)
    {
        if (i != 0)
        {
            res.push_back(path[i]);
            res.push_back(' ');
        }
        else
        {
            res.push_back(path[i]);
        }
    }
    return res;
}