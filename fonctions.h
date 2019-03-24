#ifndef FONCTIONS_H
#define FONCTIONS_H

char* expansion(int E[], char* binaire);

char* permutation(int P[], char* chiffrerBin, int tailleSortie);

int* binToDecimal(char* bin, int nbBits);

char* hexaToBin(unsigned long long hexadecimal, int tailleSortie);

void get_R16_L16(int IPInv[], unsigned long long chiffrer, unsigned long long* R16, unsigned long long* L16);

unsigned long long binToHexa(char* binaire, int tailleSortie);

int posiBitFauter(unsigned long long hexadecimal, int nbBits);

int* propaBitFaux(int position);

int puissance(int a, int b);

int appliquer(int SBox[][4][16], int expanVal, int numSBox);

unsigned long long construreCleK16(int tableau[][65], int nbSBox);

char* cleKEffIncomp(int PC2Inv[], unsigned long long cleK16);

char* cleKIncomp(int PC1Inv[], char* cleKEffIncompl);

int* getBitInconnu(char* cleKIncompl);

char* getCle(char* cleKIncompl, int* bitInconnu, int k);

void decalageG(char* CD, int dec);

unsigned long long fonctionF(int P[], int E[], int SBox[][4][16], unsigned long long Ri, char* Ki);

unsigned long long ajoutBitParite(char* cleK);


#endif