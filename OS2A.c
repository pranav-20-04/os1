#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// Function prototypes
void bass(int arr[], int n);
void bdsc(int arr[], int n);
void forkeg();

// Bubble sort for ascending order
void bass(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nAscending Order\n");
    for (i = 0; i < n; i++)
        printf("\t%d", arr[i]);
    printf("\n\n");
}

// Bubble sort for descending order
void bdsc(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nDescending Sorting\n\n");
    for (i = 0; i < n; i++)
        printf("\t%d", arr[i]);
    printf("\n\n");
}

// Forking and sorting
void forkeg() {
    int arr[25], n, i, status;
    printf("Enter the number of values in array: ");
    scanf("%d", &n);
    if (n > 25) {
        printf("Array size exceeds the limit. Maximum allowed size is 25.\n");
        return;
    }
    printf("Enter the array elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int pid = fork();
    if (pid == 0) {
        // Child process
        printf("\nChild process\n");
        printf("Child process id=%d\n", getpid());
        bdsc(arr, n);
        printf("\nElements Sorted Using Quick Sort:\n");
        for (i = 0; i < n; i++)
            printf("%d, ", arr[i]);
        printf("\n");
        printf("Parent process id=%d\n", getppid());
        system("ps -x");
    } else {
        // Parent process
        printf("\nParent process\n");
        printf("Parent process id=%d\n", getpid());
        bass(arr, n);
        printf("Elements Sorted Using Bubble Sort:\n");
        for (i = 0; i < n; i++)
            printf("%d, ", arr[i]);
        printf("\n\n");
    }
}

int main() {
    forkeg();
    return 0;
}
