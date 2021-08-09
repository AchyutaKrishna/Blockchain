#include<bits/stdc++.h>
#include "sha256.h"
#include "des.h"
#include "user.h"
#include <iostream>
#include <fstream>

using namespace std;

bool isChainValid(vector<Block> blockchain, int diff)
{
    Block curr, prev;

    char test[diff+1];
    for(int i = 0; i < diff; i++)
        test[i] = '0';

    test[diff] = '\0';
    string str = string(test);
    
    for(int i = 1; i < blockchain.size(); i++)
    {
        curr = blockchain[i];
        prev = blockchain[i-1];

        string testhash = curr.calculateHash();

        if(curr.hash != testhash)
        {
            cout<<"Hash of current block does not match for block "<<i;
            return false;
        }

        if(prev.hash != curr.prevHash)
        {
            cout<<"Hash of previous block does not match for block "<<i;
            return false;
        }

        if(curr.hash.substr(0,diff) != str)
        {
            cout<<"Block "<<i<<" hasn't been mined";
            return false;
        }

    }

    return true;
}

void saveSession(vector<User> users){
	ofstream outFile;
  	outFile.open ("users.txt");
	for(auto user:users){
		outFile << user.username <<"\n";
		outFile << user.getPassword()<<"\n";
		outFile << user.num_coins <<"\n";
        outFile << user.transactions.size() << endl;
        for(auto t: user.transactions){
            outFile << t << endl;
        }
	}
	outFile.close();
}

void loadSession(vector<User> &users){
	string curLine;
	ifstream prevSession("users.txt");
	string username;
	int numCoins;
	int numTransactions;
	while (getline (prevSession, curLine)) {
  		//cout << curLine <<"\n";
		username = curLine;
		getline (prevSession, curLine);
		int pass = (atoi(curLine.c_str()));
		getline (prevSession, curLine);
		numCoins = (atoi(curLine.c_str()));
        getline (prevSession, curLine);
		numTransactions = (atoi(curLine.c_str()));
        vector<string> transactions;
        for(int i=0; i<numTransactions; i++){
            getline (prevSession, curLine);
            transactions.push_back(curLine);
        }
		User temp = User(username, pass, numCoins, transactions);
		users.push_back(temp);
	}
	prevSession.close();
}
void saveChain(vector<Block> blockchain){
	ofstream outFile;
  	outFile.open ("blockchain.txt");
	for(auto block:blockchain){
		outFile << block.hash <<"\n";
		outFile << block.prevHash<<"\n";
		outFile << block.data <<"\n";
		outFile << block.nonce <<"\n";
	}
	outFile.close();
}
void loadChain(vector<Block> &blockchain){
	string curLine;
	ifstream prevSession("blockchain.txt");
	string hash,prevHash,data;
	int nonce;
	while (getline (prevSession, curLine)) {
		hash = curLine;
		getline (prevSession, curLine);
		prevHash = curLine;
		getline (prevSession, curLine);
		data = curLine;
		getline (prevSession, curLine);
		int nonce = (atoi(curLine.c_str()));
		Block temp = Block(data, prevHash, hash, nonce);
		blockchain.push_back(temp);
	}
	prevSession.close();	
}

int32_t main()
{

	vector<User> users;

	//Comment these two lines to save into files
	loadSession(users);
	loadChain(blockchain);

	int diff = 2;
	if(blockchain.empty()){
    
        Block a("grape","zero");
        a.mineBlock(diff);
        blockchain.push_back(a);
        
        Block b("apple",blockchain[blockchain.size()-1].hash);
        b.mineBlock(diff);
        blockchain.push_back(b);

	}
    
    isChainValid(blockchain,diff);

	if(users.empty()){ //users.txt is empty
		User u = User("Arpan", 12345678);
		if(!u.addCoins(4, blockchain[blockchain.size()-1].hash, 12345678)){
			cout << "Could not add coins.\n";
		}
		if(!u.withdrawCoins(1, blockchain[blockchain.size()-1].hash, 12345678)){
			cout << "Could not withdraw coins.\n";
		}
		// u.viewUser(12345678);
		users.push_back(u);
		saveSession(users);
		saveChain(blockchain);
	}
	else {
		//for(auto user:users){
			//cout<<user.username<<" "<<user.getPassword()<<" "<<user.num_coins<<"\n";
		//}
		//for(auto block:blockchain){
			//cout<<block.hash<<" "<<block.prevHash<<" "<<block.data<<" "<<block.nonce<<"\n";
		//}
	}

    cout << "\n1. Create Account\n2. Add Coins\n3. Withdraw Coins\n4. Show details\n5. Exit\n";
    int choice;
    do {
        cout << "\nEnter choice: ";
        cin >> choice;
        switch(choice){
            case 1: {
                string username;
                int password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                User u(username, password);
                users.push_back(u);
                cout << "Account created"<<endl;
                break;
            }
            case 2: {
                string username;
                int password;
                int numCoins;
                cout << "Enter username: ";
                cin >> username;
                int flag = 0;
                User u1(username, 123);
                for(auto u: users){
                    if(u.username == username){
                        flag = 1;
                        u1 = u;
                        break;
                    }
                }
                if(flag == 0)   {
                    cout << "No such user exists. Exiting...\n";
                    break;
                }
                cout << "Enter number of coins: ";
                cin >> numCoins;
                cout << "Enter password: ";
                cin >> password;
                if(!u1.addCoins(numCoins, blockchain[blockchain.size()-1].hash, password)){
                    cout << "Could not add coins."<<endl;
                } else {
                    cout << "Successful"<<endl;
                    for(int i = 0; i < users.size(); i++){
                        if(users[i].username == username)
                            users[i] = u1;  
                }
                saveChain(blockchain);
                saveSession(users);
                break;
            }
        }
            case 3: {
                string username;
                int password;
                int numCoins;
                cout << "Enter username: ";
                cin >> username;
                int flag = 0;
                User u1(username, 123);
                for(auto u: users){
                    if(u.username == username){
                        flag = 1;
                        u1 = u;
                        break;
                    }
                }
                if(flag == 0)   {
                    cout << "No such user exists. Exiting...\n";
                    break;
                }
                cout << "Enter number of coins: ";
                cin >> numCoins;
                cout << "Enter password: ";
                cin >> password;
                if(!u1.withdrawCoins(numCoins, blockchain[blockchain.size()-1].hash, password)){
                    cout << "Could not withdraw coins."<<endl;
                } else {
                    cout << "Successful"<<endl;
                    for(int i = 0; i < users.size(); i++){
                        if(users[i].username == username)
                            users[i] = u1;
                    }

                }
                saveChain(blockchain);
                saveSession(users);
                break;
            }
            case 4: {
                string username;
                int password;
                cout << "Enter username: ";
                cin >> username;
                User u1(username, 123);
                int flag = 0;
                for(auto u: users){
                    if(u.username == username){
                        flag = 1;
                        u1 = u;
                        break;
                    }
                }
                if(flag == 0)   {
                    cout << "No such user exists. Exiting...\n";
                    break;
                }
                cout << "Enter password: ";
                cin >> password;
                if(!u1.viewUser(password)){
                    cout << "Wrong password.";
                }
                break;
            }
            case 5: break;
            default: 
                cout << "Wrong choice...\n";
                break;
        } 
    } while(choice!=5);

	saveChain(blockchain);
    saveSession(users);

    return 0;
}
