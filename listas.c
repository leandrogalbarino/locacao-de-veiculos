#include <stdio.h>
#include <stdlib.h>

struct lista
{
    int info;
    struct lista *prox;
};

struct lista_caracteres
{
    char cadeia[10];
    struct lista_caracteres *prox;
};
typedef struct lista_caracteres Lista_c;

typedef struct lista Lista;

/*Implemente uma função que altere uma lista, de forma que os valores positivos fiquem negativos e os negativos fiquem positivos.*/
Lista *lista_altera(Lista *l)
{
    Lista *p;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->info != 0)
        {
            p->info = p->info * (-1);
        }
    }
    return l;
}

Lista *lista_cria()
{
    return NULL;
}

Lista *lista_insere(Lista *l, int i)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = l;
    return novo;
}

void lista_imprime(Lista *l)
{
    Lista *p;
    if (l == NULL)
    {
        printf("Lista Vazia!!\n");
    }
    for (p = l; p != NULL; p = p->prox)
    {
        printf("%d\n", p->info);
    }
    printf("\n");
}

/*
Implemente uma função que insira elementos sempre ao final da lista. Esta função deve ter o protótipo:
*/

Lista *lista_busca_ultimo(Lista *l)
{
    Lista *p;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->prox == NULL)
        {
            return p;
        }
    }
    return l;
}

Lista *lista_insere_fim(Lista *l, int i)
{
    Lista *p = lista_busca_ultimo(l);
    // ultimo
    if (p == NULL)
    {
        l = (Lista *)malloc(sizeof(Lista));
        l->info = i;
        l->prox = NULL;
    }
    else
    {
        p->prox = (Lista *)malloc(sizeof(Lista));
        p = p->prox;
        p->info = i;
        p->prox = NULL;
    }

    return l;
}
/*
Implemente uma função que calcule a média aritmética dos valores armazenados.
*/
int lista_calculaMedia(Lista *l)
{
    Lista *p;
    int media = 0;
    int elementos = 0;
    if (l == NULL)
    {
        return media;
    }

    for (p = l; p != NULL; p = p->prox)
    {
        media = media + p->info;
        elementos++;
    }

    media = media / elementos;
    return media;
}

/*Implemente uma função que remova o elemento anterior a um elemento de valor v.
 */
Lista *lista_retira_ant(Lista *l, int v)
{
    Lista *ant;
    if (l == NULL)
    {
        return NULL;
    }
    Lista *p;
    ant = l;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->info == v)
        {
            ant->info = p->info;
            ant->prox = p->prox;
        }
        ant = p;
    }
    return l;
}

// Considere listas de valores inteiros e implemente uma função que receba como parâmetros uma lista encadeada e um valor inteiro n, retire da lista todas as ocorrências de n e retorne a lista resultante. Esta função deve obedecer ao protótipo:
Lista *retira_n(Lista *l, int n)
{
    // tratar o inicio;
    Lista *ant = NULL;
    Lista *p = l;
    while (p != NULL && p->info == n)
    {
        Lista *temp;
        temp = p;
        p = p->prox;
        free(temp);
    }

    l = p;

    while (p != NULL)
    {
        if (p->info == n)
        {
            Lista *temp = p;
            if (ant != NULL)
            {
                ant->prox = p->prox;
            }
            else
            {
                l = p->prox;
            }
            p = p->prox;
            free(temp);
        }
        else
        {
            ant = p;
            p = p->prox;
        }
    }
    return l;
}
// divida a lista em duas, de forma a segunda lista começar no primeiro nó logo após a ocorrência de n na lista original.

// A função deve retornar um ponteiro para a segunda subdivisão da lista original, enquanto l deve continuar apontando para o primeiro elemento da primeira subdivisão da lista.
Lista *separa(Lista *l, int n)
{
    Lista *p;
    Lista *nova = NULL;
    if (l == NULL || l->info == n)
    {
        return l;
    }

    else
    {
        for (p = l; p != NULL; p = p->prox)
        {
            if (p->info == n)
            {
                nova = p->prox;
                p->prox = NULL;
                break;
            }
        }
    }
    return nova;
}

// Implemente uma função que construa uma nova lista com a intercalação dos nós de outras duas listas passadas como parâmetros. Esta função deve retornar a lista resultante, conforme ilustrado a seguir:

// Esta função deve obedecer ao protótipo:
int lista_tamanho(Lista *l)
{
    int tamanho = 0;
    Lista *p;
    for (p = l; p != NULL; p = p->prox)
    {
        tamanho++;
    }
    return tamanho;
}

// listas iguais
Lista *merge(Lista *l1, Lista *l2)
{
    Lista *nova = lista_cria();
    Lista *p;
    Lista *q = l2;
    int tam1, tam2;
    tam1 = lista_tamanho(l1);
    tam2 = lista_tamanho(l2);
    if (tam1 == tam2)
    {
        for (p = l1; p != NULL; p = p->prox)
        {
            nova = lista_insere_fim(nova, p->info);
            nova = lista_insere_fim(nova, q->info);
            q = q->prox;
        }
    }
    return nova;
}

// Implemente uma função que receba como parâmetro uma lista encadeada e inverta o encadeamento de seus nós, retornando a lista resultante.
Lista *inverte(Lista *l)
{
    Lista *p;
    Lista *ant = NULL;
    Lista *temp;
    if (l == NULL)
    {
        return l;
    }

    for (p = l; p != NULL;)
    {
        temp = p->prox;
        p->prox = ant;
        ant = p;
        p = temp;
    }

    p = ant;
    return p;
}

// 6. Considere listas que armazenam cadeias de caracteres e implemente uma função para criar uma cópia de uma lista encadeada. Essa função deve obedecer ao protótipo:

Lista_c *lista_c_ultimo(Lista_c *l)
{
    Lista_c *p = l;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->prox == NULL)
        {
            break;
        }
    }
    return p;
}

Lista_c *lista_c_insere_fim(Lista_c *l, char *string)
{
    Lista_c *p = lista_c_ultimo(l);

    if (p == NULL)
    {
        l = (Lista_c *)malloc(sizeof(Lista_c));
        strcpy(p->cadeia, string);
        l->prox = NULL;
    }
    else
    {
        p->prox = (Lista_c *)malloc(sizeof(Lista_c));
        p = p->prox;
        strcpy(p->cadeia, string);
        p->prox = NULL;
    }
    return l;
}

Lista_c *lista_c_insere_inicio(Lista_c *l, char *string)
{
    Lista_c *p = (Lista_c *)malloc(sizeof(Lista_c));
    if (p == NULL)
    {
        return l;
    }

    strcpy(p->cadeia, string);
    p->prox = l;

    return p;
}

Lista_c *copia(Lista_c *l)
{
    Lista_c *p;
    Lista_c *copia = lista_cria();
    for (p = l; p != NULL; p = p->prox)
    {
        copia = lista_c_insere_string(copia, p->cadeia);
    }
    return copia;
}
