/*
용돈관리 - BOJ 6236

시간복잡도 : O(Nlog(sum(금액)))
공간복잡도 : O(N)

문제 접근
        M번 인출을 초과하지만 않으면 정확히 M번 꺼낼 수 있음
        → 가능성 판별은 K원씩 출금시 N일을 보냈을 때, M회 이하의 인출 횟수인지 검사
        이분탐색으로 K원을 구하자. 가능한 K의 범위는 [1, sum(금액)]
        

제출 결과
메모리: 2412KB, 시간: 52ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

bool isPossible(const vector<int>& dayInfo, int n, int m, int k);
int bSearch(const vector<int>& dayInfo, int n, int m);

int main() {
    
    int n, m; cin >> n >> m;

    vector<int> dayInfo(n);
    for (auto& x: dayInfo) cin >> x;

    cout << bSearch(dayInfo, n, m);

    return 0;
}


bool isPossible(const vector<int>& dayInfo, int n, int m, int k){
    int cnt = 1;
    int money = k;

    for (int i = 0; i < n; ++i){
        if (dayInfo[i] > k) return false;
        if (money - dayInfo[i] < 0){
            cnt += 1;
            money = k;
        }
        if (cnt > m) return false;

        money -= dayInfo[i];
    }
    return true;
}

int bSearch(const vector<int>& dayInfo, int n, int m){
    int ans = 0;
    int l = 1;
    int r = 0; for(int x: dayInfo) r += x;

    while (l <= r){
        int mid = l + (r-l)/2;

        if (isPossible(dayInfo, n, m, mid)){
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return ans;
}