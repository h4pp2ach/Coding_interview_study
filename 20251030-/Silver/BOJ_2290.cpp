/*
LCD - BOJ 2290

시간복잡도 : O(S²*N자릿수)
공간복잡도 : O(S²*N자릿수)

문제 접근
        공식처럼 접근해서, 미리 2차원 배열을 만들어놓고 특정 위치에 찍어내듯이 하는게 낫지 않을까?
        어차피 s=10, 자릿수=10 일 때, 23 X 129 크기의 배열이 최대 크기니까 메모리 걱정도 없다.

        i번 인덱스의 숫자가 가지는 공간은 [0][i*(s+2) + i] ~ [2s+3-1][(i+1)*(s+2)-1 + i]
        1. 가로 문자('-')가 들어가는 기준
        행: 0번행, s+1번행, 2s+2번행 - 3가지 경우에만 '-'이 들어감
        열: 0번열, s+1번열 - 2가지 경우에는 '-'이 들어가지 않음

        2. 세로 문자('|')가 들어가는 기준은 가로 문자와 정반대

제출 결과
메모리: 2028KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int s; string num; 

void fillResult(vector<vector<char>>& result, char n, int index);

int main() {
    
    cin >> s >> num;
    int width = s+2, height = 2*s+3;

    vector<vector<char>> result(height, vector<char>((width + 1) * num.length(), ' '));

    int idx = -1;
    for (char c: num){
        idx += 1;
        fillResult(result, c, idx);
    }

    for (const auto& row: result){
        for (auto c: row) cout << c;
        cout << std::endl;
    }

    return 0;
}

void fillResult(vector<vector<char>>& result, char n, int index){
    int startCol = index*(s+3);
    vector<int> hRowIdx, vUpperColIdx, vLowerColIdx;

    // 가로선 놓을 위치 지정
    if (n == '2' || n == '3' || n == '5' || n == '6' || n == '8' || n == '9'){
        hRowIdx.emplace_back(0);
        hRowIdx.emplace_back(s+1);
        hRowIdx.emplace_back(2*s+2);
    }
    else if (n == '4') hRowIdx.emplace_back(s+1);
    else if (n == '7') hRowIdx.emplace_back(0);
    else if (n == '0'){
        hRowIdx.emplace_back(0);
        hRowIdx.emplace_back(2*s+2);
    }
    
    // 중간을 기준으로 위쪽 세로선 위치 지정
    if (n == '1' || n == '2' || n == '3' || n == '7') vUpperColIdx.emplace_back(s+1);
    else if (n == '5' || n == '6') vUpperColIdx.emplace_back(0);
    else if (n == '0' || n == '4' || n == '8' || n == '9'){
        vUpperColIdx.emplace_back(0);
        vUpperColIdx.emplace_back(s+1);
    }

    // 아래쪽 세로선 위치 지정
    if (n == '1' || n == '3' || n == '4' || n == '5' || n == '7' || n == '9') vLowerColIdx.emplace_back(s+1);
    else if (n == '2') vLowerColIdx.emplace_back(0);
    else if (n == '0' || n == '6' || n == '8'){
        vLowerColIdx.emplace_back(0);
        vLowerColIdx.emplace_back(s+1);
    }


    // 가로선 놓기
    for (int col = startCol+1; col < (startCol+s+1); ++col){
        for (int row: hRowIdx){
            result[row][col] = '-';
        }
    }

    // 위쪽 세로선 놓기
    for (int row = 1; row < (s+1); ++row){
        for (int col: vUpperColIdx){
            result[row][startCol + col] = '|';
        }
    }

    // 아래쪽 세로선 놓기
    for (int row = s+2; row < (2*s+2); ++row){
        for (int col: vLowerColIdx){
            result[row][startCol + col] = '|';
        }
    }
}