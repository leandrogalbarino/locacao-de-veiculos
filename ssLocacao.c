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

int diasdoMes(int mes, int ano){
    int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verifica se é um ano bissexto e atualiza o número de dias em fevereiro
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        dias[1] = 29;
    }

    return dias[mes - 1];
}


void devolver_veiculo(Locacao *locacao, Veiculos *veiculos) {
    int cnh;
    char placa[50];

    printf("DIGITE A CNH CLIENTE: ");
    scanf("%d", &cnh);

    printf("DIGITE A PLACA DO CARRO: ");
    scanf("%s", placa);

    Locacao *loc = encontrar_locacao(locacao, cnh, placa);

    if (loc != NULL) {
        int novaQuilometragem, difeQuilometragem, dias, valorTotal, diasDevolucao;

        printf("DIGITE A NOVA QUILOMETRAGEM: ");
        scanf("%d", &novaQuilometragem);

        // Calcula a diferença na quilometragem
        difeQuilometragem = novaQuilometragem - loc->veiculo_locado->quilometragem;

        // Calcula o valor total da locação
        dias = compare_datas(loc->retirada, loc->devolucao);
        valorTotal = dias * loc->veiculo_locado->valor_diaria + difeQuilometragem;

        // Correção para casos onde a locação atravessa meses diferentes
        if (loc->retirada.mes != loc->devolucao.mes) {
            // Calcula o número total de dias no mês de devolução
            diasDevolucao = diasdoMes(loc->devolucao.mes, loc->devolucao.ano);
            //calculo de quantos de locacao ocorrem no mes colocando o +1 para incluir o proprio dia de devolucao
            valorTotal += (diasDevolucao - loc->devolucao.dia + 1) * loc->veiculo_locado->valor_diaria;
        }

        // Atualiza a quilometragem do veículo
        loc->veiculo_locado->quilometragem = novaQuilometragem;

        // Deixa o veículo disponível para locação
        loc->veiculo_locado->disponibilidade = true;

        printf("VEICULO DEVOLVIDO COM SUCESSO.\n");
        
        printf("VALOR TOTAL A PAGAR R$ %d\n", valorTotal);
    } else {
        printf("LOCACAO NAO FOI ENCONTRADA.\n");
    }
}



void listar_locacao(Locacao *locacao)
{
    Locacao *p;

    if (locacao == NULL)
    {
        printf("NAO EXISTE NENHUMA LOCACAO.\n");
    }
    else
    {
        printf("Locacoes:\n\n");

        for (p = locacao; p != NULL; p = p->prox)
        {
            printf("NOME DO CLIENTE: %s\n", p->cliente->nome);
            printf("PLACA DO VEICULO: %s\n", p->veiculo_locado->placa);
            printf("DATA DE RETIRADA: %d/%d/%d\n", p->retirada.dia, p->retirada.mes, p->retirada.ano);
            printf("DATA DE DEVOLUCAO: %d/%d/%d\n", p->devolucao.dia, p->devolucao.mes, p->devolucao.ano);
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
    printf("INFORME O DIA DA LOCACAO: ");
    scanf("%d", &data.dia);
    printf("INFORME O MES DA LOCACAO: ");
    scanf("%d", &data.mes);
    printf("INFORME O ANO DA LOCACAO: ");
    scanf("%d", &data.ano);

    printf("LOCACOES ATIVAS NO DIA: %d/%d/%d\n\n", data.dia, data.mes, data.ano);

    for (p = locacao; p != NULL; p = p->prox)
    {
        // verifica se a data fornecida é maior ou igual a data de retirada e menor ou igual a data de devolucao
        if (compare_datas(p->retirada, data) <= 0 && compare_datas(p->devolucao, data) >= 0)
        {
            // lista as informacoes e seta encontrou como verdadeiro
            printf("NOME DO CLIENTE: %s\n", p->cliente->nome);
            printf("PLACA DO VEICULO: %s\n", p->veiculo_locado->placa);
            printf("DATA DE RETIRADA: %d/%d/%d\n", p->retirada.dia, p->retirada.mes, p->retirada.ano);
            printf("DATA DE DEVOLUCAO: %d/%d/%d\n", p->devolucao.dia, p->devolucao.mes, p->devolucao.ano);
            encontrou = true;
        }
    }

    if (encontrou == false)
    {
        printf("NAO POSSUEM LOCACOES ATIVAS NA DATA %d/%d/%d\n", data.dia, data.mes, data.ano);
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
    printf("DIGITE A CHN DO CLIENTE: ");
    scanf("%d", &cnh);

    for (p = locacao; p != NULL; p = p->prox)
    {
        // compara a chn do cliente com a fornecida pelo usuario, se for igual seta encontrou como verdadeiro
        if (cnh == p->cliente->cnh && p->cliente != NULL)
        {
            printf("LOCACOES FEITAS PELO CLIENTE: %s\n", p->cliente->nome);
            printf("PLACA DO VEICULO: %s\n", p->veiculo_locado->placa);
            printf("DATA DE RETIRADA: %d/%d/%d\n", p->retirada.dia, p->retirada.mes, p->retirada.ano);
            printf("DATA DE DEVOLUCAO: %d/%d/%d\n", p->devolucao.dia, p->devolucao.mes, p->devolucao.ano);
            encontrou = true;
        }
    }

    if (encontrou == false)
    {
        printf("NAO FOI ENCONTRADO NENHUMA LOCACAO DO CLIENTE COM CNH: %d", cnh);
    }
}

void listar_faturamento_mes(Locacao *locacao)
{
    int dias, mes, faturamento = 0;
    Locacao *p;

    printf("INFORME O MES PARA CONSULTAR O FATURAMENTO: ");
    scanf("%d", &mes);

    printf("FATURAMENTO DA LOCADORA NO MES %d:\n", mes);
    for (p = locacao; p != NULL; p = p->prox)
    {
        if (p->retirada.mes == mes)
        {
            dias = compare_datas(p->retirada, p->devolucao);
            faturamento += dias * p->veiculo_locado->valor_diaria;
        }
    }

    if (faturamento < 0)
    {
        printf("NAO HOUVE FATURAMENTO NO MES %d.\n", mes);
    }
    else
    {
        printf("VALOR FATURADO NO MES %d: R$ %d\n", mes, faturamento);
    }
}
