/*
중량제한 - BOJ 1939

시간복잡도 : O((N+M)logC)
공간복잡도 : O(N+M)

문제 접근
        시간제한 1초인데 C에 대한 범위가 매우 크다.
        정답 중량은 [1, max(C)] 이라는 monotonic하게 증가하는 구간 안에 존재.

        해당 중량에 대해 가능한지 여부를 판단하며 이분탐색으로 답을 찾을 수 있다.

        1. 각 섬을 연결하는 다리를 인접 리스트로 표시 (다리가 여러개면 maxC 하나만 저장)
        (이 때 인접행렬 쓰면 10^4^2 = 10^8, 메모리 약 400MB로 메모리 초과)
        2. 이분 탐색으로 가능한 중량의 upperbound 찾기
        가능한지 판별 → BFS로 탐색해서 도달 가능한지 검사
        

제출 결과
메모리: 13900KB, 시간: 172ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <unordered_map>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int n;

struct edge{
    int next;
    int weightLimit;
};

bool isValid(const vector<vector<edge>>& adjList, int num, int startIdx, int endIdx);
int bSearch(const vector<vector<edge>>& adjList, int startIdx, int endIdx, int l, int r);

int main() {
    int m; cin >> n >> m;

    vector<std::unordered_map<int,int>> temp(n + 1); // 중복 제거용 컨테이너
    int a, b, c, cMax = 0;
    for (int i = 0; i < m; ++i){
        cin >> a >> b >> c;
        temp[a][b] = std::max(temp[a][b], c);
        temp[b][a] = temp[a][b];
        cMax = std::max(c, cMax);
    }

    vector<vector<edge>> adjList(n+1); // 가장 가중치가 큰 다리만 남김
    for (int i = 1; i <= n; ++i) {
        for (auto [next, w] : temp[i]){
            adjList[i].push_back({next, w});
    }
}

    int startIdx, endIdx; cin >> startIdx >> endIdx;
    cout << bSearch(adjList, startIdx, endIdx, 1, cMax);

    return 0;
}

bool isValid(const vector<vector<edge>>& adjList, int num, int startIdx, int endIdx){
    vector<bool> visited(n+1, false);
    
    std::deque<int> q;
    q.emplace_back(startIdx); visited[startIdx] = true;

    while (!q.empty()){
        int currentIsland = q.front(); q.pop_front();
        if (currentIsland == endIdx) return true;

        for (auto edge: adjList[currentIsland]){
            if (!visited[edge.next] && edge.weightLimit >= num){
                visited[edge.next] = true;
                q.emplace_back(edge.next);
            }
        }
    }

    return false;
}

int bSearch(const vector<vector<edge>>& adjList, int startIdx, int endIdx, int l, int r){
    int ans = 0;
    while (l <= r){
        int m = l + (r-l)/2;

        if (isValid(adjList, m, startIdx, endIdx)){
            ans = m;
            l = m + 1;
        }
        else r = m - 1;
    }
    return ans;
}