#include <iostream>
#include <random>

using namespace std;

int main(int argc, char const *argv[])
{
    // Parsing arguments
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <n_numbers_to_generate>" << endl;
        return 1;
    }

    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n = atoi(argv[1]);

    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> dist(lower_bound, upper_bound);
    default_random_engine generator;
    generator.seed(time(NULL));

    cout << n << endl;

    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
        {
            cout << dist(generator) << endl;
        }
        else
        {
            cout << dist(generator);
        }
    }

    return 0;
}
