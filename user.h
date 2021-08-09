#include<bits/stdc++.h>
#include "block.h"
#define int long long
using namespace std;

random_device rd;     
const int p = 1e9+7;
const int g = 2;
int b;

int modularExponentiation(int a, int b, int mod){
    if(b==0)    return 1;
    int t = modularExponentiation(a, b/2, mod);
    int c = (t%mod * t%mod) % mod;
    if(b%2==0)  return c;
    return (c%mod * a%mod) % mod;
}

int randomBit () {
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0,1); 
    int b = uni(rng);
    return b;
}

bool verifyTransaction (int s, int h, int y) {
    int lhs = modularExponentiation(g, s, p);
    int rhs = modularExponentiation(y, b, p);
    rhs = (h%p * rhs) % p;
    return (lhs==rhs);
}


class User {
    private:
        int password;
        bool hasZKP(){
            mt19937 rng(rd());
            uniform_int_distribution<int> uni(0, p-2); 
            for(int i=0; i<100; i++){
                int r = uni(rng);
                int x = this->password;
                int h = modularExponentiation(g, r, p);
                int y = modularExponentiation(g, x, p);
                b = randomBit();
                int s = (r+b*x) % (p-1);
                if(!verifyTransaction(s, h, y)) return false;
            }
            return true;
        }
    public:
        string username;
        int num_coins;
		vector<string> transactions;
        User(string username, int password){
            this->username = username;
            this->password = password;
            this->num_coins = 0;
        }
        User(string username, int password, vector<string> transactions){
            this->username = username;
            this->password = password;
            this->num_coins = 0;
            for(auto t: transactions){
                this->transactions.push_back(t);
            }
        }
        User(string username, int password, int coins, vector<string> transactions){
            this->username = username;
            this->password = password;
            this->num_coins = coins;
            for(auto t: transactions){
                this->transactions.push_back(t);
            }
        }
        bool addCoins(int n, string prevHash, int pass) {
            if(pass!=this->password){
                cout << "Wrong password!\n";
                return false;
            }
            if(hasZKP()){
                this->num_coins += n;
                string tr = "Added " + to_string(n) + " coins.";
                this->transactions.push_back(tr);
                Block b(this->username + " " + tr, prevHash);
                b.mineBlock(2);
                blockchain.push_back(b);
                return true;
            } else {
                return false;
            }
        }
		int getPassword(){
			return this->password;
		}
        bool withdrawCoins(int n, string prevHash, int pass) {
            if(pass!=this->password){
                cout << "Wrong password!\n";
                return false;
            }
            if(n > this->num_coins){
                cout << "Not enough balance.\n";
                return false;
            }
            if(hasZKP()){
                this->num_coins -= n;
                string tr = "Withdrew " + to_string(n) + " coins.";
                this->transactions.push_back(tr);
                Block b(this->username + " " + tr, prevHash);
                b.mineBlock(2);
                blockchain.push_back(b);
                return true;
            } else {
                return false;
            }
        }

        bool viewUser(int pass) {
            if(this->password != pass){
                cout << "Wrong password!\n";
                return false;
            }
            cout << "Username: " << this->username << endl;
            cout << "Number of coins: " << this->num_coins << endl;
            cout << "Transactions: \n";
            for(string t: transactions){
                cout<<t<<endl;
            }
            return true;
        }
};
