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