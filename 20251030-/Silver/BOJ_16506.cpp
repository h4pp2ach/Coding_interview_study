/*
CPU - BOJ 16506

시간복잡도 : O(N)
공간복잡도 : O(1)

문제 접근
        단순 구현.
        
        opcode에 오는 문자의 C 여부에 따라 type 구분해서 처리
        첫 4비트 변환을 위한 배열 사용, isC이면 앞에 문자만 읽어서 대응되도록 구현
        

제출 결과
메모리: 2028KB, 시간: 12ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <bitset>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::bitset;

vector<string> opcodeList{"ADD", "SUB", "MOV", "AND", "OR", "NOT", "MULT", "LSFTL", "LSFTR", "ASFTR", "RL", "RR"};

string assembler(string& opcode, int rD, int rA, int rB);

int main() {
    
    int n; cin >> n;

    string opcode; int rD, rA, rB;
    for(int i = 0; i < n; ++i){
        cin >> opcode >> rD >> rA >> rB;
        string result = assembler(opcode, rD, rA, rB);

        cout << result << std::endl;
    }

    return 0;
}

string assembler(string& opcode, int rD, int rA, int rB){
    string result;
    bool isC = false;
    if (opcode[opcode.length()-1] == 'C'){
        opcode = opcode.substr(0, opcode.length()-1);
        isC = true;
    }

    //opcode
    int i;
    for (i = 0; i < 12; ++i){
        if (opcode == opcodeList[i]){
            result += bitset<4>(i).to_string();
            break;
        }
    }
    if (isC) result += "10";
    else result += "00";

    //rD
    result += bitset<3>(rD).to_string();

    //rA
    if (i == 2 || i == 5) result += "000";
    else result += bitset<3>(rA).to_string();

    //rB
    if (isC) result += bitset<4>(rB).to_string();
    else result = result + bitset<3>(rB).to_string() + "0";

    return result;
}