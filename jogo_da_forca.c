#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes_forca.h" // inclui os cabeçalhos das funções. A ordem não importa.
#define TAMANHO_DA_PALAVRA 30
/////////////////////////////////////////////////////////////////////
////////////////////// VARIÁVEIS GLOBAIS ///////////////////////////
///////////////////////////////////////////////////////////////////
char chutes[TAMANHO_DA_PALAVRA];
char palavra_secreta[TAMANHO_DA_PALAVRA];
int chutes_dados = 0;
///////////////////////////////////////////////////////////////////
////////////////////////////   FUNÇÕES  ///////////////////////////
///////////////////////////////////////////////////////////////////
void welcome()
{
	printf("=================================================================\n");
	printf("\t\t # JOGO DA FORCA ! #\n \t\t # ESCREVA COM LETRA MAIUSCULA ! #\n");
	printf("---------------------------------------------------------------\n\n");
	printf("Regras do Jogo:\n");
	printf("* O objetivo do jogo é adivinhar uma palavra secreta, chutando uma letra por vez.\n");
	printf("* Você tem 5 tentativas para adivinhar a palavra.\n");
	printf("* Se você errar 5 vezes, você perde o jogo.\n");
	printf("* Você pode inserir uma nova palavra no jogo ao final do jogo.\n");
	printf("=================================================================\n");
}

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
	
	//a função rand() gera um número muito grande. Por isso o resultado será o resto da divisão desse número pelo número de palavras presentes no arquivo*/
	int total_palavras = rand() % num_palavras;

	for(int i = 0; i <= total_palavras; i++)
	{
		fscanf(f, "%s", palavra_secreta);
	}
    fclose(f);
}


void chuta()
{
	char chute;

	printf("Chute uma letra ! >>>  ");
	scanf(" %c", &chute);

	if(letra_existe(chute))
	{
        printf("Você acertou: a palavra tem a letra %c\n\n", chute);
    } 
    else
    {
        printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
    }
	
	chutes[chutes_dados] = chute; // a variável ponteiro *t está entre () para demostrar que será somado +1 ao conteúdo da variável que ela está apontando
	chutes_dados++; // t = tentativas. para cada t haverá uma posição começando em 0 -> fim do loop
}


int letra_existe(char letra)
{
    for(int j = 0; j < strlen(palavra_secreta); j++)
    {
        if(letra == palavra_secreta[j])
        {
            return 1;
        }
    }

    return 0;
}

int chutes_errados()
{
	int erros = 0;
	for(int i = 0; i < chutes_dados; i++)
	{
		if(!letra_existe(chutes[i]))
		{
			erros++;
		}
	}
	return erros;
}

int enforcou()
{
	
	return chutes_errados() >= 5;
}

void desenha_forca()
{
	 //printf("Você já deu %d chutes\n", chutes_dados);
	for (int i = 0; i < strlen(palavra_secreta); i++)
		{
			if(encontrou(palavra_secreta[i]))
			{
				printf("%c ", palavra_secreta[i]);
			}
			else
			{
				printf(" _ ");
			}
		}
		printf("\n");
}

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

int ganhou()
{
    for(int i = 0; i < strlen(palavra_secreta); i++)
	{
		if(!encontrou(palavra_secreta[i]))
		{
			return 0;
		}
	}
	return 1;
}

void vitoria()
{
    printf("\n\n");
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

void adiciona_palavra()
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
        printf("\n");
        printf("Nova palavra inserida com sucesso !\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////!!! O PROGRAMA COMEÇA AQUI !!!!!////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	setlocale(LC_ALL, "Portuguese");

	welcome(); 
    palavra_escolhida();
	do {
		desenha_forca();
		chuta();

	} while(!ganhou() && !enforcou());

	// Mensagem após o fim de jogo
	ganhou() ? vitoria() : derrota();
	printf("\n\n\n");
	adiciona_palavra();
}