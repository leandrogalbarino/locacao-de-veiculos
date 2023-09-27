#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct veiculos
{
    char *placa[50];
    char *marca[50];
    char *modelo[50];
    int ano_fabricacao;
    int quilometragem;
    int valor_diaria;
    bool disponibilidade;
    struct veiculos *prox;
};
typedef struct veiculos Veiculos;
// LISTA DE CADASTRO DE VEICULOS

void informacoes_veiculo(Veiculos *novo)
{
    printf("MODELO DO VEICULO:");
    scanf(" %49s", novo->modelo);

    printf("MARCA DO VEICULO:");
    scanf(" %49s", novo->marca);

    printf("PLACA DO VEICULO:");
    scanf(" %49s", novo->placa);

    printf("ANO DA FABRICACAO:");
    scanf("%d", novo->ano_fabricacao);

    printf("QUILOMETRAGEM ATUAL:");
    scanf("%d", novo->quilometragem);

    printf("VALOR DA DIARIA:");
    scanf("%d", novo->valor_diaria);

    printf("\n");
}

Veiculos *incluir_veiculos(Veiculos *veiculos)
{
    Veiculos *novo = (Veiculos *)malloc(sizeof(Veiculos));
    if (novo == NULL)
    {
        printf("ERRO AO ALOCAR!!");
        exit(1);
    }
    informacoes_veiculo(novo);
    novo->prox = NULL;

    if (veiculos == NULL)
    {
        return novo;
    }

    veiculos->prox = novo;
    return veiculos;
}

char *veiculo_disponivel(bool disponibilidade)
{
    if (disponibilidade == true)
    {
        return "DISPONIVEL";
    }
    else
    {
        return "INDISPONIVEL";
    }
}

void listar_veiculos(Veiculos *veiculos)
{
    printf("VEICULOS CADASTRADOS:\n\n");
    Veiculos *p;
    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!");
    }
    for (p = veiculos; p != NULL; p = p->prox)
    {
        printf("PLACA:%s\n", veiculos->placa);
        printf("MARCA:%s\n", veiculos->marca);
        printf("MODELO:%s\n", veiculos->modelo);

        printf("ANO DE FABRICACAO:%d\n");
        printf("QUILOMETRAGEM:%d\n");
        printf("VALOR DA DIARIA:%d\n");
        printf("DISPONIVEL:%s\n\n", veiculo_disponivel(veiculos->disponibilidade));
    }
}

void listar_veiculos_disponiveis(Veiculos *veiculos)
{
    Veiculos *p;
    int disponiveis = 0;

    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!\n\n");
    }

    printf("VEICULOS DISPONIVEIS:\n\n");
    for (p = veiculos; p != NULL; p = p->prox)
    {
        if (p->disponibilidade == true)
        {
            printf("PLACA:%s\n", veiculos->placa);
            printf("MODELO:%s\n\n", veiculos->modelo);
            disponiveis++;
        }
    }
    if (disponiveis == 0)
    {
        printf("NAO EXISTEM VEICULOS DISPONIVEIS!!");
    }
}

void listar_placa_3_mais_rodados(Veiculos *veiculos)
{
    Veiculos *primeiro = (Veiculos *)malloc(sizeof(Veiculos));
    Veiculos *segundo = (Veiculos *)malloc(sizeof(Veiculos));
    Veiculos *terceiro = (Veiculos *)malloc(sizeof(Veiculos));
    primeiro->quilometragem = -1;
    segundo->quilometragem = -2;
    terceiro->quilometragem = -3;

    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!\n\n");
    }
    Veiculos *p;
    for (p = veiculos; p != NULL; p = p->prox)
    {
        if (p->quilometragem > terceiro->quilometragem)
        {
            
            if (terceiro->quilometragem > segundo->quilometragem)
            {
                if (segundo->quilometragem > primeiro->quilometragem)
                {
                }
            }
        }
    }

    printf("3 VEICULOS MAIS RODADOS:\n\n");
}