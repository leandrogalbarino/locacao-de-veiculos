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

int difereca_entre_datas(Data date1, Data date2)
{
    int dias1 = date1.ano * 365 + date1.dia;
    int dias2 = date2.ano * 365 + date2.dia;

    dias1 += date1.ano / 4 - date1.ano / 100 + date1.ano / 400;
    dias2 += date2.ano / 4 - date2.ano / 100 + date2.ano / 400;

    int mesdias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = 1; i < date1.mes; i++)
    {
        dias1 += mesdias[i];
    }
    for (int i = 1; i < date2.mes; i++)
    {
        dias2 += mesdias[i];
    }

    if (date1.mes <= 2 && (date1.ano % 4 == 0 && (date1.ano % 100 != 0 || date1.ano % 400 == 0)))
    {
        dias1--;
    }
    if (date2.mes <= 2 && (date2.ano % 4 == 0 && (date2.ano % 100 != 0 || date2.ano % 400 == 0)))
    {
        dias2--;
    }

    int diferenca = dias2 - dias1;
    return diferenca;
}

int calcula_valor_locacao(Locacao *loc)
{
    int valorTotal;
    valorTotal = (difereca_entre_datas(loc->retirada, loc->devolucao) + 1) * loc->veiculo_locado->valor_diaria;
    return valorTotal;
}

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
            if (p->retirada.ano == veiculo_locado->retirada.ano || p->devolucao.ano == veiculo_locado->retirada.ano)
            {
                if (compare_datas(p->devolucao, veiculo_locado->retirada) < 0)
                {
                    return false;
                }
            }
        }
    }
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
    if (novo == NULL)
    {
        printf("ERRO AO ALOCAR!!\n");
        exit(1);
    }
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

    if (novo->veiculo_locado->disponibilidade == true)
    {
        datas_de_locacao(&retirada, &devolucao);
        novo->retirada = retirada;
        novo->devolucao = devolucao;
        novo->valor_total_pago = calcula_valor_locacao(novo);
        novo->veiculo_locado->disponibilidade = false;
        printf("LOCACAO REALIZADA COM SUCESSO!!\n");
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

    printf("DIGITE A CNH CLIENTE: ");
    scanf("%d", &cnh);

    printf("DIGITE A PLACA DO CARRO: ");
    scanf("%s", placa);

    Locacao *loc = encontrar_locacao(locacao, cnh, placa);

    if (loc != NULL)
    {
        int novaQuilometragem;

        printf("DIGITE A NOVA QUILOMETRAGEM: ");
        scanf("%d", &novaQuilometragem);

        loc->veiculo_locado->quilometragem = novaQuilometragem;
        loc->veiculo_locado->disponibilidade = true;

        printf("VEICULO DEVOLVIDO COM SUCESSO.\n");

        printf("VALOR TOTAL A PAGAR R$ %d\n", loc->valor_total_pago);
    }
    else
    {
        printf("LOCACAO NAO FOI ENCONTRADA.\n");
    }
}

void listar_locacao(Locacao *locacao)
{
    Locacao *p;

    if (locacao == NULL)
    {
        printf("NAO EXISTE NENHUMA LOCACAO!\n");
    }
    else
    {
        printf("LOCACOES:\n");

        for (p = locacao; p != NULL; p = p->prox)
        {
            printf("\n");
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
            printf("NOME DO CLIENTE: %s\n", p->cliente->nome);
            printf("PLACA DO VEICULO: %s\n", p->veiculo_locado->placa);
            printf("DATA DE RETIRADA: %d/%d/%d\n", p->retirada.dia, p->retirada.mes, p->retirada.ano);
            printf("DATA DE DEVOLUCAO: %d/%d/%d\n", p->devolucao.dia, p->devolucao.mes, p->devolucao.ano);
            encontrou = true;
        }
    }

    if (encontrou == false)
    {
        printf("NAO FORAM ENCONTRADAS LOCACOES NA DATA %d/%d/%d\n", data.dia, data.mes, data.ano);
    }
}

void listar_loc_realizadas(Locacao *locacao)
{
    int cnh;
    bool encontrou = false;
    Locacao *p;
    int quant_locacoes = 0;
    if (locacao == NULL)
    {
        printf("NAO EXISTEM LOCACOES!!\n");
        return;
    }
    printf("DIGITE A CHN DO CLIENTE: ");
    scanf("%d", &cnh);

    for (p = locacao; p != NULL; p = p->prox)
    {
        if (cnh == p->cliente->cnh)
        {
            if (quant_locacoes == 0)
            {
                printf("LOCACOES FEITAS PELO CLIENTE: %s\n", p->cliente->nome);
                quant_locacoes++;
            }
            printf("\n");
            printf("PLACA DO VEICULO: %s\n", p->veiculo_locado->placa);
            printf("DATA DE RETIRADA: %d/%d/%d\n", p->retirada.dia, p->retirada.mes, p->retirada.ano);
            printf("DATA DE DEVOLUCAO: %d/%d/%d\n", p->devolucao.dia, p->devolucao.mes, p->devolucao.ano);
            encontrou = true;
        }
    }

    if (encontrou == false)
    {
        printf("NAO FOI ENCONTRADO NENHUMA LOCACAO DO CLIENTE COM CNH: %d\n", cnh);
    }
}

void listar_faturamento_mes(Locacao *locacao)
{
    int mes, ano, faturamento = 0;
    Locacao *p;

    printf("INFORME O MES E O ANO PARA CONSULTAR O FATURAMENTO:\n");
    do
    {
        printf("DIGITE O MES:");
        scanf("%d", &mes);
        if (mes < 1 || mes > 12)
        {
            printf("DIGITE UM MES VALIDO!!\n");
        }
    } while (mes < 1 || mes > 12);
    printf("DIGITE O ANO:");
    scanf("%d", &ano);
    printf("FATURAMENTO DA LOCADORA NO MES %d DO ANO %d:\n\n", mes, ano);
    for (p = locacao; p != NULL; p = p->prox)
    {
        if (p->retirada.mes == mes && p->retirada.ano == ano)
        {
            faturamento += p->valor_total_pago;
        }
    }

    if (faturamento <= 0)
    {
        printf("NAO HOUVE FATURAMENTO NO MES %d DO ANO %d.\n", mes, ano);
    }
    else
    {
        printf("VALOR FATURADO NO MES %d DO ANO %d: R$ %d\n", mes, ano, faturamento);
    }
}
