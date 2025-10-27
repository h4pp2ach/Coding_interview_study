/*
공유기 설치 - BOJ 2110

시간복잡도 : O(NlogN + Nlog(max(xi))) ≈ O(NlogN)
공간복잡도 : O(N)

문제 접근
        조건을 만족하는 공유기 사이의 최대 거리 d는 구간 [1, max(xi)] 안에 존재
        → 정렬된 구간 안에서 조건을 만족하는지 검사 후 upper bound를 찾는 이분탐색으로 풀이 가능

제출 결과
메모리: 2804KB, 시간: 112ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int n, c;

bool isValid(const vector<int>& houseList, int distance);
int bSearch(const vector<int>& houseList, int l, int r);

int main() {
    
    cin >> n >> c;
    
    vector<int> houseList(n);
    for (int& x: houseList) cin >> x;

    std::sort(houseList.begin(), houseList.end());
    cout << bSearch(houseList, 0, houseList[n-1]);

    return 0;
}

bool isValid(const vector<int>& houseList, int distance){
    int router = 1, adjDistance = 0;
    for (int i = 1; i < n; ++i){
        adjDistance += houseList[i] - houseList[i-1];
        
        if (adjDistance >= distance){
            router += 1;
            adjDistance = 0;
        }
    }

    if (router >= c) return true;
    return false;
}

int bSearch(const vector<int>& houseList, int l, int r){
    int ans = 0;
    while (l <= r){
        int m = l + (r-l)/2;

        if (isValid(houseList, m)){
            ans = m;
            l = m + 1;
        }
        else r = m - 1;
    }

    return ans;
}