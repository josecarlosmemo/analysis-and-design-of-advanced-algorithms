#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void merge(vector<double> &left, vector<double> &right, vector<double> &vect)
{
    vector<double>::iterator v = vect.begin();
    vector<double>::iterator l = left.begin();
    vector<double>::iterator r = right.begin();
    while (v != vect.end())
    {
        while (l != left.end() && (r == right.end() || *l >= *r))
        {
            *v = *l;
            l++;
            v++;
        }
        while (r != right.end() && (l == left.end() || *r > *l))
        {
            *v = *r;
            r++;
            v++;
        }
    }
}

void mergeSort(vector<double> &vect)
{
    if (vect.size() > 1)
    {
        vector<double> left(vect.begin(), vect.begin() + vect.size() / 2);
        vector<double> right(vect.begin() + vect.size() / 2, vect.end());
        mergeSort(left);
        mergeSort(right);
        merge(left, right, vect);
    }
}

int main(int argc, char const *argv[])
{
    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<double> v(N);
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }
    auto start = chrono::high_resolution_clock::now();

    mergeSort(v);
    auto end = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
    {
        cout << v[i] << endl;
    }
    cout << "Time Taken (microseconds): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;

    return 0;
}
