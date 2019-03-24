#include "keySchedule.h"
// #include "definitions.h"
#include "fonctions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* keySchedule(int PC2[], char* cleK, char* CD, int ki)
{
	int taille = strlen(cleK);
	int dec = 0;
	// char* CD = NULL;
	char* cleKi = NULL;
	char* resCleKi = NULL;
	resCleKi = malloc(taille * sizeof(char) + sizeof(char));
	if(resCleKi == NULL)
	{
		exit(2);
	}
	resCleKi[taille] = '\0';
	// int taille = 2*28;
	// int tours = 16;
	// int CD[taille];
	// for(int i = 0; i < taille; i++)
	// {
	// 	CD[i] = PC1[1];
	// }
	// CD = permutationCle(PC1, cleK);

	if(ki == 1 || ki == 2 || ki == 9 || ki == 16)
	{
		dec = 1;
		decalageG(CD, dec);
		cleKi = permutationCle(PC2, CD);
	}
	else
	{
		dec = 2;
		decalageG(CD, dec);
		cleKi = permutationCle(PC2, CD);
	}
	strcpy(resCleKi, cleKi);
	// printf("k_%d = %s\n",ki, resCleKi);
	free(cleKi);
	return resCleKi;
}


// 11110111X11001010X100X00X111010111X10X0111X0100101101X01
// 1101001P10001XXP11XX111P0001011P1001111P1111000P11X10X1P1X0X100P
// 1101001P1000100P1100111P0001011P1001111P1111000P1101001P1001100P
// 1101001110001001110011100001011010011110111100011101001110011000
// D389CE169EF1D398