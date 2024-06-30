#pragma once

#include <string>
#include <bitset>
#include <vector>

using namespace std;

union word_union
{
    unsigned w;
    unsigned char b[4];
};


class Chunk
{
public:
    Chunk();
    ~Chunk();

    word_union &operator[](int index);
private:
    word_union chunk_data[16];
};

class Md5
{
private:
    const int R[64] = 
        {
            7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
            5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
            4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
            6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
        };

public:
    Md5();
    ~Md5();

    string encrypt(const string &text);

private:
    vector<Chunk> fill_chunks(const string &message);

    unsigned k[64];
};

