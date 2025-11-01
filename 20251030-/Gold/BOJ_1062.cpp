/*
가르침 - BOJ 1062

시간복잡도 : O( C(x, k-5)*N )
공간복잡도 : O(NL)

문제 접근
        a, c, i, n, t
        5개는 필수야. (K < 5 이면, 답은 무조건 0)

        결국, X개의 문자 중에서 K-5개를 고르는 문제다.
        X 개 = a, c, i, n, t를 제외하고, 주어진 단어들에 들어가는 문자의 갯수.

        완전탐색으로 풀어보자.
        X의 최댓값은 21, K = 15 or 16일 때 가장 많은 조합의 수가 나옴 (=35만개)
        N = 50, 단어 길이 전부 15이면 앞뒤 4개씩 짤라서 L = 7
        35만 * 50 * 7 = 약 1억2천만 연산.. 통과 가능할까?


제출 결과
메모리: 2032KB, 시간: 536ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::unordered_set;

int n, k, x;

bool isSubset(const unordered_set<char>& needAlpha, const unordered_set<char>& selectedAlpha);
int canReadWordsNum(const vector<unordered_set<char>>& wordList, const unordered_set<char>& selectedAlpha);
void solution(const vector<unordered_set<char>>& wordList, const vector<char>& alphabetList,
              unordered_set<char>& selectedAlpha, int idx, int num, int& ans);

int main() {
    
    cin >> n >> k;

    if (k < 5){
        cout << 0;
        return 0;
    }

    unordered_set<char> alphabetList; 
    vector<unordered_set<char>> wordList(n);
    string word;
    for (int i = 0; i < n; ++i){
        cin >> word;
        word = word.substr(4, word.length()-8);
        for (char c: word){
            if (c == 'a' || c == 'n' || c == 't' || c == 'i' || c == 'c') continue;
            wordList[i].insert(c);
            alphabetList.insert(c);
        }
    }

    x = alphabetList.size();

    if (k-5 >= x){
        cout << n;
        return 0;
    }

    vector<char> alphabetList_v(alphabetList.begin(), alphabetList.end());

    unordered_set<char> selectedAlpha;
    
    int ans = 0;
    solution(wordList, alphabetList_v, selectedAlpha, 0, 0, ans);
    cout << ans;
    return 0;
}

bool isSubset(const unordered_set<char>& needAlpha, const unordered_set<char>& selectedAlpha){
    for (char c : needAlpha) {
        if (selectedAlpha.find(c) == selectedAlpha.end())
            return false;
    }
    return true;
}

int canReadWordsNum(const vector<unordered_set<char>>& wordList, const unordered_set<char>& selectedAlpha){
    int result = 0;
    for (const auto& word: wordList){
        if (isSubset(word, selectedAlpha)) result += 1;
    }
    return result;
}

void solution(const vector<unordered_set<char>>& wordList, const vector<char>& alphabetList,
              unordered_set<char>& selectedAlpha, int idx, int num, int& ans){
    if (num == k-5){
        ans = std::max(ans, canReadWordsNum(wordList, selectedAlpha));
        return;
    }

    if (idx >= x) return;

    selectedAlpha.insert(alphabetList[idx]);
    solution(wordList, alphabetList, selectedAlpha, idx + 1, num + 1, ans);
    selectedAlpha.erase(alphabetList[idx]);

    solution(wordList, alphabetList, selectedAlpha, idx + 1, num, ans);
}