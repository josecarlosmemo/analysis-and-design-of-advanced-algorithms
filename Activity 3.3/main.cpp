#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    vector<int> weights(n);
    vector<int> values(n);

    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> weights[i];
    }

    int W;
    cin >> W;

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

    return 0;
}
