#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct veiculos
{
    char *placa;
    char *marca;
    char *modelo;
    int ano_fabricacao;
    int quilometragem;
    int valor_diaria;
    bool disponibilidade;
    struct veiculos *prox;
};
typedef struct veiculos Veiculos;
// LISTA DE CADASTRO DE VEICULOS

struct clientes
{
    int cnh;
    char *nome;
    int telefone;
    struct clientes *prox;
};
typedef struct clientes Clientes;
// LISTA DE CADASTRO DE CLIENTES

struct data
{
    int retirada;
    int devolucao;
};
typedef struct data Data;

struct locacao_veiculos_por_clientes
{
    // Se não for cadastrado, cadastrar cliente; Retornar a posicao do cliente que alugou o veiculo;
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

/*Implemente uma função que altere uma lista, de forma que os valores positivos fiquem negativos e os negativos fiquem positivos.*/

Locacao *lista_cria()
{
    return NULL;
}

Clientes *Clientes_busca(Clientes *l)
{
    Locacao *p;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p == l)
        {
            return p;
        }
    }
    return p;
}

Locacao *lista_insere(Locacao *l, int i)
{
    Locacao *novo = (Locacao *)malloc(sizeof(Locacao));
    Clientes *p = Clientes_busca(l->cliente);

    if (p == NULL)
    {
        // cadastrar cliente;
    }
    novo->cliente = i;
    novo->veiculo_alocado = i;
    novo->dia.retirada = i;
    novo->dia.devolucao = i;

    novo->prox = l;
    return novo;
}

Locacao *lista_busca_ultimo(Locacao *l)
{
    Locacao *p;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->prox == NULL)
        {
            return p;
        }
    }
    return l;
}

void lista_imprime(Locacao *l)
{
    Locacao *p;
    if (l == NULL)
    {
        printf("Locacao Vazia!!\n");
    }
    for (p = l; p != NULL; p = p->prox)
    {
        printf("%d\n", p->info);
    }
    printf("\n");
}

Locacao *lista_insere_fim(Locacao *l, int i)
{
    Locacao *p = lista_busca_ultimo(l);
    // ultimo
    if (p == NULL)
    {
        l = (Locacao *)malloc(sizeof(Locacao));
        l->info = i;
        l->prox = NULL;
    }
    else
    {
        p->prox = (Locacao *)malloc(sizeof(Locacao));
        p = p->prox;
        p->info = i;
        p->prox = NULL;
    }

    return l;
}