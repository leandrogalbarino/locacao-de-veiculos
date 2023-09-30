#ifndef VEICULOS_H
#define VEICULOS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// LISTA DE CADASTRO DE VEICULOS
struct veiculos
{
    char placa[50];
    char marca[50];
    char modelo[50];
    int ano_fabricacao;
    int quilometragem;
    int valor_diaria;
    bool disponibilidade;
    struct veiculos *prox;
};
typedef struct veiculos Veiculos;

Veiculos *cria_lista_veiculos();

void informacoes_veiculo(Veiculos *novo);

Veiculos *incluir_veiculos(Veiculos *veiculos);

char *veiculo_disponivel(bool disponibilidade);

void listar_veiculos(Veiculos *veiculos);

void listar_veiculos_disponiveis(Veiculos *veiculos);

int compararVeiculos(const void *a, const void *b);

void reorganizarLista(Veiculos **l, Veiculos **vet, int tamanho);

Veiculos *lista_ordena(Veiculos *l);

void listar_placa_3_mais_rodados(Veiculos *veiculos);

Veiculos *verif_veiculos_cadastrado(Veiculos *veiculos, char *placa);

#endif