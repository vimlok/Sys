#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 5000
#define BYTE 8
#define MAX_VALUE_BYTE 255
/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/
int take_photo(unsigned char out[], int* rows, int* cols);

unsigned char get_bit(unsigned char byte, int bit);
unsigned char set_bit(unsigned char byte, int bit);
unsigned char clear_bit(unsigned char byte, int bit);
void print_raw(unsigned char raw_string[], int rows, int cols);
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]);
void print_packed(unsigned char packed[], int rows, int cols);
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]);
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols);

int main() {

    unsigned char raw_array[MAX_ARR];
    unsigned char packed_array[MAX_ARR];
    unsigned char encoded_array[MAX_ARR];

    int rows;
    int cols;

    int size = take_photo(raw_array, &rows, &cols);

    while (size != 0) {
        printf("Raw photo (%d bytes):\n", size);
        print_raw(raw_array, rows, cols);

        int packed_size = pack_bits(raw_array, size, packed_array);
        printf("\nPacked photo (%d bytes):\n", packed_size);
        print_packed(packed_array, rows, cols);

        int encoded_size = encode_bits(packed_array, packed_size, encoded_array);
        printf("\nEncoded photo (%d bytes):\n", encoded_size);
        print_encoded(encoded_array, encoded_size, rows, cols);

        printf("Sizes: raw = %d bytes, packed = %d bytes, encoded = %d bytes\n", size, packed_size, encoded_size);

        size = take_photo(raw_array, &rows, &cols);
    }
}

void print_raw(unsigned char raw_string[], int rows, int cols) {
    int increment = 0;
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {
            if (raw_string[increment + j] == '1') {
                printf("*");
            }
            else {
                printf(".");
            }
        }

        increment += cols;
        printf("\n");
    }
}

unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}

unsigned char set_bit(unsigned char byte, int bit) {
    return byte | (1 << bit);
}

unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}

int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]) {
    int byte_index = 0;
    int bit_index = 0;

    for (int i = 0; i < num_chars; i++) {
        if (unpacked_string[i] == '1') {
            packed_result[byte_index] = set_bit(packed_result[byte_index], bit_index);
        }
        else {
            packed_result[byte_index] = clear_bit(packed_result[byte_index], bit_index);
        }

        bit_index += 1;

        if (bit_index == BYTE) {
            byte_index += 1;

            bit_index = 0;
        }
    }

    if (bit_index != 0) {
        byte_index += 1;
    }

    return byte_index;
}

void print_packed(unsigned char packed[], int rows, int cols) {
    int increment = 0;
    int size = (rows * cols) / BYTE;

    int bit_cols = 0; // Keeps track of number of bits printed inside a row, in order to print newline

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < BYTE; j++) {
            unsigned char bit_value = get_bit(packed[i], j);

            if (bit_cols == cols) {
                printf("\n");
                bit_cols = 0;
            }

            if (bit_value == 1) {
                printf("*");
                bit_cols += 1;
            }

            if (bit_value == 0) {
                printf(".");
                bit_cols += 1;
            }
        }
    }
    printf("\n");
}

int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]) {
    unsigned char count = 0;
    unsigned char bit_sequence = 1;
    int encoded_index = 0;

    for (int i = 0; i < packed_size; i++) {

        for (int j = 0; j < BYTE; j++) {
            unsigned char bit_value = get_bit(packed[i], j);

            if (bit_value == bit_sequence) {

                if (count == MAX_VALUE_BYTE) {
                    encoded_result[encoded_index] = count;
                    encoded_index += 1;

                    count = 0;
                    bit_sequence = 1 - bit_sequence;
                }

                count += 1;
            }
            else {
                encoded_result[encoded_index] = count;
                encoded_index += 1;

                bit_sequence = 1 - bit_sequence;
                count = 1;
            }
        }
    }

    if (count != 0) {
        encoded_result[encoded_index] = count;
        encoded_index += 1;
    }

    return encoded_index;
}

void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols) {
    int bit_cols = 0;
    unsigned char bit_sequence = 1;

    for (int i = 0; i < encoded_size; i++) {
        unsigned char number_sequence = encoded[i];
        if (number_sequence == 0) {
            bit_sequence = 1 - bit_sequence;
            continue;
        }

        for (int j = 0; j < number_sequence; j++) {
            if (bit_cols == cols) {
                bit_cols = 0;
                printf("\n");
            }

            if (bit_sequence == 1) {
                printf("*");
                bit_cols += 1;
            }
            else {
                printf(".");
                bit_cols += 1;
            }
        }

        bit_sequence = 1 - bit_sequence;
    }
    printf("\n");
}


