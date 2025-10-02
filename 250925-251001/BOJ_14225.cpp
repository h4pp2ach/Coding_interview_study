/*
부분수열의 합 - BOJ 14225

시간복잡도 : O(n*2^n)
공간복잡도 : O(2^n)

문제 접근
        부분 수열을 구한다는 건 조합을 구하는 것과 동일
        N = 20일 때 전체 부분집합의 갯수는 2^20 = 1,048,576
        모든 부분집합을 구하려면 약 2000만번 연산.
        합을 계산할 때 DP로 연산시간을 줄일수도 있겠고, 입력 크기상 브루트 포스로도 가능할듯

        1. 부분집합의 합을 저장할 집합(set) 생성
        2. 부분집합을 하나씩 만들면서 합을 계산 후 집합에 insert
        3. set은 기본 오름차순 정렬. index != value인 첫번째 지점 리턴

제출 결과
메모리: 22220KB, 시간: 208ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::set;

int n;
vector<int> seq;
set<int> sumSet;

void insertSubsetSum(int idx, int subsetSum);

int main() {
    cin >> n;

    seq.resize(n);
    for (int& x: seq) cin >> x;
    
    insertSubsetSum(0, 0);

    int num = 1;
    for (auto x: sumSet){
        if (x != num) break;
        num ++;
    }
    
    cout << num;
    return 0;
}

void insertSubsetSum(int idx, int subsetSum){
    if (idx == n){
        if (subsetSum > 0) sumSet.insert(subsetSum);
        return;
    }

    insertSubsetSum(idx + 1, subsetSum + seq[idx]);
    insertSubsetSum(idx + 1, subsetSum);
}