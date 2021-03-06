#include "lucasLehmerMersenne.h"

int lucasLehmerMersenne(int p)
{
	int i = 0;
	mpz_t m;
	mpz_t s;

	mpz_init(m);
	mpz_ui_pow_ui(m, 2, p);
	mpz_sub_ui(m, m,1);
	mpz_init_set_ui(s, 4);
	if(p <= 1)
	{
		printf("Cette puissance est incorrect. Retour au menu.\n");
		mpz_clear(m);
		mpz_clear(s);

		return 0;
	}
	gmp_printf("On va vérifier si le nombre de Mersenne %Zd est premier ou non.\n", m);
	while(i < p - 2)			// On effectue p-2 fois les instructions suivantes : 
	{
		mpz_mul(s, s, s);		// s = s * s
		mpz_sub_ui(s, s, 2);	// s = s - 2
		mpz_mod(s, s, m);		// s = s mod m
		i = i + 1;
	}
	if(mpz_cmp_ui(s, 0) == 0 || p == 2)	// On teste si la fonction renvoie 0 : Si oui, alors s = 0, donc s est premier
	{
		mpz_clear(m);
		mpz_clear(s);

		return 1;
	}
	else
	{
		mpz_clear(m);
		mpz_clear(s);
		
		return 0;
	}
}