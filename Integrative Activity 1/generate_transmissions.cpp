#include <iostream>
#include <fstream>
#include <random>
#include <iterator>
#include <algorithm>

using namespace std;

// Select random Item from a vector
// Reference: https://stackoverflow.com/a/16421677
template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator &g)
{
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template <typename Iter>
Iter select_randomly(Iter start, Iter end)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

string gen_transmission(size_t length)
{
    const string chars = "abcdefABCDEF0123456789\n ";
    string result;

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dist(0, chars.size() - 1);

    for (size_t i = 0; i < length; i++)
        result += chars[dist(generator)];

    return result;
}

string gen_code(size_t length)
{
    const string chars = "0123456789abcdefABCDEF";
    string result;

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dist(0, chars.size() - 1);

    for (size_t i = 0; i < length; i++)
        result += chars[dist(generator)];

    return result;
}

int main(int argc, char const *argv[])
{

    vector<string> codes_files = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};
    vector<string> transmissions_files = {"transmission1.txt", "transmission2.txt"};
    vector<string> codes;

    // Parsing arguments
    if (argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " <code_length_min> <code_length_max> <transmission_length_min> <transmission_length_max>"
             << endl;
        return 1;
    }

    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int code_length_min = atoi(argv[1]);
    int code_length_max = atoi(argv[2]);

    cout << "--- Generating codes ---" << endl;
    cout << endl;

    for (auto code_file : codes_files)
    {
        cout << "Generating code " << code_file << endl;
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> dist(code_length_min, code_length_max);
        int code_length = dist(generator);
        string code = gen_code(code_length);
        codes.push_back(code);
        ofstream out(code_file);
        out << code;
        out.close();
        cout << "Generated code of length " << code_length << " and saved to " << code_file << endl;
        cout << "Code: " << code << endl;
        cout << endl;
    }

    int transmission_length_min = atoi(argv[3]);
    int transmission_length_max = atoi(argv[4]);

    cout << endl;
    cout << "--- Generating transmissions ---" << endl;
    cout << endl;

    for (auto transmission_file : transmissions_files)
    {
        cout << "Generating transmission " << transmission_file << endl;
        // Generate transmission of random length
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> dist(transmission_length_min, transmission_length_max);
        int transmission_length = dist(generator);
        string transmission = gen_transmission(transmission_length);

        // Generate random number between 0 and 3
        random_device rd2;
        mt19937 generator2(rd2());
        uniform_int_distribution<> dist2(0, 3);
        int num_codes = dist2(generator2);

        vector<int> code_indexes;
        vector<string> codes_inserted;

        vector<string> codes_copy = codes;

        // Insert random number of codes into transmission
        for (int i = 0; i < num_codes; i++)
        {
            // Get random position to insert code
            random_device rd;
            mt19937 generator(rd());
            uniform_int_distribution<> dist(0, transmission.size() - 1);
            bool inserted = false;
            int pos;
            while (!inserted)
            {
                pos = dist(generator);
                inserted = true;
                for (int i = 0; i < code_indexes.size(); i++)
                {

                    if (pos >= code_indexes[i] && pos <= code_indexes[i] + codes[i].size())
                    {
                        inserted = false;
                        break;
                    }
                }
            }

            string code = *select_randomly(codes_copy.begin(), codes_copy.end());
            codes_copy.erase(remove(codes_copy.begin(), codes_copy.end(), code), codes_copy.end());

            for (int &code_index : code_indexes)
            {
                if (pos <= code_index)
                {
                    code_index += code.size();
                }
            }

            code_indexes.push_back(pos);
            codes_inserted.push_back(code);

            transmission.insert(pos, code);
        }

        for (int i = 0; i < codes_inserted.size(); i++)

        {
            cout << "Inserted code of length " << codes_inserted[i].size() << " at position " << code_indexes[i] << endl;
            cout << "Inserted code: " << codes_inserted[i] << endl;
            cout << endl;
        }

        // Save transmission to file
        ofstream out(transmission_file);
        out << transmission;
        out.close();

        cout << "Generated transmission of length " << transmission.size() << " with " << num_codes << " codes and saved to " << transmission_file << endl;
        cout << endl;
    }

    return 0;
}
