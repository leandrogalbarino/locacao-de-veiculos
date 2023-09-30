#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "clientes.h"
#include "veiculos.h"
#include "locacao.h"

void apresenta_relatorio(Veiculos *veiculos, Clientes *clientes, Locacao *locacao, int escolha)
{
    switch (escolha)
    {
    case 1:
        // listar_loc_ativas();
        // R1) Listar todas as locações ativas (clientes ainda não devolveram os carros) em uma certa data (a data é informada pelo usuário);
        break;
    case 2:
        // R2) Listar todas as locações já realizadas por um cliente (a CNH do cliente é informada pelo usuário);
        // listar_loc_realizadas();
        break;
    case 3:
        // R3) Listar o faturamento da locadora por mês (mês é informado pelo usuário). Por faturamento, entenda o total arrecadado em locações.
        // listar_faturamento_mes();
        break;
    case 4:
        listar_placa_3_mais_rodados(veiculos);
        break;
    case 5:
        listar_veiculos_disponiveis(veiculos);
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
void esperar_enter()
{
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar(); // Aguarda o Enter ser pressionado
}
// Faça um menu de opções que permita ao usuário realizar as operações descritas acima e gerar os seguintes relatórios:
void menu_opcoes(Veiculos **veiculos, Clientes **clientes, Locacao **locacao, int escolha)
{
    switch (escolha)
    {
    case 1:
        *veiculos = incluir_veiculos(*veiculos);
        break;
    case 2:
        listar_veiculos(*veiculos);
        break;

    case 3:
        *clientes = incluir_clientes(*clientes);
        break;
    case 4:
        listar_clientes(*clientes);
        break;
    case 5:
        *locacao = realizar_locacao(*locacao, *clientes, *veiculos);
        break;
    case 6:
        // devolver_veiculo(locacao);
        break;
    case 7:
        // listar_locacao(locacao);
        break;
    case 8:
        menu_relatorios(*veiculos, *clientes, *locacao);
        break;
    default:
        break;
    }
    esperar_enter();
}

void menu_principal(Veiculos **veiculos, Clientes **clientes, Locacao **locacao)
{
    char sair;
    int escolha;
    do
    {
        system("cls");
        printf("\tMENU\n");

        printf("1. Incluir veiculos\n");
        printf("2. Listar veiculos\n");
        printf("3. Incluir clientes\n");
        printf("4. Listar clientes\n");
        printf("5. Realizar locacao\n");
        printf("6. Devolver veiculo\n");
        printf("7. Listar locacoes\n");
        printf("8. Gerar relatorios\n");
        printf("9. Sair\n");

        do
        {
            printf("DIGITE O NUMERO DO QUE DESEJA VER:");
            scanf("%d", &escolha);
            if (escolha < 1 || escolha > 9)
            {
                printf("POR FAVOR DIGITE UM NUMERO VALIDO!\n");
            }
            printf("\n");
        } while (escolha < 1 || escolha > 9);
        menu_opcoes(veiculos, clientes, locacao, escolha);

    } while (escolha != 9);
}

int main()
{
    Veiculos *veiculos = cria_lista_veiculos();
    Clientes *clientes = cria_lista_clientes();
    Locacao *locacao = cria_lista_locacao();
    menu_principal(&veiculos, &clientes, &locacao);
}
