#include <iostream>

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

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
        {
            cout << rand() % 100 << endl;
        }
        else
        {
            cout << rand() % 100;
        }
    }

    return 0;
}
