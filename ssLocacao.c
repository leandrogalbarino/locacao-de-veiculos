#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "estruturas.h"


void dias_de_locacao(Data *retirada, Data *devolucao)
{
    printf("DIGITE A DATA DE RETIRADA:\n");

    printf("DIA:");
    scanf("%d", retirada->dia);
    printf("MES:");
    scanf("%d", retirada->mes);
    printf("ANO:");
    scanf("%d", retirada->ano);
    printf("\n");    

    printf("DIGITE A DATA DE DEVOLUCAO:\n");
    printf("DIA:");
    scanf("%d", devolucao->dia);
    printf("MES:");
    scanf("%d", devolucao->mes);
    printf("ANO:");    
    scanf("%d", devolucao->ano);    
    printf("\n");    
}

void informacoes_de_locacao(char *nome_cliente, char *placa, Data *retirada, Data *devolucao)
{
    printf("PARA FAZER A LOCACAO DE UM VEICULO:\n\n");
    printf("DIGITE SEU NOME:");
    scanf("%s", nome_cliente);
    printf("\n");
    printf("DIGITE A PLACA DO VEICULO QUE DESEJA FAZER A LOCACAO:");
    scanf("%s", placa);
    printf("\n");
    dias_de_locacao(retirada, devolucao);
}

Clientes *verif_cliente_cadastrado(Clientes *clientes, char *nome_cliente)
{
    Clientes *c;
    for (c = clientes; c != NULL; c = c->prox)
    {
        if (strcmp(c->nome, nome_cliente) == 0)
        {
            return c;
        }
    }
    return NULL;
}

Veiculos *verif_veiculos_cadastrado(Veiculos *veiculos, char *placa)
{
    Veiculos *v;
    for (v = veiculos; v != NULL; v = v->prox)
    {
        if (strcmp(v->placa, placa) == 0)
        {
            if (v->disponibilidade == true)
            {
                return v;
            }
            break;
        }
    }
    return NULL;
}

// bool verif_disponibilidade(Veiculos *veiculo_locado, Locacao *locacao){
//     if(veiculo_locado->disponibilidade == true){
//         return true;
//     }
//     return false;
// }
Locacao *realizar_locacao(Locacao *locacao, Clientes *clientes, Veiculos *veiculos)
{
    if (clientes == NULL)
    {
        printf("NAO EXISTEM CLIENTES CADASTRADOS!!");
        return locacao;
    }
    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!");
        return locacao;
    }

    Locacao *novo = (Locacao *)malloc(sizeof(Locacao));
    novo->prox = locacao;

    char nome_cliente[50];
    char placa[50];
    Data retirada;
    Data devolucao;
    informacoes_de_locacao(nome_cliente, placa, &retirada, &devolucao);

    novo->cliente = verif_cliente_cadastrado(clientes, nome_cliente);
    novo->veiculo_locado = verif_veiculos_cadastrado(veiculos, placa);
    if(novo->veiculo_locado->disponibilidade == true){
        novo->retirada = retirada;
        novo->devolucao = devolucao;
    }

    if (novo->cliente == NULL || novo->veiculo_locado == NULL)
    {
        printf("NAO FOI POSSIVEL REALIZAR A LOCACAO!!");
        free(novo);
        return locacao;
    }

    return novo;
}
