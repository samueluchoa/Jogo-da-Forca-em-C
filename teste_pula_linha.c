#include <stdio.h>
#include <stdlib.h>


void pula_lina(int tam)
{
	for (int i = 0; i < tam; ++i)
	{
		//printf("%d ", i);
		printf("\n");
	}
}
int main()
{
	int tam = 0;
	scanf("%d", &tam);
	
	for (int i = 0; i < tam; ++i)
	{
		printf("========================================");
		pula_lina(tam);
	}
}