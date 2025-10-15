/*
체인 - BOJ 2785

시간복잡도 : O(NlogN)
공간복잡도 : O(N)

문제 접근
        분리된 N개의 체인을 연결하기 위해서 N-1개의 단위 체인이 필요.
        
        근데 한개의 분리된 체인을 모두 열어재낀다면, 
        N-1개의 분리된 체인을 연결하는 문제로 바뀌고, N-2개의 단위 체인이 필요하게 됨.
        ex)
        N=4, 2 10 10 10 일 때, 2를 다 열면, 10 3개만 연결하면 되고 답은 2가 됨.
        N=5, 3 10 10 10 10 일 때, 3을 다 열면, 10 4개만 연결하면 되고 답은 3이 됨.
        N=5, 1 1 10 10 10 일 때, 1을 각각 다 열면, 10 3개만 열결하면 되고 답은 2가 됨.


        즉, 가장 길이가 작은 체인을 먼저 여는 쪽으로 합쳐야 최소 횟수를 구할 수 있다.
        
        접근방법 1)
        0. n0 = N으로 설정
        1. 체인의 길이를 오름차순 정렬한다.
        2. 왼쪽(길이가 짧은) 체인부터 1씩 열면서 n을 1씩 줄인다.
        3. 이 때, 해당 체인의 길이가 0이 되면 n을 1 줄인다.
        4. n이 1이 될 때까지 반복한다.
        
        이렇게 풀면 정렬에서 O(NlogN), 체인을 여는 반복에서 O(N) = O(NlogN)

        1씩 줄이는 방식과 계산식으로 한번에 연산하는 방식의 시간 성능 차이를 고민해봤는데,
        어차피 초기 체인 수 N이 1이 될 때 까지 연산이 반복되므로 Li가 크다고 해서 큰 차이는 없을듯.
        그래도 해보자.
        
        접근방법 2)
        0. n0 = N으로 설정
        1. 동일하게 오름차순 정렬
        2. 가장 왼쪽에 있는 값이 n-1 이상이면, n-1만큼 열고 종료. n = 1, ans += n-1
        3. 가장 왼쪽에 있는 값이 n-1보다 작으면, 전부 다 열고 다음으로.  n -= (해당 값 + 1), ans += 해당 값, idx += 1
        4. n이 1이 될 때까지 반복.

        4ms 줄었네.

        
제출 결과
1번) 메모리: 3976KB, 시간: 220ms
2번) 메모리: 3980KB, 시간: 216ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

int n, ans, idx;
vector<int> chainList;

void openChain();
void connectChain();
void openChain2();
void connectChain2();

int main() {

    cin >> n;
    chainList.assign(n, 0);
    for (int& x: chainList) cin >> x;

    std::sort(chainList.begin(), chainList.end());

    while (n > 1){
        //openChain();
        openChain2();
    }

    cout << ans;

    return 0;
}

void openChain(){
    // 가장 짧은 체인 하나씩 open 후 뒤에 연결
    chainList[idx] -= 1;
    ans += 1;
    connectChain();

    // 가장 짧은 체인 다 썼을 때 다음 체인으로 넘어감
    if (chainList[idx] == 0){
        n -= 1;
        idx += 1;
    }

    return;
}

void connectChain(){
    n -= 1;
    return;
}

void openChain2(){

    // 가장 짧은 체인의 길이가 n-1 이상이면 n-1만큼 열어서 연결 후 종료
    if (chainList[idx] >= n-1){
        ans += n-1;
        n = 1;
        return;
    }

    // 가장 짧은 체인의 길이가 n-1보다 작으면, 전부 다 열고 연결 후 다음으로
    ans += chainList[idx];
    connectChain2();
    idx += 1;

    return;
}

void connectChain2(){
    n -= (chainList[idx] + 1);
    return;
}