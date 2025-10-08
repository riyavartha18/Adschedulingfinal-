#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int profit;
    int deadline;
} Ad;

// Swap function
void swap(Ad *a, Ad *b) {
    Ad temp = *a;
    *a = *b;
    *b = temp;
}

// Sort ads by profit descending for Greedy
void sortByProfit(Ad ads[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (ads[j].profit > ads[i].profit)
                swap(&ads[i], &ads[j]);
}

// Find maximum deadline to define slot size
int findMaxDeadline(Ad ads[], int n) {
    int maxd = 0;
    for (int i = 0; i < n; i++)
        if (ads[i].deadline > maxd)
            maxd = ads[i].deadline;
    return maxd;
}

// Greedy approach for scheduling ads
void greedyScheduling(Ad ads[], int n) {
    sortByProfit(ads, n);
    int maxDeadline = findMaxDeadline(ads, n);
    int slot[maxDeadline + 1];
    for (int i = 0; i <= maxDeadline; i++) slot[i] = -1;

    int totalProfit = 0;
    printf("\nSelected Ads (Greedy):\nAdID\tProfit\tDeadline\n");
    for (int i = 0; i < n; i++) {
        for (int j = ads[i].deadline; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = ads[i].id;
                totalProfit += ads[i].profit;
                printf("%d\t%d\t%d\n", ads[i].id, ads[i].profit, ads[i].deadline);
                break;
            }
        }
    }
    printf("Total Profit (Greedy): %d\n", totalProfit);
}

// Utility max function
int max(int a, int b) { return (a > b) ? a : b; }

// Dynamic Programming approach for scheduling ads
void dpscheduling(Ad ads[], int n) {
    int maxDeadline = findMaxDeadline(ads, n);

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        dp[i] = (int *)calloc(maxDeadline + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= maxDeadline; j++) {
            if (ads[i - 1].deadline >= j)
                dp[i][j] = max(dp[i - 1][j], ads[i - 1].profit + dp[i - 1][j - 1]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    printf("\nMaximum Profit (DP): %d\n", dp[n][maxDeadline]);
    printf("Selected Ads (DP):\nAdID\tProfit\tDeadline\n");

    int res = dp[n][maxDeadline];
    int j = maxDeadline;

    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][j]) {
            printf("%d\t%d\t%d\n", ads[i - 1].id, ads[i - 1].profit, ads[i - 1].deadline);
            res -= ads[i - 1].profit;
            j--;
        }
    }

    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);
}

int main() {
    int n, choice;
    printf("Enter number of ads: ");
    scanf("%d", &n);

    Ad ads[n];
    for (int i = 0; i < n; i++) {
        ads[i].id = i + 1;
        printf("Enter profit and deadline for ad %d: ", i + 1);
        scanf("%d %d", &ads[i].profit, &ads[i].deadline);
    }

    do {
        printf("\nMenu:\n1. Greedy Scheduling\n2. Dynamic Programming Scheduling\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                greedyScheduling(ads, n);
                break;
            case 2:
                dpscheduling(ads, n);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 3);

    return 0;
}
