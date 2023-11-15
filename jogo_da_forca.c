#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes_forca.h" // inclui os cabeçalhos das funções. A ordem não importa.

/////////////////////////////////////////////////////////////////////
////////////////////// VARIÁVEIS GLOBAIS ///////////////////////////
///////////////////////////////////////////////////////////////////
char chutes[TAMANHO_DA_PALAVRA];
char palavra_secreta[TAMANHO_DA_PALAVRA];
int chutes_dados = 0;
///////////////////////////////////////////////////////////////////
////////////////////////////   FUNÇÕES  ///////////////////////////
///////////////////////////////////////////////////////////////////
void vitoria()
{
    pula_lina();
    printf("\nParabéns, você ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
}
///////////////////////////////////////////////////////////////////
void derrota()
{
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavra_secreta);

    printf("    _______________         \n");
    printf("   /               \\       \n");
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");

}
///////////////////////////////////////////////////////////////////
void welcome()
{
	printf("=================================================================\n");
	printf("\t\t # JOGO DA FORCA ! #\n \t\t # ESCREVA COM LETRA MAIUSCULA ! #\n");
	printf("=================================================================\n");
}
///////////////////////////////////////////////////////////////////
void chuta()
{
	char chute;

	printf("Chute uma letra ! >>>  ");
	scanf(" %c", &chute);

	chutes[chutes_dados] = chute; // a variável ponteiro *t está entre () para demostrar que será somado +1 ao conteúdo da variável que ela está apontando
	chutes_dados++; // t = tentativas. para cada t haverá uma posição começando em 0 -> fim do loop
}
///////////////////////////////////////////////////////////////////
int encontrou(char letra)
{
	int achou = 0;
		for (int i = 0; i < chutes_dados; i++)
		{
			if (chutes[i] == letra)
				{
					achou = 1;
					break;
				}
		}
	return achou;
}
///////////////////////////////////////////////////////////////////
void desenha_forca()
{
	 //printf("Você já deu %d chutes\n", chutes_dados);
	for (int i = 0; i < strlen(palavra_secreta); i++)
		{
			int acertou = encontrou(palavra_secreta[i]);
			if (acertou)
			{
				printf(" %c ", palavra_secreta[i]);
			}
			else
			{
				printf(" _ ");
			}
		}
}
///////////////////////////////////////////////////////////////////
void pula_lina()
{
	printf("\n\n");
}
///////////////////////////////////////////////////////////////////
void palavra_escolhida() // essa função escolhe uma palavra aleatória com base nas palavras presentes em um banco de dados(arquivo)
{
	FILE* f;
	f = fopen("palavras_secretas.txt", "r");
	
	if(f == 0)
	{
		printf("Desculpe, banco de dados não disponível \n");
		exit(1);
	}

	int num_palavras;
	// a primeira linha do arquivo se destina a informar o número de palavras presentes no arquivo
	fscanf(f, "%d", &num_palavras); // essa função irá procurar esse número e irá guardar em uma variável
	
	srand(time(0));
	/* a função rand() gera um número muito grande.
	Por isso o resultado será o resto da divisão desse número pelo número de palavras presentes no arquivo*/
	int total_palavras = rand() % num_palavras;
	for(int i = 0; i <= total_palavras; i++)
	{
		fscanf(f, "%s", palavra_secreta);
	}
    fclose(f);
}
///////////////////////////////////////////////////////////////////
int acertou()
{
    for(int i = 0; i < strlen(palavra_secreta); i++)
	{
		if (!encontrou(palavra_secreta[i]))
		{
			return 0;
		}
	}
	return 1;
}
///////////////////////////////////////////////////////////////////
int enforcou()
{
	int erro = 0;
	for(int i = 0; i < chutes_dados; i++)
	{
		int existe = 0;
		for(int p = 0; p < strlen(palavra_secreta); p++)
		{
			if (chutes[i] == palavra_secreta[p])
			{
				existe = 1;
				break;
			}
		}
		if(!existe) erro++;
	}
	return erro >= 5;
}
void add_new_palavra()
{
    char nova_p;
    printf("Você deseja inserir uma nova palavra no jogo ? (S/N)  ");
    scanf(" %c", &nova_p);

    if (nova_p == 'S')
    {
        char nova_palavra[TAMANHO_DA_PALAVRA];
        printf("Qual nova palavra você deseja inserir ?");
        scanf("%s", nova_palavra);


        FILE* f;
        f = fopen("palavras_secretas.txt", "r+");

        if(f == 0)
        {
            printf("Desculpe, Banco de dados não disponível :( \n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
            fprintf(f, "%d", qtd);
        fseek(f, 0, SEEK_END);
            fprintf(f, "\n%s", nova_palavra);

        fclose(f);

        printf("Nova palavra inserida com sucesso !\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////!!! O PROGRAMA COMEÇA AQUI !!!!!////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
setlocale(LC_ALL, "");

    palavra_escolhida();
    welcome(); // BOAS VINDAS
	do {
		desenha_forca();
		pula_lina();
		chuta();

	} while(!acertou() && !enforcou());

    //add_new_palavra();

    //Mensagem ao Final do Jogo !
    if(acertou())
        vitoria();
    else
        derrota();
}