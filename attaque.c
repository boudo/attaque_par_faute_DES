#include "attaque.h"
#include "fonctions.h"
#include "resultats.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void attaqueBox(int numero[], int expanJuste[], int expanFaux[], int verification[], int valPossibles[8][65])
{
	// int** tab;
	int nbBits = 6;
	int resJuste = -1;
	int resFaux = -1;
	int rechExhau = puissance(2, nbBits);
	printf("rechExhau = %d\n", rechExhau);
	for(int i = 0; i <= rechExhau ; i++)
	{	
		// printf("numero = %d\n", numero[0]);
		// printf("putttttttttttt\n");
		// printf("sb_0 %x\n", SBox[1]);
		// tab = SBox[1];
		// printf("tab_0_2 %d\n", tab[0][2]);
		// printf(" val1 %d\n", expanJuste[ numero[0] ]);
		resJuste = appliquer(SBox, (expanJuste[ numero[0] ] ^ i), numero[0]);
		// printf("resJuste = %d\n", resJuste);
		resFaux = appliquer(SBox, (expanFaux[ numero[0] ] ^ i), numero[0]);
		// printf("resFaux = %d\n", resFaux);
		// printf(" val2 %d\n", expanFaux[ numero[0] ]);
		// printf("rien ici************\n");
		// printf("xor = %d\n", (int)(resJuste ^ resFaux));
		// printf("ver = %d\n",verification[ numero[0] ]);
		if( (resJuste ^ resFaux)  == verification[ numero[0] ])
		{
			valPossibles[ numero[0] ][i]++;
			printf("\nnum %d = %d\n\n",numero[0], i );
		}
		if(numero[1] > -1)
		{
		// 	printf("numero = %d\n", numero[1]);
		// 	printf(" val1 %d\n", expanJuste[ numero[1] ]);
		// 	printf(" val2 %d\n", expanFaux[ numero[1] ]);
			resJuste = appliquer(SBox, (expanJuste[ numero[1] ] ^ i), numero[1]);
			// printf("resJuste = %d\n", resJuste);
			resFaux = appliquer(SBox, (expanFaux[ numero[1] ] ^ i), numero[1]);
			// printf("resFaux = %d\n", resFaux);
			// printf("xor = %d\n", (int)(resJuste ^ resFaux));
			// printf("ver = %d\n",verification[ numero[1] ]);
			if( (resJuste ^ resFaux)  == verification[ numero[1] ])
			{
				valPossibles[ numero[1] ][i]++;
				printf("\nnum %d = %d\n\n",numero[1], i );
			}
		}
	}

}

void attaqueSbox()
{
	char* R15bin = NULL;
	char* R15binaire = NULL;
	char* R15Fauxbinaire = NULL;
	char*  R15binaireE = NULL;
	char*  R15FauxbinaireE = NULL;
	int* expanJuste = NULL;
	int* expanFaux = NULL;
	int valPossibles[8][65] = {0};

	unsigned long long chifrJuste = messageChifrJuste;
	unsigned long long chifrFaux;// = messageChifrFaux[0];
	unsigned long R15;
	unsigned long R15Faux;
	unsigned long R16;
	unsigned long R16Faux;
	unsigned long L16;
	unsigned long L16Faux;
	unsigned long verification;
	char* binaire = NULL;
	char* ver = NULL;
	int* propa = NULL;
	int* binDecimals = NULL;
	int taille;// = 0;
	unsigned long bitFaux;
	int position;// = -2;
	for(int test = 0; test < 32; test++){
	taille = 0;
	position = -2;
	chifrFaux = messageChifrFaux[test];
	get_R16_L16(IP, chifrJuste, &R16, &L16);
	R15 = L16;
	// printf("R16 = %lX  ", R16);printf("L16 = %lX\n", L16);
	get_R16_L16(IP, chifrFaux, &R16Faux, &L16Faux);
	R15Faux = L16Faux;
	//  printf("R16F= %lX  ", R16Faux);printf("L16F= %lX\n", L16Faux);
	bitFaux = R15 ^ R15Faux;
	printf("%lX\n", bitFaux);
	printf("%d\n", (int) bitFaux);
	position = posiBitFauter32(bitFaux);
	propa = propaBitFaux(position);
	for (int p = 0; p < 2; p++)
	{
		printf("%d ", propa[p]);
	}printf("\n");
	binaire = bin32(R16 ^ R16Faux);
	// verification = permutation(PInv, binaire);
	ver = permutation(PInv, binaire);
	printf("%s\n", ver);
	printf("%lX\n", R15);
	 R15bin = bin32(R15);
	printf("%s\n", R15bin);
	taille = strlen(ver);
	binDecimals = binToDecimal(ver, taille, 4);
	for (int i = 0; i < taille/4; ++i)
	{
		printf("%d ", binDecimals[i]);
	}printf("\n");
	verification = binToHexa32(ver);
	printf("%lX\n", verification);
	 R15binaire = bin32(R15);
	 R15Fauxbinaire = bin32(R15Faux);
	  R15binaireE = expansion(E, R15binaire);
	  R15FauxbinaireE = expansion(E, R15Fauxbinaire);
	 expanJuste = binToDecimal(R15binaireE, 48, 6);
	 for (int i = 0; i < 8; ++i)
	 {
	 	printf("%d ", expanJuste[i]);
	 }printf("\n");
	 expanFaux = binToDecimal(R15FauxbinaireE, 48, 6);
	 for (int i = 0; i < 8; ++i)
	 {
	 	printf("%d ", expanFaux[i]);
	 }printf("\n");
	// int valPossibles[31][8][64] = {0};
	attaqueBox(propa, expanJuste, expanFaux, binDecimals, valPossibles);
	free(binaire);
	free(ver);
	free(binDecimals);
	free(propa);
	free(R15binaire);
	free(R15Fauxbinaire);
	free(R15binaireE);
	free(R15FauxbinaireE);
	free(expanJuste);
	free(expanFaux);
	free(R15bin); 
	}
	// for (int i = 0; i < 32; ++i)
	// { 
		// printf("chiffrer %d\n", i);
		for (int j = 0;  j < 8; ++j)
			{
				// printf("SBOX %d\n", j);
				for (int k = 0; k < 65; ++k)
				{
					printf("%d ", valPossibles[j][k]);
				}printf("\nk = %d\n", maximum(valPossibles[j], 65));printf("\n");
			}printf("\n");
	printf("%llx\n", construreCleK16(valPossibles, 8));
	// }printf("\n");
	// for (int i = 0; i < 32; ++i)
	// {
	// 	chifrFaux = messageChifrFaux[i];
	// 	get_R16_L16(IP, chifrFaux, &R16Faux, &L16Faux);
	//  printf("R16F= %lX  ", R16Faux);printf("L16F= %lX\n", L16Faux);
	// 	unsigned long long mask = L16 ^ L16Faux;
	// 	bin = bin64(mask);
	// 	printf("%s\n", bin);
	// 	free(bin);
	// }
	
	
	// free(binaire);
	// free(ver);
	// free(binDecimals);
	// free(propa);
	// free(R15binaire);
	// free(R15Fauxbinaire);
	// free(R15binaireE);
	// free(R15FauxbinaireE);
	// free(expanJuste);
	// free(expanFaux);
	// free(R15bin);

}

void Test()
{
	unsigned long R16Faux;
	unsigned long L16Faux;
	unsigned long long chifrFaux = 0xB668F7C89EEF61;
	get_R16_L16(IP, chifrFaux, &R16Faux, &L16Faux);
	printf("%lx%lx\n",R16Faux, L16Faux );
}