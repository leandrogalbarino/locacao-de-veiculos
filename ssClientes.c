#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "clientes.h"

Clientes *cria_lista_clientes()
{
    return NULL;
}

void informacoes_cliente(Clientes *novo)
{
    printf("NOME:");
    scanf(" %49s", novo->nome);

    printf("CNH:");
    scanf("%d", &novo->cnh);

    printf("TELEFONE:");
    scanf("%d", &novo->telefone);
    printf("\n");
}

Clientes *verif_cliente_cadastrado(Clientes *clientes, int cnh_cliente)
{
    Clientes *c;
    for (c = clientes; c != NULL; c = c->prox)
    {
        if (c->cnh == cnh_cliente)
        {
            return c;
        }
    }
    return NULL;
}

Clientes *incluir_clientes(Clientes *clientes)
{
    Clientes *novo = (Clientes *)malloc(sizeof(Clientes));
    if (novo == NULL)
    {
        printf("ERRO AO ALOCAR!!\n");
        exit(1);
    }
    informacoes_cliente(novo);
    if (verif_cliente_cadastrado(clientes, novo->cnh) != NULL)
    {
        printf("CLIENTE JA CADATRADO!! \n");
        free(novo);
        return clientes;
    }

    novo->prox = NULL;

    if (clientes == NULL)
    {
        return novo;
    }

    clientes->prox = novo;
    return clientes;
}

void listar_clientes(Clientes *clientes)
{
    printf("\tCLIENTES CADASTRADOS:\n\n");
    Clientes *p;
    if (clientes == NULL)
    {
        printf("NAO EXISTEM CLIENTES CADASTRADOS!!\n\n");
    }
    for (p = clientes; p != NULL; p = p->prox)
    {
        printf("NOME:%s\n", p->nome);
        printf("CNH:%d\n", p->cnh);
        printf("TELEFONE:%d\n\n", p->telefone);
    }
}