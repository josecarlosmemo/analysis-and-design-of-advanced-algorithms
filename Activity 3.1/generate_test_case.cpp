#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <random>

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

string gen_word(size_t length)
{
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
    // Parsing args
    if (argc != 7)
    {
        cout << "Usage: " << argv[0] << " <output_file> <num_words_min> <num_words_max> <word_length_min> <word_length_max> <num_querys>" << endl;
        return 1;
    }

    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string output_file = argv[1];
    int num_words_min = atoi(argv[2]);
    int num_words_max = atoi(argv[3]);
    int word_length_min = atoi(argv[4]);
    int word_length_max = atoi(argv[5]);
    int num_querys = atoi(argv[6]);

    // Get random number of words
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dist_num_words(num_words_min, num_words_max);
    uniform_int_distribution<> dist_word_length(word_length_min, word_length_max);

    int num_words = dist_num_words(generator);

    vector<string> words(num_words);

    // Generate words
    for (int i = 0; i < num_words; i++)
    {
        int word_length = dist_word_length(generator);
        words[i] = gen_word(word_length);
    }

    ofstream output(output_file);

    output << num_words << endl;

    for (int i = 0; i < num_words; i++)
    {
        output << words[i] << endl;
    }

    output << num_querys << endl;

    for (int i = 0; i < num_querys; i++)
    {
        // Generate random number between 0 and 10
        random_device rd2;
        mt19937 generator2(rd2());
        uniform_int_distribution<> dist2(0, 10);
        int num_words_query = dist2(generator2);

        if (num_words_query <= 2)
        {
            // Add random word to output
            output << gen_word(dist_word_length(generator)) << endl;
        }
        else
        {
            output << *select_randomly(words.begin(), words.end()) << endl;
        }
    }

    return 0;
}
