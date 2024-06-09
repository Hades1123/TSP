#include "bellman.h"
#include "tsm.h"

#include<cstring>
#include<iomanip>
#include<random>

//! How to run code ? follow 2 step below, write them in your terminal
//* g++ -o main main.cpp bellman.cpp tsm.cpp
//* ./main
const int MAXN = 14;
int BFVal[20], BFPrev[20];

int minCost(string path, char start, int G[20][20])
{
    int result = 0;
    for (int i = 0 ; i <= path.size() - 3; ++ i)
    {
        if (i % 2 == 0)
        {
            int index = path[i] - 65;
            int nextIdx = path[i+2] - 65;
            result += G[index][nextIdx];
        }
    }
    return result;
}
void testBF(int G[][20])
{
    //* Random startVertex
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(65,65 + MAXN - 1);
    char start = char((int) distrib(gen));
    cout << "After Random, StartVetex is: " << start << endl;
    for (int i = 0 ; i < MAXN; ++ i)
    {
        BFVal[i] =-1;
        BFPrev[i] =-1;
    }

    for (int i = 0 ; i < MAXN ; ++ i)
    {
        BF(G, MAXN,start,BFVal,BFPrev);
        cout << "Step: " << i + 1 << endl;
        for (int i = 0 ; i < MAXN; ++ i)
        {
            cout << fixed << setw(2) << BFVal[i] << ' ';
        }
        cout << endl;
        for (int j = 0 ; j < MAXN ; ++ j)
        {
            cout << fixed << setw(2) << BFPrev[j] << ' ';
        }
        cout << endl;
    }
    char goal = char((int) distrib(gen));
    cout << endl;
    cout << "Shortest path from " << start << ' ' << "to " << goal << " :"<< endl;
    cout << BF_Path(G, MAXN, start,goal) << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}

void testTSP(int G[20][20])
{
    cout << "TSP:\n";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(65,65 + MAXN - 1);
    char start = char((int) distrib(gen));
    string path = Traveling(G,MAXN,start);
    cout << "The Optimal Path is: " << path << endl;
    cout << "Minimum Cost is: " << minCost(path,start,G);
}
int main()
{
    int G[20][20] ={
        {0, 90, 96, 100, 59, 21, 14, 68, 44, 34, 74, 50, 4, 48},
        {35, 0, 15, 100, 47, 28, 56, 18, 98, 81, 67, 36, 50, 90},
        {99, 35, 0, 85, 89, 1, 40, 50, 68, 65, 71, 82, 32, 15},
        {15, 6, 31, 0, 87, 20, 66, 68, 86, 79, 62, 7, 97, 60},
        {89, 30, 62, 4, 0, 19, 61, 5, 71, 49, 7, 77, 65, 75},
        {8, 36, 22, 40, 17, 0, 4, 12, 48, 91, 99, 81, 58, 85},
        {59, 20, 92, 56, 46, 46, 0, 86, 7, 50, 71, 34, 22, 7},
        {49, 29, 51, 14, 70, 59, 50, 0, 92, 65, 67, 96, 44, 81},
        {86, 42, 61, 10, 26, 20, 30, 85, 0, 42, 42, 97, 94, 15},
        {47, 30, 50, 35, 4, 65, 64, 55, 79, 0, 33, 80, 95, 91},
        {44, 61, 87, 88, 42, 38, 97, 69, 48, 22, 0, 89, 44, 73},
        {97, 52, 70, 90, 68, 83, 20, 84, 17, 24, 48, 0, 47, 45},
        {94, 46, 24, 88, 36, 34, 15, 22, 89, 23, 27, 85, 0, 92},
        {75, 73, 47, 86, 12, 43, 37, 82, 100, 71, 30, 86, 20, 0}
    };

    testBF(G);
    testTSP(G);
}