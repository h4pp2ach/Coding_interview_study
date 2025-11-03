/*
동전 1 - BOJ 2293

시간복잡도 : O(NK)
공간복잡도 : O(K)

문제 접근
        1) 분할정복 + 메모이제이션
        동전 종류를 하나씩 순회하면서, 현재 동전을 고르는 경우 + 고르지 않는 경우로 더하며 재귀
        (이 때 인덱스가 역행하지 않으므로, 중복 조합을 고를 걱정이 없음)

        그러다 정확히 원하는 K원에 도달하면 가능한 조합이고,
        K원보다 작아지거나, 마지막 동전을 넘어섰다면 불가능한 조합
        
        메모이제이션을 통해 우리가 계산하는 실제 경우는 idx = 0 ~ N, remain = 0 ~ K → O(NK)

        근데 이렇게 푸니까 메모리 초과 난다. 
        사용한 메모리가 크기 N의 1차원 동전 배열이랑, N by K의 2차원 DP 배열인데
        N = 100, K = 10000일 때, 재귀 스택까지 포함하면 4MB 그냥 넘어가는구나..

        2) 1차원 DP
        선택 가능 Pool에 각 동전 종류를 하나씩 추가해주면서, 가능한 조합을 DP 테이블에 누적
        
        X원을 만드는 경우의 수 = 지금까지 선택 가능했던 동전들로 만드는 경우 + 새로운 종류의 동전으로 만드는 경우
        이 때, 새로운 동전으로 만드는 경우 = (X-동전)원을 만드는 경우의 수(새로운 동전만 추가하면 되니까)

        즉, X원을 만드는 경우의 수 += (X-동전)원을 만드는 경우의 수 이렇게 계속 누적해나가면 된다.

        시간복잡도는 1번과 동일하게 O(NK)지만, 공간복잡도가 O(K)로 줄었다.


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

int numOfCoins;
vector<int> coins;
// vector<vector<int>> dp;

// int getNumOfWays(int idx, int remain);
int getNumOfways2(int k);

int main() {
    
    int n, k; cin >> n >> k;
    
    int coin;
    for (int i = 0; i < n; ++i){
        cin >> coin;
        if (coin <= k) coins.emplace_back(coin);
    }

    cout << getNumOfways2(k);

    // numOfCoins = coins.size();
    // dp.assign(numOfCoins, vector<int>(k + 1, -1));
    // cout << getNumOfWays(0, k);

    return 0;
}

int getNumOfways2(int k){
    vector<long long> dp(k+1, 0);
    dp[0] = 1;

    for (const auto& coin: coins){
        for (int x = coin; x <= k; ++x){
            dp[x] += dp[x-coin];
        }
    }

    return dp[k];
}

// int getNumOfWays(int idx, int remain) {
//     if (remain == 0) return 1;
//     if (remain < 0 || idx == numOfCoins) return 0;

//     // 이미 계산한 적 있으면 재활용
//     if ( dp[idx][remain] != -1) return dp[idx][remain];

//     // 경우의 수 계산
//     int include = getNumOfWays(idx, remain - coins[idx]);   // 이번 동전 사용
//     int exclude = getNumOfWays(idx + 1, remain);            // 이번 동전 사용 안 함

//     dp[idx][remain] = include + exclude;
//     return dp[idx][remain];
// }