/*
아기 상어 2 - BOJ 17086

시간복잡도 : O(N²M²)
공간복잡도 : O(NM)

문제 접근
        N, M의 최댓값은 50. O(N²M²)해도 연산 약 600만. 시간제한 2초니까 왠만하면 시간초과는 안날듯

        1번 접근) BFS로 전구간 탐색하면서 가장 가까운 1을 만날때까지 찾아보자 → O(N²M²)
        2번 접근) 1에서부터 BFS를 시작하고, 퍼져나가면서 dist 맵을 생성 → O(NM), 대신 메모리가 더 쓰임

제출 결과
메모리: 2024KB, 시간: 104ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using std::cin;
using std::cout;
using std::vector;

int n, m;
vector<vector<int>> map;

int dxdy[8][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}}; // 1칸씩 이동. 0번 인덱스:↑ 부터 시계방향

int bfs(int x, int y);
bool isPossible(int x, int y);

int main() {
    
    cin >> n >> m;

    vector<int> row(m);
    for (int i = 0; i < n; ++i){
        for(int& x: row){
            cin >> x;
        }
        map.push_back(row);
    }

    int ans = -1;
    for (int r = 0; r < n; ++r){
        for (int c = 0; c < m; ++c){
            int safetyDistance = bfs(r, c);
            if (ans < safetyDistance) ans = safetyDistance;
        }
    }

    cout << ans;

    return 0;
}

int bfs(int r, int c){
    int visited[50][50] = {{}};
    std::queue<std::tuple<int, int, int>> q;

    q.emplace(c, r, 0);
    visited[r][c] = 1;

    while (!q.empty()){
        auto [x, y, dist] = q.front(); q.pop();

        if (map[y][x]) return dist;

        for (int i = 0; i < 8; ++i){
            int dx = dxdy[i][0]; int x_new = x + dx;
            int dy = dxdy[i][1]; int y_new = y + dy;

            if (isPossible(x_new, y_new) && !visited[y_new][x_new]){
                visited[y_new][x_new] = 1;
                q.emplace(x_new, y_new, dist + 1);
            }
        }
        
    }

    return -1;
}

bool isPossible(int x, int y){
    return !(x < 0 || x >= m || y < 0 || y >= n);
}