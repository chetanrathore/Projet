#include "lucasLehmerRiesel.h"

int lucasLehmerRiesel(int k, int n)
{
	//Ajustement de k et n si k est pair
	while (k % 2 == 0)
	{
		k = k / 2;
		n = n + 1;
	}
	
	//Il faut que 2^n > k
	if (pow(2,n) <= k)
	{
		printf("Erreur: 2^n <= k\n");
		return 0;
	}

	//N = k * 2^n - 1
	mpz_t N;
	mpz_init_set_ui(N, n);
	mpz_mul(N, N, N);
	mpz_mul_ui(N, N, k);
	mpz_sub_ui(N, N, 1);
	gmp_printf("On va vérifier si le nombre %Zd est premier ou non.\n", N);
	
	//Choix de u0
	double u0 = -1;
	if (k == 1)
	{
		if (n % 2 == 1)
		{
			u0 = 4;
		}
		else if (n % 4 == 3)
		{
			u0 = 3;
		}
	}
	if (k == 3)
	{
		int n_ = n % 4;
		if ((n_ == 0) || (n_ == 3))
		{
			u0 = 5778;
		}
	}
	else
	{
		int k_ = k % 6;
		if ((k_ == 1) || (k_ == 5))
		{
			mpz_t r3;
			mpz_cdiv_r_ui(r3, N, 3);
			mpz_cmp_ui(r3, 0);
			if (r3 != 0)
			{
				u0 = pow(2. + sqrt(3.), k) + pow(2. - sqrt(3.), k);
			}
		}
		else
		{
			printf("Erreur: k multiple de 3, u0 indeterminé\n");
			return 0;
		}
	}
	if (u0 == -1)
	{
		printf("Erreur: u0 indeterminé\n");
		return 0;
	}
	
	//Calcul de u indice n-2
	int i = 0;
	mpz_t u;
	mpz_init_set_ui(u, u0);
	while (i < (n - 2))
	{
		//u = u*u - 2;
		mpz_mul(u, u, u);
		mpz_sub_ui(u, u, 2);
		i = i + 1;
	}
	
	//N est premier s'il divise u indice n-2
	mpz_t r;
	mpz_cdiv_r(r, u, N);
	if (r == 0)
	{
		//N est premier
		return 1;
	}
	else
	{
		//N n'est pas premier
		return 0;
	}
}