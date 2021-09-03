/**
 * ciphersaber.c
 *
 * CS50 AP
 * Author: Aidan Nagao
 * anagao18@punahou.edu
 *
 * Description: Encrypts and decrypts messages using a key
 *
 * Usage: ./ciphersaber <key>
 * 
 */
 
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// globally declared arrays and variables
unsigned char state[256];
unsigned char key[256];
unsigned char message[256];
unsigned char output[256];
int hextable[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70};
bool convert = false;
int k = 0;

// necessary functions
void setup(int keylength);
void cipher(int msglength);

int main(int argc, string argv[])
{
    // if the user doesn't input a key and a message, returns
    // a usage message.
    if (argc != 2)
    {
        printf("Usage: ./ciphersaber <key>.\n");
        return 1;
    }
    // takes users message, or asks for 'decrypt' if the user wants
    // to decrypt a message
    printf("Please type your message (or 'decrypt' to decrypt a message.\n");
    string initmessage = GetString();
    for (int i = 0; i < strlen(initmessage); i++)
    {
        message[i] = initmessage[i];
        printf("\n%i", message[i]);
    }
    // checks if the user inputted 'decrypt'
    int decrypt = strcmp(initmessage, "decrypt");
    if (decrypt == 0)
    {
        int holder;
        // asks for encrypted message
        printf("Encrypted Message: ");
        initmessage = GetString();
        // converts the string message into individual values
        for (int i = 0; i < strlen(initmessage); i++)
        {
            message[i] = initmessage[i];
        }
        // converts the hexadecimal string into decimal values
        for (int i = 0; i < strlen(initmessage); i++)
        {
            for (int j = 0; j < 16; j++)
            {
                if (message[i] == hextable[j])
                {
                    // if the char is the first digit of the two-digit
                    // hexadecimal value multilpy its value by 16
                    if (i % 2 == 0)
                    {
                        holder = j * 16;
                    }
                    // if the char is the second digit of the two-digit
                    // hexadecimal value add its value to the holder's value
                    else
                    {
                        message[k] = holder + j;
                        printf("\n|%i", message[k]);
                        k++;
                    }
                }
            }
        }
        convert = true;
    }
    // assigning each element of the key array
    int keylength = strlen(argv[1]);
    // adding the rest of the key to the key array
    for (int i = 0; i < keylength; i++)
    {
        key[i] = argv[1][i];
    }
    // setup the state array
    setup(keylength);
    // ciphering the message inputted
    int msglength = strlen(initmessage);
    cipher(msglength);
}

/**
 * sets up the state array before the ciphering process begins
 */
void setup(int keylength)
{
    int j = 0;
    int holder;
    // initial setup of "state" array.
    for (int i = 0; i < 256; i++)
    {
        state[i] = i;
    }
    // shuffling of "state" array.
    for (int i = 0; i < 256; i++)
    {
        j = (j + state[i] + key[i % keylength]) % 256;
        // swap the ith and jth elements of the state array
        holder = state[i];
        state[i] = state[j];
        state[j] = holder;
    }
}

/**
 * Enciphers or deciphers the message or hexadecimal that the user
 * inputs into the program. This function outputs hexadecimal if the
 * user inputted strings. Or outputs strings if the 
 * user inputted hexadecimal.
 */
void cipher(msglength)
{
    int j = 0;
    int holder;
    int combo;
    int hex;
    if (convert == false)
    {
        printf("\nString: ");
        for (int i = 1; i <= msglength; i++)
        {
            j = (j + state[i]) % 256;
            // swap the ith and jth elements of the state array
            holder = state[i];
            state[i] = state[j];
            state[j] = holder;
            // add ith and jth elements of state array to make "combo"
            combo = (state[i] + state[j]) % 256;
            // XOR the state and message bytes
            output[i - 1] = state[combo] ^ message[i - 1];
        }
        printf("\nHexadecimal: ");
        // prints out the encrypted hexadecimal value
        for (int i = 0; i < msglength; i++)
        {
            hex = (output[i] % 256) / 16;
            if (hex > 9)
            {
                if (hex == 10)
                {
                    printf("A");
                }
                if (hex == 11)
                {
                    printf("B");
                }
                if (hex == 12)
                {
                    printf("C");
                }
                if (hex == 13)
                {
                    printf("D");
                }
                if (hex == 14)
                {
                    printf("E");
                }
                if (hex == 15)
                {
                    printf("F");
                }
            }
            else
            {
                printf("%i", hex);
            }
            hex = (output[i] % 256) % 16;
            if (hex > 9)
            {
                if (hex == 10)
                {
                    printf("A");
                }
                if (hex == 11)
                {
                    printf("B");
                }
                if (hex == 12)
                {
                    printf("C");
                }
                if (hex == 13)
                {
                    printf("D");
                }
                if (hex == 14)
                {
                    printf("E");
                }
                if (hex == 15)
                {
                    printf("F");
                }
            }
            else
            {
                printf("%i", hex);
            }
        }
        printf("\n");
    }
    // if the user is decrypting, only print out the string
    else
    {
        printf("\nString: ");
        for (int i = 1; i <= (msglength / 2); i++)
        {
            j = (j + state[i]) % 256;
            // swap the ith and jth elements of the state array
            holder = state[i];
            state[i] = state[j];
            state[j] = holder;
            // add ith and jth elements of state array to make "combo"
            combo = (state[i] + state[j]) % 256;
            // XOR with the state and message bytes
            output[i - 1] = (state[combo] ^ message[i - 1]) % 256;
            printf("%c ", output[i - 1]);
        }
        printf("\n");
    }
}