---
title: Activity 3.1
papersize: letter
fontsize: "12pt"
date: \today
author:
  - "José Carlos Martínez Núñez"
  - "Tania Sayuri Guizado Hernández"
bibliography: []
toc: true
titlepage: true
lang: en
---

## Problem Description

- Write a C++ program that implements a TRIE data structure.
- Write also a program that allows to verify its functionality.

The input to the program is a number $N$, followed by $N$ words, which will be inserted into the structure. Then read a number $M$ followed by $M$ words to be searched in the structure.

The output of the program is the DFS path of the TRIE, followed by $M$ booleans corresponding to the result of searching each of the $M$ words in the structure.

## Algorithm Implementation

For this activity, we implemented a TRIE data structure, which is a tree data structure that stores strings. Each node in the TRIE has a maximum of 26 children, one for each letter of the alphabet. The root node is the empty string. Each node in the TRIE has a boolean value that indicates whether the path from the root to that node is a word in the TRIE.

Rather than using pointers, to represent the connections between nodes, we used a vector of `Node` objects, where each `Node` object has a map of `<char, int>` pairs, where the key is the character of the edge and the value is the index of the node in the vector. This way, we can represent the connections between nodes without using pointers. This isn't the traditional way of implementing a TRIE, but it is used greatly in competitive programming, where dealing with pointers can be a problem.

These are the functions that we implemented:

```cpp
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
```

This function creates a new node and returns its index in the vector.

```cpp
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
```

This function adds a word to the TRIE. It starts at the root node, and then it iterates through the characters of the word. If the current node doesn't have a child with the current character, it creates a new node and adds it to the current node's children. Then, it moves to the child node with the current character. When it reaches the last character of the word, it sets the `end` boolean of the current node to `true`. Inserting a word into the TRIE takes $O(|word|)$ time.

```cpp
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
```

This function searches for a word in the TRIE. It starts at the root node, and then it iterates through the characters of the word. If the current node doesn't have a child with the current character, it returns `false`. If it does, it moves to the child node with the current character. When it reaches the last character of the word, it returns the value of the `end` boolean of the current node. Searching for a word in the TRIE takes $O(|word|)$ time.

```cpp
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
```

This function traverses the TRIE in a depth-first search manner. It starts at the root node, and then it iterates through the children of the current node. For each child, it calls the function recursively, passing the index of the child node. It prints the character of the edge between the current node and the child node, and then it moves to the child node. Traversing the TRIE takes $O(|trie|)$ time.

```cpp
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
```

This function prints all the words in the TRIE in alphabetical order (using DFS traversal). It starts at the root node, and then it iterates through the children of the current node. For each child, it calls the function recursively, passing the index of the child node. It prints the character of the edge between the current node and the child node, and then it moves to the child node. If the current node is the end of a word, it prints the word. Traversing the TRIE takes $O(|trie|)$ time.

## Different Output Formats

The program can output the TRIE in three different formats:

- ASCII
- Minimal
- Mermaid

The ASCII format is the default output format. It prints the TRIE in a tree-like format, with each node on a new line, and each edge represented by a `-->` symbol.

The Minimal format prints the TRIE in a minimal format, with each node on a new line, and each edge represented by a single character. For the queries it only prints the result of the query.

The Mermaid format prints the TRIE in a Mermaid format, which can be used to generate a graph of the TRIE.

In order to change the output format, you can add one of the following arguments to the `main.cpp` file:

- `ascii` for ASCII
- `minimal` for Minimal
- `mermaid` for Mermaid

## Program Generates Test Cases

We also created a separate program that generates test cases for the TRIE (`generate_test_case.cpp`) . It generates a random number of words, and then it generates a random number of queries. It then saves the words and queries in a file, which can be used as input for the TRIE program.

The usage of the program is as follows:

```bash
./generate_test_case <output_file> <num_words_min> <num_words_max> <word_length_min> <word_length_max> <num_querys>
```

## Test Cases

For this project, we will use the following test cases:

```mermaid
graph LR
ROOT --> c0((c))
  c0((c)) --> a1((a))
  a1((a)) --> m2((m))
  m2((m)) --> p3((p))
  a1((a)) --> s2((s))
  s2((s)) --> a3((a))
  s2((s)) --> o3((o))
  ROOT --> i0((i))
  i0((i)) --> c2((c))
  c2((c)) --> p4((p))
  p4((p)) --> c6((c))
```

`test1.txt`: 4 words inserted in the structure. 4 of the 6 words searched are valid in the structure.

```mermaid
graph LR
ROOT --> A0((A))
A0((A)) --> X1((X))
X1((X)) --> G2((G))
G2((G)) --> h3((h))
h3((h)) --> S4((S))
S4((S)) --> W5((W))
W5((W)) --> R6((R))
ROOT --> H0((H))
H0((H)) --> M2((M))
M2((M)) --> R4((R))
R4((R)) --> w6((w))
w6((w)) --> y8((y))
y8((y)) --> Q10((Q))
Q10((Q)) --> W12((W))
ROOT --> J0((J))
J0((J)) --> n3((n))
n3((n)) --> c6((c))
c6((c)) --> B9((B))
B9((B)) --> Z12((Z))
Z12((Z)) --> w15((w))
ROOT --> L0((L))
L0((L)) --> Z4((Z))
Z4((Z)) --> J8((J))
J8((J)) --> J12((J))
J12((J)) --> K16((K))
ROOT --> R0((R))
R0((R)) --> G5((G))
G5((G)) --> r10((r))
r10((r)) --> O15((O))
O15((O)) --> X20((X))
X20((X)) --> v25((v))
v25((v)) --> V30((V))
R0((R)) --> x5((x))
x5((x)) --> V10((V))
V10((V)) --> C15((C))
C15((C)) --> e20((e))
e20((e)) --> P25((P))
P25((P)) --> D30((D))
ROOT --> T0((T))
T0((T)) --> b6((b))
b6((b)) --> s12((s))
s12((s)) --> z18((z))
z18((z)) --> u24((u))
u24((u)) --> n30((n))
ROOT --> d0((d))
d0((d)) --> E7((E))
E7((E)) --> U14((U))
U14((U)) --> t21((t))
t21((t)) --> I28((I))
ROOT --> h0((h))
h0((h)) --> j8((j))
j8((j)) --> J16((J))
J16((J)) --> n24((n))
n24((n)) --> O32((O))
O32((O)) --> J40((J))
J40((J)) --> p48((p))
ROOT --> i0((i))
i0((i)) --> i9((i))
i9((i)) --> M18((M))
M18((M)) --> f27((f))
f27((f)) --> n36((n))
ROOT --> m0((m))
m0((m)) --> z10((z))
z10((z)) --> x20((x))
x20((x)) --> y30((y))
y30((y)) --> i40((i))
i40((i)) --> a50((a))
a50((a)) --> P60((P))
ROOT --> n0((n))
n0((n)) --> K11((K))
K11((K)) --> i22((i))
i22((i)) --> h33((h))
h33((h)) --> T44((T))
T44((T)) --> v55((v))
ROOT --> q0((q))
q0((q)) --> h12((h))
h12((h)) --> X24((X))
X24((X)) --> J36((J))
J36((J)) --> Q48((Q))
Q48((Q)) --> u60((u))
ROOT --> r0((r))
r0((r)) --> S13((S))
S13((S)) --> G26((G))
G26((G)) --> L39((L))
L39((L)) --> g52((g))
g52((g)) --> Q65((Q))
ROOT --> v0((v))
v0((v)) --> Q14((Q))
Q14((Q)) --> m28((m))
m28((m)) --> P42((P))
P42((P)) --> H56((H))
ROOT --> y0((y))
y0((y)) --> I15((I))
I15((I)) --> C30((C))
C30((C)) --> l45((l))
l45((l)) --> F60((F))
F60((F)) --> M75((M))

```

`test2.txt`: 16 words generated randomly inserted in the structure. 1 word searched twice. 3 of the 6 words searched are valid in the structure.

```mermaid
graph LR
ROOT --> G0((G))
G0((G)) --> N1((N))
N1((N)) --> D2((D))
D2((D)) --> n3((n))
n3((n)) --> f4((f))
f4((f)) --> R5((R))
ROOT --> O0((O))
O0((O)) --> m2((m))
m2((m)) --> T4((T))
T4((T)) --> N6((N))
N6((N)) --> Q8((Q))
ROOT --> V0((V))
V0((V)) --> f3((f))
f3((f)) --> E6((E))
E6((E)) --> H9((H))
H9((H)) --> X12((X))
X12((X)) --> N15((N))
N15((N)) --> j18((j))
ROOT --> b0((b))
b0((b)) --> W4((W))
W4((W)) --> D8((D))
D8((D)) --> x12((x))
x12((x)) --> N16((N))
b0((b)) --> j4((j))
j4((j)) --> z8((z))
z8((z)) --> n12((n))
n12((n)) --> s16((s))
s16((s)) --> G20((G))
ROOT --> o0((o))
o0((o)) --> F5((F))
F5((F)) --> L10((L))
L10((L)) --> e15((e))
e15((e)) --> L20((L))
ROOT --> y0((y))
y0((y)) --> L6((L))
L6((L)) --> z12((z))
z12((z)) --> P18((P))
P18((P)) --> G24((G))
G24((G)) --> t30((t))
ROOT --> z0((z))
z0((z)) --> F7((F))
F7((F)) --> M14((M))
M14((M)) --> c21((c))
c21((c)) --> A28((A))
A28((A)) --> e35((e))
```

`test3.txt`: 8 words generated randomly inserted in the structure. 1 word searched twice. 3 of the 6 words searched are valid in the structure.

```mermaid
graph LR
ROOT --> a0((a))
a0((a)) --> b1((b))
b1((b)) --> e2((e))
e2((e)) --> j3((j))
j3((j)) --> a4((a))
a0((a)) --> n1((n))
n1((n)) --> a2((a))
a2((a)) --> l3((l))
l3((l)) --> y4((y))
y4((y)) --> z5((z))
z5((z)) --> e6((e))
e6((e)) --> d7((d))
n1((n)) --> c2((c))
c2((c)) --> h3((h))
h3((h)) --> o4((o))
o4((o)) --> a5((a))
n1((n)) --> d2((d))
n1((n)) --> v2((v))
v2((v)) --> i3((i))
i3((i)) --> l4((l))
ROOT --> t0((t))
t0((t)) --> o2((o))
o2((o)) --> f4((f))
f4((f)) --> u6((u))
o2((o)) --> p4((p))
t0((t)) --> u2((u))
u2((u)) --> n4((n))
n4((n)) --> a6((a))
```

`test4.txt`: 8 words that start with the prefixes "an", "to" and "tu" inserted in the structure. 2 of the 6 words searched are valid in the structure.

**Note:** The `test2.txt` and `test3.txt` we generated using the above-mentioned program. To view the whole results, please check the `results` folder.

## Hardware

For this activity we used a MacBook Pro (13-inch, 2018, Four Thunderbolt 3 Ports) with the following specs:

- **Processor:** 2.3 GHz Quad-Core Intel Core i5
- **Memory:** 8 GB 2133 MHz LPDDR3
- **Graphics:** Intel Iris Plus Graphics 655 1536 MB
