#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;
/********************************************//**
 *  The matrix obtained in the main function is now used here to generate the cipher text. According to playfair
 *  algorithm the conditions for swap vary according to the locations of the digrams in the supplied matrix.
 ***********************************************/
string implmatrix(string s /**< String to be encrypted */, char mat[][5]) {
    pair<int,int> p[2];
    int i,j,k; //!< Iteration Variables for the matrix
    for(k=0;k<2;k++) {
        for(i=0;i<5;i++)
            for(j=0;j<5;j++)
                if(mat[i][j] == s[k]) {
                    p[k] = mp(i,j);
                }
    }
    /*Adhering the conditions for swapping values*/
    ///  First case handling
     /**
     *  If the the digrams are not located in the same column and same row then we swap the take the digit in the same row
     *  but column number of the second member of the diagram and vice versa for the second element of the digram
     */
    if(p[0].first != p[1].first && p[0].second != p[1].second) {
        s[0] = mat[p[0].first][p[1].second];
        s[1] = mat[p[1].first][p[0].second];
    }
    ///  Second case handling
     /**
     *  If the the digrams are located in the same row and different column then we swap the take the digit in the same row
     *  but next column number in that row and same is done for the second element of the digram.
     */
    else if(p[0].first == p[1].first) {
        s[0] = mat[p[0].first][(p[0].second + 1) % 5];
        s[1] = mat[p[1].first][(p[1].second + 1) % 5];
    }
    ///  Third case handling
     /**
     *  If the the digrams are located in the same colum and different row then we swap the take the digit in the same column
     *  but next row number in that row and same is done for the second element of the digram.
     */
    else if(p[0].second == p[1].second) {
        s[0] = mat[(p[0].first + 1) % 5][p[0].second];
        s[1] = mat[(p[1].first + 1) % 5][p[1].second];
    }
    return s;
}
int main() {
    string keyword = "PLAYFAIR";
    string message = "SECRETMESSAGEISECRET";
    char mat[5][5];
    int alpha[26] = {0};
    alpha[9] = 1;
    int keyw_len = keyword.size();
    int i, j, k, count = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (count<keyw_len) {
                if(alpha[(int) (keyword[count] - 65)] == 0){mat[i][j] = (char) (keyword[count]);}
                else{j--;}
                alpha[(int) (keyword[count] - 65)] = 1;
                count++;
            } else {
                for (k = 0; k < 26; k++) {
                    if (alpha[k] == 0) {
                        mat[i][j] = (char) (65 + k);
                        alpha[k] = 1;
                        break;
                    }

                }
            }
        }
    }
    for(i = 0;i< 5;i++) {
        for (j = 0;j<5;j++) {
            cout << mat[i][j] <<" ";
        }
        cout << endl;
    }
    /*
     * Building the secret message for encryption
     *
     */
    int msg_len = message.size();
    vector<string> digrams;
    for (i = 0; i < msg_len; i++) {
        string ss;
        if (message[i] == message[i + 1]) {
            ss += message[i];
            ss += 'X';
        } else {
            ss += message[i];
            if (i + 1 < msg_len) { ss += message[i + 1]; }
            i++;
        }
        digrams.pb(ss);
        //cout << ss<<endl;
    }

    if (digrams[digrams.size() - 1].length() == 1) {
        digrams[digrams.size() - 1] += 'X';
    }
    int no_dig = digrams.size();
    string encrypted_string;
    for (i = 0; i < no_dig; i++) {
        digrams[i].c_str();
        string str = implmatrix(digrams[i], mat);
        encrypted_string+=str;
    }
    cout << "The original string is :" << message <<endl;
    cout << "The encrypted string is :" << encrypted_string << endl;
    return 0;
}