#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Implemente um sistema em C para controle de locação de veículos a clientes. O sistema deve atender aos seguintes requisitos:
// cadastro_veiculos;
struct veiculos
{
    char *placa;
    char *marca;
    char *modelo;
    int ano_fabricacao;
    int quilometragem;
    int valor_diaria;
    Data disponibilidade;
    struct veiculos *prox;
};
typedef struct veiculos Veiculos;
// LISTA DE CADASTRO DE VEICULOS

// cadastro_clientes;
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

// locacao_veiculos_por_clientes;
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

void apresenta_relatorio(Veiculos *veiculos, Clientes *clientes, Locacao *locacao, int escolha)
{
    switch (escolha)
    {
    case 1:
        listar_loc_ativas();
        // R1) Listar todas as locações ativas (clientes ainda não devolveram os carros) em uma certa data (a data é informada pelo usuário);
        break;
    case 2:
        // R2) Listar todas as locações já realizadas por um cliente (a CNH do cliente é informada pelo usuário);
        listar_loc_realizadas();
        break;
    case 3:
        // R3) Listar o faturamento da locadora por mês (mês é informado pelo usuário). Por faturamento, entenda o total arrecadado em locações.
        listar_faturamento_mes();
        break;
    case 4:
        // listar_placa_3_mais_rodados();
        break;
    case 5:
        // listar_veiculos_disponiveis();
        break;
    default:
        break;
    }
}

void menu_relatorios(Veiculos *veiculos, Clientes *clientes, Locacao *locacao)
{
    int escolha = 0;
    printf("RELATORIOS DISPONIVEIS:\n");

    printf("1: LISTAR TODAS LOCACOES ATIVAS\n");
    printf("2: LISTAR TODAS LOCACOES REALIZADAS POR UM CLIENTE\n");
    printf("3: LISTAR FATURAMENTO DA LOCACOES POR MES\n");
    printf("4: LISTAR A PLACA DOS 3 VEICULOS MAIS RODADOS\n");
    printf("5: LISTAR A PLACA E O MODELO DE TODOS OS VEICULOS DISPONIVEIS\n");

    do
    {
        printf("DIGITE O NUMERO DO RELATORIO QUE DESEJA VER:");
        scanf("%d", &escolha);
        if (escolha < 1 || escolha > 5)
        {
            printf("POR FAVOR DIGITE UM NUMERO VALIDO!\n");
        }
        printf("\n");
    } while (escolha < 1 || escolha > 5);

    apresenta_relatorio(veiculos, clientes, locacao, escolha);
}

// Faça um menu de opções que permita ao usuário realizar as operações descritas acima e gerar os seguintes relatórios:
void menu_opcoes(Veiculos *veiculos, Clientes *clientes, Locacao *locacao, int escolha)
{
    switch (escolha)
    {
    case 1:
        // veiculos = incluir_veiculos(veiculos);
        break;
    case 2:
        // listar_veiculos(veiculos);
        break;

    case 3:
        // clientes = incluir_clientes(clientes);
        break;
    case 4:
        // listar_clientes(clientes);
        break;
    case 5:
        realizar_locacao(locacao);
        break;
    case 6:
        devolver_veiculo(locacao);
        break;
    case 7:
        listar_locacao(locacao);
        break;
    case 8:
        menu_relatorios(veiculos, clientes, locacao);
        break;
    default:
        break;
    }
}

void menu_principal(Veiculos *veiculos, Clientes *clientes, Locacao *locacao)
{
    int escolha;
    printf("MENU:\n\n");

    printf("1. Incluir veiculos\n");
    printf("2. Listar veiculos\n");
    printf("3. Incluir clientes\n");
    printf("4. Listar clientes\n");
    printf("5. Realizar locação\n");
    printf("6. Devolver veículo\n");
    printf("7. Listar locações\n");
    printf("8. Gerar relatorios\n");

    do
    {
        printf("DIGITE O NUMERO DO QUE DESEJA VER:");
        scanf("%d", &escolha);
        if (escolha < 1 || escolha > 8)
        {
            printf("POR FAVOR DIGITE UM NUMERO VALIDO!\n");
        }
        printf("\n");
    } while (escolha < 1 || escolha > 8);
    menu_opcoes(veiculos, clientes, locacao, escolha);
}

int main()
{
    Veiculos *veiculos;
    Clientes *clientes;
    Locacao *locacao;
    menu_principal(veiculos, clientes, locacao);
}
