#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "veiculos.h"
#include "clientes.h"
#include "locacao.h"

Locacao *cria_lista_locacao()
{
    return NULL;
}

void datas_de_locacao(Data *retirada, Data *devolucao)
{
    printf("DIGITE A DATA DE RETIRADA:\n");

    printf("DIA:");
    scanf("%d", &retirada->dia);
    printf("MES:");
    scanf("%d", &retirada->mes);
    printf("ANO:");
    scanf("%d", &retirada->ano);
    printf("\n");

    printf("DIGITE A DATA DE DEVOLUCAO:\n");
    printf("DIA:");
    scanf("%d", &devolucao->dia);
    printf("MES:");
    scanf("%d", &devolucao->mes);
    printf("ANO:");
    scanf("%d", &devolucao->ano);
    printf("\n");
}

void informacoes_de_locacao(int *cnh_cliente, char *placa)
{
    printf("PARA FAZER A LOCACAO DE UM VEICULO:\n");
    printf("DIGITE SEU CNH:");
    scanf("%d", cnh_cliente);
    printf("\n");
    printf("DIGITE A PLACA DO VEICULO QUE DESEJA FAZER A LOCACAO:");
    scanf("%s", placa);
    printf("\n");
}

// Função auxiliar para comparar datas (retorna 0 se iguais, < 0 se a < b, > 0 se a > b)
int compare_datas(Data a, Data b)
{
    if (a.ano == b.ano)
    {
        if (a.mes == b.mes)
        {
            return a.dia - b.dia;
        }
        return a.mes - b.mes;
    }
    return a.ano - b.ano;
}

bool verif_disponibilidade(Locacao *veiculo_locado, Locacao *locacao)
{
    Locacao *p;

    for (p = locacao; p != NULL; p = p->prox)
    {
        if (strcmp(p->veiculo_locado->placa, veiculo_locado->veiculo_locado->placa) == 0)
        {
            // Verifique se a locação está no mesmo ano da retirada do veículo
            if (p->retirada.ano == veiculo_locado->retirada.ano)
            {
                // Verifique se a devolução é posterior à retirada do veículo
                if (compare_datas(p->devolucao, veiculo_locado->retirada) < 0)
                {
                    // Se ambos os critérios forem atendidos, o veículo não está disponível
                    return false;
                }
            }
        }
    }
    // Se nenhum conflito for encontrado, o veículo está disponível
    return true;
}

Locacao *realizar_locacao(Locacao *locacao, Clientes *clientes, Veiculos *veiculos)
{
    if (clientes == NULL)
    {
        printf("NAO EXISTEM CLIENTES CADASTRADOS!!\n\n");
        return locacao;
    }
    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!\n\n");
        return locacao;
    }

    Locacao *novo = (Locacao *)malloc(sizeof(Locacao));
    novo->prox = locacao;

    int cnh_cliente;
    char placa[50];
    Data retirada;
    Data devolucao;
    informacoes_de_locacao(&cnh_cliente, placa);

    novo->cliente = verif_cliente_cadastrado(clientes, cnh_cliente);
    novo->veiculo_locado = verif_veiculos_cadastrado(veiculos, placa);

    if (novo->cliente == NULL || novo->veiculo_locado == NULL)
    {
        printf("NAO FOI POSSIVEL REALIZAR A LOCACAO!!\n");
        free(novo);
        return locacao;
    }
    if (novo->veiculo_locado->disponibilidade == false)
    {
        printf("VEICULO INDISPONIVEL!!\n");
        free(novo);
        return locacao;
    }
    // DATA NÃO É PARA DISPONIBILIDADE E SIM PARA CALCULAR O VALOR DA DIARIA;

    if (novo->veiculo_locado->disponibilidade == true)
    {
        datas_de_locacao(&retirada, &devolucao);
        novo->retirada = retirada;
        novo->devolucao = devolucao;
        novo->veiculo_locado->disponibilidade = false;
    }
    else
    {
        printf("VEICULO INDISPONIVEL!!");
        free(novo);
        return locacao;
    }

    return novo;
}

Locacao *encontrar_locacao(Locacao *locacao, int cnh, char *placa)
{
    Locacao *p;

    // percore a lista de locacao e verifica se o nome e a placa solicitada foi encontrada na locacao
    // se for encontrada retorna um ponteiro pra essa locacao, senao retorna NULL
    for (p = locacao; p != NULL; p = p->prox)
    {
        if (p->cliente->cnh == cnh && strcmp(p->veiculo_locado->placa, placa) == 0)
        {
            return p;
        }
    }
    return NULL;
}

void devolver_veiculo(Locacao *locacao, Veiculos *veiculos)
{
    int cnh;
    char placa[50];
    // Solicita o nome do cliente e a placa do carro
    printf("Digite a cnh cliente: ");
    scanf("%d", &cnh);

    printf("Digite a placa do carro: ");
    scanf("%s", placa);

    // Chama a funcao para verificar se o nome e a placa foram encontradas na locacao
    // Se for diferente de NULL significa que foi encontrado e sera possivel devolver o veiculo
    // Mudando a flag pra true
    Locacao *loc = encontrar_locacao(locacao, cnh, placa);

    if (loc != NULL)
    {
        int novaQuilometragem, dias, valorTotal;
        printf("Digite a nova quilometragem: ");
        scanf("%d", &novaQuilometragem);

        // calcula os dias de locacao
        dias = compare_datas(loc->retirada, loc->devolucao);

        // calcula o valor total entre dias de locacao * valor da diaria
        valorTotal = dias * loc->veiculo_locado->valor_diaria;

        // armazena a nova quilometragem do veiculo
        loc->veiculo_locado->quilometragem = novaQuilometragem;

        // deixa o veiculo disponivel para locacao
        loc->veiculo_locado->disponibilidade = true;

        printf("Veiculo devolvido com sucesso.\n");
        printf("Valor total a pagar R$ %d\n", valorTotal);
    }
    else
    {
        printf("Locacao nao foi encontrada.\n");
    }
}

void listar_locacao(Locacao *locacao)
{
    Locacao *p;

    if (locacao == NULL)
    {
        printf("Nao existe nenhuma locacao.\n");
    }
    else
    {
        printf("Locacoes:\n\n");

        for (p = locacao; p != NULL; p = p->prox)
        {
            printf("Nome do Cliente: %s\n", p->cliente->nome);
            printf("Placa do Veiculo: %s\n", p->veiculo_locado->placa);
            printf("Data de Retirada: %d/%d/%d\n", p->retirada.dia, p->retirada.mes, p->retirada.ano);
            printf("Data de Devolucao: %d/%d/%d\n", p->devolucao.dia, p->devolucao.mes, p->devolucao.ano);
        }
    }
}

void listar_loc_ativas(Locacao *locacao)
{
    bool encontrou = false;
    Data data;
    Locacao *p;
    if (locacao == NULL)
    {
        printf("NAO EXISTEM LOCACOES REALIZADAS!!\n");
        return;
    }
    printf("Informe o dia da locacao: ");
    scanf("%d", &data.dia);
    printf("Informe o mes da locacao: ");
    scanf("%d", &data.mes);
    printf("Informe o ano da locacao: ");
    scanf("%d", &data.ano);

    printf("Locacoes ativas no dia: %d/%d/%d\n\n", data.dia, data.mes, data.ano);

    for (p = locacao; p != NULL; p = p->prox)
    {
        // verifica se a data fornecida é maior ou igual a data de retirada e menor ou igual a data de devolucao
        if (compare_datas(p->retirada, data) <= 0 && compare_datas(p->devolucao, data) >= 0)
        {
            // lista as informacoes e seta encontrou como verdadeiro
            printf("Nome do cliente: %s\n", p->cliente->nome);
            printf("Placa do veiculo: %s\n", p->veiculo_locado->placa);
            printf("Data de retirada: %d/%d/%d\n", p->retirada.dia, p->retirada.mes, p->retirada.ano);
            printf("Data de devolucao: %d/%d/%d\n", p->devolucao.dia, p->devolucao.mes, p->devolucao.ano);
            encontrou = true;
        }
    }

    if (encontrou == false)
    {
        printf("Nao possuem locacoes ativas na data %d/%d/%d\n", data.dia, data.mes, data.ano);
    }
}

void listar_loc_realizadas(Locacao *locacao)
{
    int cnh;
    bool encontrou = false;
    Locacao *p;

    if (locacao == NULL)
    {
        printf("NAO EXISTEM LOCACOES!!\n");
        return;
    }
    printf("Digite a CHN do cliente: ");
    scanf("%d", &cnh);

    for (p = locacao; p != NULL; p = p->prox)
    {
        // compara a chn do cliente com a fornecida pelo usuario, se for igual seta encontrou como verdadeiro
        if (cnh == p->cliente->cnh && p->cliente != NULL)
        {
            printf("Locacoes feitas pelo cliente: %s\n", p->cliente->nome);
            printf("Placa do veiculo: %s\n", p->veiculo_locado->placa);
            printf("Data de retirada: %d/%d/%d\n", p->retirada.dia, p->retirada.mes, p->retirada.ano);
            printf("Data de devolucao: %d/%d/%d\n", p->devolucao.dia, p->devolucao.mes, p->devolucao.ano);
            encontrou = true;
        }
    }

    if (encontrou == false)
    {
        printf("Nao foi encontrado nenhuma locacao do cliente com CNH: %d", cnh);
    }
}

// errado o CALCULO;
void listar_faturamento_mes(Locacao *locacao)
{
    bool encontrou = false;
    int dias, mes, faturamento, valorTotal;
    Locacao *p;

    printf("Informe o mes para consultar o faturamento: ");
    scanf("%d", &mes);

    printf("Faturamento da locador no mes %d.\n", mes);
    for (p = locacao; p != NULL; p = p->prox)
    {
        // verifca o mes das locacoes com o mes fornecido pelo usuario para poder fazer o calculo do faturamento naquele mes
        if (p->retirada.mes == mes)
        {
            dias = compare_datas(p->retirada, p->devolucao);
            valorTotal = dias * p->veiculo_locado->valor_diaria;
            faturamento += valorTotal;
            encontrou = true;
        }
    }

    if (encontrou == false)
    {
        printf("Nao houve faturamente no mes: %d", mes);
    }
    else
    {
        printf("Valor faturado: %d\n", faturamento);
    }
}