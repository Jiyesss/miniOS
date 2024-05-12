#include <stdio.h>      
#include <stdlib.h>     
#include <pthread.h>   
#include <math.h>       
#include <time.h>       

#define NUM_THREADS 6   // 사용할 스레드의 수
#define NUM_POINTS 1000000  // 각 스레드가 생성할 임의의 점의 수

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 뮤텍스 초기화
long long circle_count = 0;  // 단위 원 안에 들어간 점의 총 수

void *estimate_pi(void *param) {  // 원주율을 추정하는 함수
    int points_inside_circle = 0;  // 단위 원 안에 들어간 점의 수 (각 스레드별)
    unsigned int seed = time(NULL) ^ pthread_self();  

    for (int i = 0; i < NUM_POINTS; ++i) {
        double x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;  // x좌표 생성
        double y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;  // y좌표 생성

        if (x * x + y * y <= 1.0) {  // 점이 단위 원 안에 있는지 확인
            ++points_inside_circle;
        }
    }

    pthread_mutex_lock(&mutex);  // 뮤텍스를 이용해 critical section 보호
    circle_count += points_inside_circle;  // 전역 변수에 점의 수 추가
    pthread_mutex_unlock(&mutex);  // critical section  보호 해제

    return NULL;
}

int monte_mutex() {
    pthread_t threads[NUM_THREADS];  // 스레드 식별자 배열
    
    for (int i = 0; i < NUM_THREADS; ++i) {  // 스레드 생성
        if (pthread_create(&threads[i], NULL, estimate_pi, NULL)) {
            fprintf(stderr, "Error creating thread\n");  // 스레드 생성 실패 시 에러 메시지 출력
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {  // 모든 스레드가 종료될 때까지 대기
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Error joining thread\n");  // 스레드 종료 대기 실패 시 에러 메시지 출력
            return 2;
        }
    }

    double pi_estimate = 4.0 * circle_count / (NUM_THREADS * NUM_POINTS);  // 원주율 추정치 계산
    printf("Estimated Pi = %f\n", pi_estimate);  // 원주율 추정치 출력

    return 0;
}
