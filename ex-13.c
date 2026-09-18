#include <stdio.h>
#include <stdlib.h>
#define MAX 100 
void sstf(int req[], int n, int head)
{
    int visited[MAX] = {0};
    int total = 0, cur = head, i, count = 0;
    printf("\n--- SSTF (Shortest Seek Time First) ---\n");
    printf("Seek Sequence: %d", cur);
 
    while (count < n) {
        int min_dist = 1000000, idx = -1;
        for (i = 0; i < n; i++) {
            if (!visited[i]) {
                int dist = abs(req[i] - cur);
                if (dist < min_dist) {
                    min_dist = dist;
                    idx = i;
                }
            }
        }
        visited[idx] = 1;
        total += min_dist;
        cur = req[idx];
        printf(" -> %d", cur);
        count++;
    }
    printf("\nTotal Head Movement (SSTF) = %d\n", total);
}
int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
void scan(int req[], int n, int head, int disk_size, int direction)
{
    /* direction: 1 = towards higher cylinder numbers first, 0 = towards lower first */
    int sorted[MAX];
    int i;
    for (i = 0; i < n; i++) sorted[i] = req[i];
    qsort(sorted, n, sizeof(int), cmp);
 
    int total = 0, cur = head;
    printf("\n--- SCAN (Elevator Algorithm) ---\n");
    printf("Seek Sequence: %d", cur);
 
    if (direction == 1) { /* move up towards disk_size-1, then reverse */
        for (i = 0; i < n; i++) {
            if (sorted[i] >= head) {
                printf(" -> %d", sorted[i]);
                total += abs(sorted[i] - cur);
                cur = sorted[i];
            }
        }
        if (cur != disk_size - 1) {
            printf(" -> %d", disk_size - 1);
            total += abs((disk_size - 1) - cur);
            cur = disk_size - 1;
        }
        for (i = n - 1; i >= 0; i--) {
            if (sorted[i] < head) {
                printf(" -> %d", sorted[i]);
                total += abs(cur - sorted[i]);
                cur = sorted[i];
            }
        }
    } else { /* move down towards 0, then reverse */
        for (i = n - 1; i >= 0; i--) {
            if (sorted[i] <= head) {
                printf(" -> %d", sorted[i]);
                total += abs(cur - sorted[i]);
                cur = sorted[i];
            }
        }
        if (cur != 0) {
            printf(" -> %d", 0);
            total += abs(cur - 0);
            cur = 0;
        }
        for (i = 0; i < n; i++) {
            if (sorted[i] > head) {
                printf(" -> %d", sorted[i]);
                total += abs(sorted[i] - cur);
                cur = sorted[i];
            }
        }
    }
    printf("\nTotal Head Movement (SCAN) = %d\n", total);
}
 
void cscan(int req[], int n, int head, int disk_size)
{
    /* C-SCAN always moves in one direction (towards higher cylinders here),
       then jumps back to 0 and continues in the same direction */
    int sorted[MAX];
    int i;
    for (i = 0; i < n; i++) sorted[i] = req[i];
    qsort(sorted, n, sizeof(int), cmp);
 
    int total = 0, cur = head;
    printf("\n--- C-SCAN (Circular SCAN) ---\n");
    printf("Seek Sequence: %d", cur);
 
    for (i = 0; i < n; i++) {
        if (sorted[i] >= head) {
            printf(" -> %d", sorted[i]);
            total += abs(sorted[i] - cur);
            cur = sorted[i];
        }
    }
    if (cur != disk_size - 1) {
        printf(" -> %d", disk_size - 1);
        total += abs((disk_size - 1) - cur);
        cur = disk_size - 1;
    }
    /* jump to the beginning of the disk (this jump is not counted as seek time) */
    printf(" -> 0 (jump)");
    cur = 0;
    for (i = 0; i < n; i++) {
        if (sorted[i] < head) {
            printf(" -> %d", sorted[i]);
            total += abs(sorted[i] - cur);
            cur = sorted[i];
        }
    }
    printf("\nTotal Head Movement (C-SCAN) = %d\n", total);
}
 
int main()
{
    int n, head, disk_size, i, direction;
    int req[MAX];
 
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    printf("Enter the request queue (cylinder numbers):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);
 
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size (max cylinder number + 1, e.g. 200): ");
    scanf("%d", &disk_size);
    printf("Enter initial direction for SCAN (1 = towards higher, 0 = towards lower): ");
    scanf("%d", &direction);
 
    sstf(req, n, head);
    scan(req, n, head, disk_size, direction);
    cscan(req, n, head, disk_size);
 
    return 0;
}
 
