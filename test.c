#include "attaque.h"
// #include "definition.h"
#include "fonctions.h"
#include <stdlib.h>
#include <stdio.h>







int main(int argc, char const *argv[])
{
	// afficher IP
	// for (int i = 0; i < 64; ++i)
	// {
	// 	if (i%8 == 0)
	// 	{
	// 		printf("\n");
	// 	}
	// 	printf("%d ",IP[i]);
	// }

	// afficher IPInv
	// for (int i = 0; i < 64; ++i)
	// {
	// 	if (i%8 == 0)
	// 	{
	// 		printf("\n");
	// 	}
	// 	printf("%d ",IPInv[i]);
	// }

	// afficher E
	// for (int i = 0; i < 48; ++i)
	// {
	// 	if (i%6 == 0)
	// 	{
	// 		printf("\n");
	// 	}
	// 	printf("%d ",E[i]);
	// }

	// long t1 = 0xFE644C784D21BC3E >> 32;
	// long t2 = (0xFE644C784D21BC3E & 0x00000000FFFFFFFF);
	// printf("%lX\n", t1);
	// printf("%lX\n", t2);

	// for (int i = 0; i < 32; ++i)
	// {
	// 	printf("%llX\n", messageChifrFaux[i] | messageChifrJuste);
	// }
	// printf("\n%llX\n", messageChifrJuste);
	// printf("\n%llX\n", messageClair);
	

	// unsigned long long t = 0xFC754C3C4D21BC3A;
	// unsigned long R16;
	// unsigned long L16;
	// get_R16_L16(t, &R16, &L16);
	// printf("%lX\n", R16);
	// printf("%lX\n", L16);
	unsigned long long cleK16;
	unsigned long long maCleK;
	cleK16 = attaqueSbox();
	maCleK = cleK(cleK16);
	printf("voici ma cleK = %llX\n", maCleK);
	// printf("%d\n", puissance(2, 5));
	printf("\ntout marche bien\n");
	return 0;
}

//D389CE169EF1D398