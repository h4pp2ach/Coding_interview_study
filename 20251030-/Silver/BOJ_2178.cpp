/*
미로 탐색 - BOJ 2178

시간복잡도 : O(NM)
공간복잡도 : O(NM)

문제 접근
        가중치 없는 최단거리 문제 → BFS로 접근
        방문 배열 사용해서, BFS로 (N, M) 도착할때까지 돌려보자
        미로 입력이 붙어서 들어오니까, string 배열로 미로 선언하는게 나을듯

제출 결과
메모리: 2028KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <algorithm>
#include <string>
#include <deque>

using std::cin;
using std::cout;
using std::vector;
using std::string;

vector<vector<int>> dxdy = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

struct P{
    int x, y, count;
};

bool isInvalid(const vector<string>& maze, int n, int m, int x, int y);
int bfs(const vector<string>& maze, int n, int m);

int main() {
    
    int n, m; cin >> n >> m;
    vector<string> maze(n);
    for (auto& x: maze) cin >> x;

    cout << bfs(maze, n, m);
    return 0;
}

bool isInvalid(const vector<string>& maze, int n, int m, int x, int y){
    return (x >= n || x < 0 || y >= m || y < 0 || maze[x][y] == '0');
}

int bfs(const vector<string>& maze, int n, int m){
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    std::deque<P> Q; Q.push_back({0, 0, 1});
    visited[0][0] = true;

    while (!Q.empty()){
        P currentPoint = Q.front(); Q.pop_front();
        int x_cur = currentPoint.x;
        int y_cur = currentPoint.y;
        int dist = currentPoint.count;

        for (int i = 0; i < 4; ++i){
            int x_new = x_cur + dxdy[i][1];
            int y_new = y_cur + dxdy[i][0];

            if (isInvalid(maze, n, m, x_new, y_new)) continue;
            if (visited[x_new][y_new]) continue;

            if (x_new == n-1 && y_new == m-1) return dist + 1;
            Q.push_back({x_new, y_new, dist+1});
            visited[x_new][y_new] = true;
        }
    }

    return 0;
}