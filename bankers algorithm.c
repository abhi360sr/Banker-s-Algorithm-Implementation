#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int need_matrix[MAX][MAX];
int allocation_matrix[MAX][MAX];
int available[MAX];
int max[MAX][MAX];
int need_matrix_copy[MAX][MAX];
int n, m;

void safetyAlgorithm() {
    int index = 0;
    int sequence[MAX];
    int exited = 0;
    int available_temp[MAX];
    int isFinished[MAX];

    for (int i = 0; i < m; i++) {
        available_temp[i] = available[i];
    }

    for (int i = 0; i < n; i++) {
        isFinished[i] = 0;
    }

    while (exited < n) {
        int flag = 0;

        for (int i = 0; i < n; i++) {
            if (!isFinished[i]) 
            {
                int j;
                for (j = 0; j < m; j++) 
                {
                    if (need_matrix[i][j] > available_temp[j])
                        break;
                }
                if (j == m) 
                {
                    for (int k = 0; k < m; k++) 
                    {
                        available_temp[k] += allocation_matrix[i][k];
                    }
                    sequence[index++] = i;
                    isFinished[i] = 1;
                    exited++;
                    flag = 1;
                }
            }
        }

        if (!flag) {
            printf("\nUnsafe state detected!\n");
            return;
        }
    }

    printf("\nSafe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

void calculateNeedMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (max[i][j] >= allocation_matrix[i][j]) {
                need_matrix[i][j] = max[i][j] - allocation_matrix[i][j];
            } else {
                printf("Error in the resource allocation and demand of the process P%d!\n", i);
                exit(1);
            }
        }
    }

    printf("\nNeed matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d ", need_matrix[i][j]);
        }
        printf("\n");
    }
}

void copyNeedMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need_matrix[i][j] = need_matrix_copy[i][j];
        }
    }
}

void resetNeedMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need_matrix[i][j] = need_matrix_copy[i][j];
        }
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("\nEnter the number of resources: ");
    scanf("%d", &m);

    printf("\nEnter the number of instances of each resource (current available): ");
    for (int i = 0; i < m; i++) {
        printf("\nFor resource %d: ",i);
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("\nFor process (p%d): ", i);
        for (int j = 0; j < m; j++) {
            printf("\nAllocated Resource %d: ", j);
            scanf("%d", &allocation_matrix[i][j]);
        }
    }

    printf("\nAllocation Matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d ", allocation_matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        printf("\nFor process (p%d): ", i);
        for (int j = 0; j < m; j++) {
            printf("\nMax Resource %d: ",j);
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nMax matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d ", max[i][j]);
        }
        printf("\n");
    }

    calculateNeedMatrix();

    while (1) {
        char input[4];
        printf("\nDoes any process have any request? (yes/no) ");
        scanf("%s", input);

        if (strcmp(input, "yes") == 0) {
            int pid;
            printf("\nProcess no: ");
            scanf("%d", &pid);

            for (int i = 0; i < m; i++) {
                int temp;
                printf("\nResource new request %d: ",i);
                scanf("%d", &temp);
                allocation_matrix[pid][i] += temp;
                available[i] -= temp;
            }

            calculateNeedMatrix();
            safetyAlgorithm();
            resetNeedMatrix();
        } else {
            break;
        }
    }

    return 0;
}