---
title: Activity 3.3
papersize: letter
fontsize: "12pt"
date: \today
author:
  - "José Carlos Martínez Núñez"
  - "Tania Sayuri Guizado Hernández"
bibliography: []
toc: true
titlepage: true
lang: en
---

## Problem Description

- Write a C++ program that solves the Knapsack problem.

The input to the program is a number $N$ representing the number of possible elements available, followed by $N$ integers representing the value of each of those elements, followed by $N$ integers representing the weights associated with each element. Finally, an integer $W$, representing the maximum weight or capacity of the backpack.

The output of the program should be the optimal gain (or profit).

**Sample input:**

```text
3
1
2
3
4
5
1
4
```

**Sample output:**

```text
3
```

## Algorithm Implementation

### Knapsack Problem

```cpp
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++)
    {

        for (int j = 1; j <= W; j++)
        {
            if (weights[i - 1] <= j)
            {
                dp[i][j] = max(dp[i - 1][j], values[i - 1] + dp[i - 1][j - weights[i - 1]]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][W] << endl;
```

This is the code for the Knapsack problem, it uses dynamic programming to solve the problem. The first for loop iterates through the number of elements, the second for loop iterates through the capacity of the backpack. The time complexity of this algorithm is $O(NW)$, where $N$ is the number of elements and $W$ is the capacity of the backpack. And the space complexity is $O(NW)$, because we are using a matrix to store the values.

## Test Cases

- `example_test.txt`: The example test case from the problem description. The output is `3`.
- `10_test.txt`: The test case with 10 elements. The output is `295`. (Taken from [here](https://www.researchgate.net/figure/Five-typical-test-cases-of-0-1-knapsack-problems_tbl1_349878676))
- `50_test.txt`: 50 different elements, with weights and values between 1 and 500. For the capacity of `376` the maximum value is `2397`.
- `100_test.txt`: 100 different elements, with weights between 1 and 500 and values between 1 and 50. For the capacity of `119` the maximum value is `101`.

## Hardware

For this activity we used a MacBook Pro (13-inch, 2018, Four Thunderbolt 3 Ports) with the following specs:

- **Processor:** 2.3 GHz Quad-Core Intel Core i5
- **Memory:** 8 GB 2133 MHz LPDDR3
- **Graphics:** Intel Iris Plus Graphics 655 1536
