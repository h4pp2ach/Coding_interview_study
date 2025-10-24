/*
숌트링 - BOJ 1488

시간복잡도 : 1번방식 - O(1), 2번방식 - O(cA+cB)
공간복잡도 : 1번방식 - O(1), 2번방식 - O(1)

문제 접근
        시간제한 2초, 문제 크기상 직접 문자열을 만들어보면서 갯수 세어보는 완전탐색으로는 불가능.
        
        1)수학적 접근 !보완 필요
        기본 아이디어: 문자 1개를 나열해놓고, 그 사이에 다 들어가는지 검사하면 됨
        
        예외처리) max A == 0이면, 정답은 min(count B, max B). 반대도 마찬가지
        
        max A != 0 && max B != 0 일 때:
        1. A의 갯수가 너무 많아서 B를 다 써도 커버가 안됨 : cA > mA*(cB + 1)
        → B는 1씩 cB개를 놓고, A는 그 사이에 mA개씩 끼워넣음. 결과는 A: mA*(cB + 1)개 + B: cB개

        2. B의 갯수가 너무 많아서 A를 다 써도 커버가 안됨 : cB > mB*(cA + 1)
        → 위와 동일한 과정으로 mB*(cA + 1) + cA

        3. 두 조건 다 아니면, A랑 B 둘 다 사용 가능함
        → cA + cB


        2)그리디
        기본 아이디어: A와 B중에 더 많이 남은 녀석을 먼저 소모해야 함. max 값 이상으로는 나열 불가능
        연속으로 나온 A와 B의 수를 저장하는 변수: numA, numB

        1. while (cA == 0 || cB == 0)
        2-1. cX > cY 인 상황에서,
            현재까지 나열된 X가 maxX보다 작을 때 (numX < maxX), cX가 남아있다면:
                cX -= 1
                numY = 0
                numX += 1
                ans += 1
            더이상 X를 놓을 수 없을 때 cY가 남아있다면:
                cY -= 1
                numX = 0
                numY += 1
                ans += 1


제출 결과
메모리: KB, 시간: ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::min;

int findMaxLenS(int cA, int cB, int mA, int mB);
int findMaxLenS2(int cA, int cB, int mA, int mB);

int main() {
    
    int cA, cB, mA, mB; cin >> cA >> cB >> mA >> mB;
    cout << findMaxLenS2(cA, cB, mA, mB);
    return 0;
}

int findMaxLenS(int cA, int cB, int mA, int mB){
    if (mA == 0) return min(cB, mB);
    if (mB == 0) return min(cA, mA);

    if (cA > mA*(cB+1))  
        return mA*(cB+1) + cB;
    else if (cB > mB*(cA+1))  
        return mB*(cA+1) + cA;
    else  
        return cA + cB;
}

int findMaxLenS2(int cA, int cB, int mA, int mB){
    if (mA == 0) return min(cB, mB);
    if (mB == 0) return min(cA, mA);

    int ans = 0;

    int numA = 0, numB = 0;
    while (cA != 0 || cB != 0){

        if (cA > cB){
            if (numA < mA && cA > 0){
                cA -= 1;
                numB = 0;
                numA += 1;
                ans += 1;
            }
            else if(cB > 0){
                cB -= 1;
                numA = 0;
                numB += 1;
                ans += 1;
            }
            else break;
        }

        else{
            if (numB < mB && cB > 0){
                cB -= 1;
                numA = 0;
                numB += 1;
                ans += 1;
            }
            else if (cA > 0){
                cA -= 1;
                numB = 0;
                numA += 1;
                ans += 1;
            }
            else break;
        }
    }

    return ans;
}