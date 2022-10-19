#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{

    //  Parsing args
    if (argc != 4)
    {
        cout << "Usage: ./generate_test_cases <number_items> <max_weight> <max_value>" << endl;
        return 0;
    }

    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //  Generating random test cases
    int number_items = stoi(argv[1]);
    int max_weight = stoi(argv[2]);
    int max_value = stoi(argv[3]);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_weight(1, max_weight);
    uniform_int_distribution<> dis_value(1, max_value);

    cout << number_items << endl;

    for (int i = 0; i < number_items; i++)
    {
        cout << dis_value(gen) << endl;
    }
    for (int i = 0; i < number_items; i++)
    {
        cout << dis_weight(gen) << endl;
    }
    cout << dis_weight(gen) << endl;

    return 0;
}
