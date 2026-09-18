#include <stdio.h>
#include <string.h>
#define MAX 20
void first_fit(int bsize[], int nb, int psize[], int np)
{
    int block[MAX], allocation[MAX];
    int i, j;
 
    for (i = 0; i < nb; i++) block[i] = bsize[i]; /* remaining size of each block */
    for (i = 0; i < np; i++) allocation[i] = -1;
 
    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (block[j] >= psize[i]) {
                allocation[i] = j;
                block[j] -= psize[i];
                break;
            }
        }
    }
 
    printf("\n--- First Fit ---\n");
    printf("Process\tSize\tBlock Allocated\n");
    for (i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tBlock %d\n", i + 1, psize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, psize[i]);
    }
}
void best_fit(int bsize[], int nb, int psize[], int np)
{
    int block[MAX], allocation[MAX];
    int i, j;
    for (i = 0; i < nb; i++) block[i] = bsize[i];
    for (i = 0; i < np; i++) allocation[i] = -1;
    for (i = 0; i < np; i++) {
        int best_idx = -1;
        for (j = 0; j < nb; j++) {
            if (block[j] >= psize[i]) {
                if (best_idx == -1 || block[j] < block[best_idx])
                    best_idx = j;
            }
        }
        if (best_idx != -1) {
            allocation[i] = best_idx;
            block[best_idx] -= psize[i];
        }
    }
    printf("\n--- Best Fit ---\n");
    printf("Process\tSize\tBlock Allocated\n");
    for (i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tBlock %d\n", i + 1, psize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, psize[i]);
    }
}
void worst_fit(int bsize[], int nb, int psize[], int np)
{
    int block[MAX], allocation[MAX];
    int i, j;
    for (i = 0; i < nb; i++) block[i] = bsize[i];
    for (i = 0; i < np; i++) allocation[i] = -1;
    for (i = 0; i < np; i++) {
        int worst_idx = -1;
        for (j = 0; j < nb; j++) {
            if (block[j] >= psize[i]) {
                if (worst_idx == -1 || block[j] > block[worst_idx])
                    worst_idx = j;
            }
        }
        if (worst_idx != -1) {
            allocation[i] = worst_idx;
            block[worst_idx] -= psize[i];
        }
    }
    printf("\n--- Worst Fit ---\n");
    printf("Process\tSize\tBlock Allocated\n");
    for (i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tBlock %d\n", i + 1, psize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, psize[i]);
    }
}
int main()
{
    int nb, np, i;
    int bsize[MAX], psize[MAX];
 
    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter size of each block:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &bsize[i]);
    }
    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter size of each process:\n");
    for (i = 0; i < np; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &psize[i]);
    }
    first_fit(bsize, nb, psize, np);
    best_fit(bsize, nb, psize, np);
    worst_fit(bsize, nb, psize, np);
 
    return 0;
}

