/*
HTML - BOJ 6581

시간복잡도 : O(N)
공간복잡도 : O(N)

문제 접근
        공백 단위로 구분해서 String vector에 담아 처리
        일단 담아놓고 처리하고 싶어서 이렇게 구현했는데 입력 받자마자 처리하면 공간복잡도 줄일 수 있을듯

제출 결과
메모리: 2024KB, 시간: 0ms

*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using std::string;
using std::vector;
using std::getline;
using std::cin;
using std::cout;

int main() {
    vector<string> html_file;
    string line;
    while (cin >> line){
        html_file.push_back(line);
    }

    int numOfLines = 0;
    for (auto& s : html_file){
        if (s == "<br>"){
            cout << std::endl;
            numOfLines = 0;
            continue;
        }
        if (s == "<hr>"){
            if (numOfLines != 0){
                cout << std::endl;
            }
            cout << std::setfill('-') << std::setw(80) << '-' << std::endl;
            numOfLines = 0;
            continue;
        }
        if (numOfLines + s.size() < 80){
            if (numOfLines != 0){
                cout << " ";
            }
            numOfLines += (s.size() + 1);
            cout << s;
        }
        else{
            numOfLines = s.size();
            cout << std::endl << s;
        }
    }

    cout << std::endl;
    return 0;
}