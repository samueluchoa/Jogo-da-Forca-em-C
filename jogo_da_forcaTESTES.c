#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");
	char palavra_secreta[20];
	//strcpy(palavra_secreta, "MELANCIA");
	sprintf(palavra_secreta, "MELANCIA");

	int acertou = 0;
	int enforcou = 0;
    
    char chutes[26];
    int tentativas = 0;

    char letra_chute;
    printf("=================================================================\n");
	printf("\t\t # JOGO DA FORCA ! #\n \t\t # ESCREVA COM LETRA MAIUSCULA ! #\n");
	printf("=================================================================\n");
	do {

		// COMENTAR ESTE TRECHO !
		for (int i = 0; i < strlen(palavra_secreta); i++)
		{
			int acertou = 0;
			for (int t = 0; t < tentativas; t++)
			{
				if (chutes[t] == palavra_secreta[i])
				{
					acertou = 1;
					break;
				}
			}
			if (acertou)
				printf(" %c ", palavra_secreta[i]);
			else
				printf(" _ ");
		}
		printf("\n\n");
		printf("Insira uma letra:    ");
		scanf(" %c", &letra_chute);
		
		printf("\n\n");
		// COMENTAR ESTE TRECHO !
		
		chutes[tentativas] = letra_chute;
		printf("chutes [%d] = %c \n", tentativas, letra_chute);
		tentativas++;


	} while(!acertou && !enforcou);
}