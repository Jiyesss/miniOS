#include <stdio.h>
#include <stdlib.h>

// 프로세스 구조체 정의
struct Process {
    int pid; // 프로세스 ID
    int burstTime; // 프로세스의 실행 시간 (버스트 타임)
    int arrivalTime; // 프로세스의 도착 시간
    int waitingTime; // 프로세스의 대기 시간
    int turnaroundTime; // 프로세스의 전체 실행 완료 시간 (대기 시간 + 실행 시간)
};

// Round Robin 스케줄러 함수 선언
void roundRobin(struct Process *processes, int n, int quantum);

int rrscheduler2() {
    int n, quantum;

    // 프로세스 개수와 시간 퀀텀 입력 받기
    printf("Process의 개수를 입력하세요: ");
    scanf("%d", &n);
    printf("Time quantum을 입력하세요: ");
    scanf("%d", &quantum);

    struct Process processes[n];

    // 각 프로세스의 도착 시간 및 버스트 타임 입력 받기
    for(int i = 0; i < n; i++) {
        printf("프로세스 %d의 arrival time을 입력하세요: ", i+1);
        scanf("%d", &processes[i].arrivalTime);
        printf("프로세스 %d의 burst time을 입력하세요: ", i+1);
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i+1; // 프로세스 ID 설정
    }

    // Round Robin 스케줄링 실행
    roundRobin(processes, n, quantum);

    return 0;
}

// Round Robin 스케줄링 함수 구현
void roundRobin(struct Process *processes, int n, int quantum) {
    int x = n, counter = 0;
    int wait_time = 0, turnaround_time = 0, t = 0;
    int temp[n];

    // 각 프로세스의 남은 실행 시간을 임시 배열에 저장
    for(int i = 0; i < n; i++) {
        temp[i] = processes[i].burstTime;
    }

    // 모든 프로세스가 완료될 때까지 실행
    while(x != 0) {
        for(int i = 0; i < n; i++) {
            if(processes[i].arrivalTime <= t && temp[i] > 0) {
                if(temp[i] <= quantum) { // 실행 시간이 퀀텀 이하일 경우
                    t += temp[i];
                    temp[i] = 0;
                    counter = 1;
                } else { // 실행 시간이 퀀텀보다 클 경우
                    temp[i] -= quantum;
                    t += quantum;
                }
                if(temp[i] == 0 && counter == 1) {
                    x--;
                    processes[i].waitingTime = t - processes[i].burstTime - processes[i].arrivalTime;
                    processes[i].turnaroundTime = t - processes[i].arrivalTime;
                    wait_time += processes[i].waitingTime;
                    turnaround_time += processes[i].turnaroundTime;
                    counter = 0;
                }
            } else if (processes[i].arrivalTime > t) {
                t++;
                i--; // 도착 시간이 되지 않으면 다음 프로세스를 검사하지 않고 시간을 증가시킴
            }
        }
    }

    // 결과 출력
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // 평균 대기 시간 및 전환 시간 출력
    printf("\nAverage waiting time = %f\n", (float)wait_time / n);
    printf("Average turnaround time = %f\n", (float)turnaround_time / n);
}
