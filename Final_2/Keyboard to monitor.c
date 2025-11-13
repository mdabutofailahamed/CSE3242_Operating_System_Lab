#include <unistd.h>
#include <stdio.h>

int main() {
    char buffer[1024];  // Buffer to store input
    ssize_t bytes_read;

    // Prompt the user
    write(STDOUT_FILENO, "Enter text (Ctrl+D to end):\n", 28);

    // Read input from keyboard (standard input, file descriptor 0)
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0) {
        // Write the input back to the monitor (standard output, file descriptor 1)
        write(STDOUT_FILENO, "You entered: ", 13);
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        write(STDOUT_FILENO, "Error reading input.\n", 22);
        return 1;
    }

    write(STDOUT_FILENO, "\nEnd of Input.\n", 15);
    return 0;
}
