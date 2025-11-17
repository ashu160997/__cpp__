#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <climits>

using namespace std;

void addEdge(vector<vector<int>> &vec, int i, int j)
{
    vec[i][j] = 1;
    vec[j][i] = 1;
}

void displayGraph(vector<vector<int>> &vec, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << vec[i][j] << " ";

        cout << endl;
    }
}

vector<vector<vector<int>>> constuctedge(int V, vector<vector<int>> &edges)
{
    vector<vector<vector<int>>> adj(V);
    for (auto &x : edges)
    {
        int u = x[0];
        int v = x[1];

        int dist = x[2];

        adj[u].push_back({v, dist});
        adj[v].push_back({u, dist});
    }

    return adj;
}

// Returns shortest distances from src to all other vertices
vector<int> dijkstra(int V, vector<vector<int>> &edges, int src)
{
    vector<vector<vector<int>>> adj = constuctedge(V, edges);

    vector<int> dist(V, INT_MAX);

    dist[src] = 0;

    priority_queue<vector<int>, vector<vector<int>>,
                   greater<vector<int>>>
        pq;

    pq.push({0, src});

    while (pq.empty() == false)
    {
        int u = pq.top()[1];

        pq.pop();

        for (auto x : adj[u])
        {
            int v = x[0];
            int dis = x[1];
            if (dist[v] > dist[u] + dis)
            {
                dist[v] = dist[u] + dis;
                pq.push({dist[v], v});
            }
        }

        return dist;
    }
}

bool isBipartite(int V, vector<vector<int>> &edges)
{
    vector<int> color(V, -1);

    queue<int> q;

    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            color[i] = 0;
            q.push(i);
            while (q.empty() == false)
            {
                int x = q.front();
                q.pop();

                for (int j = 0; j < V; j++)
                {
                    if (edges[x][j] == 1 && color[j] == -1)
                    {
                        color[j] = 1 - color[x];
                        q.push(j);
                    }
                    else if (edges[x][j] == 1 && color[j] != -1)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
}

void bfs(vector<vector<int>> &adj, int s)
{
    int n1 = adj.size();
    bool visited[n1];

    for (int i = 0; i < n1; i++)
        visited[i] = false;

    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (q.empty() == false)
    {
        int l = q.front();
        q.pop();
        cout << l << " ";

        int m = adj[s].size();

        for (int i = 0; i < m; i++)
        {
            int k1 = adj[l][i];
            if (visited[i] == false && k1 == 1)
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

bool isCyclicUtil(vector<vector<int>> &adj, int u, vector<bool> &recstack, vector<bool> &visited)
{
    if (recstack[u] == true)
    {
        return true;
    }

    if (visited[u] == true)
        return false;

    recstack[u] = true;
    visited[u] = true;

    for (auto x : adj[u])
    {
        if (isCyclicUtil(adj, x, recstack, visited))
            return true;
    }

    recstack[u] = false;

    return false;
}

vector<vector<int>> constructadj(int V, vector<vector<int>> &edges)
{
    vector<vector<int>> adj(V);

    for (auto x : edges)
    {
        adj[x[0]].push_back(x[1]);
    }

    return adj;
}

bool isCyclic(int V, vector<vector<int>> &edges)
{
    vector<bool> recstack(V, false);
    vector<bool> visited(V, false);

    vector<vector<int>> adj = constructadj(V, edges);

    for (int i = 0; i < V; i++)
    {
        if (visited[i] == false && isCyclicUtil(adj, i, recstack, visited) == true)
            return true;
    }

    return false;
}

// dfs recrusion function

void dfs_rec(vector<vector<int>> &adj, int n, bool visited[], int s)
{
    cout << s << " ";
    visited[s] = true;

    int m = adj[s].size();

    for (int i = 0; i < m; i++)
    {
        if (adj[s][i] == 1 && visited[i] == false)
        {
            dfs_rec(adj, n, visited, i);
        }
    }
}

// depth first search

void dfs(vector<vector<int>> &adj, int n, int s)
{
    bool visit[n];

    for (int i = 0; i < n; i++)
    {
        visit[i] = false;
    }

    dfs_rec(adj, n, visit, s);
}

bool isSafe(int i, int j, int m, int n)
{
    if (i >= 0 && j >= 0 && i < m && j < n)
        return true;

    return false;
}

int orangesRotting(vector<vector<int>> &mat)
{
    int n = mat.size();
    int m = mat[0].size();

    queue<vector<int>> q;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 2)
            {
                q.push({i, j});
            }
        }
    }

    int count = 0;

    while (q.empty() == false)
    {
        count++;
        int l = q.size();

        while (l--)
        {
            vector<int> v1 = q.front();
            q.pop();

            int x = v1[0];
            int y = v1[1];

            if (isSafe(x + 1, y, n, m) == true && mat[x + 1][y] == 1)
            {
                mat[x + 1][y] = 2;
                q.push({x + 1, y});
            }

            if (isSafe(x, y + 1, n, m) == true && mat[x][y + 1] == 1)
            {
                mat[x][y + 1] = 2;
                q.push({x, y + 1});
            }

            if (isSafe(x - 1, y, n, m) == true && mat[x - 1][y] == 1)
            {
                mat[x - 1][y] = 2;
                q.push({x - 1, y});
            }

            if (isSafe(x, y - 1, n, m) == true && mat[x][y - 1] == 1)
            {
                mat[x][y - 1] = 2;
                q.push({x, y - 1});
            }
        }
    }

    // cout<<count<<endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 1)
            {
                cout << "value of i " << i << endl;
                cout << "value of j " << j << endl;

                return -1;
            }
        }
    }

    return max(0, count - 1);
}

bool safe(vector<vector<char>> &grid, int i, int j, int n, int m, vector<vector<bool>> &visited)
{
    if ((i >= 0) && (j >= 0) && (i < n) && (j < m) && (grid[i][j] == 'L') && (visited[i][j] == false))
    {
        return true;
    }
    return false;
}

void dfs_island(vector<vector<char>> &grid, int i, int j, vector<vector<bool>> &visited)
{
    int n = grid.size();
    int m = grid[0].size();

    visited[i][j] = true;
    cout << "making i & j true " << i << " " << j << endl;

    int row[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int col[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int l = 0; l < 8; l++)
    {
        if (safe(grid, i + row[l], j + col[l], n, m, visited) == true)
        {
            dfs_island(grid, i + row[l], j + col[l], visited);
        }
    }
}

int countIslands(vector<vector<char>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'L' && visited[i][j] == false)
            {
                count++;
                cout << " i and j and count are " << i << " " << j << " " << count << endl;
                dfs_island(grid, i, j, visited);
            }
        }
    }

    return count;
}

// snake and ladder problem
// Create a visited array to keep track of visited cells during the BFS traversal of the board.
// Initialize a queue that stores pairs of current cell index and the number of moves taken.
// Begin from cell 0 with distance 0, mark it visited, and push into the queue as the starting point.
// While the queue is not empty, extract the front element and get its current cell and distance.
// If the current cell is the last one, return the distance as it represents minimum dice throws.
// Loop through all possible next 6 cells using a dice roll and for each, check snake or ladder jump.
// If the destination cell is not visited, mark it visited and enqueue it with distance incremented by 1.

int getMinDiceThrows(vector<int> &move)
{
    int n = move.size();
    vector<bool> visited(n, false);
    queue<vector<int>> q;

    visited[0] = true;

    q.push({0, 0});

    while (q.empty() == false)
    {
        vector<int> v1 = q.front();
        q.pop();

        int src = v1[0];
        int dist = v1[1];

        if (src == n - 1)
        {
            return dist;
        }

        for (int i = src + 1; i <= src + 6; i++)
        {
            if (visited[i] == false)
            {
                visited[i] = true;
                if (move[i] != -1)
                {
                    src = move[i];
                    q.push({src, dist + 1});
                }
                else
                {
                    src = i;
                    q.push({src, dist + 1});
                }
            }
        }
    }

    return -1;
}

// prims algorithm for minimum spanning tree

void printMST(vector<int> &parent, vector<vector<int>> &graph)
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < graph.size(); i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[parent[i]][i] << " \n";
}

int minKey(vector<int> minSet, vector<bool> visited, int V)
{
    int mink = INT_MAX;

    for (int i = 0; i < V; i++)
    {
        if (visited[i] == false && minSet[i] < mink)
            mink = minSet[i];
    }
    return mink;
}

int prim_mst(vector<vector<int>> &graph)
{
    int V = graph.size();
    vector<int> parent(V, -1);
    vector<int> minSet(V, INT_MAX);
    vector<bool> visited(V, false);

    parent[0] = -1;
    minSet[0] = 0;

    for (int i = 0; i < V; i++)
    {
        int u = minKey(minSet, visited, V);
        minSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] != 0 && visited[v] == false && graph[u][v] < minSet[v])
            {
                parent[v] = u;
                minSet[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph);
}

int main()
{
    // creating graph
    /*int V = 5;


    addEdge(mat,0,1);
    addEdge(mat,0,2);
    addEdge(mat,0,3);
    addEdge(mat,2,4);
    displayGraph(mat,5);

    bfs(mat,0); */
    // dfs(mat,5,0);

    // vector<vector<int>> mat = {{2, 1, 0, 2, 1}, {1, 0, 1, 2, 1}, {1, 0, 0, 2, 1}};
    // cout << orangesRotting(mat);

    /*vector<vector<char>> grid = { { 'L', 'W', 'W', 'W', 'W' },
                                  { 'W', 'L', 'W', 'W', 'L' },
                                  { 'L', 'W', 'W', 'L', 'L' },
                                  { 'W', 'W', 'W', 'W', 'W' },
                                  { 'L', 'W', 'L', 'L', 'W' } };

    cout << countIslands(grid) << endl;

    */

    /* int V=4;

     vector<vector<int>> mat(V,vector<int>(V,0));
     addEdge(mat,0,1);
     addEdge(mat,1,2);
     addEdge(mat,0,2);
     addEdge(mat,2,3);

     if(isBipartite(V, mat))
          cout << "true";
      else
          cout << "false";

      return 0;
      */

    /*
    int n = 30;
     vector<int> moves(n, -1);

     // Ladders
     moves[2] = 21;
     moves[4] = 7;
     moves[10] = 25;
     moves[19] = 28;

     // Snakes
     moves[26] = 0;
     moves[20] = 8;
     moves[16] = 3;
     moves[18] = 6;

     cout << getMinDiceThrows(moves);
     return 0;

     */

    // int V = 4; // Number of vertices

    // Directed edges of the graph
    // vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}, {2, 3}};

    // Output whether the graph contains a cycle
    // cout << (isCyclic(V, edges) ? "true" : "false") << endl;

    /*

        int V = 5;
        int src = 0;

        // edge list format: {u, v, weight}
        vector<vector<int>> edges = {{0, 1, 4}, {0, 2, 8}, {1, 4, 6},
                                     {2, 3, 2}, {3, 4, 10}};

        vector<int> result = dijkstra(V, edges, src);

        // Print shortest distances in one line
        for (int dist : result)
            cout << dist << " ";

        return 0;

        */

    vector<vector<int>> graph = {{0, 2, 0, 6, 0},
                                 {2, 0, 3, 8, 5},
                                 {0, 3, 0, 0, 7},
                                 {6, 8, 0, 0, 9},
                                 {0, 5, 7, 9, 0}};

    // Print the solution
    prim_mst(graph);

    return 0;
}