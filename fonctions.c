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
	// printf("exp = %s\n", expan);
	return expan;
}

char* permutation(int P[], char* chiffrerBin, int tailleSortie)
{
	int taille = tailleSortie;
	char* chiffrerPermuter = NULL;
	chiffrerPermuter = malloc(taille * sizeof(char) + sizeof(char));
	chiffrerPermuter[taille] = '\0';
	if (chiffrerPermuter == NULL)
	{
		exit(2);
	}
	for(int i = 0; i < taille; i++)
	{
		chiffrerPermuter[i] = chiffrerBin[ P[i] - 1];
	}
	return chiffrerPermuter;
}

int* binToDecimal(char* bin, int nbBits)
{
	int T = 0;
	int k = 0;
	int i = 0;
	int taille = strlen(bin);
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
		tmp = puissance(2, nbBits - 1);
		val = 0;
	}
	return decimals;
}

char* hexaToBin(unsigned long long hexadecimal, int tailleSortie)
{
	char* bits = NULL;
	bits = malloc(tailleSortie * sizeof(char) + sizeof(char));
	if(bits == NULL)
	{
		exit(2);
	}
	bits[tailleSortie] = '\0';

	unsigned long long mask = 1;
	mask = (mask << (tailleSortie - 1));
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
	// printf("tailleSortie %d\n", tt);
	return bits;
}

void get_R16_L16(int IPInv[], unsigned long long chiffrer, unsigned long long* R16, unsigned long long* L16)
{
	char* chiffrerPermuter = NULL;
	char* chiffrerBin = NULL;
	int* decimals = NULL;
	int tmp = 0;
	int dec = 4;
	chiffrerBin = hexaToBin(chiffrer, 64);
	chiffrerPermuter = permutation(IPInv, chiffrerBin, 64);
	decimals = binToDecimal(chiffrerPermuter, dec);
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

unsigned long long binToHexa(char* binaire, int tailleSortie)
{
	int taille = tailleSortie;
	int tailleHexa = taille / 4;
	int dec = 4;
	int* decimals = NULL;
	unsigned long long hexa;
	decimals = binToDecimal(binaire, dec);
	hexa = decimals[0];
	for(int i = 1; i < tailleHexa; i++)
	{
		hexa = hexa << dec;
		hexa = hexa | decimals[i];
	}
	free(decimals);
	return hexa;
}

int posiBitFauter(unsigned long long hexadecimal, int nbBits)
{
	unsigned long long tmpHexa = hexadecimal;
	int position = nbBits+1;
	// int position = -1;
	while(tmpHexa)
	{
		position--;
		tmpHexa = tmpHexa >> 1;
	}
	// printf("posi = %d\n", position);
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

int appliquer(int SBox[][4][16], int expanVal, int numSBox)
{
	// printf("dans appliquer\n");
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
	c = c >> 1;

	return SBox[numSBox][r][c];
}

// int maximum(int tableau[], int taille)
// {
// 	int max = tableau[0];
// 	for(int i = 1; i < taille; i++)
// 	{
// 		if (max < tableau[i])
// 		{
// 			max = i;
// 		}
// 	}
// 	return max;
// }

unsigned long long construreCleK16(int tableau[][65], int nbSBox)
{
	printf("construire\n");
	unsigned long long K16;
	// K16 = maximum(tableau[0], 65);
	// for (int i = 0; i < 8; ++i)
	// {
	// 	for (int j = 0; j < 65; ++j)
	// 	{
	// 		printf("%d ", j);
	// 	}printf("\n");
	// }

	int max = -1;
	for(int k = 0; k < 65; k++)
	{
		if(tableau[0][k] == 6)
			{
				max = k;
			}
	}
	K16 = max;
	printf("%d ", max);
	for(int i = 1; i < nbSBox; i++)
	{
		max = -1;
		for (int j = 0; j < 65; j++)
		{
			if(tableau[i][j] == 6)
			{
				max = j;
				// printf("%d ", max);
			}
		}printf("%d ", max);
		K16 = K16 << 6;
		K16 = K16 | max;
	}printf("\n");

	return K16;
}

char* cleKEffIncomp(int PC2Inv[], unsigned long long cleK16)
{
	// unsigned long long res = 0;
	char* cleK16Bin = NULL;
	char* cleEff = NULL;
	int taille = 56;
	cleK16Bin = hexaToBin(cleK16, 48);
	cleEff = malloc(taille * sizeof(char) + sizeof(char));
	if(cleEff == NULL)
	{
		exit(2);

	}
	cleEff[taille] = '\0';
	for(int i = 0; i < taille; i++)
	{
		/*if(i == 9 || i == 18 || i == 22 || i == 25 || i == 35 || i == 38 || i == 43 || i == 54)*/
		if(PC2Inv[i] == 0)
		{
			cleEff[i] = 'X';
		}
		else
		{
			cleEff[i] = cleK16Bin[ PC2Inv[i] -1 ];
		}
		
	}
	// printf("cleEff = %s \n", cleEff);
	// res = binToHexa56(cleEff);
	free(cleK16Bin);
	// free(cleEff);
	return cleEff;
}

char* cleKIncomp(int PC1Inv[], char* cleKEffIncompl)
{
	// unsigned long long res = 0;
	char* cleK = NULL;
	// char* cleKEffInBin = NULL;
	int taille = 64;
	// cleKEffInBin = hexaToBin(cleKEffIncomp, 56);
	cleK = malloc(taille * sizeof(char) + sizeof(char));
	if(cleK == NULL)
	{
		exit(2);
	}
	cleK[taille] = '\0';
	for(int i = 0; i < taille; i++)
	{
		if( (i + 1) % 8 == 0 )
		{
			cleK[i] = 'P';
		}
		else
		{
			cleK[i] = cleKEffIncompl[ PC1Inv[i] - 1 ];
		}
		
	}
	return cleK;

}

int* getBitInconnu(char* cleKIncompl)
{
	int tailleCle = strlen(cleKIncompl);
	int tailleIncon = 8; // 8 bit inconnu
	int j = 0;
	int* inconnu = NULL;
	inconnu = malloc(tailleIncon * sizeof(int));
	for(int i = 0; i < tailleCle; i++)
	{
		if(cleKIncompl[i] == 'X')
		{
			inconnu[j++] = i;
			printf("%d ", i+1);
		}
	}printf("\n j = %d", j);
	return inconnu;
}

char* getCle(char* cleKIncompl, int* bitInconnu, int k)
{
	int taille = strlen(cleKIncompl);
	int tailleInconnu = 8;
	int mask = 1;
	mask = mask << 7;
	char* cleTmp = NULL;
	cleTmp = malloc(taille * sizeof(char) + sizeof(char));
	if (cleTmp == NULL)
	{
		exit(2);
	}
	cleTmp[taille] = '\0';
	strcpy(cleTmp, cleKIncompl);

	for (int i = 0; i < tailleInconnu; i++)
	{
		if ( k & mask )
		{
			cleTmp[ bitInconnu[i] ] = '1';
		}
		else
		{
			cleTmp[ bitInconnu[i] ] = '0';
		}
		mask = mask >> 1;
	}
	return cleTmp;
}

void decalageG(char* CD, int dec)
{
	int taille = strlen(CD);
	taille = taille / 2;
	int tmpC = 0;
	int tmpD = 0;
	for(int i = 0; i < dec; i++)
	{
		tmpC = CD[0];
		tmpD = CD[taille];
		for(int j = 0; j < taille-1; j++)
		{
			
			CD[j] = CD[j+1];
			CD[j+taille] = CD[j+taille+1];
		}
		CD[taille-1] = tmpC;
		CD[2*taille - 1] = tmpD;
	}
}

unsigned long long fonctionF(int P[], int E[], int SBox[][4][16], unsigned long long Ri, char* Ki)
{
	char* RiBinaire = NULL;
	char* RiExpan = NULL;
	int* RiExpanDecim = NULL;
	int* KiDecim = NULL;
	char* resFBin = NULL;
	char* resPerm = NULL;
	int nbSBox = 8;
	int resSDecim[ 8 ] = {-1};
	unsigned long long resF;
	int dec = 4;
	int tmp = 0;
	RiBinaire = hexaToBin(Ri, 32);
	RiExpan = expansion(E, RiBinaire);
	RiExpanDecim = binToDecimal(RiExpan, 6);
	KiDecim = binToDecimal(Ki, 6);
	for(int i = 0; i < nbSBox; i++)
	{
		resSDecim[i] = appliquer(SBox, (RiExpanDecim[i] ^ KiDecim[i]), i);
	}
	resF = resSDecim[0];
	for (int i = 1; i < nbSBox; i++)
	{
		resF = resF << dec;
		tmp = resSDecim[i];
		resF = resF | tmp;
	}
	resFBin = hexaToBin(resF, 32);
	resPerm = permutation(P, resFBin, 32);
	resF = binToHexa(resPerm, 32);
	free(RiBinaire);
	free(RiExpan);
	free(RiExpanDecim);
	free(KiDecim);
	free(resFBin);
	free(resPerm);
	return resF;
}

unsigned long long ajoutBitParite(char* cleK)
{
	int taille = strlen(cleK);
	int parite = 0;
	unsigned long long cleComplete;
	char* cleKTmp = NULL;
	cleKTmp = malloc(taille * sizeof(char) + sizeof(char));
	if(cleKTmp == NULL)
	{
		exit(2);
	}
	cleKTmp[taille] = '\0';
	strcpy(cleKTmp, cleK);
	for (int i = 0; i < taille; i++)
	{
		if(cleKTmp[i] == '1')
		{
			parite++;
		}
		if(cleKTmp[i] == 'P')
		{
			if(parite % 2 == 0)
			{
				cleKTmp[i] = '1';
			}
			else
			{
				cleKTmp[i] = '0';
			}
			parite = 0;
		}
	}
	cleComplete = binToHexa(cleKTmp, 64);
	printf("%s\n", cleKTmp);
	free(cleKTmp);
	return cleComplete;
}


// 101010 110101 010011 000110 000110 111111 000111 011101
// AB54C61BF1DD
// ab54c61bf1dd
// cleEff = 1010 0101 0110 1100 0011 0000 0101 0101 1101 1001 0100 1011 0110 1001
// A56C3055D94B69