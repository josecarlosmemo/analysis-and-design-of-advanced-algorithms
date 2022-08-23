#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    auto start = chrono::high_resolution_clock::now();
    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Parsing arguments
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open())
    {
        cout << "Error: File " << argv[1] << " not found" << endl;
        return 1;
    }
    int sum = 0;

    while (!file.eof())
    {
        int n;
        file >> n;
        sum += n;
    }
    cout << "The sum is: " << sum << endl;
    file.close();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time: " << duration.count() << " microseconds" << endl;

    return 0;
}
