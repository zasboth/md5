#include "md5.hh"
#include <cmath>
#include <stdlib.h>
#include <format>
#include <sstream>
#include <iostream>
#include <intrin.h>
#include <iomanip>

#define INT_BITS 32

Md5::Md5()
{
    double pwr = pow(2,32);
    for (size_t i = 0; i < 64; i++)
    {
        this->k[i] = unsigned(floor( fabs( sin(i + 1)) * pwr));
    }
}

Md5::~Md5()
{
}

int leftRotate(unsigned v, unsigned amt)
{ 
    //return (n << d)|(n >> (INT_BITS - d));
    unsigned  msk1 = (1<<amt) -1;
    return ((v>>(32-amt)) & msk1) | ((v<<amt) & ~msk1);
}

string Md5::encrypt(const string &text)
{
    vector<Chunk> chunks = fill_chunks(text);
    word_union res[4] = {0,0,0,0};
    for (size_t di = 0; di < chunks.size(); di++)
    {     
        unsigned h0 = 0x67452301;
        unsigned h1 = 0xEFCDAB89;
        unsigned h2 = 0x98BADCFE;
        unsigned h3 = 0x10325476;
        unsigned a = h0;
        unsigned b = h1;
        unsigned c = h2;
        unsigned d = h3;
        unsigned f = 0;
        unsigned g = 0;
        for (size_t i = 0; i < 64; i++)
        {
            if (i < 16) 
            {
                f = (b & c) | (~b & d);
                g = i;
            }
            else if (i < 32)
            {
                f = (d & b) | (~d & c);
                g = (5*i + 1) % 16;
            }
            else if (i < 48)
            {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            }
            else 
            {
                f = c ^ (b | ~d);
                g = (7*i) % 16;
            }
    
            unsigned temp = leftRotate(a + f + k[i] + chunks[di][g].w, R[i]) + b;
            a = d;
            d = c;
            c = b;
            b = temp;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;

        //__uint128_t r = 
        res[0].w += h0;
        res[1].w += h1;
        res[2].w += h2;
        res[3].w += h3;
    }
    
    std::stringstream ss;
    for (const word_union& ri : res)
    {
        for (size_t i = 0; i < 4; i++)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << (0xff & (unsigned char)ri.b[i]);
        }
    }
    return ss.str();
}

vector<Chunk> Md5::fill_chunks(const string &mess)
{
    vector<Chunk> chunks;
    size_t counter = 0;
    string message = mess + char(0x80);
    while (counter < message.length())
    {
        Chunk chunk;
        for (size_t i = 0; i < 16; i++)
        {
            word_union wu = {0};
            size_t j = 0;
            for (; j < 4 && counter < message.length(); j++)
            {
                 wu.b[j] = message[counter++];
            }
            if (i == 14 && counter >= message.length()) {
                wu.w = 8*(message.length()-1);
            }
            chunk[i] = wu;
            //::cout << wu.w << " " << i << std::endl;
            /*for (size_t ki = 0; ki < 4; ki++)
            {
                cout << int(wu.b[ki]) << " ";
            }*/
            
        }
        chunks.push_back(chunk);
    }    
    return chunks;
}

Chunk::~Chunk()
{
}

Chunk::Chunk()
{ 
}

word_union &Chunk::operator[](int index)
{
    return chunk_data[index];
}
