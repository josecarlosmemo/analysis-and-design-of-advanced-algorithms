#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

bool debug = false;

using namespace std;

// Longest Proper Prefix Suffix Table
void computeLPSArray(string pattern, int m, int *lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
// KMP Algorithm
int KMP(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    int lps[m];
    int j = 0;
    int i = 0;
    computeLPSArray(pattern, m, lps);
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }
        if (j == m)
        {
            return i - j;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}
// Manacher's algorithm
void findLongestPalindromicString(string text)
{
    int n = text.length();
    if (n == 0)
        return;

    n = 2 * n + 1;
    int lps[n];
    computeLPSArray(text, n, lps);

    int center = 1, right = 2, i = 0;

    int mirror;
    int expand = -1, diff = -1;
    int max_length = 0, max_center = 0;
    int start = -1, end = -1;

    for (i = 2; i < n; i++)
    {
        mirror = 2 * center - i;
        expand = 0;
        diff = right - i;

        if (diff >= 0)
        {

            if (lps[mirror] < diff)
                lps[i] = lps[mirror];

            else if (lps[mirror] == diff && right == n - 1)
                lps[i] = lps[mirror];

            else if (lps[mirror] == diff && right < n - 1)
            {
                lps[i] = lps[mirror];

                expand = 1;
            }

            else if (lps[mirror] > diff)
            {
                lps[i] = diff;

                expand = 1;
            }
        }
        else
        {
            lps[i] = 0;

            expand = 1;
        }

        if (expand == 1)
        {

            while (((i + lps[i]) < n && (i - lps[i]) > 0) && (((i + lps[i] + 1) % 2 == 0) || (text[(i + lps[i] + 1) / 2] == text[(i - lps[i] - 1) / 2])))
            {
                lps[i]++;
            }
        }

        if (lps[i] > max_length)
        {
            max_length = lps[i];
            max_center = i;
        }

        if (i + lps[i] > right)
        {
            center = i;
            right = i + lps[i];
        }
    }

    start = (max_center - max_length) / 2;
    end = start + max_length - 1;

    cout << start << " " << end << endl;

    if (debug)
    {
        cout << "The longest palindrome is: " << text.substr(start, end - start + 1) << endl;
    }
}

void longest_common_substring(string str1, string str2)
{
    int m = str1.length();
    int n = str2.length();
    int result = 0;
    int endingIndex = m;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > result)
                {
                    result = dp[i][j];
                    endingIndex = i;
                }
            }
            else
                dp[i][j] = 0;
        }
    }
    cout << endingIndex - result << " " << endingIndex - 1 << endl;
    if (debug)
    {
        cout << "The longest common substring is: " << str1.substr(endingIndex - result, result) << endl;
    }
}

void part1(string transFile, string mcodeFile)
{

    // Reading file
    ifstream file_stream(transFile);
    string transmission;
    string mcode;

    // Save file content in a string
    if (file_stream.is_open())
    {
        string line;
        while (getline(file_stream, line))
        {
            transmission += line + "\n";
        }
        file_stream.close();
    }
    else
    {
        cout << "Unable to open file " << transFile << endl;
        return;
    }

    // Reading pattern from file
    file_stream.open(mcodeFile);
    if (file_stream.is_open())
    {
        string line;
        while (getline(file_stream, line))
        {
            mcode += line;
        }
        file_stream.close();
    }
    else
    {
        cout << "Unable to open file " << mcode << endl;
        return;
    }

    // KMP
    int index = KMP(transmission, mcode);
    if (index != -1)
    {
        cout << "true "
             << index << endl;
        if (debug)
        {
            cout
                << "The code found is: " << transmission.substr(index, mcode.length()) << endl
                << endl;
        }
    }
    else
    {
        cout << "false" << endl;
    }
}

void part2(string filename)
{
    // Reading file
    ifstream file_stream(filename);
    string text;

    // Save file content in a string
    if (file_stream.is_open())
    {
        string line;
        while (getline(file_stream, line))
        {
            text += line + "\n";
        }
        file_stream.close();
    }
    else
    {
        cout << "Unable to open file " << filename << endl;
        return;
    }

    // Manacher's algorithm
    findLongestPalindromicString(text);
}

void part3(string filename1, string filename2)
{
    // Reading file
    ifstream file_stream(filename1);
    string text1;

    // Save file content in a string
    if (file_stream.is_open())
    {
        string line;
        while (getline(file_stream, line))
        {
            text1 += line + "\n";
        }
        file_stream.close();
    }
    else
    {
        cout << "Unable to open file " << filename1 << endl;
        return;
    }

    // Reading file
    file_stream.open(filename2);
    string text2;

    // Save file content in a string
    if (file_stream.is_open())
    {
        string line;
        while (getline(file_stream, line))
        {
            text2 += line + "\n";
        }
        file_stream.close();
    }
    else
    {
        cout << "Unable to open file " << filename2 << endl;
        return;
    }

    // LCS
    longest_common_substring(text1, text2);
}

int main(int argc, char const *argv[])
{

    // Parsing arguments
    if (argc != 1)
    {
        debug = true;
    }

    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<string> transmissions = {"transmission1.txt", "transmission2.txt"};
    vector<string> mcode = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};

    if (debug)
    {
        cout << "Part 1" << endl;
        auto global_start = chrono::high_resolution_clock::now();
        auto part1_start = chrono::high_resolution_clock::now();
        for (auto t : transmissions)
        {
            if (debug)
            {
                cout << "Transmission: " << t << endl;
            }

            for (auto m : mcode)
            {
                part1(t, m);
            }
        }
        auto part1_end = chrono::high_resolution_clock::now();
        cout << "Part 1 took " << chrono::duration_cast<chrono::microseconds>(part1_end - part1_start).count() << " microseconds" << endl
             << endl;

        cout << "Part 2" << endl;
        auto part2_start = chrono::high_resolution_clock::now();

        for (auto t : transmissions)
        {
            part2(t);
        }
        auto part2_end = chrono::high_resolution_clock::now();
        cout << "Part 2 took " << chrono::duration_cast<chrono::microseconds>(part2_end - part2_start).count() << " microseconds" << endl
             << endl;

        cout << "Part 3" << endl;
        auto part3_start = chrono::high_resolution_clock::now();
        part3(transmissions[0], transmissions[1]);
        auto part3_end = chrono::high_resolution_clock::now();
        cout << "Part 3 took " << chrono::duration_cast<chrono::microseconds>(part3_end - part3_start).count() << " microseconds" << endl
             << endl;
        auto global_end = chrono::high_resolution_clock::now();
        auto global_duration = chrono::duration_cast<chrono::microseconds>(global_end - global_start);
        cout << "Time taken the program: " << global_duration.count() << " microseconds" << endl;
    }
    else
    {
        for (auto t : transmissions)
        {
            for (auto m : mcode)
            {
                part1(t, m);
            }
        }
        for (auto t : transmissions)
        {
            part2(t);
        }
        part3(transmissions[0], transmissions[1]);
    }

    return 0;
}
