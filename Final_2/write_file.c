#include <fcntl.h>   // For open()
#include <unistd.h>  // For read(), write(), close()
#include <string.h>  // For strlen()
#include <stdio.h>   // For perror()

int main() {
    int fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    // Open a file for writing (create it if it doesn't exist)
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Prompt user for input
    write(STDOUT_FILENO, "Enter text to write to the file (Ctrl+D to end):\n", 48);

    // Read input from the user and write it to the file
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to file");
            close(fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading input");
        close(fd);
        return 1;
    }

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    write(STDOUT_FILENO, "Data successfully written to 'output.txt'.\n", 43);
    return 0;
}

