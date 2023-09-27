#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct clientes
{
    char nome[50];
    int cnh;
    int telefone;
    struct clientes *prox;
};
typedef struct clientes Clientes;
// LISTA DE CADASTRO DE CLIENTES

void informacoes_veiculo(Clientes *novo)
{
    printf("NOME:");
    scanf(" %49s", novo->nome);

    printf("CNH");
    scanf("%d", novo->cnh);

    printf("VALOR DA DIARIA:");
    scanf("%d", novo->telefone);
    printf("\n");
}

Clientes *incluir_clientes(Clientes *clientes)
{
    Clientes *novo = (Clientes *)malloc(sizeof(Clientes));
    if (novo == NULL)
    {
        printf("ERRO AO ALOCAR!!");
        exit(1);
    }
    informacoes_cliente(novo);
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
    printf("CLIENTES CADASTRADOS:\n\n");
    Clientes *p;
    if (clientes == NULL)
    {
        printf("NAO EXISTEM CLIENTES CADASTRADOS!!");
    }
    for (p = clientes; p != NULL; p = p->prox)
    {
        printf("PLACA:%s\n", clientes->nome);
        printf("MARCA:%d\n", clientes->cnh);
        printf("MODELO:%d\n", clientes->telefone);
    }    
}