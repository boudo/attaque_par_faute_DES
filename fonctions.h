#ifndef FONCTIONS_H
#define FONCTIONS_H

char* expansion(int E[], char* binaire);

char* permutation(int P[], char* chiffrerBin);

int* binToDecimal(char* bin, int taille, int nbBits);

char* bin64(unsigned long long hexadecimal);

char* bin32(unsigned long hexadecimal);

void get_R16_L16(int permutation[], unsigned long long chiffrer, unsigned long* R16, unsigned long* L16);

unsigned long long binToHexa64(char* binnaire);

unsigned long binToHexa32(char* binnaire);

int posiBitFauter32(unsigned long hexadecimal);

int* propaBitFaux(int position);

int puissance(int a, int b);

int appliquer(int SBox[][4][16], int expanVal, int numSBox);

int maximum(int tableau[], int taille);

unsigned long long construreCleK16(int tableau[][65], int nbSBox);

#endif