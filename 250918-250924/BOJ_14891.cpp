/*
톱니바퀴 - BOJ 14891

시간복잡도 : O(K)
공간복잡도 : O(1)

문제 접근
        시간제한 2초. 톱니바퀴는 4개이고 K <= 100. O(K⁴)만 넘지 않으면 되니 시간초과는 크게 고려하지 않아도 될듯.
        
        5행 8열짜리 배열 써서 각 톱니바퀴의 상태 저장. 원형이니까 2배 해서 만드는게 나을까?
        일단 8열짜리 배열 만들어서 해보자. 

        12시 방향의 위치만 기억하고, 나머지는 +3에 모듈러 연산으로 구하자.

        1) 첫번째 접근, BFS처럼 각 K번째 step마다 돌려보자

            1. 해당 톱니바퀴의 번호와 회전 방향을 Queue에 넣음
            2. Queue에서 하나씩 꺼내며 톱니바퀴의 회전 연산 수행(12시 방향의 인덱스만 변경)
            3. 조건에 따라 좌, 우를 회전시키고, Queue에 넣음
            3-1. 좌의 경우 3시와 이전 톱니바퀴의 9시 정보를 비교해, 다르다면 회전 연산 수행
            3-2. 우의 경우 9시와 이전 톱니바퀴의 3시 정보를 비교해, 다르다면 회전 연산 수행
            4. 회전 연산이 수행되었다면, 1번 수행

        → 내가 문제를 잘못 이해했음. 순차적으로 돌아간다고 생각했는데, 특정 시점에 검사 후 한번에 돌아가는 모델이었다..

        2) 두번째 접근, step마다 최대 전파 위치를 찾고, 각 기어의 회전 방향이 결정되면 한번에 돌리자
        
            1. 해당 톱니바퀴 번호와 회전 방향을 기록
            2. 좌우로 전파하며 이전 톱니바퀴와의 정보를 비교해 다르다면 회전 방향을 기록
            3. 각 기어의 회전 유무와 방향이 결정되면 모든 톱니를 한번에 돌림

제출 결과
메모리: 2024KB, 시간: 0ms

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

int findState(int gearNum, int num_12, int num_des);
void rotate(int gearNumber, int rotateDirection);

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

    // K step 연산
    for (int i = 0; i < k; ++i){
        cin >> gearNumber >> rotateDirection;

        int dir = rotateDirection;

        int dirList[5] = {0}; dirList[gearNumber] = rotateDirection;
        for (int left = gearNumber - 1; left > 0; --left){

            int cur_9   = findState(left+1, gear_12index[left+1], 6);
            int left_3  = findState(left,   gear_12index[left],   2);

            if (cur_9 != left_3){
                dir = - dir;
                dirList[left] = dir;
            }
            else break;
        }

        dir = rotateDirection;
        for (int right = gearNumber + 1; right < 5; ++right){

            int cur_3   = findState(right-1, gear_12index[right-1], 2);
            int right_9 = findState(right,   gear_12index[right],   6);

            if (cur_3 != right_9){
                dir = - dir;
                dirList[right] = dir;
            }
            else break;
        }
        
        for (int g = 1; g <= 4; ++g) {
            if (dirList[g]) rotate(g, dirList[g]);
        }
    }

    // 최종 점수 계산
    int ans = 0, score = 1;
    for (int gearnum = 1; gearnum <= 4; ++gearnum){
        if (gear[gearnum][gear_12index[gearnum]] == 1){
            ans += score;
        }
        score *= 2;
    }

    cout << ans;

    return 0;
}

int findState(int gearNum, int num_12, int num_des){
    return gear[gearNum][(num_12+num_des)%8];
}

void rotate(int gearNumber, int rotateDirection){
    if (rotateDirection == 0) return;

    if (rotateDirection > 0){
        gear_12index[gearNumber] = (gear_12index[gearNumber] + 7)%8;
    }
    else{
        gear_12index[gearNumber] = (gear_12index[gearNumber] + 1 )%8;
    }
}




/* 1번 시도
for (int i = 0; i < k; ++i){
    cin >> gearNumber >> rotateDirection;

    std::queue<stepInfo> q;
    q.push({gearNumber, rotateDirection});

    while(!q.empty()){
        auto [cur, dir] = q.front();
        q.pop();
        rotate(cur, dir);

        int currentGear_3 = findState(cur, gear_12index[cur], 2);
        int currentGear_9 = findState(cur, gear_12index[cur], 6);

        // 왼쪽 톱니바퀴
        if (cur > 1){
            int left = cur - 1;
            int leftGear_3 = findState(left, gear_12index[left], 2);
            if (currentGear_9 != leftGear_3){
                q.push({left, -dir});
            }
        }

        // 오른쪽 톱니바퀴
        if (cur < 4){
            int right = cur + 1;
            int rightGear_9 = findState(right, gear_12index[right], 6);
            if (currentGear_3 != rightGear_9){
                q.push({right, -dir});
            }
        }

    }
}
*/