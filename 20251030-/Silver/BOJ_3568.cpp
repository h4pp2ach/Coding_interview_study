/*
iSharp - BOJ 3568

시간복잡도 : O(M) M:입력 전체 문자 수
공간복잡도 : O(M)

문제 접근
        단순 구현 문제.

        첫번째 입력받은 값은 공통으로 써주면 되고,
        쉼표 또는 세미콜론 사이에 오는 애들을 처리해줌.
        변수의 이름이 어디까지인지를 파악해야 함.
        
        전체 선언문 길이 - 2 부터 변수의 이름 길이까지 --로 역순으로 읽기.
        [] ← 얘는 추가 처리 필요함.

        각 변수 선언 마지막엔 
        쉼표 있으면, 세미콜론 붙이고 \n
        세미콜론 있으면, 그대로 세미콜론 하나만.

제출 결과
메모리: 2024KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int main() {
    
    vector<string> inputData;
    string data;

    while (cin >> data){
        inputData.push_back(data);
    }

    int numOfVar = inputData.size();
    for (int i = 1; i < numOfVar; ++i){
        cout << inputData[0];

        int variableLength = 0;
        for (auto x: inputData[i]){
            if (!std::isalpha(x)) break;
            variableLength += 1;
        }
        int dataLength = inputData[i].length();
        for (int j = dataLength-2; j > variableLength-1; --j){
            
            if (inputData[i][j] == ']')
                {cout << "[]";
                --j;
            }
            else cout << inputData[i][j];
        }

        cout << " ";
        for (int j = 0; j < variableLength; ++j){
            cout << inputData[i][j];
        }
        cout << ";";

        if (inputData[i][dataLength-1] == ',') cout << std::endl;
    }
    return 0;
}
