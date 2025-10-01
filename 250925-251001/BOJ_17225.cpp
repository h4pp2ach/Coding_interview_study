/*
N으로 만들기 - BOJ 17225

시간복잡도 : O(K*2^K)
공간복잡도 : O(2^K)

문제 접근
        N의 유효한 최대 자리수 = 7이라고 볼 수 있음. 이 때 경우의 수는 9^7 = 4,782,969.
        시간제한은 1초지만 브루트 포스로 돌려도 크게 문제 없긴 할듯.

        나는 분할정복으로 풀어볼까.
        k개의 자릿수를 가지는 숫자 N에서, 오른쪽 끝을 제거한 부분을 nl, 왼쪽 끝을 제거한 부분을 nr이라고 하면,
    
        N을 만드는 방법의 수 = nl을 만드는 방법의 수 + nr을 만드는 방법의 수
        이 때 nl과 nr이 같으면 방법은 1개만 존재.

        시간복잡도 계산: K개의 자릿수에 대해 2번씩 재귀호출 → O(2^K), 그리고 각 경우에서 nl과 nr을 비교해야 하므로 총 O(K*2^K)
        공간복잡도 계산: 매 재귀호출마다 O(K) 수준의 메모리 2개씩 사용. O(2^K)

제출 결과
메모리: 2024KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int findNumOfCases(const vector<int>& n);
vector<int> slicingVector(const vector<int>& v, int s, int e);


int main() {
    string n; cin >> n;
    
    vector<int> sliced_n;
    for(auto x: n){
        sliced_n.push_back(x - '0');
    }

    int ans = findNumOfCases(sliced_n);
    cout << ans;
    return 0;
}

int findNumOfCases(const vector<int>& n){
    int numLength = n.size();
    if (numLength == 1) return 1;

    auto nl = slicingVector(n, 0, numLength-1);      // 오른쪽 끝을 잘라낸 나머지 왼쪽 부분
    auto nr = slicingVector(n, 1, numLength);        // 왼쪽 끝을 잘라낸 나머지 오른쪽 부분

    if (nl == nr) return 1; //한가지 수로 이루어져있는 숫자를 만드는 방법은 1가지
    return findNumOfCases(nl) + findNumOfCases(nr);
}

vector<int> slicingVector(const vector<int>& v, int s, int e){
    return vector<int>(v.begin() + s, v.begin() + e);
}