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

struct clientes
{
    int cnh;
    char *nome;
    int telefone;
    struct clientes *prox;
};
typedef struct clientes Clientes;




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

