#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Title: Lab 3
 * Semester: COP4338 - Spring 2021
 * Author Megan Jane Thompson
 * Panther ID: 3276301
 *
 * I affirm that the revisions of this program is entirely
 * my own work and none of it is the work of any other person.
 *
 * This program extracts the flag values from a file and prints it to the display.
 * It also finds the number count of words in the file, finds the number of
 * occurrences of a substring, and takes all words into a String to sort them
 * lexicographically (ASCII order).
 *
 */

int main(int argc, char ** argv){
	extern char *optarg;
	extern int optind;
	int i, j, c, cflag=0, sflag=0, fflag=0, err=0;
	int numWords = 0;
    char *subStr;
    char *fileName;
    char fileConts[1000];
    FILE *fptr;
	static char usage[] = "usage: mywords [-cs] [-f substring] filename\n";

	if(argc < 2){
		printf("Try running the program with some arguments\n\t%sSomething like:\texample -c file1\n\t\texample -c -s file1\n", usage);
		exit(0);
	}
	while ((c = getopt(argc, argv, "csf:")) > 0){
		switch (c) {
		case 'c':
			cflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'f':
			fflag = 1;
			subStr = (char*)calloc(strlen(optarg)+1, sizeof(char));
			strcpy(subStr, optarg);
			strcat(subStr, "\0");
			break;
		case '?':
			err = 1;
			break;
		}
	}


	if (err) {                          //general error
		fprintf(stderr, "%s %s %s", "General Error.", usage, argv[0]);
		exit(1);
	}
	if((fflag == 1) && (subStr == NULL)){
		printf("-f is missing substring\n");
		fprintf(stderr, usage, argv[0]);
	}
	if ((optind+1) > argc) {                 //need filename
		printf("optind = %d, argc=%d\n", optind, argc);
		fprintf(stderr, "%s %s\n", "Missing File Name", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}



	//argument after the command-line options that contains the file name
	if (optind < argc){
		fileName = (char*)calloc(strlen((argv[optind]))+1, sizeof(char));     //gets filename
		strcpy(fileName, argv[optind]);
		fptr = fopen(fileName, "r");
		if (fptr == NULL){
			printf("Error opening %s.", fileName);
			printf(" Please be sure file extension is included.\n");
			exit(0);
		}
		else{
			printf("The contents of %s is: ", fileName);
			fgets(fileConts, 1000, fptr);
			printf("%s", fileConts);
			char fileContsCpy[strlen(fileConts)+1];
			strcpy(fileContsCpy, fileConts);
			char *word = strtok(fileContsCpy, " ");
			while(word != NULL){
				++numWords;
				word = strtok(NULL, " ");
			}
		}
	}
	else {
		printf("No arguments left to process\n");
	}


	//prints out flagged command line options
	if (sflag == 1){           //print out words of file in ASCII order
		char wordArray[numWords+1][50];
		char asciiArray[numWords+1][50];
		char fileContsCpy[strlen(fileConts)+1];
		strcpy(fileContsCpy, fileConts);
		char *word = strtok(fileContsCpy, " ");
		i = 0;
		while(word != NULL && i < numWords){
			strcpy(wordArray[i], word);
			word = strtok(NULL, " ");
			++i;
		}
		char cmp[50];
		char temp[50];
		i = 0;
		while (i < numWords){
			strcpy(cmp, wordArray[i]);
			j = i;
			while (j < numWords){
				if (strcmp(wordArray[j], cmp) < 0){
					strcpy(temp, cmp);
					strcpy(cmp, wordArray[j]);
					strcpy(wordArray[j], temp);
				}
				++j;
			}
			strcpy(asciiArray[i], cmp);
			++i;
		}
		printf("The ASCII order of %s is: ", fileName);
		i = 0;
		while (i < numWords){
			printf("%s ", asciiArray[i]);
			++i;
		}
	}
	if (cflag == 1){           //print out number of words in file
		printf("The total number of words in %s is: %d\n", fileName, numWords);
	}
	if (fflag == 1){           //find number of substring occurrences within file
		int subCount = 0;
		char wordArray[numWords+1][50];
		char fileContsCpy[strlen(fileConts)+1];
		strcpy(fileContsCpy, fileConts);
		char *word = strtok(fileContsCpy, " ");
		i = 0;
		while(word != NULL && i < numWords){
			strcpy(wordArray[i], word);
			word = strtok(NULL, " ");
			++i;
		}
		if (subStr != NULL){
			i = 0;
			while(i < numWords){
				if (strcmp(subStr, wordArray[i]) == 0){
					++subCount;
				}
				++i;
			}
			printf("The number of times the word \"%s\" occurs in %s is %d.\n", subStr, fileName, subCount);
		}
	}
//	free(subStr);
//	free(fileName);
//	free(fileCont);

	exit(0);
}

