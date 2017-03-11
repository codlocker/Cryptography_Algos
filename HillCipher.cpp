#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
int key[15][15],invkey[15][15];
char in[1000],ciphertext[1000];
#define SPACE 26
#define DOT 28
#define QUESTION 27
int modinv(int num)
{
    while(num<0)
        num+=29;
    int inv=2;
    while(inv<29)
    {
        if(((inv*num)%29)==1)
            return inv;
        else
            inv++;
    }
    return -50;
}
void hill_encrypt(int size)
{
    int length=0;
    while(in[length]!='\0')
    {
        length++;
    }
    int plain[15],test;
    int len=0,len1=0;
    go_row: int i=0;
    while(len<length && i<size)
    {
        if(in[len]==' ')
            plain[i]=SPACE;
        else if(in[len]=='?')
            plain[i]=QUESTION;
        else if(in[len]=='.')
            plain[i]=DOT;
        else
            plain[i]=(int)in[len]-97;
        i++;
        len++;
    }

    while(i<size)
    {
        plain[i++]=23;
    }
    int p,c[15],j,k;
    for (j = 0; j < size; j++)
    {
        int val = 0;
        for (int k = 0; k < size; k++)
        {
            val = val + plain[k] * key[k][j];
            val=val % 29;
        }
        c[j] = val;
        //cout<<c[j]<<endl;
    }
    int t_index=0;
    while(t_index<size)
    {

        if(c[t_index]==SPACE)
            ciphertext[len1]=' ';
        else if(c[t_index]==QUESTION)
            ciphertext[len1]='?';
        else if(c[t_index]==DOT)
            ciphertext[len1]='.';
        else
            ciphertext[len1]=c[t_index]+97;
        len1++;
        t_index++;
    }
    //cout<<ciphertext<<endl;
    if(len<length)
        goto go_row;
}
void hill_decrypt(int size)
{
    int l=0;
    while(in[l]!='\0')
    {
        //cout<<in[l]<<"len:"<<l<<endl;
        l++;
    }
    //cout<<"\n";
    //cout<<l<<endl;
    int plaintext[15],test;
    int len=0,len1=0;
    another_row: int i=0;
    //cout<<"new iteration\n";
    while(len<l && i<size)
    {

        if(in[len]==' ')
            plaintext[i]=26;
        else if(in[len]=='?')
            plaintext[i]=27;
        else if(in[len]=='.')
            plaintext[i]=28;
        else
            plaintext[i]=(int)in[len]-97;
        i++;
        len++;
    }

    int p,c[15],j,k;
    for (j = 0; j < size; j++)
    {
        c[j] = 0;
        for (int k = 0; k < size; k++)
        {
            c[j] = c[j] + plaintext[k] * invkey[k][j];
            c[j]=c[j]%29;
        }
        //cout<<c[j]<<endl;
    }
    int temp=0;
    while(temp<size)
    {
        //cout<<"len1"<<len1<<endl;
        if(c[temp]==26)
            ciphertext[len1]=' ';
        else if(c[temp]==27)
            ciphertext[len1]='?';
        else if(c[temp]==28)
            ciphertext[len1]='.';
        else
            ciphertext[len1]=c[temp]+97;
        len1++;
        temp++;
    }
    // puts(ciphertext);
    if(len<l)
        goto another_row;
}
int find_det(int matrix[15][15],int size)
{
    int s=1,determinant=0,m_minor[15][15];
    int i,m,c,n ,j , sign = 1;
    if (size==1)
    {
        return (matrix[0][0]);
    }
    else
    {
        determinant=0;
        for (c=0;c<size;c++)
        {
            m=0;
            n=0;
            for (i=0;i<size;i++)
            {
                for (j=0;j<size;j++)
                {
                    m_minor[i][j]=0;
                    if (i != 0 && j != c)
                    {
                        m_minor[m][n]=matrix[i][j];
                        if (n<(size-2))n++;
                        else{n=0;m++;}
                    }
                }
            }
            determinant=determinant + s * (matrix[0][c] * find_det(m_minor,size-1));
            s=-1 * s;
        }
    }
    return determinant;
}

void get_transpose(int matrix[15][15],int matrix_cofactor[15][15],int size)
{
    int i,j;
    int m_transpose[15][15],d;

    for (i=0;i<size;i++)
    {
        for (j=0;j<size;j++)
        {
            m_transpose[i][j]=matrix_cofactor[j][i];
        }
    }
    for (i=0;i<size;i++)
    {
        for (j=0;j<size;j++)
        {
            invkey[i][j]=m_transpose[i][j];
        }
    }

}
void cofactor(int mat[15][15],int size)
{
    int m_cofactor[15][15],matrix_cofactor[15][15];
    int p,q,m,n,i,j;
    for (q=0;q<size;q++)
    {
        for (p=0;p<size;p++)
        {
            m=0;
            n=0;
            for (i=0;i<size;i++)
            {
                for (j=0;j<size;j++)
                {
                    if (i != q && j != p)
                    {
                        m_cofactor[m][n]=mat[i][j];
                        if (n<(size-2))
                            n++;
                        else
                        {
                            n=0;
                            m++;
                        }
                    }
                }
            }
            matrix_cofactor[q][p]=pow(-1,q + p) * find_det(m_cofactor,size-1);
        }
    }
    get_transpose(mat,matrix_cofactor,size);
}

void key_of_inverse(int key[15][15],int len)
{
    int det=find_det(key,len);
    // cout << det <<endl;
    det=modinv(det);
    // cout << det <<endl;
    int i,j;
    cofactor(key,len); // Calculate the Matrix CoFactors
    for (i=0;i<len;i++)
    {
        for (j=0;j<len;j++)
        {
            invkey[i][j]=(det*invkey[i][j])%29;
            while(invkey[i][j]<0)
                invkey[i][j]+=29;
            //cout<<invkey[i][j]<<" ";
        }
        //cout<<"\n";
    }
}
int main()
{

    int size_key,i,j,t;
    cin>>size_key;
    for(i=0;i<size_key;i++)
    {
        for(j=0;j<size_key;j++)
            cin>>key[i][j];
    }
    key_of_inverse(key,size_key);
    cin>>t;
    string st;
    getline(cin,st);
    for(i=0;i<t;i++)
    {
        string line;
        getline(cin, line);
        // cout << line <<endl;
        if(line[0]=='e')
        {
            string plain = line.substr(2);
            strcpy(in ,plain.c_str());
            hill_encrypt(size_key);
            cout << ciphertext <<endl;
        }
        else if(line[0]=='d')
        {
            string plain = line.substr(2);
            strcpy(in ,plain.c_str());
            hill_decrypt(size_key);
            cout << ciphertext <<endl;
        }
    }
    return 0;
}