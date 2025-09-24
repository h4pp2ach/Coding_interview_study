/*

시간복잡도 :
공간복잡도 :

문제 접근
        시간제한 2초. 톱니바퀴는 4개이고 K <= 100. O(K⁴)만 넘지 않도록 짜보자.
        
        5행 8열짜리 배열 써서 각 톱니바퀴의 상태 저장. 원형이니까 2배 해서 만드는게 나을까?
        일단 8열짜리 배열 만들어서 해보자. 

        12시 방향의 위치만 기억하고, 나머지는 +3에 모듈러 연산으로 구하자.

        각 K번쨰 step에 대해서 순차적으로 연산 수행.
            1. 해당 톱니바퀴의 번호와 회전 방향을 Queue에 넣음.
            2. Queue에서 하나씩 꺼내며 톱니바퀴의 회전 연산 수행(12시 방향의 인덱스만 변경).
            3. 조건에 따라 좌, 우를 회전시키고, Queue에 넣음
            3-1. 좌의 경우 3시와 이전 톱니바퀴의 9시 정보를 비교해, 다르다면 회전 연산 수행
            3-2. 우의 경우 9시와 이전 톱니바퀴의 3시 정보를 비교해, 다르다면 회전 연산 수행
            4. 회전 연산이 수행되었다면, 1번 수행

*/

#include <iostream> 
#include <vector>
#include <string>
#include <queue>

using std::cin;
using std::cout;

int gear[5][8]; // 기어의 전체 state를 담을 배열
int gear_12index[5] = {}; // 기어의 12시방향 인덱스를 담을 배열

struct stepInfo{
    int gearNum;
    int rotateDirection;
};

auto find369(int gearNum, int num_12, int num_des);
void rotate(int arr[], int gearNumber, int rotateDirection);

int main() {
    
    // 톱니바퀴의 초기 State 설정
    for (int i = 1; i <= 4; ++i){
        std::string gear_state;
        cin >> gear_state;
        for (int j = 0; j < 8; ++j){
            gear[i][j] = gear_state[j] - '0';
        }
    }

    int k; cin >> k;

    int gearNumber, rotateDirection;

    //각 k번째 step에 대한 연산 수행
    for (int i = 1; i <= k; ++i){
        cin >> gearNumber >> rotateDirection;

        std::queue<stepInfo> q;
        q.push({gearNumber, rotateDirection});

        while(!q.empty()){
            auto [cur, dir] = q.front();
            q.pop();
            rotate(cur, dir);

            int currentGear_3 = findState(cur, gear_12index[cur], 3);
            int currentGear_9 = findState(cur, gear_12index[cur], 9);

            // 왼쪽 톱니바퀴
            if (cur > 1){
                int left = cur - 1;
                int leftGear_3 = findState(left, gear_12index[left], 3);
                if (gear[cur][currentGear_9] != gear[left][leftGear_3]){
                    q.push({left, -dir});
                }
            }

            // 오른쪽 톱니바퀴
            if (cur < 4){
                int right = cur + 1;
                int rightGear_9 = findState(right, gear_12index[right], 9);
                if (gear[cur][currentGear_3] != gear[right][rightGear_9]){
                    q.push({right, -dir});
                }
            }

        }
    }
    int ans = 0;

    //for (int i = 0; )

    return 0;
}

auto findState(int gearNum, int num_12, int num_des){
    return gear[gearNum][(num_12+num_des)%8];
}

void rotate(int gearNumber, int rotateDirection){
    if (rotateDirection < 0){
        gear_12index[gearNumber] = (gear_12index[gearNumber] + 7)%8;
    }
    else{
        gear_12index[gearNumber] = (gear_12index[gearNumber] + 1 )%8;
    }
}