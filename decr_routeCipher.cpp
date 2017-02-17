//
// Created by shuttle3468 on 4/2/17.
//
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
int main() {
    string enc_message = "", str;
    ull len ,i ,j ,k ,l, row, col;
    string enc_matrix[100];
    i=0;
    getline(cin,str);
    istringstream istream(str);
    for(string s; istream >> s;) {
        enc_matrix[i] = s;
        i++;
    }
    row = i;
    col = enc_matrix[0].size();
    //cout << row << " " << col <<endl;
    pair<ull,ull> dim = make_pair(row,col);
    ull c_count = 0, max_r = dim.first-1, min_c = 0, min_r = 0, max_c = dim.second-1;
    len = row * col;
    //cout << min_r <<" " << max_r <<" " << min_c << " " << max_c <<endl;
    while(c_count < len) {
        for(i = min_r; i <= max_r;++i) {
            if(c_count == len) {break;}
            enc_message+= enc_matrix[i][max_c];
            c_count ++;
        }

        //cout << c_count << endl;
        for(j = max_c-1;j>=min_c;--j) {
            if(c_count == len) {break;}
            enc_message+= enc_matrix[max_r][j];
            ++c_count;
            if(j == min_c){ break;}

        }
        //cout << c_count << endl;
        for(k = max_r-1;k>=min_r;--k) {
            if(c_count == len) {break;}
            enc_message+= enc_matrix[k][min_c];
            ++c_count;
            if(k == min_r){ break;}
        }
        //cout << c_count << endl;
        for(l = min_c + 1;l<=max_c -1;++l) {
            if(c_count == len) {break;}
            enc_message+= enc_matrix[min_r][l];
            c_count ++;
        }
        //cout << c_count << endl;
        ++min_c;
        ++min_r;
        --max_r;
        --max_c;
    }
    cout << enc_message <<endl;
    return 0;
}

