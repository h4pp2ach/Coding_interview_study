/*
쓰레기 치우기 - BOJ 1736

시간복잡도 : O(NM²)
공간복잡도 : O(NM)

문제 접근
        시간제한 2초. 대충 최대 입력에 대해서 O(N⁴)이내로 짜도 됨. (최대입력일 때 N=M)

        아이디어:
        로봇은 →, ↓ 로만 이동하므로 다음 행의 쓰레기가 로봇보다 왼쪽 열에 있다면 주울 수 없음.
        현재 로봇들이 존재하는 열을 리스트로 저장해놓고, 커버 불가능하면 해당 열에 새로운 로봇을 보내자.

        1. row 탐색 → 쓰레기가 위치한 col 확인
        2. 로봇이 커버 가능한 col일 경우, 그대로 진행
        3. 로봇이 커버 가능한 col이 아닐 경우,
            더 낮은 col에 있는 애들 중 가장 가까운 녀석이 해당 col로 이동
            더 낮은 col에 아무도 없으면, 새로운 로봇 추가 후 해당 col에 배치
        4. 가장 아래 row까지 반복


제출 결과
메모리: 2024KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

vector<vector<int>> trashMap;
int n, m;

int solution();
int findNearbyIdx(const vector<int>& v, int col);
void moveRobot(vector<int>& v, int col);

int main() {
    
    cin >> n >> m;
    trashMap.assign(n, vector<int>(m));
    for (auto& row: trashMap){
        for (auto& x: row) cin >> x;
    }

    cout << solution();
    return 0;
}

int solution() {
    int robot = 0;
    vector<int> robotCoverageCol(m, 0);

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col){
            if (trashMap[row][col]){

                int idx = findNearbyIdx(robotCoverageCol, col);

                if (idx == -1){ // 이전 열을 커버하는 로봇이 없으면, 새로운 로봇 출발
                    robot += 1;
                    robotCoverageCol[col] = 1;
                }
                else{ // 해당 열과 가장 가까운 로봇 이동
                    robotCoverageCol[idx] = 0;
                    robotCoverageCol[col] = 1;
                }

            }
        }
    }

    return robot;
}

int findNearbyIdx(const vector<int>& v, int col){
    for (int i = col; i >= 0; --i){
        if (v[i]) return i;
    }
    return -1;
}