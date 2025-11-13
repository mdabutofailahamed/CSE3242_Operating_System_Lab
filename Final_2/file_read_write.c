#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILE_NAME "example_file.txt"
#define MAX_BUFFER_SIZE 1024

int main() {
    int fd;
    ssize_t bytesWritten, bytesRead;
    char writeBuffer[] = "Hello, this is a test file.\nWriting to a file using open(), write(), and read().";
    char readBuffer[MAX_BUFFER_SIZE];

    // Open the file for writing (create if it doesn't exist)
    fd = open(FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        write(2, "Error opening file for writing\n", 30); // Write error to standard error
        return 1;
    }

    // Write data to the file
    bytesWritten = write(fd, writeBuffer, strlen(writeBuffer));
    if (bytesWritten == -1) {
        write(2, "Error writing to file\n", 22);
        close(fd);
        return 1;
    }

    // Close the file after writing
    close(fd);

    // Reopen the file for reading
    fd = open(FILE_NAME, O_RDONLY);
    if (fd == -1) {
        write(2, "Error opening file for reading\n", 30); // Write error to standard error
        return 1;
    }

    // Read the contents of the file
    bytesRead = read(fd, readBuffer, MAX_BUFFER_SIZE - 1); // Leave space for null-terminator
    if (bytesRead == -1) {
        write(2, "Error reading from file\n", 24);
        close(fd);
        return 1;
    }

    // Null-terminate the string and print it
    readBuffer[bytesRead] = '\0';
    write(1, "File contents:\n", 15);
    write(1, readBuffer, bytesRead);

    // Close the file after reading
    close(fd);

    return 0;
}
