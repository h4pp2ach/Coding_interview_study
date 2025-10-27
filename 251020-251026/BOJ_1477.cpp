/*
휴게소 세우기 - BOJ 1477

시간복잡도 : O(NlogN + Nlog(L)) ≈ O(NlogN)
공간복잡도 : O(N) 

문제 접근
        조건을 만족하는 휴게소가 없는 거리의 최대 거리 d는 구간 [1, L] 안에 반드시 존재
        → 정렬된 구간 안에서 조건을 만족하는지 검사 후 lower bound를 찾는 이분탐색으로 풀이 가능
        
        조건 만족하는지 검사하는 로직
        1. 고속도로의 각 구간 길이를 d로 나눈 몫을 전부 더함
        2. 몫이 m(추가할 휴게소)보다 크면 해당 d를 만들어내기 위해 m개 이상의 휴게소가 필요하다는 의미 (불가능하다)

제출 결과
메모리: 2024KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::string;

bool isPossible(const vector<int>& highwayInfo, int highwayLength, int distance, int extraRest);
int bSearch(const vector<int>& highwayInfo, int extraRest, int l, int r);

int main() {
    
    int n, m, l; cin >> n >> m >> l;

    if (n == 0) { // 고속도로가 비어있으면 길이 L을 m+1개의 구간으로 나누는 문제로 바뀜
    cout << static_cast<int>(ceil(static_cast<double>(l) / (m + 1)));
    return 0;
    }

    vector<int> highwayInfo(n);
    for (auto& x: highwayInfo) cin >> x;

    std::sort(highwayInfo.begin(), highwayInfo.end());
    cout << bSearch(highwayInfo, m, 1, l);

    return 0;
}

bool isPossible(const vector<int>& highwayInfo, int highwayLength, int distance, int extraRest){

    int result = (highwayInfo[0] - 1) / distance;
    for (int i = 1; i < highwayInfo.size(); ++i){
        result += (highwayInfo[i] - highwayInfo[i-1] - 1) / distance;
    }
    result += (highwayLength - highwayInfo[highwayInfo.size()-1] - 1) / distance;

    if (result <= extraRest) return true;
    return false;
}

int bSearch(const vector<int>& highwayInfo, int extraRest, int l, int r){
    int highwayLength = r;
    int ans = 1001;

    while (l <= r){
        int m = (l + r) / 2;

        if (isPossible(highwayInfo, highwayLength, m, extraRest)){
            ans = m;
            r = m - 1;
        }
        else l = m + 1;
    }

    return ans;
}