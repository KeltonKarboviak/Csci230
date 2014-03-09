/***********************************/
/* CSci 230 HW #6                  */ 
/*                                 */
/* File:   hw6-Karboviak.c         */
/* Author: Kelton Karboviak        */
/***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dCount 10
#define nCount 50

/************************************************************/
/* STRUCTS                                                  */
/************************************************************/
struct contact {
	char fname[20];
	char lname[20];
	int startBlock;
};

struct phoneNumber {
	char number[7];
	int nextBlock;
};


/************************************************************/
/* FUNCTIONS                                                */
/************************************************************/
/****************************************************/
/* Searches the directory for the specified         */
/* contact name                                     */
/*   returns index of match if successful,          */
/*           -1 if unsuccessful                     */
/****************************************************/
int Search_Contacts(char *fname, char *lname, struct contact *directory) {
	int i;
	for (i = 0; i < dCount; i++) {
		if (!strcmp(fname, directory[i].fname) && !strcmp(lname, directory[i].lname))
			return i;
	}

	return -1;
}


/****************************************************/
/* Removes the specified contact from the directory */
/* if it is in the list.                            */
/*   returns 0 if successful, -1 if unsuccessful    */
/****************************************************/
int Remove_Contact() {


	return 0;
}


/****************************************************/
/* Adds the specified contact to the directory      */
/* if it is not in the list.                        */
/*   returns 0 if successful, -1 if unsuccessful    */
/****************************************************/
int Add_Contact(char *fname, char *lname, int N, char **numbers,
                struct contact *directory, struct phoneNumber *number_list) {
    // Search contacts to get the index of the name in the directory
	int index = Search_Contacts(fname, lname, directory);
	if (index != -1)  return -1;  // Contact already exists in the directory
	
	// Search directory for an empty index
	int i, emptyIndex;
	for (i = 0; i < dCount; i++) {
		if (directory[i].startBlock == -1) {
			emptyIndex = i;
			break;
		}
	}
	
	// Add new contact into directory
	strcpy(directory[emptyIndex].fname, fname);
	strcpy(directory[emptyIndex].lname, lname);
	
	// Search number_list for the new contact's start block
	int currentBlock;
	for (i = 0; i < nCount; i++) {
		if (number_list[i].nextBlock == -1) {
			currentBlock = i;
			break;
		}
	}
	
	// Add new contact's start block
	directory[emptyIndex].startBlock = currentBlock;
	
	// Add new contact's phone numbers into number_list
	for (i = 0; i < N; i++) {
		
	}

	return 0;
}


/************************************************************/
/* MAIN                                                     */
/************************************************************/
int main(void) {
	// Open file for reading
	char fileName[] = "./hw6data.txt";
	FILE *inFile;
	inFile = fopen(fileName, "r");
	// Trap file open error
	if (inFile == NULL) {
		printf("\nUnable to open file: %s\n\n", fileName);
		exit (0);
	}

	// Create struct arrays
	struct contact     DIRECTORY[dCount];    // Array of contact structs
	struct phoneNumber NUMBER_LIST[nCount];  // Array of phoneNumber structs


	int i;
	// Initialize DIRECTORY with -1 (indicates free block)
	for (i = 0; i < dCount; i++) {
		DIRECTORY[i].startBlock = -1;
	}

	// Initialize NUMBER_LIST with -1 (indicates free block)
	for (i = 0; i < nCount; i++) {
		NUMBER_LIST[i].nextBlock = -1;
	}

	// Check inFile contents
	char status, fname[20], lname[20];
	char **temp;  // Temporary dynamic array to hold multiple numbers as strings
	int N;        // number of phone numbers for 1 contact
	do {
		fscanf(inFile, "%c", &status);

		if (status == 'I') {        // Add a contact
			fscanf(inFile, "%s %s %d", fname, lname, &N);
			// Create 2D dynamic char array for phone numbers as strings
			temp = (char**) calloc(N, sizeof(*temp));        // Creates a column of pointers
			for (i = 0; i < N; i++) {
				temp[i] = (char*) calloc(7, sizeof(char));  // Create a row of chars
			}

			// Store N numbers in dynamic array
			for (i = 0; i < N; i++) {
				fscanf(inFile, "%s", temp[i]);
			}
			for (i = 0; i < N; i++) {    // TEST TEST TEST
				printf("%s\n", temp[i]);
			}

			Add_Contact(fname, lname, N, temp, DIRECTORY, NUMBER_LIST);
		}
		else if (status == 'R') {  // Remove a contact

		}

	} while (status != 'Q');

	printf("\nDONE !!!\n");

	fclose(inFile);
	return 0;
}