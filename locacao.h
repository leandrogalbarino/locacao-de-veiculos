#ifndef LOCACAO_H
#define LOCACAO_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "clientes.h"
#include "veiculos.h"

// LISTA DE LOCACAO DE VEICULOS
struct data
{
    int dia;
    int mes;
    int ano;
};
typedef struct data Data;

struct locacao_veiculos_por_clientes
{
    Clientes *cliente;
    Veiculos *veiculo_locado;

    Data retirada;
    Data devolucao;

    int valor_total_pago;

    struct locacao_veiculos_por_clientes *prox;
};
typedef struct locacao_veiculos_por_clientes Locacao;
// LISTA DE LOCACAO DE VEICULOS

Locacao *cria_lista_locacao();

void data_de_locacao(Data *retirada, Data *devolucao);

void informacoes_de_locacao(int *cnh_cliente, char *placa);

int compare_datas(Data a, Data b);

bool verif_disponibilidade(Locacao *veiculo_locado, Locacao *locacao);

Locacao *realizar_locacao(Locacao *locacao, Clientes *clientes, Veiculos *veiculos);

void devolver_veiculo(Locacao *locacao, Veiculos *veiculos);

Locacao *encontrar_locacao(Locacao *locacao, char *nome, char *placa);
#endif

void listar_locacao(Locacao *locacao);

void listar_loc_ativas(Locacao* locacao);

void listar_loc_realizadas(Locacao *locacao);

void listar_faturamento_mes(Locacao *locacao);