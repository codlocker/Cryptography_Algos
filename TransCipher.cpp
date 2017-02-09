//
// Created by shuttle3468 on 4/2/17.
//
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define pb push_back
string fillBlanks(string s, ull l) {
    if(s.size() < l) {
        while(s.size() != l) {
            s += "!";
        }
    }
    return s;
}
int main() {
    cout << "IMPLEMENTATION OF TRANSPOSITION CIPHER USING COLUMNAR TRANPOSITION" <<endl;
    string key, str;
    vector<string> message;
    vector<string> enc_message;
    ull i,j,len,key_len, order_size;
    cin >> key;
    key_len = key.size();
    string  temp_key = key;
    getline(cin,str);
    while(getline(cin, str)){
        if(str.empty()){break;}
        message.pb(str);
    }
    double time_taken = clock();

    len = message.size();
    enc_message = message;
    message[len - 1] = fillBlanks(message[len - 1], key_len);
    for(i=0;i<len;i++) {
        cout << message[i] <<endl;
    }
    /* Forming the key*/
    vector<ull> ordered, unordered;
    sort(temp_key.begin(), temp_key.end());
    for(i=0;i<key_len;i++) {
        ordered.pb(i+1);
    }
    order_size = ordered.size();
    for(i=0;i<order_size;i++) {
        for(j = 0;j<order_size;j++) {
            if(temp_key[j] == key[i]) {
                //cout << temp_key[j] << " Matched " << key[i]<<endl;
                unordered.pb(j+1);
                break;
            }
        }
    }
    /* Forming the encrypted message*/
    for(i=0;i<key_len;i++) {
        for(j=0;j<len;j++) {
            enc_message[j][unordered[i] - 1] = message[j][ordered[i]-1];
        }
    }
    for(i=0;i<key_len;i++) {
        for(j=0;j<len;j++) {
            cout<< enc_message[j][i];
        }
        cout << " ";
    }
    cout << endl;
    time_taken = (clock() - time_taken)/CLOCKS_PER_SEC;
    cout << time_taken <<endl;
    return 0;
}