// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int bucket = 60000;

// Hash table
node *table[bucket];

// Word Counter for size function
int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hashes the word
    int hash_index = hash(word);
    // Declare a new node variable called cursor to traverse the list
    node *cursor = table[hash_index];
    // Read through the words and compare them
    while (cursor != NULL)
    {
        // Use strcasecmp to ensure check function is not case sensitive. If same, return true, afterwards, move cursor to next word.
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
// With reference to DJB2. Link - http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    // Returns hash value as modulus to return smaller value within N.
    return hash % bucket;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Creating an array of characters (string) to store from dictionary
    char storeWord[LENGTH + 1];

    // Opening dictionary file in "read" mode
    FILE *dictionaries = fopen(dictionary, "r");

    // If dictionary file does not exist, return false.
    if (dictionaries == NULL)
    {
        return false;
    }

    // Creating an empty table
    for (int i = 0; i < bucket; i++)
    {
        table[i] = NULL;
    }

    // Scan the dictionary files for strings, and storing these strings into character array storeWord, until end-of-file.
    while (fscanf(dictionaries, "%s\n", storeWord) != EOF)
    {
        // Allocating memory to n with the size of a node.
        node *new_word = malloc(sizeof(node));

        // If 'n' cannot be found, return 1.
        if (new_word == NULL)
        {
            return false;
        }

        // Copy string from storeWord into the node
        strcpy(new_word -> word, storeWord);

        // Allocating hash value of a string into an index
        int hash_index = hash(new_word -> word);

        if (table[hash_index] == NULL)
        {
            // If table[hash_index] does not have an indexed word, insert the word into it.
            table[hash_index] = new_word;
            // Pointer of next node points to null.
            new_word -> next = NULL;
        }
        else
        {
            // "Next" points to the index of the word in the hash table
            new_word -> next = table[hash_index];
            // Insert the word into the hash
            table[hash_index] = new_word;
        }

        // Increment word count.
        word_count++;
    }

    // Close dictionary after reading
    fclose(dictionaries);

    // Return true if able to read
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int size = word_count;
    return size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loops through the buckets
    for (int i = 0; i < bucket; i++)
    {
        // Cursor is initially pointing at the head of the linked list
        node *cursor = table[i];
        // Cursor will point until it reaches null (No more words found).
        while (cursor != NULL)
        {
            // Add temporary cursor to point, and primary cursor to proceed to next word.
            node *temp = cursor;
            cursor = cursor -> next;
            // Free the temporary cursor
            free(temp);
        }
    }
    return true;
}
