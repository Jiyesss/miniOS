#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <system.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>

#include "system.h"


void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while(1) {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input,"exit") == 0) {
            break;
        }

        if (strcmp(input,"minisystem") == 0){
            minisystem();
        }

	    else if (strcmp(input,"date") == 0) {
            time_t now;
            time(&now);
            printf("%s", ctime(&now)); // ctime 함수를 사용해 현재 시간을 문자열로 변환하여 출력
        }

        else if (strcmp(input,"startfork") == 0) {
            new_fork();
        }

        else if (strcmp(input,"ipc") == 0) {
            ipc_pipe();
        }
        /*
        else if (strcmp(input,"pi") == 0) {
            calculate_pi();
        }
        */
        else if (strcmp(input,"roundrobin") == 0) {
            rrscheduler2();
        }
        
        else if (strcmp(input,"multipi") == 0) {
            monte_mutex();
        }
        
        else system(input);
    }

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
