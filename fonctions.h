#ifndef FONCTIONS_H
#define FONCTIONS_H

char* expansion(int E[], char* binaire);

char* permutation(int P[], char* chiffrerBin);

char* permutationCle(int P[], char* chiffrerBin);

int* binToDecimal(char* bin, int taille, int nbBits);

char* hexaToBin(unsigned long long hexadecimal, int taille);

char* bin64(unsigned long long hexadecimal);

char* bin32(unsigned long hexadecimal);

void get_R16_L16(int permutation[], unsigned long long chiffrer, unsigned long* R16, unsigned long* L16);

unsigned long long binToHexa64(char* binnaire);

unsigned long long binToHexa56(char* binnaire);

unsigned long binToHexa32(char* binnaire);

int posiBitFauter32(unsigned long hexadecimal);

int* propaBitFaux(int position);

int puissance(int a, int b);

int appliquer(int SBox[][4][16], int expanVal, int numSBox);

int maximum(int tableau[], int taille);

unsigned long long construreCleK16(int tableau[][65], int nbSBox);

char* cleKEffIncomp(int PC2Inv[], unsigned long long cleK16);

char* cleKIncomp(int PC1Inv[], char* cleKEffIncompl);

int* getBitInconnu(char* cleKIncompl);

char* getCle(char* cleKIncompl, int* bitInconnu, int k);

void decalageG(char* CD, int dec);

unsigned long fonctionF(int P[], int E[], int SBox[][4][16], unsigned long Ri, char* Ki);

unsigned long long ajoutBitParite(char* cleK);

// char* verif(int PC1[], char* cleKIncompl);

#endif