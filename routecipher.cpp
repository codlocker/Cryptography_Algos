//
// Created by shuttle3468 on 4/2/17.
//
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
pair<ull,ull> getRC(ull len) {
    ull i;
    pair<ull,ull> dim;
    for(i=2;i<=len; i++) {
        if(len % i == 0) {
            dim.first = i;
            dim.second = len/i;
            return dim;
        }
    }
    return dim;
}
int main() {
    string enc_message;
    cin >> enc_message;
    cout << enc_message.size() <<endl;
    ull len = enc_message.size() ,i ,j ,k ,l;
    pair<ull,ull> dim = getRC(len);
    cout << dim.first <<" " << dim.second <<endl;
    char enc_matrix[dim.first][dim.second];

    ull c_count = 0, max_r = dim.first-1, min_c = 0, min_r = 0, max_c = dim.second-1;
    //cout << min_r <<" " << max_r <<" " << min_c << " " << max_c <<endl;
    while(c_count < len) {
        for(i = min_r; i <= max_r;++i) {
            if(c_count == len) {break;}
            enc_matrix[i][max_c] = (enc_message[c_count]);
            c_count ++;
        }

        //cout << c_count << endl;
        for(j = max_c-1;j>=min_c;--j) {
            if(c_count == len) {break;}
            enc_matrix[max_r][j] = (enc_message[c_count]);
            ++c_count;
            if(j == min_c){ break;}

        }
        //cout << c_count << endl;
        for(k = max_r-1;k>=min_r;--k) {
            if(c_count == len) {break;}
            enc_matrix[k][min_c] = (enc_message[c_count]);
            ++c_count;
            if(k == min_r){ break;}
        }
        //cout << c_count << endl;
        for(l = min_c + 1;l<=max_c -1;++l) {
            if(c_count == len) {break;}
            enc_matrix[min_r][l] = (enc_message[c_count]);
            c_count ++;
        }
        cout << c_count << endl;
        ++min_c;
        ++min_r;
        --max_r;
        --max_c;
    }
    for(i=0;i<dim.first;i++) {
        for(j=0;j<dim.second;j++)
            cout << enc_matrix[i][j];
        cout << " ";
    }
    cout <<endl;
    return 0;
}
