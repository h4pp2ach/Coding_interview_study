/*
우리집엔 도서관이 있어 - BOJ 2872

시간복잡도 : O(N)
공간복잡도 : O(N)

문제 접근
        시간제한 1초. N = 300,000 → O(NlogN)이내로 짜야 함.
        마지막 책 번호 앞으로 정렬되어있는 친구들은 안옮겨도 됨.

        N부터 시작해서 ← 방향으로 정렬된 숫자가 몇개인지 찾음

제출 결과
메모리: 3068KB, 시간: 120ms

*/

#include <iostream> 
#include <vector>
#include <string>

using std::cin;
using std::cout;

int main() {
    
    int n; cin >> n;
    int ans = 0;

    int i, book_indices[n];
    for (i = 0; i < n; ++i){
        cin >> book_indices[i];
    }

    int last_num = n;
    for (i = n-1; i >= 0; --i){
        if (book_indices[i] == last_num){
            last_num -= 1;
        }
        else{
            ans += 1;
        }
    }
    
    cout << ans;

    return 0;
}