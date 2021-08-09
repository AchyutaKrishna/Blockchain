#include<bits/stdc++.h>
#include "sha256.h"
#include "des.h"
using namespace std;

class Block
{
    public:
            string hash, prevHash;
            
   // private:
            string data;
            int nonce;
    //public:
            Block(){}
            Block(string data, string prevHash)
            {
                this->data = data;
                this->prevHash = prevHash;
                time_t now = time(0);
                this->nonce = -1;
                this->hash = calculateHash();
            }
			Block(string data, string prevHash, string hash, int nonce)
            {
                this->data = data;
                this->prevHash = prevHash;
                this->nonce = nonce;
                this->hash = hash;
            }
            string calculateHash()
            {
                string a,b,c,d,sha;
                sha = sha256(prevHash + to_string(nonce) + data);
                a = sha.substr(0,16);
                b = sha.substr(16,16);
                c = sha.substr(32,16);
                d = sha.substr(48,16);
                string hashval = computeDES(a) + computeDES(b) + computeDES(c) + computeDES(d);  
                return hashval; 
            }

            void mineBlock(int diff)
            {
                char test[diff+1];
                for(int i = 0; i < diff; i++)
                    test[i] = '0';

                test[diff] = '\0';
                string str = string(test);

                do
                {
                    nonce++;
                    hash = calculateHash();

                }while(hash.substr(0,diff) != str);
            }
            
};

vector<Block> blockchain;
