#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

int* longestDivisibleSubsequence(int arr[], int n) {
    int* dp = (int*)malloc(sizeof(int) * n);
    int* result = (int*)malloc(sizeof(int) * (n+1));

    int maxLen = 1;
    int maxLenInx = 0;

    for (int i = 0; i < n; i++)
        dp[i] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] % arr[j] == 0 && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1;
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxLenInx = i;
        }
    }
    result[0] = maxLen;
    for (int i = maxLenInx - maxLen + 1; i < maxLenInx + 1; i++) {
        result[i - maxLenInx + maxLen] = arr[i];
    }
    free(dp);
    return result;
}
int check(int* arr, int* result, int n) {
    int* realResult = longestDivisibleSubsequence(arr, n);
    for (int i = 0; i < 5; ++i) {
    }
    for (int i = 0; i < realResult[0]; ++i) {
        if (realResult[i+1] != result[i]) return 0;
    }
    return 1;
}

TEST(longestDivisibleSubsequenceTest, HandlesOneElementInput) {
    int arr[] = { 1 };
    int result[] = { 1 };
    ASSERT_TRUE(check(arr, result, sizeof(arr) / sizeof(arr[0])));
}
TEST(longestDivisibleSubsequenceTest, HandlesPrimeNumbersInput) {
    int arr[] = { 2, 3, 5, 7 };
    int result[] = { 2 };
    ASSERT_TRUE(check(arr, result, sizeof(arr) / sizeof(arr[0])));
}
TEST(longestDivisibleSubsequenceTest, HandlesRepeatedNumberInput) {
    int arr2[] = { 5, 5, 5, 5, 5 };
    int result2[] = { 5, 5, 5, 5, 5 };
    ASSERT_TRUE(check(arr2, result2, sizeof(arr2) / sizeof(arr2[0])));
}

TEST(longestDivisibleSubsequenceTest, HandlesStandartInput) {
    int arr[] = { 1, 2, 4, 8 };
    int result[] = { 1, 2, 4, 8 };
    ASSERT_TRUE(check(arr, result, sizeof(arr) / sizeof(arr[0])));

    int arr2[] = { 3, 9, 18, 3, 9, 777 };
    int result2[] = { 3, 9, 18 };
    ASSERT_TRUE(check(arr2, result2, sizeof(arr2) / sizeof(arr2[0])));

    int arr3[] = { 11, 900, 2, 8, 78 };
    int result3[] = { 2, 8 };
    ASSERT_TRUE(check(arr3, result3, sizeof(arr3) / sizeof(arr3[0])));
}
