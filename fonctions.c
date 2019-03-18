#include "fonctions.h"
// #include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* expansion(int E[], char* binaire)
{
	int taille = (strlen(binaire) * 2) - 16; // 48 bits
	char* expan = NULL;
	expan = malloc(taille * sizeof(char) + sizeof(char));
	expan[taille] = '\0';
	if(expan == NULL)
	{
		exit(2);
	}
	for(int i = 0; i < taille; i++)
	{
		expan[i] = binaire[E[i] - 1];
	}
	return expan;
}

char* permutation(int P[], char* chiffrerBin)
{
	int taille = strlen(chiffrerBin);
	char* chiffrerPermuter = NULL;
	chiffrerPermuter = malloc(taille * sizeof(char) + sizeof(char));
	chiffrerPermuter[taille] = '\0';
	if (chiffrerPermuter == NULL)
	{
		exit(2);
	}
	for(int i = 0; i < taille; i++)
	{
		chiffrerPermuter[i] = chiffrerBin[P[i] - 1];
	}
	return chiffrerPermuter;
}

int* binToDecimal(char* bin, int taille, int nbBits)
{
	int T = 0;
	int k = 0;
	int i = 0;
	int* decimals = NULL;
	int val = 0;
	int tmp = puissance(2, nbBits - 1);
	T = taille / nbBits;
	// printf("T = %d\n", T);
	decimals =  malloc(T * sizeof(int));
	if(decimals == NULL)
	{
		exit(2);
	}
	// printf("taille de decimals = %d\n", T);
	while(i <= taille - nbBits)
	{
		for(int j = i; j < i + nbBits; j++)
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
		i += nbBits;
		tmp = 8;
		val = 0;
	}
	// printf("taille de decimals = %d\n", T);
	// printf("okkkkkkkkkkkkkkkkkkkkkkk\n");
	// for (int t = 0; t < T; t++)
	// {
	// 	printf("%d ", decimals[t]);
	// }printf("\n");
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
	bits[taille] = '\0';

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
	}
	// int tt = strlen(bits);
	// printf("taille %d\n", tt);
	return bits;
}

char* bin32(unsigned long hexadecimal)
{
	int taille = 8 * 4; // chaque val haxadecimal est sur 4 bit. on a 8 val
	char* bits = NULL;
	bits = malloc(taille * sizeof(char) + sizeof(char));
	if(bits == NULL)
	{
		exit(2);
	}
	bits[taille] = '\0';

	unsigned long long mask = 1;
	mask = (mask << 31);
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
	}
	// int tt = strlen(bits);
	// printf("taille %d\n", tt);
	return bits;
}

void get_R16_L16(int permutations[], unsigned long long chiffrer, unsigned long* R16, unsigned long* L16)
{
	char* chiffrerPermuter = NULL;
	char* chiffrerBin = NULL;
	int* decimals = NULL;
	int taille = 0;
	int tmp = 0;
	int dec = 4;
	// unsigned long long mask = (1 << 31);
	chiffrerBin = bin64(chiffrer);
	// printf("ici ici ici ici \n");
	chiffrerPermuter = permutation(permutations, chiffrerBin);
	// printf("okkkkkk   kkkkk\n");
	// printf("%s\n", chiffrerBin);
	// printf("%s\n", chiffrerPermuter);
	taille = strlen(chiffrerPermuter);
	// printf("taille = %d\n", taille);
	decimals = binToDecimal(chiffrerPermuter, taille, dec);
	// for (int t = 0; t < taille/4; t++)
	// {
	// 	printf("%d ", decimals[t]);
	// }printf("\n");
	*R16 = decimals[0];
	for(int i = 1; i < 8; i++)
	{
		*R16 = (*R16) << dec;
		tmp = decimals[i];
		*R16 = (*R16) | tmp;
	}
	*L16 = decimals[8];
	for(int j = 9; j < 16; j++)
	{
		*L16 = (*L16) << dec;
		tmp = decimals[j];
		*L16 = (*L16) | tmp;
	}
	free(chiffrerBin);
	free(chiffrerPermuter);
	free(decimals);
}

unsigned long long binToHexa64(char* binaire)
{
	int taille = 64;
	int tailleHexa = taille / 4;
	int dec = 4;
	int* decimals = NULL;
	unsigned long long hexa;
	decimals = binToDecimal(binaire, taille, dec);
	hexa = decimals[0];
	for(int i = 1; i < tailleHexa; i++)
	{
		hexa = hexa << dec;
		hexa = hexa | decimals[i];
	}
	free(decimals);
	return hexa;
}

unsigned long binToHexa32(char* binaire)
{
	int taille = 32;
	int tailleHexa = taille / 4;
	int dec = 4;
	int* decimals = NULL;
	unsigned long long hexa;
	decimals = binToDecimal(binaire, taille, dec);
	hexa = decimals[0];
	for(int i = 1; i < tailleHexa; i++)
	{
		hexa = hexa << dec;
		hexa = hexa | decimals[i];
	}
	free(decimals);
	return hexa;
}

int posiBitFauter32(unsigned long hexadecimal)
{
	unsigned long tmpHexa = hexadecimal;
	int position = 0;
	// int position = -1;
	while(tmpHexa)
	{
		position++;
		tmpHexa = tmpHexa >> 1;
	}
	printf("posi = %d\n", position);
	return position;
}

int* propaBitFaux(int position)
{
	int taille = 2;
	int* propa = NULL;
	propa = malloc(taille * sizeof(int));
	if(propa == NULL)
	{
		exit(2);
	}
	if(position == 1)
	{
		propa[0] = 0; // s1 et s8
		propa[1] = 7; 
	}
	else if(position % 4 == 0)
	{
		propa[0] = ((position / 4) - 1) % 8; // propa : posi=12 / 4 = 3 - 1 -> 2 donc s[2] 
		propa[1] = (position / 4) % 8; // propa : posi=12 / 4 = 3 -> 2 donc s[3] 
	}
	else if(position % 4 == 1)
	{
		propa[0] = ((position / 4) - 1) % 8;
		propa[1] = (position / 4) % 8; 
	}
	else if(position % 4 == 2)
	{
		propa[0] = (position / 4) % 8;
		propa[1] = -1; 
	}
	else if(position % 4 == 3)
	{
		propa[0] = (position / 4) % 8;
		propa[1] = -1; 
	}
	else
	{
		printf("Erreur !!!!!!!!!\n");
		exit(3);
	}

	return propa;
}

int puissance(int a, int b) // a != 0
{
	if(a == 1 || b == 0)
	{
		return 1;
	}

	return a * puissance(a, b - 1);
}

int appliquer(int SBox[4][16], int expanVal)
{
	// int nbBits = 6;
	int r = -1;
	int c = -1;
	int mask1 = 1;
	int mask2 = 30;
	int b1 = 0;
	int b6 = 0;
	mask1 = mask1 << 5;
	if(expanVal & mask1)
	{
		b1 = 1;
	}
	if(expanVal & 1)
	{
		b6 = 1;
	}
	r = (2 * b1) + b6;
	c = expanVal & mask2;

	return SBox[r][c];
}