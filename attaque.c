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
		resJuste = appliquer(SBox, (expanJuste[ numero[0] ] ^ i), numero[0]);
		// printf("resJuste = %d\n", resJuste);
		resFaux = appliquer(SBox, (expanFaux[ numero[0] ] ^ i), numero[0]);
		// printf("resFaux = %d\n", resFaux);
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

unsigned long long attaqueSbox()
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
	unsigned long long chifrFaux;
	unsigned long long R15;
	unsigned long long R15Faux;
	unsigned long long R16;
	unsigned long long R16Faux;
	unsigned long long L16;
	unsigned long long L16Faux;
	// unsigned long long verification;
	char* binaire = NULL;
	char* ver = NULL;
	int* propa = NULL;
	int* binDecimals = NULL;
	// int taille;// = 0;
	unsigned long long bitFaux;
	int position;// = -2;
	for(int test = 0; test < 32; test++){
	// taille = 0;
	position = -2;
	chifrFaux = messageChifrFaux[test];
	get_R16_L16(IP, chifrJuste, &R16, &L16);
	R15 = L16;
	// printf("R16 = %lX  ", R16);printf("L16 = %lX\n", L16);
	get_R16_L16(IP, chifrFaux, &R16Faux, &L16Faux);
	R15Faux = L16Faux;
	bitFaux = R15 ^ R15Faux;
	// printf("%lX\n", bitFaux);
	position = posiBitFauter(bitFaux, 32);
	propa = propaBitFaux(position);
	// for (int p = 0; p < 2; p++)
	// {
	// 	printf("%d ", propa[p]);
	// }printf("\n");
	binaire = hexaToBin(R16 ^ R16Faux, 32);
	// verification = permutation(PInv, binaire);
	ver = permutation(PInv, binaire, 32);
	// printf("%s\n", ver);
	// printf("%lX\n", R15);
	 R15bin = hexaToBin(R15, 32);
	// printf("%s\n", R15bin);
	// binToHexa = strlen(ver);
	binDecimals = binToDecimal(ver, 4);
	// for (int i = 0; i < taille/4; ++i)
	// {
	// 	printf("%d ", binDecimals[i]);
	// }printf("\n");
	// verification = binToHexa(ver, 32);
	// printf("%lX\n", verification);
	 R15binaire = hexaToBin(R15, 32);
	 R15Fauxbinaire = hexaToBin(R15Faux, 32);
	  R15binaireE = expansion(E, R15binaire);
	  R15FauxbinaireE = expansion(E, R15Fauxbinaire);
	 expanJuste = binToDecimal(R15binaireE, 6);
	 // for (int i = 0; i < 8; ++i)
	 // {
	 // 	printf("%d ", expanJuste[i]);
	 // }printf("\n");
	 expanFaux = binToDecimal(R15FauxbinaireE, 6);
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

	return construreCleK16(valPossibles, 8);
}

unsigned long long cleK(unsigned long long cleK16)
{
	unsigned long long cleAttribuer;
	char* cle1 = NULL;
	char* cle2 = NULL;
	cle1 = cleKEffIncomp(PC2Inv, cleK16);
	cle2 = cleKIncomp(PC1Inv, cle1);
	printf("%s\n", cle1);
	printf("%s\n", cle2);



	char* cleK = NULL;
	cleK = recheCleKEff(messageClair,messageChifrJuste, cle2);
	printf("ma cle k = %s\n", cleK);
	cleAttribuer = ajoutBitParite(cleK);
	printf("ma cle attribuer est = %llX\n", cleAttribuer);

	free(cle1);
	free(cle2);
	free(cleK);

	return cleAttribuer;
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
	unsigned long long L0;
	unsigned long long Li;
	unsigned long long R0;
	unsigned long long Ri;
	unsigned long long resF;
	unsigned long long R16L16;
	unsigned long long mask1 = 0xFFFFFFFF00000000;
	unsigned long long mask2 = 0x00000000FFFFFFFF;
	unsigned long long messgTmp;
	char* Ki = NULL;
	char* CD = NULL;
	char* R16L16Bin = NULL;
	char* R16L16BinPerm = NULL;
	char* messgClairPermut = NULL;

	char* messgBin = hexaToBin(messgClair, 64);
	messgClairPermut = permutation(IP, messgBin, 64);
	messgTmp = binToHexa(messgClairPermut, 64);
	L0 = (messgTmp & mask1) >> 32;
	R0 = (messgTmp & mask2);

	CD = permutation(PC1, cleKEff, 56);
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
	R16L16Bin = hexaToBin(R16L16, 64);
	R16L16BinPerm = permutation(IPInv, R16L16Bin, 64);
	C = binToHexa(R16L16BinPerm, 64);
	
	free(CD);
	free(R16L16Bin);
	free(R16L16BinPerm);
	free(messgClairPermut);
	free(messgBin);
	return C;
}