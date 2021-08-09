#include <bits/stdc++.h>
#include "des.h"
using namespace std;

string round_keys[17], l[17], r[17];

void generateRoundKeys(string k)
{
	// The PC1 table 
	int pc1[56] = {
	  57, 49, 41, 33, 25, 17, 9,
	   1, 58, 50, 42, 34, 26, 18,
	  10, 2, 59, 51, 43, 35, 27,
	  19, 11, 3, 60, 52, 44, 36,
	  63, 55, 47, 39, 31, 23, 15,
	   7, 62, 54, 46, 38, 30, 22,
	  14, 6, 61, 53, 45, 37, 29,
	  21, 13, 5, 28, 20, 12, 4 };

	// The PC2 table
	int pc2[48] = { 
	  14, 17, 11, 24, 1, 5,
	   3, 28, 15, 6, 21, 10,
	  23, 19, 12, 4, 26, 8,
	  16, 7, 27, 20, 13, 2,
	  41, 52, 31, 37, 47, 55,
	  30, 40, 51, 45, 33, 48,
	  44, 49, 39, 56, 34, 53,
	  46, 42, 50, 36, 29, 32 };


	int left_shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};  // left shifts

	string k_plus;

	for(int i = 0; i < 56; i++)
		k_plus = k_plus + k[pc1[i]-1];


	string c[17], d[17];

	c[0] = k_plus.substr(0, 28);
	d[0] = k_plus.substr(28, 28);

    for(int i = 1; i <= 16; i++)
    {
       if(left_shifts[i-1] == 1)
       {
       	  string tmp = "";
       	  char first = c[i-1][0];
       	  tmp = c[i-1].substr(1, 27);
 		  tmp += first;
 		  c[i] = tmp;
          
          tmp = "";
          first = d[i-1][0];
       	  tmp = d[i-1].substr(1, 27);
 		  tmp += first;
          d[i] = tmp; 
 		  //cout<<"A";

       }

       else if(left_shifts[i-1] == 2)
       {
       		char first = c[i-1][0];
       		char second = c[i-1][1];
       		string tmp ="";
            tmp = c[i-1].substr(2, 26);
            tmp += first;
            tmp += second;  
            c[i] = tmp;

            first = d[i-1][0];
       		second = d[i-1][1];
       		tmp = "";
       		tmp = d[i-1].substr(2, 26);
            tmp += first;
            tmp += second;
            d[i] = tmp;
       }
    }
    

    string concat[17];
    concat[0] = "";
    
    for(int i = 1; i <= 16; i++)
    	concat[i] = c[i] + d[i];

    round_keys[0] = "";

    for(int i = 1; i <= 16; i++)
    {
    	string tmp = "";
    	for(int j = 0; j < 48; j++)
    	{
         	tmp += concat[i][pc2[j]-1];
         	
    	}
    	round_keys[i] = tmp;  
        //cout<<tmp.length()<<" ";
    }
 
    
}

string ip(string pt)
{
	int ip[64] = {58, 50, 42, 34, 26, 18, 10, 2,
				  60, 52, 44, 36, 28, 20, 12, 4,
				  62, 54, 46, 38, 30, 22, 14, 6,
				  64, 56, 48, 40, 32, 24, 16, 8,
				  57, 49, 41, 33, 25, 17, 9, 1,
				  59, 51, 43, 35, 27, 19, 11, 3,
				  61, 53, 45, 37, 29, 21, 13, 5,
				  63, 55, 47, 39, 31, 23, 15, 7 };

	string ipt = "";

	for(int i = 0; i < 64; i++)
	{
		ipt += pt[ip[i]-1];
	}
    
    return ipt;
}

string xorf(string a, string b)
{
	int n = a.length();
	string c = "";
	for(int i = 0; i < n; i++)
	{
		if(a[i] == b[i])
			c += '0';
		else
			c += '1';
	}

	return c;
}

int getIntFromString(string s)
{
	map<string, int> m;
	m["00"] = 0;
	m["01"] = 1;
	m["10"] = 2;
	m["11"] = 3;
	m["0000"] = 0;
	m["0001"] = 1;
	m["0010"] = 2;
	m["0011"] = 3;
	m["0100"] = 4;
	m["0101"] = 5;
	m["0110"] = 6;
	m["0111"] = 7;
	m["1000"] = 8;
	m["1001"] = 9;
	m["1010"] = 10;
	m["1011"] = 11;
	m["1100"] = 12;
	m["1101"] = 13;
	m["1110"] = 14;
	m["1111"] = 15;
	return m[s];
 }

 string getStringFromInt(int n)
 { 
 	map<int, string> m;
 	m[0] = "0000";
 	m[1] = "0001";
 	m[2] = "0010";
 	m[3] = "0011";
 	m[4] = "0100";
 	m[5] = "0101";
 	m[6] = "0110";
 	m[7] = "0111";
 	m[8] = "1000";
 	m[9] = "1001";
 	m[10] = "1010";
 	m[11] = "1011";
 	m[12] = "1100";
 	m[13] = "1101";
 	m[14] = "1110";
 	m[15] = "1111";
 	return m[n];
 }

string f(string r, string key)
{
	int E[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
	   6, 7, 8, 9, 8, 9, 10, 11,
	  12, 13, 12, 13, 14, 15, 16, 17,
	  16, 17, 18, 19, 20, 21, 20, 21,
	  22, 23, 24, 25, 24, 25, 26, 27,
	  28, 29, 28, 29, 30, 31, 32, 1 };

	string t1 = "", t2 = "", t3 = "";
	
	for(int i = 0; i < 48; i++)
	{
		t1 += r[E[i]-1];
	}  

	t2 = xorf(key, t1);
    
	string txt = "";
    
    int s[8][4][16] = 
    { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
       0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
      4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},  
   
   { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
      0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
     13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
  
   { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
     13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
     13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
       1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                     
   { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
     3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
 
   { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
     4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
 
   { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
     10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
      9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
      4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                        
   
  { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
   13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
 
 { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };


  for(int i = 0; i < 8; i++)
  {
  		string tmp = t2.substr(6*i, 6);
        string p = "", q = "";
        p += tmp[0];
        p += tmp[5];
        int j = getIntFromString(p);
        q = tmp.substr(1,4);
        int k = getIntFromString(q);
        int l = s[i][j][k];
        string w = getStringFromInt(l); 
        txt += w; 
         

  }


  string f = "";

  int p[32] = { 16, 7, 20, 21,
			    29, 12, 28, 17,
			     1, 15, 23, 26,
			     5, 18, 31, 10,
			     2, 8, 24, 14,
			    32, 27, 3, 9,
			    19, 13, 30, 6,
			    22, 11, 4, 25 };

  for(int i = 0; i < 32; i++)
  {
  	 f += txt[p[i]-1];
  }

  return f;

}

void round(int n)
{
   l[n] = r[n-1];
   r[n] = xorf(l[n-1], f(r[n-1],round_keys[n]));
}

string ipinv(string s)
{
	string final = "";
	int ipi[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
	  39, 7, 47, 15, 55, 23, 63, 31,
	  38, 6, 46, 14, 54, 22, 62, 30,
	  37, 5, 45, 13, 53, 21, 61, 29,
	  36, 4, 44, 12, 52, 20, 60, 28,
	  35, 3, 43, 11, 51, 19, 59, 27,
	  34, 2, 42, 10, 50, 18, 58, 26,
	  33, 1, 41, 9, 49, 17, 57, 25 };

   for(int i = 0; i < 64; i++)
   {
   		final += s[ipi[i]-1];
   }

   return final;
}
string hex_char_to_bin(char c)
{
  
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
	default : return "0000";	   
    }
}
string hex_to_bin (string a)
{
  string b = "";
  for(int i=0;i<a.size();i++)
  {
    b += hex_char_to_bin(a[i]);
  }
  return b;
}
string computeDES(string pt)
{ 
   pt = hex_to_bin(pt);
   string key = "133457799BBCDFF1";
   string k = "0001001100110100010101110111100110011011101111001101111111110001";

   generateRoundKeys(k); 

   string ipt;
   ipt = ip(pt);

   l[0] = ipt.substr(0, 32);
   r[0] = ipt.substr(32,32);

   for(int i = 1; i <= 16; i++)
   	 round(i);

   string ans = "";
   ans += r[16];
   ans += l[16];

   string final = ipinv(ans);	

   return final;
}
