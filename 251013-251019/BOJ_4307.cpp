/*
개미 - BOJ 4307

시간복잡도 : O(1)
공간복잡도 : O(1)

문제 접근
        모든 개미가 가장 빨리 떨어지는 경우
        - 모든 개미가 바깥쪽을 보고 있음
        - L/2 기준으로 값이 더 작은 애들은 x만큼, 이상인 애들은 L-x만큼 가면 떨어짐
        - 가장 중앙에 가까운 녀석이 떨어지는 시간

        모든 개미가 가장 늦게 떨어지는 경우
        - 모든 개미가 안쪽을 보고 있음
        - 시뮬레이션으로 하나씩 움직이면서 구현하면 시간이 괜찮을까? 수학적으로 풀어야되나?
        - 생각해보면 충돌해봤자 어차피 그대로 반대방향으로 가니까, 원래 가던방향 그대로 개미만 바뀐거 아님?
        - 그러면 그냥 제일 멀리서 시작하는 개미가 제일 오래걸리는데 관여하겠네.

제출 결과
메모리: 3052KB, 시간: 116ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::min;

int findMinTime(int l, const vector<int>& antList);
int findMaxTime(int l, const vector<int>& antList);

int main() {
    
    int testcase; cin >> testcase;

    int l; int n; int antPos;
    for (int i = 0; i < testcase; ++i){
        cin >> l >> n;
        vector<int> antList = {};
        for (int _ = 0; _ < n; ++_){
            cin >> antPos;
            //if (antPos == 0 || antPos == l) continue; // 막대 끝에 있으면 바로 떨어짐
            antList.push_back(antPos);
        }
        cout << findMinTime(l, antList) << " " << findMaxTime(l, antList) << std::endl;
    }

    return 0;
}

int findMinTime(int l, const vector<int>& antList){
    int ans = 0;
    for (const int& x: antList){
        ans = max(ans, min(x, l-x)); // 가까운 막대 끝까지의 거리가 가장 먼 개미가 떨어지는 시간
    }
    return ans;
}
int findMaxTime(int l, const vector<int>& antList){
    int ans = 0;
    for (const int& x: antList){
        ans = max(ans, max(x, l-x)); // 반대쪽 막대 끝까지의 거리가 가장 먼 개미가 떨어지는 시간
    }
    return ans;
}