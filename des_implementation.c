#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =================================================================
// 1. DATA STRUCTURES & TABLES
// =================================================================

// Initial Permutation (IP) - 64 bits
int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

// Inverse Initial Permutation (IP^-1) - 64 bits
int IP_INV[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

// Expansion Permutation (E) - 32 bits to 48 bits
int E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

// Permutation P (P-Box) - 32 bits
int P[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25};

// Permuted Choice 1 (PC-1) - 64 bits to 56 bits
int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

// Permuted Choice 2 (PC-2) - 56 bits to 48 bits
int PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};

// Number of left shifts per round
int SHIFTS[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// S-Boxes
int S_BOX[8][4][16] = {
    // S1
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    // S2
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    // S3
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    // S4
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    // S5
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    // S6
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    // S7
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    // S8
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

// =================================================================
// 2. HELPER FUNCTIONS
// =================================================================

// Converts hexadecimal input to an array of bits (0 or 1)
void hex_to_bits(char *hex, int *bits)
{
    for (int i = 0; i < 16; i++)
    {
        int val;
        if (hex[i] >= '0' && hex[i] <= '9')
            val = hex[i] - '0';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            val = hex[i] - 'A' + 10;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            val = hex[i] - 'a' + 10;
        else
            val = 0; // Fallback

        for (int j = 0; j < 4; j++)
        {
            bits[i * 4 + (3 - j)] = (val >> j) & 1;
        }
    }
}

// Converts array of bits to hexadecimal output
void bits_to_hex(int *bits, int n)
{
    for (int i = 0; i < n / 4; i++)
    {
        int val = 0;
        for (int j = 0; j < 4; j++)
        {
            val = (val << 1) | bits[i * 4 + j];
        }
        printf("%X", val);
    }
    printf("\n");
}

// Generic Permutation Function
void permute(int *input, int *output, int *table, int n)
{
    for (int i = 0; i < n; i++)
    {
        output[i] = input[table[i] - 1];
    }
}

// Left Circular Shift for Key Schedule
void left_shift(int *bits, int n, int shifts)
{
    int temp[28];
    for (int i = 0; i < shifts; i++)
    {
        temp[i] = bits[i];
    }
    for (int i = 0; i < n - shifts; i++)
    {
        bits[i] = bits[i + shifts];
    }
    for (int i = 0; i < shifts; i++)
    {
        bits[n - shifts + i] = temp[i];
    }
}

// XOR two bit arrays
void xor_func(int *a, int *b, int *out, int n)
{
    for (int i = 0; i < n; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

// =================================================================
// 3. ARCHITECTURE MODULES
// =================================================================

// --- KEY SCHEDULE MODULE ---
void generate_subkeys(int *key_64, int subkeys[16][48])
{
    int key_56[56];
    int C[28], D[28];

    permute(key_64, key_56, PC1, 56);

    for (int i = 0; i < 28; i++)
        C[i] = key_56[i];
    for (int i = 0; i < 28; i++)
        D[i] = key_56[i + 28];

    for (int round = 0; round < 16; round++)
    {
        left_shift(C, 28, SHIFTS[round]);
        left_shift(D, 28, SHIFTS[round]);

        int combined[56];
        for (int i = 0; i < 28; i++)
            combined[i] = C[i];
        for (int i = 0; i < 28; i++)
            combined[i + 28] = D[i];

        permute(combined, subkeys[round], PC2, 48);
    }
}

// --- ROUND FUNCTION ---
void feistel_function(int *right_half, int *round_key, int *output_32)
{
    int expanded_R[48];
    int xored_R[48];
    int sbox_output[32];

    // 1. Expansion Permutation (32 -> 48)
    permute(right_half, expanded_R, E, 48);

    // 2. XOR with Round Key
    xor_func(expanded_R, round_key, xored_R, 48);

    // 3. S-Boxes
    for (int i = 0; i < 8; i++)
    {
        int row = (xored_R[i * 6] << 1) + xored_R[i * 6 + 5];
        int col = (xored_R[i * 6 + 1] << 3) + (xored_R[i * 6 + 2] << 2) +
                  (xored_R[i * 6 + 3] << 1) + xored_R[i * 6 + 4];

        int val = S_BOX[i][row][col];

        for (int j = 0; j < 4; j++)
        {
            sbox_output[i * 4 + (3 - j)] = (val >> j) & 1;
        }
    }

    // 4. P-Box Transposition
    permute(sbox_output, output_32, P, 32);
}

// --- MAIN ENCRYPTION LOGIC ---
void des_encrypt(int *plaintext, int *key)
{
    int subkeys[16][48];
    int data[64];
    int L[32], R[32], temp_R[32];
    int f_result[32];

    // 1. Generate Subkeys
    generate_subkeys(key, subkeys);

    // 2. Initial Permutation
    permute(plaintext, data, IP, 64);

    // Split into Left and Right
    for (int i = 0; i < 32; i++)
        L[i] = data[i];
    for (int i = 0; i < 32; i++)
        R[i] = data[i + 32];

    printf("\n[DEBUG] After Initial Permutation:\n");
    printf("L0: ");
    bits_to_hex(L, 32);
    printf("R0: ");
    bits_to_hex(R, 32);
    printf("----------------------------------------\n");

    // 3. 16 Rounds
    for (int i = 0; i < 16; i++)
    {
        for (int k = 0; k < 32; k++)
            temp_R[k] = R[k];

        // Feistel Function
        feistel_function(R, subkeys[i], f_result);

        // XOR Left with Result -> New Right
        xor_func(L, f_result, R, 32);

        // New Left = Old Right
        for (int k = 0; k < 32; k++)
            L[k] = temp_R[k];

        printf("Round %02d | L: ", i + 1);
        bits_to_hex(L, 32);
        printf("         | R: ");
        bits_to_hex(R, 32);
    }

    // 4. 32-bit Swap (Output is R16 L16)
    int combined[64];
    for (int i = 0; i < 32; i++)
        combined[i] = R[i];
    for (int i = 0; i < 32; i++)
        combined[i + 32] = L[i];

    // 5. Inverse Initial Permutation
    int ciphertext[64];
    permute(combined, ciphertext, IP_INV, 64);

    printf("\n========================================\n");
    printf("FINAL CIPHERTEXT: ");
    bits_to_hex(ciphertext, 64);
    printf("========================================\n");
}

// =================================================================
// 4. MAIN (DYNAMIC INPUT)
// =================================================================
int main()
{
    char pt_hex[17];
    char key_hex[17];
    int plaintext[64];
    int key[64];

    printf("=== DES Encryption Program ===\n");

    // Get Plaintext
    while (1)
    {
        printf("Enter 64-bit Plaintext (16 Hex characters): ");
        if (scanf("%16s", pt_hex) != 1)
            return 1;
        if (strlen(pt_hex) != 16)
        {
            printf("Error: Please enter exactly 16 hex characters.\n");
        }
        else
        {
            break;
        }
    }

    // Get Key
    while (1)
    {
        printf("Enter 64-bit Key       (16 Hex characters): ");
        if (scanf("%16s", key_hex) != 1)
            return 1;
        if (strlen(key_hex) != 16)
        {
            printf("Error: Please enter exactly 16 hex characters.\n");
        }
        else
        {
            break;
        }
    }

    // Parse Input
    hex_to_bits(pt_hex, plaintext);
    hex_to_bits(key_hex, key);

    printf("\nProcessing...\n");

    // Run DES
    des_encrypt(plaintext, key);

    return 0;
}