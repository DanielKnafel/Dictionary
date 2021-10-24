/***********************
* Daniel Knafel
* 316012624
* Group 01 - CS
* Assignment 6
***********************/
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include "genericSort.h"

// A struct containing 2 integers
typedef struct KeyValuePair
{
	int key, value;
}KeyValuePair;
// the dictionary struct
struct Dictionary
{
	KeyValuePair* keys;
	int keysSize, currentKeys;
};

#define KEY_NOT_FOUND -1

/******************
* Function Name: initDictionary
* Input: None
* Output: Dictionary*
* Function Operation: Initiates a new Dictionary
******************/
Dictionary* initDictionary()
{
	// Allocate memory for a new dictionary
	Dictionary* dictionary = malloc(sizeof(Dictionary));
	if (dictionary == NULL)
		return NULL;

	// Allocate memory for a new array
	dictionary->keys = malloc(sizeof(KeyValuePair));
	if (dictionary->keys == NULL)
		return NULL;

	// Set default values 
	dictionary->keysSize = 1;
	dictionary->currentKeys = 0;

	return dictionary;
}
/******************
* Function Name: destroyDictionary
* Input: Void
* Output: Void
* Function Operation: Frees all memory allocated for a Dictionary
******************/
void destroyDictionary(Dictionary* d)
{
	if (d != NULL)
	{
		if (d->keys != NULL)
			free(d->keys);
		free(d);
	}
}
/******************
* Function Name: sizeOfDictionary
* Input: Dictionary* d
* Output: int
* Function Operation: Returns the amount of entries on a given Dictionary
******************/
int sizeOfDictionary(Dictionary* d)
{
	if (d != NULL)
		return d->currentKeys;
	return 0;
}
/******************
* Function Name: resizeKeysArr
* Input: KeyValuePair* arr, int newSize
* Output: KeyValuePair*
* Function Operation: Resizes a given array to a given size and return a pointer to the new allocation
******************/
KeyValuePair* resizeKeysArr(KeyValuePair* arr, int newSize)
{
	if (arr == NULL)
		return NULL;
	// Allocate a new array
	KeyValuePair* newArr = realloc(arr, sizeof(KeyValuePair) * newSize);
	return newArr;
}
/******************
* Function Name: findKeyinDictionary
* Input: Dictionary* d, int key
* Output: int
* Function Operation: Searches for a given key in a Dictionary and return its mathcing value.
*					  returns 0 if key is not pressent.
******************/
int findKeyinDictionary(Dictionary* d, int key)
{
	if (d == NULL)
		return FAILURE;
	// Search the dictionary for a specific key
	for (int i = 0; i < d->currentKeys; i++)
	{
		// if key was found, return its index in the array
		if (d->keys[i].key == key)
			return i;
	}

	return KEY_NOT_FOUND;
}
/******************
* Function Name: shiftArrLeft
* Input: Dictionary* d, int i
* Output: Result
* Function Operation: Moves all the cells in a given Dictionary to the left, starting from a given index.
******************/
Result shiftArrLeft(Dictionary* d, int i)
{
	/*
	Move each cell in the array to the left, starting from the end, and up to the given index
	there is always a spare cell in the end of the array
	*/
	if (d == NULL)
		return FAILURE;
	for (int j = i; j < d->currentKeys; j++)
		d->keys[j] = d->keys[j + 1];
	return SUCCESS;
}
/******************
* Function Name: putInDictionary
* Input: Dictionary* d, int key, int value
* Output: Result
* Function Operation: Adds a new (key:value) pair to the Dictionary. 
*					  If key already exists, update its value to the new one. Returns SUCCESS/ FAILURE respectively.
******************/
Result putInDictionary(Dictionary* d, int key, int value)
{
	if (d == NULL)
		return FAILURE;
	// check if the key already exists
	int foundPos = findKeyinDictionary(d, key);

	// key does not exists in the dictionary
	if (foundPos == KEY_NOT_FOUND)
	{
		// add the key to the dictionary
		KeyValuePair p = { key, value };
		d->keys[d->currentKeys] = p;
		d->currentKeys++;
	}
	// key exists in the dictionary
	else
	{
		// change the current value of the key to the new one
		d->keys[foundPos].value = value;
		return SUCCESS;
	}
	// if needed, double the size of the array
	if (d->currentKeys >= d->keysSize)
	{
		KeyValuePair* newArr = resizeKeysArr(d->keys, d->keysSize * 2);
		if (newArr == NULL)
			return MEM_ERROR;
		d->keys = newArr;
		d->keysSize *= 2;
	}
	return SUCCESS;
}
/******************
* Function Name: getFromDictionary
* Input: Dictionary* d, int key
* Output: int
* Function Operation: Returns the matching value for a given key from the Dictionary.
*					  If key doesn't exist, returns 0.
******************/
int getFromDictionary(Dictionary* d, int key)
{
	if (d == NULL)
		return 0;
	// find a given key in the dictionary
	int isFound = findKeyinDictionary(d, key);
	if (isFound == KEY_NOT_FOUND)
		return 0;
	return d->keys[isFound].value;
}
/******************
* Function Name: removeFromDictionary
* Input: Dictionary* d, int key
* Output: Result
* Function Operation: Removes a (key:value) pair from the Dictionary, specified by a given key and returns SUCCESS.
*					  If key doesn't exist, returns FAILURE.
******************/
Result removeFromDictionary(Dictionary* d, int key)
{
	if (d == NULL)
		return FAILURE;
	// find a given key in the dictionary
	int foundPos = findKeyinDictionary(d, key);

	if (foundPos == KEY_NOT_FOUND)
		return FAILURE;

	// if the key was found, remove it from the array
	shiftArrLeft(d, foundPos);
	// update the key-count
	d->currentKeys--;

	// if needed, half the size of the array
	if (d->currentKeys <= d->keysSize / 2 && d->keysSize > 1)
	{
		KeyValuePair* p = resizeKeysArr(d->keys, d->keysSize / 2);
		if (p == NULL)
			return MEM_ERROR;
		d->keys = p;
		d->keysSize /= 2;
	}
	return SUCCESS;
}
/******************
* Function Name: compareKeys
* Input: void* arr, int i, int j
* Output: int
* Function Operation: Coampares 2 keys in a dictionary, given by 2 indexes.
*					  returns a possitive numer if the first is bigger, a negative numer if the second is bigger and
*					  0 if they are equal.
******************/
int compareKeys(void* arr, int i, int j)
{
	KeyValuePair* arr2 = (KeyValuePair*)arr;
	return arr2[i].key - arr2[j].key;
}
/******************
* Function Name: swapKeys
* Input: Void
* Output: void* arr, int i, int j
* Function Operation: Swaps 2 keyValuePair indexes in a given array.
******************/
void swapKeys(void* arr, int i, int j)
{
	KeyValuePair* arr2 = (KeyValuePair*)arr;
	KeyValuePair temp = arr2[i];
	arr2[i] = arr2[j];
	arr2[j] = temp;
}
/******************
* Function Name: printDictionary
* Input: Dictionary* d
* Output: Void
* Function Operation: Prints the content in a given Dictionary in ascending-key order
******************/
void printDictionary(Dictionary* d)
{
	// sort the array in ascending-key order
	if (d != NULL)
		sort(d->keys, d->currentKeys, compareKeys, swapKeys);
	else
		return;
	// print each key:value pair
	printf("{");
	for (int i = 0; i < d->currentKeys; i++)
		printf("[%d:%d]", d->keys[i].key, d->keys[i].value);
	printf("}");
}
/******************
* Function Name: createDictionaryFromArrays
* Input: int keys[], int values[], int size
* Output: Dictionary*
* Function Operation: Creates a new dictionary from 2 given arrays of keys and values, and return a pointer to it.
******************/
Dictionary* createDictionaryFromArrays(int keys[], int values[], int size)
{
	int i = 0;
	// initiate a new dictionary
	Dictionary* d = initDictionary();
	if (d == NULL)
		return NULL;
	Result result = SUCCESS;
	// add each key:value pair to the dictionary
	for (i = 0; i < size && result == SUCCESS; i++)
		result = putInDictionary(d, keys[i], values[i]); 
	if (result != SUCCESS)
		printf("An error occurred. Dictionary was not fully created");
	return d;
}
