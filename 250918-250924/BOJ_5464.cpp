/*

시간복잡도 :
공간복잡도 :

문제 접근
        시간제한 1초. N = 100, M = 2000 → O(M²N) 넘어가면 연산 4억번 이상. 위험.
        O(N²M) 정도면 연산 2000만번. 낫배드.

        배열 3개 쓰고, 큐 1개 쓰고, 변수 2개 써서 구현해보자
            - i번째 주차 공간의 사용 여부를 나타내는 N+1크기 배열
            - i번째 주차 공간의 Rs를 저장하는 N+1크기 배열
            - i번 차량의 [무게, 사용중인 자리]를 나타내는 (M+1) by 2크기 배열

            - 차량의 대기 Queue

            - 남아있는 주차 공간 수
            - 수입

제출 결과
메모리: 2020KB, 시간: 0ms

*/

#include <iostream> 
#include <vector>
#include <string>
#include <queue>

using std::cin;
using std::cout;

int main() {
    
    int n, m; cin >> n >> m;

    int RsList[n+1];

    for (int i = 1; i <= n; ++i){
        cin >> RsList[i];
    }

    int carInfo[m+1][2] = {{0}};

    for (int i = 1; i <= m; ++i){
        cin >> carInfo[i][0];
    }

    std::queue<int> q;

    int is_using[n+1] = {0};
    int leftSpace = n, income = 0;

    int log;
    for (int i = 0; i < (2*m); ++i){
        cin >> log;

        if (log < 0){
            is_using[carInfo[-log][1]] = 0;
            carInfo[-log][1] = 0;
            leftSpace += 1;
        }
        else{
            q.push(log);
        }

        if (leftSpace > 0 && !q.empty()){
            for (int j = 1; j <= n; ++j){
                if (is_using[j] == 0){
                    int car_idx = q.front();
                    q.pop();

                    is_using[j] = 1;
                    carInfo[car_idx][1] = j;
                    leftSpace -= 1;
                    income += carInfo[car_idx][0]*RsList[j];
                    break;
                }
            }
        }
    }

    cout << income;
    return 0;
}