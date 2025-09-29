/*
치킨배달 - BOJ 15686

시간복잡도 :
공간복잡도 :

문제 접근
        입력 범위가 크지 않아서, O(N⁴M)일 때 연산수 약 8125만번이라 브루트 포스로 짜도 가능할듯

        전체 맵을 갖고있을 필요가 있을까? 어차피 좌표만 알면 계산 가능한데.

        1. 집의 좌표와 치킨집의 좌표만 받아서 저장해놓자. (1,1)부터 → 방향, 행별로 내려가며 인덱스가 매핑됨
        2. 각 치킨집마다 집 좌표까지 치킨거리를 계산한 리스트 생성
        3. M개의 치킨집을 고름 (조합)
        4. 치킨거리 리스트에서 인덱스별 최솟값을 더해 결과 비교


제출 결과
메모리: 2172KB, 시간: 4ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <cmath>
#include <climits>

#define HOME 1
#define CHICKEN 2

using std::cin;
using std::cout;
using std::vector;
using std::abs;

struct Point{
    int r;
    int c;
};

int n, m;
int numOfHome;
int numOfChickenHouse;

vector<Point> homePointList;
vector<Point> chickenPointList;
vector<vector<int>> chickenDistanceList;

vector<int> comb;
vector<vector<int>> combList;

int getDistance(Point p1, Point p2);
int calCityChickenDistance(vector<int> aliveList);
void makeChickenDistList(Point p_chicken);
void combination(int n, int r);


int main() {
    
    cin >> n >> m;

    // 집과 치킨집의 좌표를 저장
    int val;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j){
            cin >> val;

            if (val == HOME) homePointList.push_back({i, j});
            else if (val == CHICKEN) chickenPointList.push_back({i, j});
        }
    }
    
    numOfHome = homePointList.size();
    numOfChickenHouse = chickenPointList.size();
    

    // 모든 치킨집의 치킨 거리 리스트 생성
    for (Point p_chicken: chickenPointList){
        makeChickenDistList(p_chicken);
    }


    // 치킨집 서바이벌 시작
    comb.assign(numOfChickenHouse, 0);
    combination(0, 0);


    // 도시치킨거리 최소값 계산
    int ans = INT_MAX; int result;
    for (auto arriveList: combList){
        result = calCityChickenDistance(arriveList);
        if (result < ans) ans = result;
    }

    cout << ans;
    return 0;
}


int getDistance(Point p1, Point p2){
    return abs(p1.r - p2.r) + abs(p1.c - p2.c);
}

void makeChickenDistList(Point p_chicken){
    vector<int> chickenDistance;
    for (Point p_home : homePointList) chickenDistance.push_back(getDistance(p_chicken, p_home));
    chickenDistanceList.push_back(chickenDistance);
    return;
}

int calCityChickenDistance(vector<int> aliveList){
    int ans = 0;

    for (int idx_home = 0; idx_home < numOfHome; ++idx_home){

        int min_val = 69;
        for (int idx_ck = 0; idx_ck < numOfChickenHouse; ++idx_ck){
            if (aliveList[idx_ck] && chickenDistanceList[idx_ck][idx_home] < min_val){
                min_val = chickenDistanceList[idx_ck][idx_home];
            }
        }
        ans += min_val;
    }

    return ans;
}

void combination(int idx, int count){
    if (count == m){
        combList.push_back(comb);
        return;
    }
    
    if (idx == numOfChickenHouse) return;

    comb[idx] = 1;
    combination(idx + 1, count + 1);

    comb[idx] = 0;
    combination(idx + 1, count);
}