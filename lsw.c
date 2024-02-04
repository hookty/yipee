#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;

    char *path = argv[1];

    if (path == NULL) {
        path = ".";
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // chillin run wc on the read end
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // parent run ls on the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);

        execlp("ls", "ls", path, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}