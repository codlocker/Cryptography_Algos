IMPLEMENTING CRYPTOGRAPHY ALGORITHMS            {#mainpage}
====================================

Documentation for the Algorithms used
------------------------

> Basic implementation of Classical Cipher Algorithms. The aim of the 
> repository is to include implementation of major cipher algorithms
> during the course


1. [PlayFair Cipher](https://en.wikipedia.org/wiki/Playfair_cipher)
   > The technique encrypts pairs of letters (bigrams or digrams), 
   > instead of single letters as in the simple 
   > substitution cipher and rather more complex Vigenère cipher systems 
   > then in use. The Playfair is thus significantly harder 
   > to break since the frequency analysis used for simple substitution ciphers does not work with it.

2. [Route Cipher](https://en.wikipedia.org/wiki/Transposition_cipher#Route_cipher) 
   + Encryption to Cipher text
   
        The implementation of Route Cipher is similar to a spiral matrix
        where the key is a matrix written as spiral inwards, starting 
        from top right.
   
   + Decryption of the Cipher text

3. [Row Transposition Cipher](https://en.wikipedia.org/wiki/Transposition_cipher#Columnar_transposition)
    + Single Encryption

4. [DES Key generation and first step Encryption](https://www.tutorialspoint.com/cryptography/data_encryption_standard.htm)
    > DES is an implementation of a Feistel Cipher. It uses 16 round Feistel structure. 
    > The block size is 64-bit. Though, key length is 64-bit, DES has an effective key length of 56 bits, since 8 of the 64 bits of the 
    > key are not used by the encryption algorithm (function as check bits only). General Structure of DES is depicted in the following illustration −
