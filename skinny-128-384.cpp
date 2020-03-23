/*
 * C++ implementation of Skinny-128-384
 * Date: March 10, 2020
 * Author: Hosein Hadipour
 * Contact: hsn.hadipour@gmail.com
*/
//Skinny-128-384: 56 rounds

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <iostream>

using namespace std;

// 8-bit Sbox
const uint8_t S[256] = {0x65, 0x4c, 0x6a, 0x42, 0x4b, 0x63, 0x43, 0x6b, 0x55, 0x75, 0x5a, 0x7a, 0x53, 0x73, 0x5b, 0x7b, 0x35, 0x8c, 0x3a, 0x81, 0x89, 0x33, 0x80, 0x3b, 0x95, 0x25, 0x98, 0x2a, 0x90, 0x23, 0x99, 0x2b, 0xe5, 0xcc, 0xe8, 0xc1, 0xc9, 0xe0, 0xc0, 0xe9, 0xd5, 0xf5, 0xd8, 0xf8, 0xd0, 0xf0, 0xd9, 0xf9, 0xa5, 0x1c, 0xa8, 0x12, 0x1b, 0xa0, 0x13, 0xa9, 0x05, 0xb5, 0x0a, 0xb8, 0x03, 0xb0, 0x0b, 0xb9, 0x32, 0x88, 0x3c, 0x85, 0x8d, 0x34, 0x84, 0x3d, 0x91, 0x22, 0x9c, 0x2c, 0x94, 0x24, 0x9d, 0x2d, 0x62, 0x4a, 0x6c, 0x45, 0x4d, 0x64, 0x44, 0x6d, 0x52, 0x72, 0x5c, 0x7c, 0x54, 0x74, 0x5d, 0x7d, 0xa1, 0x1a, 0xac, 0x15, 0x1d, 0xa4, 0x14, 0xad, 0x02, 0xb1, 0x0c, 0xbc, 0x04, 0xb4, 0x0d, 0xbd, 0xe1, 0xc8, 0xec, 0xc5, 0xcd, 0xe4, 0xc4, 0xed, 0xd1, 0xf1, 0xdc, 0xfc, 0xd4, 0xf4, 0xdd, 0xfd, 0x36, 0x8e, 0x38, 0x82, 0x8b, 0x30, 0x83, 0x39, 0x96, 0x26, 0x9a, 0x28, 0x93, 0x20, 0x9b, 0x29, 0x66, 0x4e, 0x68, 0x41, 0x49, 0x60, 0x40, 0x69, 0x56, 0x76, 0x58, 0x78, 0x50, 0x70, 0x59, 0x79, 0xa6, 0x1e, 0xaa, 0x11, 0x19, 0xa3, 0x10, 0xab, 0x06, 0xb6, 0x08, 0xba, 0x00, 0xb3, 0x09, 0xbb, 0xe6, 0xce, 0xea, 0xc2, 0xcb, 0xe3, 0xc3, 0xeb, 0xd6, 0xf6, 0xda, 0xfa, 0xd3, 0xf3, 0xdb, 0xfb, 0x31, 0x8a, 0x3e, 0x86, 0x8f, 0x37, 0x87, 0x3f, 0x92, 0x21, 0x9e, 0x2e, 0x97, 0x27, 0x9f, 0x2f, 0x61, 0x48, 0x6e, 0x46, 0x4f, 0x67, 0x47, 0x6f, 0x51, 0x71, 0x5e, 0x7e, 0x57, 0x77, 0x5f, 0x7f, 0xa2, 0x18, 0xae, 0x16, 0x1f, 0xa7, 0x17, 0xaf, 0x01, 0xb2, 0x0e, 0xbe, 0x07, 0xb7, 0x0f, 0xbf, 0xe2, 0xca, 0xee, 0xc6, 0xcf, 0xe7, 0xc7, 0xef, 0xd2, 0xf2, 0xde, 0xfe, 0xd7, 0xf7, 0xdf, 0xff};
// 8-bit Sbox Inverse
const uint8_t Sinv[256] = {0xac, 0xe8, 0x68, 0x3c, 0x6c, 0x38, 0xa8, 0xec, 0xaa, 0xae, 0x3a, 0x3e, 0x6a, 0x6e, 0xea, 0xee, 0xa6, 0xa3, 0x33, 0x36, 0x66, 0x63, 0xe3, 0xe6, 0xe1, 0xa4, 0x61, 0x34, 0x31, 0x64, 0xa1, 0xe4, 0x8d, 0xc9, 0x49, 0x1d, 0x4d, 0x19, 0x89, 0xcd, 0x8b, 0x8f, 0x1b, 0x1f, 0x4b, 0x4f, 0xcb, 0xcf, 0x85, 0xc0, 0x40, 0x15, 0x45, 0x10, 0x80, 0xc5, 0x82, 0x87, 0x12, 0x17, 0x42, 0x47, 0xc2, 0xc7, 0x96, 0x93, 0x03, 0x06, 0x56, 0x53, 0xd3, 0xd6, 0xd1, 0x94, 0x51, 0x04, 0x01, 0x54, 0x91, 0xd4, 0x9c, 0xd8, 0x58, 0x0c, 0x5c, 0x08, 0x98, 0xdc, 0x9a, 0x9e, 0x0a, 0x0e, 0x5a, 0x5e, 0xda, 0xde, 0x95, 0xd0, 0x50, 0x05, 0x55, 0x00, 0x90, 0xd5, 0x92, 0x97, 0x02, 0x07, 0x52, 0x57, 0xd2, 0xd7, 0x9d, 0xd9, 0x59, 0x0d, 0x5d, 0x09, 0x99, 0xdd, 0x9b, 0x9f, 0x0b, 0x0f, 0x5b, 0x5f, 0xdb, 0xdf, 0x16, 0x13, 0x83, 0x86, 0x46, 0x43, 0xc3, 0xc6, 0x41, 0x14, 0xc1, 0x84, 0x11, 0x44, 0x81, 0xc4, 0x1c, 0x48, 0xc8, 0x8c, 0x4c, 0x18, 0x88, 0xcc, 0x1a, 0x1e, 0x8a, 0x8e, 0x4a, 0x4e, 0xca, 0xce, 0x35, 0x60, 0xe0, 0xa5, 0x65, 0x30, 0xa0, 0xe5, 0x32, 0x37, 0xa2, 0xa7, 0x62, 0x67, 0xe2, 0xe7, 0x3d, 0x69, 0xe9, 0xad, 0x6d, 0x39, 0xa9, 0xed, 0x3b, 0x3f, 0xab, 0xaf, 0x6b, 0x6f, 0xeb, 0xef, 0x26, 0x23, 0xb3, 0xb6, 0x76, 0x73, 0xf3, 0xf6, 0x71, 0x24, 0xf1, 0xb4, 0x21, 0x74, 0xb1, 0xf4, 0x2c, 0x78, 0xf8, 0xbc, 0x7c, 0x28, 0xb8, 0xfc, 0x2a, 0x2e, 0xba, 0xbe, 0x7a, 0x7e, 0xfa, 0xfe, 0x25, 0x70, 0xf0, 0xb5, 0x75, 0x20, 0xb0, 0xf5, 0x22, 0x27, 0xb2, 0xb7, 0x72, 0x77, 0xf2, 0xf7, 0x2d, 0x79, 0xf9, 0xbd, 0x7d, 0x29, 0xb9, 0xfd, 0x2b, 0x2f, 0xbb, 0xbf, 0x7b, 0x7f, 0xfb, 0xff};
// Permutation
const uint8_t P[16] = {0x0, 0x1, 0x2, 0x3, 0x7, 0x4, 0x5, 0x6, 0xa, 0xb, 0x8, 0x9, 0xd, 0xe, 0xf, 0xc};
const uint8_t Pinv[16] = {0x0, 0x1, 0x2, 0x3, 0x5, 0x6, 0x7, 0x4, 0xa, 0xb, 0x8, 0x9, 0xf, 0xc, 0xd, 0xe};
// Tweakey Permutation
const uint8_t Q[16] = {0x9, 0xf, 0x8, 0xd, 0xa, 0xe, 0xc, 0xb, 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
// const uint8_t Qinv[16] = {0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x2, 0x0, 0x4, 0x7, 0x6, 0x3, 0x5, 0x1};
// Round Constants
const unsigned char RC[62] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3E, 0x3D, 0x3B, 0x37, 0x2F,
                              0x1E, 0x3C, 0x39, 0x33, 0x27, 0x0E, 0x1D, 0x3A, 0x35, 0x2B,
                              0x16, 0x2C, 0x18, 0x30, 0x21, 0x02, 0x05, 0x0B, 0x17, 0x2E,
                              0x1C, 0x38, 0x31, 0x23, 0x06, 0x0D, 0x1B, 0x36, 0x2D, 0x1A,
                              0x34, 0x29, 0x12, 0x24, 0x08, 0x11, 0x22, 0x04, 0x09, 0x13,
                              0x26, 0x0c, 0x19, 0x32, 0x25, 0x0a, 0x15, 0x2a, 0x14, 0x28,
                              0x10, 0x20};

void print_state(uint8_t state[16]);
void convert_hexstr_to_statearray(string hex_str, uint8_t int_array[16], bool reversed);
uint8_t tweak_tk2_lfsr8(uint8_t x);
uint8_t tweak_tk3_lfsr8(uint8_t x);
void mix_columns(uint8_t state[16]);
void inv_mix_columns(uint8_t state[16]);
void tweakey_schedule(int rounds, uint8_t tk1[][16], uint8_t tk2[][16], uint8_t tk3[][16], uint8_t round_tweakey[][8]);
void enc(int R, uint8_t plaintext[16], uint8_t ciphertext[16], uint8_t tk[][8]);
void dec(int R, uint8_t plaintext[16], uint8_t ciphertext[16], uint8_t tk[][8]);

void print_state(uint8_t state[16])
{
    for (int i = 0; i < 16; i++)
        printf("%02x", state[i]);
    printf("\n");
}

void convert_hexstr_to_statearray(string hex_str, uint8_t int_array[16], bool reversed = false)
{
    if (reversed == true)
        for (size_t i = 0; i < 16; i++)
            int_array[15 - i] = static_cast<uint8_t> (stoi(hex_str.substr(2 * i, 2), 0, 16) & 0xff);
    else
        for (size_t i = 0; i < 16; i++)
            int_array[i] = static_cast<uint8_t> (stoi(hex_str.substr(2 * i, 2), 0, 16) & 0xff);
}

uint8_t tweak_tk2_lfsr8(uint8_t x)
{
    x = ((x << 1) & 0xFE) ^ (((x >> 7) ^ (x >> 5)) & 0x01);
    x = x & 0xff;
    return x;
}

uint8_t tweak_tk3_lfsr8(uint8_t x)
{
    x = ((x >> 1) & 0x7F) ^ (((x << 7) ^ (x << 1)) & 0x80);
    x = x & 0xff;
    return x;
}

void mix_columns(uint8_t state[16])
{
    uint8_t tmp;
    for (uint8_t j = 0; j < 4; j++)
    {
        state[j + 4 * 1] ^= state[j + 4 * 2];
        state[j + 4 * 2] ^= state[j + 4 * 0];
        state[j + 4 * 3] ^= state[j + 4 * 2];
        tmp = state[j + 4 * 3];
        state[j + 4 * 3] = state[j + 4 * 2];
        state[j + 4 * 2] = state[j + 4 * 1];
        state[j + 4 * 1] = state[j + 4 * 0];
        state[j + 4 * 0] = tmp;
    }
}

void inv_mix_columns(uint8_t state[16])
{
    uint8_t tmp;
    for (uint8_t j = 0; j < 4; j++)
    {
        tmp = state[j + 4 * 3];
        state[j + 4 * 3] = state[j + 4 * 0];
        state[j + 4 * 0] = state[j + 4 * 1];
        state[j + 4 * 1] = state[j + 4 * 2];
        state[j + 4 * 2] = tmp;
        state[j + 4 * 3] ^= state[j + 4 * 2];
        state[j + 4 * 2] ^= state[j + 4 * 0];
        state[j + 4 * 1] ^= state[j + 4 * 2];
    }
}

void tweakey_schedule(int rounds, uint8_t tk1[][16], uint8_t tk2[][16], uint8_t tk3[][16], uint8_t round_tweakey[][8])
{
    // Declare tweakey after permutation
    uint8_t tkp1[rounds - 1][16];
    uint8_t tkp2[rounds - 1][16];
    uint8_t tkp3[rounds - 1][16];
    for (uint8_t i = 0; i < 16; i++)
        tk1[0][i] = (tk1[0][i] & 0xff);
    for (uint8_t i = 0; i < 16; i++)
        tk2[0][i] = (tk2[0][i] & 0xff);
    for (uint8_t i = 0; i < 16; i++)
        tk3[0][i] = (tk3[0][i] & 0xff);
    for (uint8_t i = 0; i < 8; i++)
        round_tweakey[0][i] = (tk1[0][i] ^ tk2[0][i] ^ tk3[0][i]);
    for (int r = 1; r < rounds; r++)
    {
        // Apply tweakey permutation on TK1, TK2, and TK3
        for (int i = 0; i < 16; i++)
        {
            tkp1[r - 1][i] = tk1[r - 1][Q[i]];
            tkp2[r - 1][i] = tk2[r - 1][Q[i]];
            tkp3[r - 1][i] = tk3[r - 1][Q[i]];
        }
        // Apply LFSR on two upper rows of TK2, TK3
        for (int i = 0; i < 16; i++)
        {
            // LFSRs are not performed on TK1 at all
            tk1[r][i] = tkp1[r - 1][i];
            if (i < 8)
            {
                tk2[r][i] = tweak_tk2_lfsr8(tkp2[r - 1][i]);
                tk3[r][i] = tweak_tk3_lfsr8(tkp3[r - 1][i]);
            }
            else
            {
                tk2[r][i] = tkp2[r - 1][i];
                tk3[r][i] = tkp3[r - 1][i];
            }
        }
        // Update round-tweakey
        for (int i = 0; i < 8; i++)
            round_tweakey[r][i] = (tk1[r][i] ^ tk2[r][i] ^ tk3[r][i]);
        // print_state(round_tweakey[r]);
    }
}

void enc(int R, uint8_t plaintext[16], uint8_t ciphertext[16], uint8_t tk[][8])
{
    for (uint8_t i = 0; i < 16; i++)
    {
        ciphertext[i] = plaintext[i] & 0xff;
    }
    for (uint8_t r = 0; r < R; r++)
    {
        // SBox
        for (uint8_t i = 0; i < 16; i++)
            ciphertext[i] = S[ciphertext[i]];
        // Add constants (constants only affects on three upper cells of the first column)
        ciphertext[0] ^= (RC[r] & 0xf);
        ciphertext[4] ^= ((RC[r] >> 4) & 0x3);
        ciphertext[8] ^= 0x2;
        // Add round tweakey (tweakey only exclusive-ored with two upper rows of the state)
        for (uint8_t i = 0; i < 8; i++)
            ciphertext[i] ^= tk[r][i];
        // Permute nibbles
        uint8_t temp[16];
        for (uint8_t i = 0; i < 16; i++)
            temp[i] = ciphertext[i];
        for (uint8_t i = 0; i < 16; i++)
            ciphertext[i] = temp[P[i]];
        // MixColumn
        mix_columns(ciphertext);
        // Print state
        // print_state(ciphertext);
    }
}

void dec(int R, uint8_t plaintext[16], uint8_t ciphertext[16], uint8_t tk[][8])
{
    for (uint8_t i = 0; i < 16; i++)
    {
        plaintext[i] = ciphertext[i] & 0xff;
    }
    int ind;
    uint8_t temp[16];
    for (int r = 0; r < R; r++)
    {
        // MixColumn inverse
        inv_mix_columns(plaintext);
        // Permute nibble inverse
        for (uint8_t i = 0; i < 16; i++)
            temp[i] = plaintext[i];
        for (uint8_t i = 0; i < 16; i++)
            plaintext[i] = temp[Pinv[i]];
        //temp[P[i]] = plaintext[i];
        // Add tweakey
        ind = R - r - 1;
        for (uint8_t i = 0; i < 8; i++)
            plaintext[i] ^= tk[ind][i];
        // Add constants
        plaintext[0] ^= (RC[ind] & 0xf);
        plaintext[4] ^= ((RC[ind] >> 4) & 0x3);
        plaintext[8] ^= 0x2;
        // SBox inverse
        for (uint8_t i = 0; i < 16; i++)
            plaintext[i] = Sinv[plaintext[i]];
        // Print state
        // print_state(plaintext);
    }
}

int main()
{
    uint8_t plaintext[16];
    uint8_t ciphertext[16];
    int R = 56;
    uint8_t tk1[R][16];
    uint8_t tk2[R][16];
    uint8_t tk3[R][16];
    uint8_t rtk[R][8];
    uint8_t tweakey1[16];
    uint8_t tweakey2[16];
    uint8_t tweakey3[16];
    // Test vectors
    string tk1_str = "df889548cfc7ea52d296339301797449";
    string tk2_str = "ab588a34a47f1ab2dfe9c8293fbea9a5";
    string tk3_str = "ab1afac2611012cd8cef952618c3ebe8";
    string plain_str = "a3994b66ad85a3459f44e92b08f550cb";
    string cipher_str = "94ecf589e2017c601b38c6346a10dcfa";
    bool reversed = false;
    convert_hexstr_to_statearray(tk1_str, tweakey1, reversed);
    convert_hexstr_to_statearray(tk2_str, tweakey2, reversed);
    convert_hexstr_to_statearray(tk3_str, tweakey3, reversed);
    convert_hexstr_to_statearray(plain_str, plaintext, reversed);

    // string tk1_str_rv = "49747901933396d252eac7cf489588df";
    // string tk2_str_rv = "a5a9be3f29c8e9dfb21a7fa4348a58ab";
    // string tk3_str_rv = "e8ebc3182695ef8ccd121061c2fa1aab";
    // string plain_rv = "cb50f5082be9449f45a385ad664b99a3";
    // string cipher_str = "94ecf589e2017c601b38c6346a10dcfa";
    // bool reversed = true;
    // convert_hexstr_to_statearray(tk1_str_rv, tweakey1, reversed);
    // convert_hexstr_to_statearray(tk2_str_rv, tweakey2, reversed);
    // convert_hexstr_to_statearray(tk3_str_rv, tweakey3, reversed);
    // convert_hexstr_to_statearray(plain_rv, plaintext, reversed);
    for (uint8_t i = 0; i < 16; i++)
    {
        tk1[0][i] = tweakey1[i];
        tk2[0][i] = tweakey2[i];
        tk3[0][i] = tweakey3[i];
    }
    tweakey_schedule(R, tk1, tk2, tk3, rtk);
    printf("%-30s", "plaintext before encryption:");
    print_state(plaintext);
    enc(R, plaintext, ciphertext, rtk);
    printf("%-30s", "ciphertext:");
    print_state(ciphertext);
    printf("%-30s", "expected ciphertext:");
    printf("%s\n", cipher_str.c_str());
    dec(R, plaintext, ciphertext, rtk);
    printf("%-30s", "plaintext after decryption:");
    print_state(plaintext);
    printf("Press Enter to exit ...\n");
    getchar();
    return 0;
}