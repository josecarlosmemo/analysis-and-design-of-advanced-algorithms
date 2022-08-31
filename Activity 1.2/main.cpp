#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void greedy_algorithm(vector<int> &coins, int change)
{
    vector<int> coins_used;
    int total_coins = 0;

    for (int coin : coins)
    {
        while (change >= coin)
        {
            change -= coin;
            total_coins++;
            coins_used.push_back(coin);
        }
    }
    cout << "Total coins used: " << total_coins << endl;

    for (int i = 0; i < coins_used.size(); i++)
    {
        cout << coins_used[i] << endl;
    }
    cout << endl;
}

void dynamic_programming(vector<int> &coins, int change)
{

    vector<int> dp(change + 1, -1);
    vector<int> coins_used(change + 1, -1);

    dp[0] = 0;
    coins_used[0] = 0;
    for (int i = 1; i <= change; i++)
    {
        for (auto coin : coins)
        {

            if (i - coin >= 0)
            {
                if (dp[i - coin] != -1)
                {
                    if (dp[i] == -1 || dp[i] > dp[i - coin] + 1)
                    {
                        dp[i] = dp[i - coin] + 1;
                        coins_used[i] = coin;
                    }
                }
            }
        }
    }
    cout << "Total coins used: " << dp[change] << endl;

    while (change > 0)
    {
        cout << coins_used[change] << endl;
        change -= coins_used[change];
    }
}

int main(int argc, char const *argv[])
{
    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }
    // Sort the coins in descending order
    sort(coins.begin(), coins.end(), greater<int>());

    int price;
    cin >> price;

    int money_given;
    cin >> money_given;

    int change = money_given - price;

    if (change < 0)
    {
        cout << "Not enough money was given in order to pay for the product." << endl;
    }
    else
    {
        cout << "---- Greedy Algorithm ----" << endl;
        greedy_algorithm(coins, change);
        cout << "---- Dynamic programming ----" << endl;
        dynamic_programming(coins, change);
    }

    return 0;
}
