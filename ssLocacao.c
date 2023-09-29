#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "estruturas.h"

struct data
{
    int retirada;
    int devolucao;
};
typedef struct data Data;

struct locacao_veiculos_por_clientes
{
    Clientes *cliente;
    // trocar disponibilidade do veiculo alocado; Retornar a posicao do veiculo alocado
    Veiculos *veiculo_alocado;

    Data dia;
    // veiculo so pode ser alocado se estiver disponivel na data;

    int valor_total_pago;

    struct locacao_veiculos_por_clientes *prox;
};
typedef struct locacao_veiculos_por_clientes Locacao;
// LISTA DE LOCACAO DE VEICULOS

void informacoes_de_locacao(char *nome_cliente, char *placa)
{
    printf("PARA FAZER A LOCACAO DE UM VEICULO:\n\n");
    printf("DIGITE SEU NOME:");
    scanf("%s", nome_cliente);
    printf("\n");
    printf("DIGITE A PLACA DO VEICULO QUE DESEJA FAZER A LOCACAO:");
    scanf("%s", placa);
    printf("\n");
}

Clientes verif_cliente_cadastrado(Clientes *clientes, char *nome_cliente)
{
    Clientes *c;
    for (c = clientes; c != NULL; c = c->prox)
    {
        if (strcmp(c->nome, nome_cliente) == 0)
        {
            return c;
        }
    }
    return NULL;
}

Veiculos verif_veiculos_cadastrado(Veiculos *veiculos, char *placa)
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

Locacao *realizar_locacao(Locacao *locacao, Clientes *clientes, Veiculos *veiculos)
{
    if (clientes == NULL)
    {
        printf("NAO EXISTEM CLIENTES CADASTRADOS!!");
        return locacao;
    }
    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!");
        return locacao;
    }

    Locacao *novo = (Locacao *)malloc(sizeof(Locacao));
    novo->prox = locacao;

    char nome_cliente[50];
    char placa[50];
    informacoes_de_locacao(nome_cliente, placa);

    novo->cliente = verif_cliente_cadastrado(clientes, nome_cliente);
    novo->veiculo_alocado = verif_veiculos_cadastrado(veiculos, placa);

    if (novo->cliente == NULL || novo->veiculo_alocado == NULL)
    {
        printf("NAO FOI POSSIVEL REALIZAR A LOCACAO!!\n CLIENTE OU VEICULO NAO CADASTRADO!!");
        free(novo);
        return locacao;
    }
}
