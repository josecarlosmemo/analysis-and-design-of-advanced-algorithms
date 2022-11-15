#include <iostream>
#include <vector>
#include <random>

using namespace std;

int getRandomNumber(int lower_bound, int upper_bound)
{
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(lower_bound, upper_bound);
    return dist(generator);
}

int randomizedBinarySearch(vector<int> &arr, int left, int right, int x)
{
    if (right >= left)
    {
        int mid = getRandomNumber(left, right);

        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return randomizedBinarySearch(arr, left, mid - 1, x);
        return randomizedBinarySearch(arr, mid + 1, right, x);
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    string line;

    cout << "Input: " << endl;

    getline(cin, line);

    int n = stoi(line);
    vector<int> numbers;

    getline(cin, line);

    int i = 0;
    while (i < line.size())
    {
        int j = i;
        while (j < line.size() && line[j] != ',')
        {
            j++;
        }
        string number = line.substr(i, j - i);
        numbers.push_back(stoi(number));
        i = j + 1;
    }

    for (int i = 0; i < numbers.size() - 1; i++)
    {
        if (numbers[i] > numbers[i + 1])
        {
            cout << "The array is not sorted" << endl;
            return 1;
        }
    }

    int result = randomizedBinarySearch(numbers, 0, numbers.size() - 1, n);

    if (result == -1)
    {
        cout << "Output: " << endl;
        cout << "The element is not present in the array" << endl;
    }
    else
    {
        cout << "Output: " << endl;
        cout << "The element is present in the index: " << result << endl;
    }

    return 0;
}
