#include "attaque.h"
#include "fonctions.h"
#include "resultats.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void attaqueBox(int numChif, int numero[], int expanJuste[], int expanFaux[], int verification[], int*** valPossibles)
{
	int nbBits = 6;
	int resJuste = -1;
	int resFaux = -1;
	int rechExhau = puissance(2, nbBits);
	printf("rechExhau = %d\n", rechExhau);
	for(int i = 0; i <= rechExhau ; i++)
	{
		resJuste = appliquer(SBox[ numero[1] ], expanJuste[ numero[1] ]);
		resFaux = appliquer(SBox[ numero[1] ], expanFaux[ numero[1] ]);

		if( (resJuste ^ resFaux)  == verification[ numero[1] ])
		{
			valPossibles[numChif][ numero[1] ][i] = i;
		}
		if(numero[2] > -1)
		{
			resJuste = appliquer(SBox[ numero[2] ], expanJuste[ numero[2] ]);
			resFaux = appliquer(SBox[ numero[2] ], expanFaux[ numero[2] ]);

			if( (resJuste ^ resFaux)  == verification[ numero[2] ])
			{
				valPossibles[numChif][ numero[2] ][i] = i;
			}
		}
	}

}

void attaqueSbox()
{
	unsigned long long chifrJuste = messageChifrJuste;
	unsigned long long chifrFaux = messageChifrFaux[0];
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
	int taille = 0;
	unsigned long bitFaux;
	int position = -2;

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
	taille = strlen(ver);
	binDecimals = binToDecimal(ver, taille, 4);
	for (int i = 0; i < taille/4; ++i)
	{
		printf("%d ", binDecimals[i]);
	}printf("\n");
	verification = binToHexa32(ver);
	printf("%lX\n", verification);
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
	
	
	free(binaire);
	free(ver);
	free(binDecimals);
	free(propa);

}