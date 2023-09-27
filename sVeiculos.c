#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct veiculos
{
    char *placa[50];
    char *marca[50];
    char *modelo[50];
    int ano_fabricacao;
    int quilometragem;
    int valor_diaria;
    bool disponibilidade;
    struct veiculos *prox;
};
typedef struct veiculos Veiculos;
// LISTA DE CADASTRO DE VEICULOS

void informacoes_veiculo(Veiculos *novo)
{
    printf("MODELO DO VEICULO:");
    scanf(" %49s", novo->modelo);

    printf("MARCA DO VEICULO:");
    scanf(" %49s", novo->marca);

    printf("PLACA DO VEICULO:");
    scanf(" %49s", novo->placa);

    printf("ANO DA FABRICACAO:");
    scanf("%d", novo->ano_fabricacao);

    printf("QUILOMETRAGEM ATUAL:");
    scanf("%d", novo->quilometragem);

    printf("VALOR DA DIARIA:");
    scanf("%d", novo->valor_diaria);

    printf("\n");
}

Veiculos *incluir_veiculos(Veiculos *veiculos)
{
    Veiculos *novo = (Veiculos *)malloc(sizeof(Veiculos));
    if (novo == NULL)
    {
        printf("ERRO AO ALOCAR!!");
        exit(1);
    }
    informacoes_veiculo(novo);
    novo->prox = NULL;

    if (veiculos == NULL)
    {
        return novo;
    }

    veiculos->prox = novo;
    return veiculos;
}

char *veiculo_disponivel(bool disponibilidade)
{
    if (disponibilidade == true)
    {
        return "DISPONIVEL";
    }
    else
    {
        return "INDISPONIVEL";
    }
}

void listar_veiculos(Veiculos *veiculos)
{
    printf("VEICULOS CADASTRADOS:\n\n");
    Veiculos *p;
    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!");
    }
    for (p = veiculos; p != NULL; p = p->prox)
    {
        printf("PLACA:%s\n", veiculos->placa);
        printf("MARCA:%s\n", veiculos->marca);
        printf("MODELO:%s\n", veiculos->modelo);

        printf("ANO DE FABRICACAO:%d\n");
        printf("QUILOMETRAGEM:%d\n");
        printf("VALOR DA DIARIA:%d\n");
        printf("DISPONIVEL:%s\n\n", veiculo_disponivel(veiculos->disponibilidade));
    }
}

void listar_veiculos_disponiveis(Veiculos *veiculos)
{
    Veiculos *p;
    int disponiveis = 0;

    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!\n\n");
    }

    printf("VEICULOS DISPONIVEIS:\n\n");
    for (p = veiculos; p != NULL; p = p->prox)
    {
        if (p->disponibilidade == true)
        {
            printf("PLACA:%s\n", veiculos->placa);
            printf("MODELO:%s\n\n", veiculos->modelo);
            disponiveis++;
        }
    }
    if (disponiveis == 0)
    {
        printf("NAO EXISTEM VEICULOS DISPONIVEIS!!");
    }
}

int compararVeiculos(const void *a, const void *b)
{
    const Veiculos *veiculo1 = (const Veiculos *)a;
    const Veiculos *veiculo2 = (const Veiculos *)b;

    return veiculo2->quilometragem - veiculo1->quilometragem;
}

void reorganizarLista(Veiculos **l, Veiculos **vet, int tamanho)
{
    if (tamanho == 0)
    {
        *l == NULL;
        return;
    }
    *l = vet[0];

    for (int i = 0; i < tamanho; i++)
    {
        vet[i]->prox = vet[i+1];
    }
    
    vet[tamanho - 1]->prox = NULL;
}

Veiculos lista_ordena(Veiculos *l)
{
    int tamanho = 0;
    Veiculos *p = l;
    while (p != NULL)
    {
        tamanho++;
        p = p->prox;
    }

    Veiculos *vet[tamanho];
    int i = 0;
    for (p = l; p != NULL; p = p->prox)
    {
        vet[i] = p;
        p = p->prox;
        i++;
    }
    qsort(vet, tamanho, sizeof(Veiculos), compararVeiculos);
    reorganizarLista(&l, vet, tamanho);
}

void listar_placa_3_mais_rodados(Veiculos *veiculos)
{
    Veiculos *aux;
    Veiculos *p;

    if (veiculos == NULL)
    {
        printf("NAO EXISTEM VEICULOS CADASTRADOS!!\n\n");
    }
    Veiculos *ant = NULL;

    for (p = veiculos; p != NULL; p = p->prox)
    {
        if (ant != NULL && p->prox != NULL)
        {
            if (p->prox->quilometragem > p->quilometragem)
            {
                ant->prox = p->prox;
                aux = p->prox->prox;
                p->prox->prox = p;
                p->prox = aux;
            }
        }
        ant = p;
    }

    printf("3 VEICULOS MAIS RODADOS:\n\n");
}