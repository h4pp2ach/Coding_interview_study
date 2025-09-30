/*
주사위 쌓기 - BOJ 2116

시간복잡도 : O(N)
공간복잡도 : O(N)

문제 접근
        시간제한 2초. N <= 10000 이니까, O(N²)이내로만 짜볼까

        1번 주사위의 형태를 결정하는 순간, 나머지 주사위들은 yaw축 회전만 고려하면 된다.
        
        1. 1번 주사위를 결정하고, 옆면 중 최댓값을 더한다.
        2. 규칙에 맞게 쌓아가면서 옆면 중 최댓값을 더한다.
        3. 모든 1번 주사위 형태에 대해 반복한 후, 최종 답을 구한다.

제출 결과
메모리: 2820KB, 시간: 20ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

vector<vector<int>> diceList;
vector<int> opp = {5, 3, 4, 1, 2, 0};

int getDiceIndex(const vector<int>& dice, int num);
int getDiceTop(const vector<int>& dice, int bottom);
int getDiceMaxSide(const vector<int>& dice, int bottom);

int main() {
    
    int n; cin >> n;

    vector<int> dice(6);
    for (int i = 0; i < n; ++i){
        for (auto &x: dice) cin >> x;
        diceList.push_back(dice);
    }

    
    int bottom, ans = -1;
    for (int i = 0; i < 6; ++i){

        // 1번 주사위 상태 결정
        bottom = diceList[0][i];
        int result = getDiceMaxSide(diceList[0], bottom);

        for (int j = 1; j < n; ++j){
            bottom = getDiceTop(diceList[j-1], bottom); // 이전 주사위의 윗면이 현재 주사위의 아랫면이 됨
            result += getDiceMaxSide(diceList[j], bottom);
        }

        if (result > ans) ans = result;
    }

    cout << ans;

    return 0;
}

int getDiceIndex(const vector<int>& dice, int num){
    return std::distance(dice.begin(), std::find(dice.begin(), dice.end(), num));
}

int getDiceTop(const vector<int>& dice, int bottom){
    int idx = getDiceIndex(dice, bottom);
    return dice[opp[idx]];
}

int getDiceMaxSide(const vector<int>& dice, int bottom){
    int idx_bottom = getDiceIndex(dice, bottom);
    int idx_top = getDiceIndex(dice, getDiceTop(dice, bottom));

    int ans = -1;
    for (int i = 0; i < 6; ++i){
        if (i == idx_bottom || i == idx_top) continue;

        if (dice[i] > ans){
            ans = dice[i];
        }
    }

    return ans;
}
