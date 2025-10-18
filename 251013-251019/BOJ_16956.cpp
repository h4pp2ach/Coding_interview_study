/*
늑대와 양 - BOJ 16956

시간복잡도 : O(rc)
공간복잡도 : O(rc)

문제 접근
        상하좌우 내로 완전히 붙어있지만 않으면, 격리 가능함.
        완전탐색으로 풀어도 최대 입력갯수일 때 격자 수 N = 250000 이므로 2초안에 충분히 가능.

        처음 맵 정보 받을 때 양이나 늑대 자리 아니면 전부 울타리로 채워버리고,
        양 좌표는 받은 후 상하좌우의 유효한 좌표들을 전부 리스트에 저장.
        map에서 해당 좌표들을 검사하며 W가 하나라도 있으면 1, 아니면 0 return

제출 결과
메모리: 8444KB, 시간: 36ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

vector<vector<int>> dxdy = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; //URDL
struct point{
    int x;
    int y;
};

bool isInvalid(int x, int y, int r, int c);
int isPossible(const vector<vector<char>>& mapInfo, const vector<point>& candidateList);

int main() {
    int r, c; cin >> r >> c;
    vector<vector<char>> map(r, vector<char>(c));
    char mapElement; vector<point> candidateList;

    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            cin >> mapElement;
            map[i][j] = mapElement;

            // 빈공간 다 울타리 세워버려
            if (mapElement == '.'){
                map[i][j] = 'D';
            }
            
            // 양이면 인접 좌표 받아서 리스트에 저장해
            if (mapElement == 'S'){
                for (int n = 0; n < 4; ++n){
                    int nx = j + dxdy[n][0];
                    int ny = i + dxdy[n][1];

                    if (isInvalid(nx, ny, r, c)) continue;
                    candidateList.push_back({nx, ny});
                }
            }
        }
    }

    cout << isPossible(map, candidateList) << std::endl;

    for (const vector<char>& row: map){
        for (const char& x: row) cout << x;
        cout << std::endl;
    }

    return 0;
}

bool isInvalid(int x, int y, int r, int c){
    return (x < 0 || x >= c || y < 0 || y >= r);
}

int isPossible(const vector<vector<char>>& mapInfo, const vector<point>& candidateList){
    for (const auto& p: candidateList){
        if (mapInfo[p.y][p.x] == 'W') return 0;
    }
    return 1;
}