#include <iostream>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

// Output Modes
enum Output
{
    minimal,
    ascii,
    mermaid,

};

// Setting default output mode
Output output = Output::ascii;

// Trie Implementation
struct Node
{
    map<char, int> next;

    bool end = false;
};
vector<Node> trie;
int current_node = 0;

int new_node()
{
    trie.push_back(Node());
    return current_node++;
}

void add(string &word)
{
    int curr = 0;
    for (int i = 0; i < word.size(); i++)
    {

        if (!trie[curr].next.count(word[i]))
        {
            trie[curr].next[word[i]] = new_node();
        }
        curr = trie[curr].next[word[i]];
    }
    trie[curr].end = true;
}

bool search(string &word)
{
    int curr = 0;
    if (output == Output::ascii)
    {
        cout << endl
             << "Searching for " << word << "..." << endl
             << endl;
        cout << "ROOT --> ";
    }

    if (output == Output::mermaid)
    {
        cout << "graph LR" << endl;
        cout << "ROOT --> ";
    }

    for (int i = 0; i < word.size(); i++)
    {
        if (!trie[curr].next.count(word[i]))
        {
            if (output == Output::ascii || output == Output::mermaid)
            {
                cout << "NULL" << endl;
            }

            return false;
        }
        if (output == Output::ascii)
            cout << word[i] << endl;

        if (output == Output::mermaid)
            cout << word[i] << i << "((" << word[i] << "))" << endl;

        curr = trie[curr].next[word[i]];
        if (output == Output::ascii)
            cout << word[i] << " --> ";
        if (output == Output::mermaid)
            cout << word[i] << i << "((" << word[i] << "))"
                 << " --> ";
    }
    if (output == Output::ascii || output == Output::mermaid)
    {

        cout << ((trie[curr].end) ? "END" : "NULL") << endl
             << endl;
    }

    return trie[curr].end;
}

void dfs(int currNodeIndex = 0, string word = "", int level = 0, bool flag = false)
{

    for (auto i : trie[currNodeIndex].next)
    {
        if (output == Output::mermaid)
        {

            if (currNodeIndex == 0)
            {

                cout << "ROOT --> " << i.first << 0 << "((" << i.first << "))" << endl;
                level = level + currNodeIndex + 1;
                flag = true;
                // cout << level << endl;
            }
            else if (flag)
            {
                cout << word[word.size() - 1] << 0 << "((" << word[word.size() - 1] << "))"
                     << " --> "
                     << i.first << (word.size()) * level << "((" << i.first << "))" << endl;
                flag = false;
            }

            else
            {
                cout << word[word.size() - 1] << (word.size() - 1) * level << "((" << word[word.size() - 1] << "))"
                     << " --> "
                     << i.first << (word.size()) * level << "((" << i.first << "))" << endl;
            }
        }

        if (output == Output::minimal)
        {
            cout << i.first << endl;
        }

        if (output == Output::ascii)
        {

            if (currNodeIndex == 0)
            {
                cout << "ROOT --> " << i.first << endl;
            }
            else
            {
                cout << word[word.size() - 1] << " --> " << i.first << endl;
            }
        }

        word.push_back(i.first);

        dfs(i.second, word, level, flag);
        word.pop_back();
    }
}

void printWordsOrdered(int currentNodeIndex = 0, string word = "")
{
    if (trie[currentNodeIndex].end)
    {
        cout << word << endl;
    }
    for (auto i : trie[currentNodeIndex].next)
    {
        word.push_back(i.first);
        printWordsOrdered(i.second, word);
        word.pop_back();
    }
}

int main(int argc, char const *argv[])
{
    // Set output mode from args
    if (argc > 1)
    {
        string arg = argv[1];
        if (arg == "minimal")
        {
            output = Output::minimal;
        }
        else if (arg == "ascii")
        {
            output = Output::ascii;
        }
        else if (arg == "mermaid")
        {
            output = Output::mermaid;
        }
    }

    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num_words;
    cin >> num_words;

    // trie.push_back(Node());
    new_node(); // Adding Root Node

    while (num_words--)
    {
        string word;
        cin >> word;
        add(word);
    }
    if (output == Output::ascii)
    {
        cout << "DFS Trie" << endl
             << endl;
    }

    if (output == Output::mermaid)
    {
        cout << "graph LR" << endl;
    }
    dfs();
    cout << endl
         << endl;
    if (output == Output::ascii)
    {
        cout << "DFS to Order Words" << endl
             << endl;
    }
    printWordsOrdered();

    cout << endl
         << endl;

    int num_querys;
    cin >> num_querys;
    while (num_querys--)
    {
        string word;
        cin >> word;

        if (output != Output::mermaid)
            cout << boolalpha << search(word) << endl;
        else
            search(word);
    }

    // dfs();
    // bfs();

    return 0;
}
