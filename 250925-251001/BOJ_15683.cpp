/*
감시 - BOJ 15683

시간복잡도 : O(4^(CCTV 개수) * NM)
공간복잡도 : O(NM)

문제 접근
        시간제한 1초. O(NM) = 64, CCTV 최대 8개 4가지 방향: 4^8 = 65536, 연산 약 420만번.
        입력 범위가 작아서 브루트 포스로 풀어도 여유로울만 하다.

        각 CCTV를 회전시키고, 그때마다 사각지대의 최솟값을 비교해서 갱신

        함수 6개 써서 만들어보자
        1. 회전시킬 CCTV 결정
        2. CCTV 타입에 맞게 회전방향 결정 (2번은 회전방향 2개, 5번은 회전X)
        3. CCTV 상태에 따라 각 타입별 어디로 뻗어나가야하는지 계산
        4. 감시할 수 있는 영역을 #으로 표시 (방향대로 뻗어나가면서 #을 채움)
        5. #이 멈출지 결정 (벽, 맵 바깥 인덱스)
        6. 맵의 사각지대 수 계산

제출 결과
메모리: 2028KB, 시간: 76ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <climits>

using std::cin;
using std::cout;
using std::vector;

int n, m;
int ans;
vector<vector<int>> map;
vector<vector<int>> dxdy = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; // URDL
vector<vector<int>> map_temp;

struct CCTV_INFO{
    int type;
    int state;
    int x;
    int y;
};

void simulate(int idx, vector<CCTV_INFO> cctvList, vector<vector<int>> curMap);
vector<int> getRotations(int type);
vector<int> getDirections(int type, int state);
void checkVisibility(const vector<vector<int>>& map, const vector<CCTV_INFO>& CCTVList);
bool isPossible(int x, int y);
int calInvisibleSection(const vector<vector<int>>& map);

int main() {
    
    cin >> n >> m;
    map.assign(n, vector<int>(m, 0));

    int type;
    vector<CCTV_INFO> cctvList;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> type;
            map[i][j] = type;

            if (type > 0 && type < 6)
                cctvList.push_back({type, 0, i, j});
        }
    }

    ans = INT_MAX;
    simulate(0, cctvList, map); //0번(첫번째 CCTV)부터 시작해서 시뮬레이션

    cout << ans;    
    return 0;
}

void simulate(int idx, vector<CCTV_INFO> cctvList, vector<vector<int>> map){
    //재귀 종료조건 - 모든 CCTV의 회전이 끝
    if (idx == cctvList.size()) { 
        checkVisibility(map, cctvList);
        ans = std::min(ans, calInvisibleSection(map_temp));
        return;
    }

    CCTV_INFO &cctv = cctvList[idx];
    
    // 현재 CCTV에 대해서 회전 수행
    for (int r : getRotations(cctv.type)) {
        cctv.state = r;  // 여기서 회전 입력
        simulate(idx + 1, cctvList, map);
    }
    return;
}

vector<int> getRotations(int type) {
    if (type == 2) return {0, 1};      
    if (type == 5) return {0};          
    return {0, 1, 2, 3};                
}

vector<int> getDirections(int type, int state){
    if (type == 1) return {0 + state};
    if (type == 2) return (state%2 == 0)? vector<int>{0, 2} : vector<int>{1, 3};    // 상하 또는 좌우
    if (type == 3) return {state, (state + 1) % 4};                                 // 연속된 두 방향
    if (type == 4){                                                                 // 한방향 제외 나머지
        vector<int> dirs;
        for (int i = 0; i < 4; i++){
            if (i != state) dirs.push_back(i);
        }
        return dirs;
    }
    if (type == 5) return {0, 1, 2, 3};
}

void checkVisibility(const vector<vector<int>>& map,const vector<CCTV_INFO>& CCTVList){
    map_temp = map;

    for (auto cctv: CCTVList){

        vector<int> dirs = getDirections(cctv.type, cctv.state);

        for (int dir: dirs){
            int x_c = cctv.x;
            int y_c = cctv.y;

            while(1){
                x_c += dxdy[dir][0];
                y_c += dxdy[dir][1];

                if (!isPossible(x_c, y_c)) break;
                if (map_temp[x_c][y_c] == 6) break;

                if (map_temp[x_c][y_c] == 0) map_temp[x_c][y_c] = 7; // # 대신 7로 채움
            }
        }
    }
    return;
}

bool isPossible(int x, int y){
    return !(x < 0 || x >= n || y < 0 || y >= m);
}

int calInvisibleSection(const vector<vector<int>>& map){
    int result = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (map[i][j] == 0) result += 1;
        }
    }

    return result;
}