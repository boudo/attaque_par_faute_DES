#ifndef FONCTIONS_H
#define FONCTIONS_H

char* permutation(int IP[], char* chiffrerBin);

int* binToDecimal(char* bin, int taille);

char* bin64(unsigned long long hexadecimal);

void get_R16_L16(unsigned long long chiffrer, unsigned long* R16, unsigned long* L16);

#endif