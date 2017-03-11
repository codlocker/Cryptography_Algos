#include<bits/stdc++.h>
#include<string>
#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;
int main() {
    ll i,j,k,n ;
    vector<ll> cipher_one, cipher_two;
    string str1, str2;
    /*Pre Processing*/
    string words[] = {"quizzicality", "embezzlement", "subjectivize", "katzenjammer", "quinquennium", "puzzleheaded", "crackerjacks", "pyrolyzable", "journalizer", "rhythmizing", "journalizes",
                      "objectivity", "overcomplex", "lacquerwork", "frizzliest", "intermezzo", "intermezzi", "liquidized",
                      "quadplexes", "jacqueries", "quillbacks", "zugzwangs", "mezzaluna", "equivoque", "jipijapas", "schnozzes", "jackknife", "krummholz"};
    ll word_len = sizeof(words)/sizeof(words[0]);
    vector<vector<ll> > ascii_val(word_len);
    for(i=0;i<word_len;i++) {
        ll len = words[i].size();
        for(j = 0; j < len; j++) {
            ascii_val[i].pb((ll)(words[i][j]));
        }
        /*for (j=0;j<len;j++)
            cout << ascii_val[i][j] << " ";
        cout << endl;*/
    }
    /*Now get the user input*/
    getline(cin,str1);
    getline(cin,str2);
    ll len1 = str1.size();
    ll len2 = str2.size();
    string number = "";
    string::size_type sz;
    for(i = 0;i < len1;i++) {
        if(str1[i]!= ' ') {
            number+=str1[i];
        }
        else {
            ll n = stoi(number, &sz);
            cipher_one.pb(n);
        }
    }
    n = stoi(number, &sz);
    cipher_one.pb(n);

    number = "";
    for(i = 0;i < len2;i++) {
        if(str2[i]!= ' ') {
            number+=str2[i];
        }
        else {
            ll n = stoi(number, &sz);
            cipher_two.pb(n);
            number = "";
        }
    }
    n = stoi(number, &sz);
    cipher_two.pb(n);
    return 0;
}