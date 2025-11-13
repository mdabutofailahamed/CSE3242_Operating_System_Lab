
#include <stdio.h>

#define MAX 100

int main() {
    int n, frames, pages[MAX], frame[MAX], index = 0;
    int pageFaults = 0, i, j, flag;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Initialize frame array with -1 (indicating empty frames)
    for (i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("\nPage reference string  | Frames\n");
    printf("-----------------------|--------\n");

    // FIFO Page Replacement Algorithm
    for (i = 0; i < n; i++) {
        flag = 0;

        // Check if the page is already in a frame
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // If the page is not found in a frame, replace it using FIFO
        if (flag == 0) {
            frame[index] = pages[i];
            index = (index + 1) % frames;  // Update index for FIFO replacement
            pageFaults++;

            // Print the current status of frames
            printf("%-23d| ", pages[i]);
            for (j = 0; j < frames; j++) {
                if (frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("\n");
        } else {
            // If the page is found, just print the current status of frames
            printf("%-23d| No Page Fault\n", pages[i]);
        }
    }

    int hit=n-pageFaults;
    printf("\nTotal Hit: %d\n", hit);
    printf("Total Page Faults/Miss: %d\n", pageFaults);
    printf("Hit Ratio: %0.2lf\n", (hit*100.00)/n);

    return 0;
}
