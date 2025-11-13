#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main() {
    // If O_APPEND is not specified, previous data will be overwritten
    int fd = open("task.txt", O_RDWR | O_CREAT |O_APPEND, 0666);
    if(fd == -1) {
        printf("Can't Open File.\n");
        return 1;
    }

    // Write
    char *msg = "1. Create a child process.\n";
    ssize_t bytes_written = write(fd, msg, strlen(msg));
    if(bytes_written == -1) {
        printf("Write Failed\n");
        close(fd);
        return 1;
    }

    lseek(fd, 0, SEEK_SET); // Move the file pointer at the beginning of the file

    // Read
    char buffer[1024];
    ssize_t bytes_read = read(fd, &buffer, sizeof(buffer));
    if(bytes_read == -1) {
        printf("Read Failed\n");
        close(fd);
        return 1;
    }
    buffer[bytes_read] = '\0';
    write(STDOUT_FILENO, buffer, strlen(buffer));
    close(fd);
}
