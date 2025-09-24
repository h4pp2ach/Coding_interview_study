/*

시간복잡도 :
공간복잡도 :

문제 접근
        시간제한 2초, 메모리 제한 128MB
        입력 범위가 작아서 시간제한은 크게 걱정 없는데,
        모든 경우에 대해서 테이블을 전부 만들어두면, 4*10000*10000 = 약 400MB 이상이여서 불가능.
        
        수학적인 관계를 찾아서 해결해야 할듯

        좌표 r,c가 있다고 하면,

        r, c 중 크기의 최댓값 -> Layer가 됨. i = 0번 레이어부터 시작.
        그리고 그 때의 최댓값 = (2i+1)^2은 항상 오른쪽 아래 모서리

        다시 i번 레이어 위의 점 (r,c)에서 오른쪽 아래 모서리를 기준으로 따라가면,
        r = i 일 때, num = (2i+1)^2 - (i-c) 
        c = -i 일 때, num = ((2i+1)^2 - 2i) - (i-r)
        r = -i 일 때, num = ((2i+1)^2 - 4i) - (i+c)
        c = i이고 r != i 일 때, num = ((2i+1)^2 - 6i) - (i+r)

        
        다시 주어진 범위 내에서 최댓값을 먼저 찾고, 자리수를 계산해서 정렬할 수 있도록..
*/

#include <iostream> 
#include <vector>
#include <string>
#include <cmath>

using std::cin;

auto calValue(int r, int c);
auto findMaxVal(int r1, int c1, int r2, int c2);

int main() {
    
    int r1, r2, c1, c2; cin >> r1 >> c1 >> r2 >> c2;

    //
    return 0;
}

auto calValue(int r, int c){
    int layer = (abs(r) > abs(c)) ? abs(r) : abs(c);
    
    int num;
    if (r == layer) num = (2*layer + 1)*(2*layer + 1) - (layer - c);
    else if (c == -layer) num = (2*layer + 1)*(2*layer + 1) - 2*layer - (layer - r);
    else if (r == -layer) num = (2*layer + 1)*(2*layer + 1) - 4*layer - (layer + c);
    else if (c == layer) num = (2*layer + 1)*(2*layer + 1) - 6*layer - (layer - c);

    return num;
}

auto findMaxVal(int r1, int c1, int r2, int c2){
    int maxVal = -1;

    for (int r = r1; r <= r2; ++r){
        for (int c = c1; c <= c2; ++c){
            
        }
    }
}