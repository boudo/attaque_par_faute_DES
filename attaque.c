#include "attaque.h"
#include "fonctions.h"
#include "resultats.h"
#include "definitions.h"
#include "keySchedule.h"
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
	// printf("rechExhau = %d\n", rechExhau);
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
			// printf("\nnum %d = %d\n\n",numero[0], i );
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
				// printf("\nnum %d = %d\n\n",numero[1], i );
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
	unsigned long long cleAttribuer;
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
	char* K16 = "101010110101010111111001100000111111000111011101";
	unsigned long TEST1 = fonctionF(P, E, SBox, R15, K16);
	unsigned long TEST2 = fonctionF(P, E, SBox, R15Faux, K16);
	printf("remon = %lX\n", R16 ^ R16Faux);
	printf("desc  = %lX\n", TEST1 ^ TEST2);
	//  printf("R16F= %lX  ", R16Faux);printf("L16F= %lX\n", L16Faux);
	bitFaux = R15 ^ R15Faux;
	// printf("%lX\n", bitFaux);
	// printf("%d\n", (int) bitFaux);
	position = posiBitFauter32(bitFaux);
	propa = propaBitFaux(position);
	// for (int p = 0; p < 2; p++)
	// {
	// 	printf("%d ", propa[p]);
	// }printf("\n");
	binaire = bin32(R16 ^ R16Faux);
	// verification = permutation(PInv, binaire);
	ver = permutation(PInv, binaire);
	// printf("%s\n", ver);
	// printf("%lX\n", R15);
	 R15bin = bin32(R15);
	// printf("%s\n", R15bin);
	taille = strlen(ver);
	binDecimals = binToDecimal(ver, taille, 4);
	// for (int i = 0; i < taille/4; ++i)
	// {
	// 	printf("%d ", binDecimals[i]);
	// }printf("\n");
	verification = binToHexa32(ver);
	// printf("%lX\n", verification);
	 R15binaire = bin32(R15);
	 R15Fauxbinaire = bin32(R15Faux);
	  R15binaireE = expansion(E, R15binaire);
	  R15FauxbinaireE = expansion(E, R15Fauxbinaire);
	 expanJuste = binToDecimal(R15binaireE, 48, 6);
	 // for (int i = 0; i < 8; ++i)
	 // {
	 // 	printf("%d ", expanJuste[i]);
	 // }printf("\n");
	 expanFaux = binToDecimal(R15FauxbinaireE, 48, 6);
	 // for (int i = 0; i < 8; ++i)
	 // {
	 // 	printf("%d ", expanFaux[i]);
	 // }printf("\n");
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
	// 	printf("chiffrer %d\n", i);
		// for (int j = 1;  j < 8; ++j)
		// 	{
		// 		// printf("SBOX %d\n", j);
		// 		for (int k = 0; k < 65; ++k)
		// 		{
		// 			printf("%d ", valPossibles[j][k]);
		// 		}printf("\n");//printf("\nk = %d\n", maximum(valPossibles[j], 65));printf("\n");
		// 	}printf("\n");
			char* cle1 = cleKEffIncomp(PC2Inv, construreCleK16(valPossibles, 8));
			char* cle2 = cleKIncomp(PC1Inv, cle1);
	printf("%llX\n", construreCleK16(valPossibles, 8));
	printf("%s\n", cle1);
	printf("%s\n", cle2); // 3 bloc perdu
	char* cleK = NULL;
	cleK = recheCleKEff(messageClair,messageChifrJuste, cle2);
	printf("ma cle k = %s\n", cleK);
	cleAttribuer = ajoutBitParite(cleK);
	printf("ma cle attribuer est = %llX\n", cleAttribuer);
	// printf("%s\n", verif(PC1, cleKIncomp(PC1Inv, cleKEffIncomp(PC2Inv, construreCleK16(valPossibles, 8)))));
	
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
	free(cle1);
	free(cle2);
	free(cleK);

}


char* recheCleKEff(unsigned long long messgClair, unsigned long long chiffJuste, char* cleKIncompl)
{
	int taille = strlen(cleKIncompl);
	int val = puissance(2,8);
	unsigned long long chiffTmp;
	char* cleKEff = NULL;
	// char* cleKEfff = "1101001110001001110011100001011010011110111100011101001110011000";
	char* resCles = NULL;
	int* bitInconnu = NULL;
	resCles = malloc(taille * sizeof(char) + sizeof(char));
	if(resCles == NULL)
	{
		exit(2);
	}
	resCles[taille] = '\0';
	bitInconnu = getBitInconnu(cleKIncompl);
	for (int i = 0; i <= val; i++)
	{
		cleKEff = getCle(cleKIncompl, bitInconnu, i);
		printf("\neffec = %s\n", cleKEff);
		// cleKEfff = "1101001110001001110011100001011010011110111100011101001110011000";
		chiffTmp = DESAttaque(messgClair, cleKEff);
		if (i<3)
		{
			printf("recher = %llX\n", chiffTmp);
			printf("Juste = %llX\n", chiffJuste);
		}
		
		// printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ici !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		if((chiffJuste ^ chiffTmp) == 0)
		{
			printf("cleKEff = %s !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", cleKEff);
			strcpy(resCles, cleKEff);
			free(cleKEff);
			break;
		}
		free(cleKEff);
	}


	free(bitInconnu);
	return resCles;
}

unsigned long long DESAttaque(unsigned long long messgClair, char* cleKEff)
{
	unsigned long long C;
	unsigned long L0;
	unsigned long Li;
	unsigned long R0;
	unsigned long Ri;
	unsigned long resF;
	unsigned long long R16L16;
	unsigned long long mask1 = 0xFFFFFFFF00000000;
	unsigned long long mask2 = 0x00000000FFFFFFFF;
	unsigned long long messgTmp;
	char* Ki = NULL;
	char* CD = NULL;
	char* R16L16Bin = NULL;
	char* R16L16BinPerm = NULL;
	char* messgClairPermut = NULL;

	char* messgBin = bin64(messgClair);
	messgClairPermut = permutation(IP, messgBin);
	messgTmp = binToHexa64(messgClairPermut);
	L0 = (messgTmp & mask1) >> 32;
	R0 = (messgTmp & mask2);

	CD = permutationCle(PC1, cleKEff);
	// for (int i = 0; i < 56; ++i)
	// {
	// 	if(i%7==0)
	// 	{
	// 		printf("\n");
	// 	}
	// 	printf("%c ", CD[i]);
	// }printf("\n");
	for (int i = 1; i <= 16; ++i)
	{
		Ki = keySchedule(PC2, cleKEff, CD, i);
		resF = fonctionF(P, E, SBox, R0, Ki);
		Li = R0;
		Ri = L0 ^ resF;
		L0 = Li;
		R0 = Ri;

		free(Ki);
	}
	R16L16 = R0;
	R16L16 = R16L16 << 32;
	R16L16 = R16L16 | L0;
	R16L16Bin = bin64(R16L16);
	R16L16BinPerm = permutation(IPInv, R16L16Bin);
	C = binToHexa64(R16L16BinPerm);
	
	free(CD);
	free(R16L16Bin);
	free(R16L16BinPerm);
	free(messgClairPermut);
	free(messgBin);
	return C;
}