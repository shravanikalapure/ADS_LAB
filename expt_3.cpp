#include <iostream>
#include <queue>
using namespace std;

// DFS & BFS
int a[7][7] = {
    {0, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0, 0},
    {1, 1, 1, 0, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 1},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0}};

//DFS
void DFS(int start, int end, int visited[])
{
    cout << start << " ";
    visited[start] = 1;

    if (start == end)
    {
        cout << "End Reached (DFS)" << endl;
        return;
    }

    for (int j = 0; j < 7; j++)
    {
        if (a[start][j] == 1 && visited[j] == 0)
        {
            DFS(j, end, visited);
            return;
        }
    }
}

//BFS
void BFS(int start, int end, int visit[])
{
    queue<int> q;
    visit[start] = 1;
    q.push(start);

    while (!q.empty())
    {
        int d = q.front();
        q.pop();
        cout << d << " ";

        if (d == end)
        {
            cout << "End Reached (BFS)" << endl;
            return;
        }

        for (int j = 0; j < 7; j++)
        {
            if (a[d][j] == 1 && visit[j] == 0)
            {
                visit[j] = 1;
                q.push(j);
            }
        }
    }
}

int main()
{
    int BFSvisit[7] = {0};
    int DFSvisit[7] = {0};

    cout << "DFS Traversal: ";
    DFS(0, 5, DFSvisit);

    cout << "BFS Traversal: ";
    BFS(0, 5, BFSvisit);

    return 0;
}
