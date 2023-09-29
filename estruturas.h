#ifndef ESTRUTURA_H  
#define ESTRUTURA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// LISTA DE CADASTRO DE VEICULOS
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

// LISTA DE CADASTRO DE CLIENTES
struct clientes
{
    char nome[50];
    int cnh;
    int telefone;
    struct clientes *prox;
};
typedef struct clientes Clientes;

// LISTA DE LOCACAO DE VEICULOS
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

#endif