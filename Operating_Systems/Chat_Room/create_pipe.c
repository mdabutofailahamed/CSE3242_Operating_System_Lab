#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    // First pipe
    char *pipe_path1 = "/home/shakil/Documents/Chat_Room/1stPipe";
    int pipe_flag1;

    // Create a named pipe
    if(access(pipe_path1, F_OK) == 0) { // pipe exists
        printf("Pipe 1 already exist.\n");
    }
    else { // Create the pipe
        pipe_flag1 = mkfifo(pipe_path1, 0666);
        if(pipe_flag1 < 0){
			printf("Error in creating a named pipe.\n");
			exit(1);	
		} else{
			printf("Pipe 1 has been created successfully.\n");
		}
    }
    // Second pipe
    char *pipe_path2 = "/home/shakil/Documents/Chat_Room/2ndPipe";
    int pipe_flag2;

    // Create a named pipe
    if(access(pipe_path2, F_OK) == 0) { // pipe exists
        printf("Pipe 2 already exist.\n");
    }
    else { // Create the pipe
        pipe_flag2 = mkfifo(pipe_path2, 0666);
        if(pipe_flag2 < 0){
			printf("Error in creating a named pipe.\n");
			exit(1);	
		} else{
			printf("Pipe 2 has been created successfully.\n");
		}
    }

    return 1;
}