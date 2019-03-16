#include "fonctions.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* permutation(int IP[], char* chiffrerBin)
{
	int taille = 64;
	char* chiffrerPermuter = NULL;
	chiffrerPermuter = malloc(taille * sizeof(char) + sizeof(char));
	chiffrerPermuter[taille] = '\0';
	if (chiffrerPermuter == NULL)
	{
		exit(2);
	}
	for(int i = 0; i < taille; i++)
	{
		chiffrerPermuter[i] = chiffrerBin[IP[i] - 1];
	}
	return chiffrerPermuter;
}

int* binToDecimal(char* bin, int taille)
{
	int T = 0;
	int k = 0;
	int i = 0;
	int* decimals = NULL;
	int val = 0;
	int tmp = 8;
	T = taille / 4;
	// printf("T = %d\n", T);
	decimals =  malloc(T * sizeof(int));
	if(decimals == NULL)
	{
		exit(2);
	}
	// printf("taille de decimals = %d\n", T);
	while(i <= taille - 4)
	{
		for(int j = i; j < i+4; j++)
		{
			if(bin[j] == '1')
			{
				val = val + (1 * tmp);
			}
			else
			{
				val = val + (0 * tmp);
			}
			tmp = tmp / 2;
		}
		decimals[k++] = val;
		i+=4;
		tmp = 8;
		val = 0;
	}
	// printf("taille de decimals = %d\n", T);
	// printf("okkkkkkkkkkkkkkkkkkkkkkk\n");
	for (int t = 0; t < T; t++)
	{
		printf("%d ", decimals[t]);
	}printf("\n");
	return decimals;
}

char* bin64(unsigned long long hexadecimal)
{
	int taille = 16 * 4; // chaque val haxadecimal est sur 4 bit. on a 16 val
	char* bits = NULL;
	bits = malloc(taille * sizeof(char) + sizeof(char));
	if(bits == NULL)
	{
		exit(2);
	}
	bits[64] = '\0';

	unsigned long long mask = 1;
	mask = (mask << 63);
	// printf("mask = %llX\n", mask);
	int i = 0;
	while(mask != 0)
	{
		if (hexadecimal & mask)
		{
			bits[i] = '1';
		}
		else
		{
			bits[i] = '0';
		}
		mask = (mask >> 1);
		// printf("mask = %llX\n", mask);
		// printf("%d\n", i);
		i++;
		if (i == 100)
		{
			break;
		}
	}
	// int tt = strlen(bits);
	// printf("taille %d\n", tt);
	return bits;
}

void get_R16_L16(unsigned long long chiffrer, unsigned long* R16, unsigned long* L16)
{
	char* chiffrerPermuter = NULL;
	char* chiffrerBin = NULL;
	int* decimals = NULL;
	int taille = 0;
	int tmp = 0;
	// unsigned long long mask = (1 << 31);
	chiffrerBin = bin64(chiffrer);
	// printf("ici ici ici ici \n");
	chiffrerPermuter = permutation(IP, chiffrerBin);
	// printf("okkkkkk   kkkkk\n");
	printf("%s\n", chiffrerBin);
	printf("%s\n", chiffrerPermuter);
	taille = strlen(chiffrerPermuter);
	// printf("taille = %d\n", taille);
	decimals = binToDecimal(chiffrerPermuter,taille);
	// for (int t = 0; t < taille/4; t++)
	// {
	// 	printf("%d ", decimals[t]);
	// }printf("\n");
	*R16 = decimals[0];
	for(int i = 1; i < 8; i++)
	{
		*R16 = (*R16) << 4;
		tmp = decimals[i];
		*R16 = (*R16) | tmp;
	}
	*L16 = decimals[8];
	for(int j = 9; j < 16; j++)
	{
		*L16 = (*L16) << 4;
		tmp = decimals[j];
		*L16 = (*L16) | tmp;
	}
	free(chiffrerBin);
	free(chiffrerPermuter);
	free(decimals);
}