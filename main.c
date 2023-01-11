#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "caesar.h"

int main(int argc, char* argv[]){
   /******Code I wrote to test the cipher******

    int num = 4;
    char string[]= {"Beware the ides of march!"};
    char newString[26];

    for(int i=0; i<strlen(string); i++){
        char preCaesar = string[i];
        char postCaesar = caesar(preCaesar, num);

        newString[i] = postCaesar;
        printf("%c", newString[i]);
    }

    *********************************************/

    //array to hold input data
    char temp[strlen(argv[1])];

	//changing char to int
	int shift = atoi(argv[3]);
    
	//handing files
    FILE *input = fopen(argv[1], "r");

    FILE *output = fopen(argv[2], "w");

    //checking cases causing errors
    if(argc != 4){
        fprintf(stderr, "Too few arguments.");
        return 1;
    }
    else if(argv[1] == 0 || argv[2] == 0){
        fprintf(stderr, "File could not open.");
        return 1;
    }
	else if(shift == 0){
		fprintf(stderr, "Offset must be a positive or negitive integer [-25,-1] and [1,25]");
		return 1;
	}
    else if(shift < -25 || shift > 25){
        fprintf(stderr, "Offset out of bounds.");
        return 1;
    }
	
    
    //reading file
    while(!feof(input)){

        fgets(temp, strlen(argv[1]), input);

        for(int i=0; i<strlen(temp); i++){
            char preCaesar = temp[i];
            char postCaesar = caesar(preCaesar, shift);

			//checking for punctuation or spaces
			if((preCaesar >= 32 && preCaesar <= 64) || (preCaesar >= 91 && preCaesar <= 96) || (preCaesar >= 123 && preCaesar <= 126)){
				fputc(preCaesar, output);
			}

			//making sure swapped letters stay letters
            if((postCaesar <= 90 && postCaesar >= 65) || (postCaesar >= 97 && postCaesar <= 122)){
                fputc(postCaesar, output);
            }
            else if(postCaesar < 65 && (preCaesar >= 65 && preCaesar <= 90)){
                int adj = postCaesar + 26;
                fputc(adj, output);
            }
            else if(postCaesar < 97 && (preCaesar >= 97 && preCaesar <= 122)){
                int adj = postCaesar + 26;
                fputc(adj, output);
            }
            else if(postCaesar > 90 && (preCaesar >= 65 && preCaesar <= 90)){
                int adj = postCaesar - 26;
                fputc(adj, output);
            }
            else if(postCaesar > 122 && (preCaesar >= 97 && preCaesar <= 122)){
                int adj = postCaesar -26;
                fputc(adj, output);
            }
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}