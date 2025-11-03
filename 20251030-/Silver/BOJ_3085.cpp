/*
사탕 게임 - BOJ 3085

시간복잡도 : O(N³)
공간복잡도 : O(N²)

문제 접근
        1. 일단 각 행별로 사탕의 색상별 갯수를 계산 → N
        2. 현재 기록하고 있는 정답의 값보다 색상별 갯수의 최댓값이 더 작으면 PASS
        3. 시뮬레이션으로 다 돌려보고 최댓값 갱신 → 2N*N
        4. 열에 대해서 반복

제출 결과
메모리: 2024KB, 시간: 128ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::swap;
using std::max;

void simulate(vector<vector<char>>& board, int n, int& ans);
int solution(vector<vector<char>>& board, int n);
int findNum(const vector<vector<char>>& board, int n);


int main() {
    
    int n; cin >> n;

    vector<vector<char>> board(n, vector<char>(n));
    for (auto& line: board){
        for (auto& c: line) cin >> c;
    }

    cout << solution(board, n);
    return 0;
}


int solution(vector<vector<char>>& board, int n){
    int ans = 1;

    for (int row = 0; row < n; ++row){

        vector<int> rowCandy(4, 0);
        for (int col = 0; col < n; ++col){

            char candyColor = board[row][col];
            if (candyColor == 'C') rowCandy[0] += 1;
            else if (candyColor == 'P') rowCandy[1] += 1;
            else if (candyColor == 'Z') rowCandy[2] += 1;
            else rowCandy[3] += 1; // color == 'Y'
        }

        int maxCandy = *std::max_element(rowCandy.begin(), rowCandy.end());

        if (maxCandy < ans) continue;
        else if (maxCandy == n) return n;

        simulate(board, n, ans);
    }

    for (int col = 0; col < n; ++col) {
        vector<int> colorCount(4, 0);

        for (int row = 0; row < n; ++row) {
            char c = board[row][col];
            if (c == 'C') colorCount[0]++;
            else if (c == 'P') colorCount[1]++;
            else if (c == 'Z') colorCount[2]++;
            else colorCount[3]++;
        }

        int maxCount = *max_element(colorCount.begin(), colorCount.end());
        if (maxCount < ans) continue;
        if (maxCount == n) return n;

        simulate(board, n, ans);
    }

    return ans;
}

void simulate(vector<vector<char>>& board, int n, int& ans){

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (j + 1 < n) { // 가로 swap
                swap(board[i][j], board[i][j + 1]);
                ans = max(ans, findNum(board, n));
                swap(board[i][j], board[i][j + 1]);
            }

            if (i + 1 < n) { // 세로 swap
                swap(board[i][j], board[i + 1][j]);
                ans = max(ans, findNum(board, n));
                swap(board[i][j], board[i + 1][j]);
            }
        }
    }

}

int findNum(const vector<vector<char>>& board, int n){
    int result = 1;

    // 행 기준
    for (int i = 0; i < n; i++) {
        int cnt = 1;
        for (int j = 1; j < n; j++) {
            if (board[i][j] == board[i][j - 1]) cnt++;
            else cnt = 1;
            result = max(result, cnt);
        }
    }

    // 열 기준
    for (int j = 0; j < n; j++) {
        int cnt = 1;
        for (int i = 1; i < n; i++) {
            if (board[i][j] == board[i - 1][j]) cnt++;
            else cnt = 1;
            result = max(result, cnt);
        }
    }

    return result;
}