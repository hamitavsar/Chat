#include "server.h"

static void deamon_failed_output(int cases) {
    if (cases == 1) {
        write(2, "error: deamon launch failed\n", 28);
        write(2, "forking error\n", 15);
        exit(EXIT_FAILURE);
    }
    if (cases == 2) {
        write(2, "error: deamon launch failed\n", 28);
        write(2, "writting log error\n", 19);
        exit(EXIT_FAILURE);
    }
}

static void deamon_successfull_output(pid_t pid) {
    write(1, "uchat_server started successfully\n", 34);
    write(1, "uchat_server pid: ", 18);
    mx_printint(pid);
    write(1, "\nto STOP uchat_server: kill <uchat_server pid>\n", 47);
    write(1, "if you lost uchat_server pid: ps -ax | grep uchat_server\n", 57);
}

void mx_deamon_start(void) {
    pid_t pid;

    
    pid = fork();
    if (pid < 0) 
        deamon_failed_output(1);
    if (pid > 0 )
        exit(EXIT_SUCCESS);
    else {
        deamon_successfull_output(getpid());
        umask(0);   
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        setsid();   
    }
}
