"""@package DESKeygen
Documentation for this module.
"""
from copy import copy
## This is an implementation of DES Cipher Algorithm
# DES = Data Encryption Standard
# STEP 1: create all constants first

## The follow lists are values used for encryption

EXPANSION = [
    31, 0, 1, 2, 3, 4,
    3, 4, 5, 6, 7, 8,
    7, 8, 9, 10, 11, 12,
    11, 12, 13, 14, 15, 16,
    15, 16, 17, 18, 19, 20,
    19, 20, 21, 22, 23, 24,
    23, 24, 25, 26, 27, 28,
    27, 28, 29, 30, 31, 0
]
## IP = Initial Permutation
# This is used to permute the plain_text binary form based on the beloe stated table
IP = [57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7,
      56, 48, 40, 32, 24, 16, 8, 0,
      58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6
      ]
## PC1 = Permuted Choice 1
# This is used to permute the plain_text binary form based on the below stated table.
# Basically PC1 converts the 64 bits key to 56 bit and values at 8th, 16th bits and soon are removed

PC1 = [56, 48, 40, 32, 24, 16, 8,
       0, 57, 49, 41, 33, 25, 17,
       9, 1, 58, 50, 42, 34, 26,
       18, 10, 2, 59, 51, 43, 35,
       62, 54, 46, 38, 30, 22, 14,
       6, 61, 53, 45, 37, 29, 21,
       13, 5, 60, 52, 44, 36, 28,
       20, 12, 4, 27, 19, 11, 3]

## PC2 = Permuted Choice 2
# This is used to permute the plain_text binary form based on the below stated table.
# Basically PC1 converts the 56 bits key to 48 bit.
PC2 = [13, 16, 10, 23, 0, 4,
       2, 27, 14, 5, 20, 9,
       22, 18, 11, 3, 25, 7,
       15, 6, 26, 19, 12, 1,
       40, 51, 30, 36, 46, 54,
       29, 39, 50, 44, 32, 47,
       43, 48, 38, 55, 33, 52,
       45, 41, 49, 35, 28, 31
       ]
LEFTROTS = [
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
]

## S-Boxes
# We now do something strange with each group of six bits: we use them as addresses in
# tables called "S boxes". Each group of six bits will give us an address in a
# different S box. Located at that address will be a 4 bit number. This 4 bit number
# will replace the original 6 bits. The net result is that the eight groups of 6 bits are
# transformed into eight groups of 4 bits (the 4-bit outputs from the S boxes) for 32
# bits total.

S = [
    # S1
    [14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
     0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
     4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
     15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13],

    # S2
    [15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
     3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
     0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
     13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9],

    # S3
    [10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
     13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
     13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
     1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12],

    # S4
    [7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
     13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
     10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
     3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14],

    # S5
    [2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
     14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
     4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
     11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3],

    # S6
    [12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
     10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
     9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
     4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13],

    # S7
    [4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
     13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
     1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
     6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12],

    # S8
    [13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
     1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
     7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
     2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11],
]

# 32-bit permutation function P for the reduced output of the S-boxes

Reduced_ka_permutation = [
    15, 6, 19, 20, 28, 11,
    27, 16, 0, 14, 22, 25,
    4, 17, 30, 9, 1, 7,
    23, 13, 31, 26, 2, 8,
    18, 12, 29, 5, 21, 10,
    3, 24
]
hexa_scale = 16


# functions library

## BINARY STRING COVERSION
# @param k hexanumber
# This basically returns a string of 64 bits to the caller
def binary_string(k):
    string = bin(int(k, hexa_scale))[2:].zfill(64)
    return string


## GET PERMUTATION STRING
# @param k hexanumber
# @param pc Permutation Array
# This basically returns a string formed by the PC array using permutation bits
def get_x_bit_permutation(k, pc):
    new_perm = ""
    size = len(pc)
    for it in range(0, size):
        new_perm += str(k[pc[it]])
    return new_perm


def perform_xor(first_d, second_d):
    bit_len = len(first_d)
    xorred_data = ""
    for it in range(0, bit_len):
        val = int(first_d[it]) ^ int(second_d[it])
        xorred_data += (str(val))
    return xorred_data


## GET PERMUTATION STRING
# @param string the 48-bit key
# Returns a compressed string of 32-bits using the S-boxes
def compression_to_32(string):
    compressed_val = ''
    for j in range(0, 8):
        six_bit = string[j * 6: (j + 1) * 6]
        bin1 = six_bit[0] + six_bit[5]
        bin2 = six_bit[1:5]
        row_val = int(bin1, 2)
        col_val = int(bin2, 2)
        # print(str(row_val) + " " + str(col_val))
        check_val = S[j][row_val * 16 + col_val]
        compressed_val += (bin(check_val)[2:].zfill(4))
    return compressed_val


# plaintext = '0123456789ABCDEF'
# key = '133457799BBCDFF1'
key = str(input())
plaintext = str(input())
# print(plaintext)
# print(key)
L = plaintext[0:8]
R = plaintext[8:16]
plain_binary = binary_string(plaintext)
b_key = binary_string(key)
# print(b_key)
five_six_perm = get_x_bit_permutation(b_key, PC1)
# print(five_six_perm)
# Now we create keys
C = []
D = []
C.append(five_six_perm[0:28])
D.append(five_six_perm[28:56])
for i in range(1, 17):
    if LEFTROTS[i - 1] == 1:
        first = C[i - 1][0]
        second = D[i - 1][0]
        Cx = C[i - 1][1:28] + first
        C.append(Cx)
        Dx = D[i - 1][1:28] + second
        D.append(Dx)
    elif LEFTROTS[i - 1] == 2:
        Cx = C[i - 1][2:28] + C[i - 1][0:2]
        Dx = D[i - 1][2:28] + D[i - 1][0:2]
        C.append(Cx)
        D.append(Dx)
key_list = []
hex_key_list = []
for i in range(0, 16):
    key_list.append(get_x_bit_permutation((C[i + 1] + D[i + 1]), PC2))
    hex_key_list.append(hex(int(key_list[i], 2))[2:].zfill(12).upper())
# print(hex_key_list)
# Now the next step is to get L1R1i
initial_permutation = get_x_bit_permutation(plain_binary, IP)
# print(initial_permutation)

# First get L0 R0
L0 = initial_permutation[0:32]
R0 = initial_permutation[32:64]
# Now get L1R1
L1 = copy(R0)
# print(L1)
# Getting value of the function
ER0 = get_x_bit_permutation(R0, EXPANSION)
# print("Expansion to 48 bits " + ER0)
func_ER0K1 = perform_xor(key_list[0], ER0)
# print("Original 48 bit is " + func_ER0K1)
reduced_value = compression_to_32(func_ER0K1)
# print("Output of function " + reduced_value)
permuted_reduced_val = get_x_bit_permutation(reduced_value, Reduced_ka_permutation)
R1 = perform_xor(L0, permuted_reduced_val)
final_bit_string = L1 + R1
final_res = hex(int(final_bit_string, 2))[2:].upper()
# Now all print statements together
for hex_val in hex_key_list:
    print(hex_val)
print(final_res)
