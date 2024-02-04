#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;

    //redirout  outfilename  command opt1 opt2 ...
    if (argc < 3) {
        fprintf(stderr, "usage: redirout  outfilename  command opt1 opt2 ...\n");
        return 1;
    }

    fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }

    execvp(argv[2], &argv[2]);
    perror("execvp");
    return 1;
}