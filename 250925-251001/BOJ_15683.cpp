/*
감시 - BOJ 15683

시간복잡도 :
공간복잡도 :

문제 접근
        시간제한 1초. O(NM) = 64, CCTV 최대 8개 4가지 방향: 4^8 = 65536, 연산 약 420만번.
        입력 범위가 작아서 브루트 포스로 풀어도 여유로울만 하다.

        각 CCTV를 회전시키고, 그때마다 사각지대의 최솟값을 비교해서 갱신

        함수 5개 써서 만들어보자
        1. 회전시킬 CCTV 결정
        2. CCTV 회전 (2번은 회전방향 2개, 5번은 회전X)
        3. 감시할 수 있는 영역을 #으로 표시 (방향대로 뻗어나가면서 #을 채움)
        4. #이 멈출지 결정 (벽, 맵 바깥 인덱스)
        5. 맵의 사각지대 수 계산

제출 결과
메모리: KB, 시간: ms

*/

#include <iostream> 
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;

int n, m;
int ans;
int numOfCCTV;
vector<vector<int>> map;
vector<vector<int>> dxdy = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // UDLR

struct CCTV_INFO{
    int type;
    int state;
    int x;
    int y;
};

void simulate();
void rotateCCTV(CCTV_INFO *info, int num);
void checkVisibility(vector<vector<int>> map, vector<CCTV_INFO> infoList);
bool isPossible(int x, int y);
int calInvisibleSection(vector<vector<int>> map);

int main() {
    
    cin >> n >> m;
    map.assign(n, vector<int>(m, 0));

    int type;
    vector<CCTV_INFO> cctvList;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> type;
            map[i][j] = type;

            if (type > 0 && type < 6){
                numOfCCTV += 1;
                cctvList.push_back({type, 0, i, j});
            }
        }
    }

    simulate();

    cout << ans;
    return 0;
}

void simulate(){

}

void rotateCCTV(CCTV_INFO *info, int num){

}

void checkVisibility(vector<vector<int>> map,vector<CCTV_INFO> infoList){
    
}

bool isPossible(int x, int y){
    return !(x < 0 || x >= n || y < 0 || y >= n);
}

int calInvisibleSection(vector<vector<int>> map){
    int result = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (map[i][j] == 0) result += 1;
        }
    }

    return result;
}