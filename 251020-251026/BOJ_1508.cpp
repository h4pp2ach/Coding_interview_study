/*
레이스 - BOJ 1508

시간복잡도 : O(KlogN)
공간복잡도 : O(K)

문제 접근
        (1) 일단 가장 가까운 심판 사이의 거리가 최대가 되는 값을 먼저 찾고, (2) 그 때 심판의 배열을 구해보자
        
        (1)의 값은 이분탐색으로 쉽게 찾을 수 있을 것 같고, 이 때 왼쪽을 먼저 배치하도록 하면 사전순으로 가장 늦게 만들 수 있을듯
        

제출 결과
메모리: 2020KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

vector<int> selectList;

bool isPossible(const vector<int>& judgePosList, int n, int m, int k, int distance);
int bSearch(const vector<int>& judgePosList, int n, int m, int k);

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> judgPositionList(k);
    
    for (int& position: judgPositionList) cin >> position;
    
    int ans = bSearch(judgPositionList, n, m, k);
    //cout << ans << std::endl;
    for (auto x: selectList) cout << x;

    return 0;
}


bool isPossible(const vector<int>& judgePosList, int n, int m, int k, int distance){
    int cnt = 1;
    int last = judgePosList[0];

    vector<int> sL(k, 0); sL[0] = 1;

    for (int i = 1; i < k; ++i){
        if (judgePosList[i] - last >= distance){
            sL[i] = 1;
            cnt += 1;
            last = judgePosList[i];
            if (cnt == m){
                selectList = sL;
                return true;
            }
        }
    }

    return false;
}

int bSearch(const vector<int>& judgePosList, int n, int m, int k){
    int ans = 0;

    int l = 1, r = n;
    while (l <= r){
        int mid = l + (r-l)/2;

        if (isPossible(judgePosList, n, m, k, mid)){
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    return ans;
}