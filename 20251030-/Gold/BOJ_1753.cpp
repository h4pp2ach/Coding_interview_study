/*
최단경로 - BOJ1753

시간복잡도 : O((E+V)logV)
공간복잡도 : O(V+E)

문제 접근
        가중치가 있으니까, 다익스트라 알고리즘 사용해서 풀어보자
        반복문으로 구현하면 O(V²)이라서 V = 20000일 때 시간제한 1초 초과날듯.
        우선순위 큐 사용해서 구현해보자
        

제출 결과
메모리: 20968KB, 시간: 872ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int V, E, K; 

struct edge{
    int node, cost;
    bool operator<(const edge& other) const {
        return cost > other.cost;
    }
};

vector<int> dijkstra(const vector<vector<edge>>& adjList);

int main() {
    
    cin >> V >> E >> K;

    vector<std::unordered_map<int,int>> temp(V + 1); // 중복 제거용 컨테이너
    int u, v, w;
    for (int i = 0; i < E; ++i){
        cin >> u >> v >> w;
        if (temp[u].count(v)) temp[u][v] = std::min(temp[u][v], w);
        else temp[u][v] = w;
    }

    // 가장 가중치가 작은 간선만 남김
    vector<vector<edge>> adjList(V + 1);
    for (int i = 1; i <= V; ++i) {
        for (auto [next, w] : temp[i]){
            adjList[i].push_back({next, w});
        }
    }

    vector<int> distList = dijkstra(adjList);

    for (int i = 1; i <= V; ++i){
        if (distList[i] == INT_MAX) cout << "INF";
        else cout << distList[i];
        cout << std::endl;
    }

    return 0;
}

vector<int> dijkstra(const vector<vector<edge>>& adjList){
    vector<int> dist(V+1, INT_MAX); dist[K] = 0;
    std::priority_queue<edge> q;

    q.push({K, 0});

    // u: 현재, v: 다음
    while (!q.empty()){
        edge u = q.top(); q.pop();

        if (dist[u.node] < u.cost) continue;

        for (edge v: adjList[u.node]){
            int newDist = dist[u.node] + v.cost;
            
            if (newDist < dist[v.node]){
                dist[v.node] = newDist;
                q.push({v.node, newDist});
            }
        }
    }

    return dist;
}