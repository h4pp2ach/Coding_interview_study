/*

시간복잡도 : O(1)
공간복잡도 : O(1)

문제 접근
        문제 특성상 N <= 75 이므로, 시간복잡도는 크게 고려하지 않아도 됨.
        
        열 = 0 ~ 14
        행을 하나씩 내려가면서 유효한 경우에 출력
        모든 행이 유효하지 않았을 경우 반복문 즉시 종료

제출 결과
메모리: 2024KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <string>

using namespace std;

int main() {
    int i, j;

    vector<string> lines(5);
    for (i = 0; i < 5; ++i) getline(cin, lines[i]);

    for (j = 0; j < 15; ++j){
        int check = 0;
        for (i = 0; i < 5; ++i){
            if (j < lines[i].size()){
                cout << lines[i][j];
                check = 1;
            }
        }
        if (!check) break;
    }
    return 0;  // 정상 종료
}