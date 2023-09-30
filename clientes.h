#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// LISTA DE CADASTRO DE CLIENTES
struct clientes
{
    char nome[50];
    int cnh;
    int telefone;
    struct clientes *prox;
};
typedef struct clientes Clientes;

Clientes *cria_lista_clientes();

void informacoes_cliente(Clientes *novo);

Clientes *incluir_clientes(Clientes *clientes);

void listar_clientes(Clientes *clientes);

Clientes *verif_cliente_cadastrado(Clientes *clientes, int cnh_cliente);

#endif