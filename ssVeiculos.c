#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "veiculos.h"

Veiculos *cria_lista_veiculos()
{
    return NULL;
}

void informacoes_veiculo(Veiculos *novo)
{
    printf("MODELO DO VEICULO:");
    scanf(" %49s", novo->modelo);

    printf("MARCA DO VEICULO:");
    scanf(" %49s", novo->marca);

    printf("PLACA DO VEICULO:");
    scanf(" %49s", novo->placa);

    printf("ANO DA FABRICACAO:");
    scanf("%d", &novo->ano_fabricacao);

    printf("QUILOMETRAGEM ATUAL:");
    scanf("%d", &novo->quilometragem);

    printf("VALOR DA DIARIA:");
    scanf("%d", &novo->valor_diaria);

    novo->disponibilidade = true;
    printf("\n");
}

Veiculos *verif_veiculos_cadastrado(Veiculos *veiculos, char *placa)
{
    Veiculos *v;
    for (v = veiculos; v != NULL; v = v->prox)
    {
        if (strcmp(v->placa, placa) == 0)
        {
            return v;
        }
    }
    return NULL;
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

    if (verif_veiculos_cadastrado(veiculos, novo->placa) != NULL)
    {
        printf("VEICULO JA CADASTRADO!!\n\n");
        free(novo);
        return veiculos;
    }
    if (veiculos == NULL)
    {
        novo->prox = veiculos;
        return novo;
    }
    Veiculos *p;
    Veiculos *ant = NULL;

    for (p = veiculos; p != NULL; p = p->prox)
    {
        if (p->quilometragem < novo->quilometragem)
        {
            if (ant == NULL)
            {
                novo->prox = veiculos;
                return novo;
            }
            else
            {
                ant->prox = novo;
                novo->prox = p;
            }
            return veiculos;
        }
        ant = p;
    }
    if (p == NULL)
    {
        ant->prox = novo;
        novo->prox = NULL;
    }
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
    printf("VEICULOS CADASTRADOS:\n");
    Veiculos *p;
    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!\n\n");
    }
    for (p = veiculos; p != NULL; p = p->prox)
    {
        printf("PLACA:%s\n", p->placa);
        printf("MARCA:%s\n", p->marca);
        printf("MODELO:%s\n", p->modelo);

        printf("ANO DE FABRICACAO:%d\n", p->ano_fabricacao);
        printf("QUILOMETRAGEM:%d\n", p->quilometragem);
        printf("VALOR DA DIARIA:%d\n", p->valor_diaria);
        printf("DISPONIVEL:%s\n\n", veiculo_disponivel(p->disponibilidade));
    }
}

void listar_veiculos_disponiveis(Veiculos *veiculos)
{
    Veiculos *p;
    int disponiveis = 0;

    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!\n\n");
        return;
    }

    printf("VEICULOS DISPONIVEIS:\n");
    for (p = veiculos; p != NULL; p = p->prox)
    {
        if (p->disponibilidade == true)
        {
            printf("PLACA:%s\n", p->placa);
            printf("MODELO:%s\n\n", p->modelo);
            disponiveis++;
        }
    }
    if (disponiveis == 0)
    {
        printf("NAO EXISTEM VEICULOS DISPONIVEIS!!\n");
    }
}

void listar_placa_3_mais_rodados(Veiculos *veiculos)
{
    Veiculos *aux;
    Veiculos *p;

    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!\n\n");
        return;
    }

    int num_veiculos = 0;
    printf("3 VEICULOS MAIS RODADOS:\n");

    for (p = veiculos; p != NULL && num_veiculos < 3; p = p->prox)
    {
        num_veiculos++;
        printf("%d - PLACA:%s ", num_veiculos, p->placa);
        printf("| QUILOMETRAGEM:%d\n", p->quilometragem);
    }

    if (num_veiculos < 3)
    {
        for (int i = num_veiculos; i < 3; i++)
        {
            printf("%d - NAO EXISTE\n", i + 1);
        }
    }
    printf("\n");
}
