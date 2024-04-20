#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4 // 스레드의 수
#define POINTS_PER_THREAD 1000000 // 각 스레드에서 생성할 랜덤 포인트의 수

pthread_mutex_t mutex; // 전역 변수에 대한 접근을 동기화하기 위한 뮤텍스
long total_points_in_circle = 0; // 원 안에 들어간 포인트의 총 수를 저장

// 각 스레드가 실행
void* calculate(void* arg) {
    unsigned int seed = time(NULL) ^ pthread_self();
    long points_in_circle = 0;
    for (int i = 0; i < POINTS_PER_THREAD; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX * 2 - 1; // -1과 1 사이의 x 좌표
        double y = (double)rand_r(&seed) / RAND_MAX * 2 - 1; // -1과 1 사이의 y 좌표
        if (x * x + y * y <= 1) points_in_circle++; // 포인트가 원 안에 있는지 확인
    }
    
    pthread_mutex_lock(&mutex); // 뮤텍스로 보호하여 전역 변수를 업데이트
    total_points_in_circle += points_in_circle;
    pthread_mutex_unlock(&mutex); // 뮤텍스 잠금을 해제

    return NULL;
}

int calculate_pi() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL); // 뮤텍스 초기화

    // 스레드 생성
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calculate, NULL);
    }

    // 모든 스레드가 종료될 때까지 대기
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // π 추정값 계산 및 출력
    double pi_estimate = 4 * (double)total_points_in_circle / (NUM_THREADS * POINTS_PER_THREAD);
    printf("Estimated π = %f\n", pi_estimate);

    pthread_mutex_destroy(&mutex); // 뮤텍스 소멸

    return 0;
}
