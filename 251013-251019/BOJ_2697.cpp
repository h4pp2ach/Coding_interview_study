/*
다음수 구하기 - BOJ 2697

시간복잡도 : O(NT)
공간복잡도 : O(N)

문제 접근
        A의 최대 자릿수 N: 80, T <= 1000, 시간제한 1초.
        O(N²)정도의 알고리즘으로 짰을 때 연산 약 640만번으로 무난.


        뒤에서부터 앞으로 자릿수를 비교 - 숫자가 감소하는 지점을 찾음

        1. 감소하는 지점 없이 첫번째 자리까지 올 경우: 해당 값이 동일 구성에서 가장 큰 값
        2. 감소하는 지점이 있을 경우: 
            해당 지점의 값보다 큰 이전 값들(더 뒤에 있는 자릿수들)중 최솟값 return
            (이 때 이전 값들은 감소하는 부분이 없으므로 내림차순 정렬되어있음. 가장 오른쪽 값이 최솟값이 됨)
            이후 나머지 뒷부분 오름차순 정렬
            (내림차순 정렬되어있는 값에서 최솟값만 더 작은 값으로 바꿨으므로, 여전히 내림차순 정렬. 뒤집기만 하면 됨.)

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

string findNextNum(string n);

int main() {
    int t; cin >> t;

    string s;
    for (int i = 0; i < t; ++i){
        cin >> s;
        cout << findNextNum(s) << std::endl;
    }

    return 0;
}

string findNextNum(string n){
    int idx;
    for (idx = n.size()-1; idx > 0; --idx){
        if (n[idx] > n[idx-1]){
            idx -= 1;
            break;
        }
    }

    if (idx == 0) return "BIGGEST";

    for (int j = n.size()-1; j > idx; --j){
        if (n[idx] < n[j]){
            std::swap(n[idx], n[j]);
            break;
        }
    }

    std::reverse(n.begin() + idx + 1, n.end());
    return n;
}