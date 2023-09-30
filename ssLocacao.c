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
