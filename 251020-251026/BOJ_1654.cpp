/*
랜선 자르기 - BOJ 1654

시간복잡도 : O(klogN)
공간복잡도 : O(K)

문제 접근
        시간제한 2초인데, 입력 범위가 매우 큼
        랜선의 길이는 정렬된 데이터로 생각할 수 있으니, 이분탐색 각이다

        기본적으로 랜선이 가질 수 있는 최대 길이는 초기에 주어진 길이 중 최댓값
        [1, max(Lk)] 범위 내에서 이분탐색으로 최댓값을 찾아보자

        문제의 조건을 만족하는지 검사하는 함수를 만들고,
        조건을 만족하면 더 큰 범위를 검사, 아니면 더 작은 범위를 검사하면 최댓값을 찾을 수 있음
        

제출 결과
메모리: 2020KB, 시간: 8ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int k, n;

bool canCut(const vector<int>& lineList, long long num);
int bSearch(const vector<int>& lineList, long long l, long long r);

int main() {
    
    cin >> k >> n;

    vector<int> lineList(k); int maxLen = 0;
    for (int& x: lineList){
        cin >> x;
        maxLen = std::max(x, maxLen);
    }

    cout << bSearch(lineList, 1, maxLen);

    return 0;
}

bool canCut(const vector<int>& lineList, long long num){
    int ea = 0;
    for (auto x: lineList) ea += x/num;

    if (ea >= n) return true;
    return false;
}

int bSearch(const vector<int>& lineList, long long l, long long r){
    int ans = 0;
    while (l <= r){
        long long m = (l + r)/2;

        if (canCut(lineList, m)){
            ans = m;
            l = m + 1;
        }
        else r = m - 1;
    }

    return ans;
}
