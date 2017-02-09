//
// Created by shuttle3468 on 4/2/17.
//
//
// Created by shuttle3468 on 4/2/17.
//
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
int main() {
    string enc_message = "";

    ull len ,i ,j ,k ,l, row, col;
    cin >> row >> col;
    pair<ull,ull> dim = make_pair(row, col);

    //cout << dim.first <<" " << dim.second <<endl;
    string enc_matrix[dim.first];
    ull c_count = 0, max_r = dim.first-1, min_c = 0, min_r = 0, max_c = dim.second-1;

    for(i=0;i<dim.first;i++) {
        cin >> enc_matrix[i];
    }
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

