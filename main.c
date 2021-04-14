#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

#define C_CLIENTES 5
#define D_VOLUNTARIOS 5

typedef struct
{
  int Codigo;
  char *Modelo;
  float Preco;
  char *Tamanho;
} ROUPA;

typedef struct LINKED_LIST
{
  ROUPA Atual;
  struct LINKED_LIST *Prox;
};

struct LINKED_LIST *roupas_venda;
struct LINKED_LIST *roupas_reparo;

void add_roupas_venda(ROUPA roupa)
{
  if (roupas_venda == NULL)
  {
    roupas_venda->Atual = roupa;
    free(roupas_venda->Prox);
  }
  else
  {
    struct LINKED_LIST roupa_atual = *roupas_venda;
    while (roupa_atual.Prox != NULL)
    {
      roupa_atual = *roupa_atual.Prox;
    }

    //struct LINKED_LIST *lista_final;
    //lista_final = (struct LINKED_LIST *)malloc(sizeof(struct LINKED_LIST));

    //lista_final->Atual = roupa;

    //roupa_atual.Prox = lista_final;
    //free(roupa_atual.Prox);
  }
}

void add_roupas_reparo(ROUPA roupa)
{
  if (roupas_reparo == NULL)
  {
    // roupas_reparo->Atual = roupa;
    // free(roupas_reparo->Prox);
  }
  else
  {
    struct LINKED_LIST roupa_atual = *roupas_reparo;
    while (roupa_atual.Prox != NULL)
    {
      roupa_atual = *roupa_atual.Prox;
    }

    //struct LINKED_LIST *lista_final;
    //lista_final = (struct LINKED_LIST *)malloc(sizeof(struct LINKED_LIST));

    //lista_final->Atual = roupa;

    //roupa_atual.Prox = lista_final;
    //free(roupa_atual.Prox);
  }
}

ROUPA remove_roupas_venda(int codigo)
{
  if (roupas_venda != NULL)
  {
    ROUPA retorna_roupa;
    struct LINKED_LIST *roupa_atual = roupas_venda;
    if (roupa_atual->Prox != NULL)
    {
      while (roupa_atual->Prox != NULL)
      {
        if (roupa_atual->Prox != NULL && roupa_atual->Prox->Atual.Codigo == codigo)
        {
          if (roupa_atual->Prox->Prox != NULL)
          {
            retorna_roupa = roupa_atual->Prox->Atual;
            roupa_atual->Prox = roupa_atual->Prox->Prox;
          }
          else
          {
            retorna_roupa = roupa_atual->Prox->Atual;
            free(roupa_atual->Prox);
          }
        }
      }
    }
    else
    {
      retorna_roupa = roupa_atual->Atual;
      roupa_atual = roupa_atual->Prox;
    }

    return retorna_roupa;
  }
}

ROUPA remove_roupas_reparo(int codigo)
{
  if (roupas_reparo != NULL)
  {
    ROUPA retorna_roupa;
    struct LINKED_LIST *roupa_atual = roupas_reparo;
    if (roupa_atual->Prox != NULL)
    {
      while (roupa_atual->Prox != NULL)
      {
        if (roupa_atual->Prox != NULL && roupa_atual->Prox->Atual.Codigo == codigo)
        {
          if (roupa_atual->Prox->Prox != NULL)
          {
            retorna_roupa = roupa_atual->Prox->Atual;
            roupa_atual->Prox = roupa_atual->Prox->Prox;
          }
          else
          {
            retorna_roupa = roupa_atual->Prox->Atual;
            free(roupa_atual->Prox);
          }
        }
      }
    }
    else
    {
      retorna_roupa = roupa_atual->Atual;
      roupa_atual = roupa_atual->Prox;
    }

    return retorna_roupa;
  }
}

ROUPA remove_ultima_roupas_venda(void)
{
  if (roupas_venda != NULL)
  {
    ROUPA retorna_roupa;
    struct LINKED_LIST *roupa_atual = roupas_venda;
    if (roupa_atual->Prox != NULL)
    {
      do
      {
        roupa_atual = roupa_atual->Prox;
      } while (roupa_atual->Prox != NULL);
    }
    retorna_roupa = roupa_atual->Atual;
    free(roupa_atual->Prox);

    return retorna_roupa;
  }
}

ROUPA remove_ultima_roupas_reparo(void)
{
  if (roupas_reparo != NULL)
  {
    ROUPA retorna_roupa;
    struct LINKED_LIST *roupa_atual = roupas_reparo;
    if (roupa_atual->Prox != NULL)
    {
      do
      {
        roupa_atual = roupa_atual->Prox;
      } while (roupa_atual->Prox != NULL);
    }
    retorna_roupa = roupa_atual->Atual;
    free(roupa_atual->Prox);

    return retorna_roupa;
  }
}

ROUPA remove_roupas_aleatoria_venda(void)
{
  if (roupas_venda != NULL)
  {
    ROUPA retorna_roupa;
    struct LINKED_LIST *roupa_atual = roupas_venda;
    while (roupa_atual->Prox != NULL)
    {
      int random = rand();
      if (roupa_atual->Prox != NULL && random % 2)
      {
        if (roupa_atual->Prox->Prox != NULL)
        {
          retorna_roupa = roupa_atual->Prox->Atual;

          roupa_atual = realloc(roupa_atual->Prox, sizeof(roupa_atual->Prox->Prox));
          roupa_atual->Prox = roupa_atual->Prox->Prox;
        }
        else
        {
          retorna_roupa = roupa_atual->Prox->Atual;
          free(roupa_atual->Prox);
        }
      }
    }
    retorna_roupa = roupa_atual->Atual;

    roupa_atual = (struct LINKED_LIST *)realloc(roupas_venda, sizeof(roupa_atual->Prox));
    roupa_atual = roupa_atual->Prox;
    return retorna_roupa;
  }
}

void *cria_voluntario(void *threadid);
void *cria_cliente(void *threadid);

int criar_random_id(void)
{
  return rand() % 89;
}

char *pegar_random_modelo(void)
{
  char arr[][10] =
      {"Camisa",
       "Bermuda",
       "Calça",
       "Casaco"};

  char *selected = arr[rand() % 4];
  return selected;
}

char *pegar_random_tamanho(void)
{
  char arr[][10] =
      {"P",
       "M",
       "G",
       "GG"};

  char *selected = arr[rand() % 4];
  return selected;
}

float pegar_random_preco(void)
{
  return (rand() % 420) * 0.69;
}

ROUPA criar_random_roupa(void)
{
  ROUPA roupa;
  roupa.Codigo = criar_random_id();
  roupa.Modelo = pegar_random_modelo();
  roupa.Preco = pegar_random_preco();
  roupa.Tamanho = pegar_random_tamanho();
}

void *cria_voluntario(void *threadid)
{
  sleep(3);
  long tid = (long)threadid;
  if (tid % 3)
  {
    // Remove roupa mais antiga da lista de roupas a venda
    int len = sizeof(roupas_venda);
    int cod_remove = roupas_venda->Atual.Codigo;

    pthread_mutex_lock(&mutex);
    ROUPA removendo = remove_roupas_venda(cod_remove);
    pthread_mutex_unlock(&mutex);

    printf("Voluntário %ld remove a roupa mais antiga (%d) da lista de roupas à venda\n", tid, removendo.Codigo);
  }
  else if (tid % 2)
  {
    // Doa roupa nova
    int len = sizeof(roupas_venda);
    ROUPA roupa_doada = criar_random_roupa();

    pthread_mutex_lock(&mutex);
    add_roupas_venda(roupa_doada);
    pthread_mutex_unlock(&mutex);

    printf("Voluntário %ld doa roupa nova: %d\n", tid, roupa_doada.Codigo);
  }
  else
  {
    // Move roupas da lista de reparo para a lista de roupas a venda
    int len_reparo = sizeof(roupas_reparo);
    int len_venda = sizeof(roupas_venda);
    ROUPA movendo = remove_ultima_roupas_reparo();

    pthread_mutex_lock(&mutex);
    add_roupas_venda(movendo);
    pthread_mutex_unlock(&mutex);

    printf("Voluntário %ld move roupa %d de reparo para venda\n", tid, movendo.Codigo);
  }
  pthread_exit(NULL);
}

void *cria_cliente(void *threadid)
{
  long tid = (long)threadid;

  int len_venda = sizeof(roupas_venda);
  int random = rand() % len_venda;
  // Compra Roupa Aleatória
  pthread_mutex_lock(&mutex);
  ROUPA comprando = remove_roupas_aleatoria_venda();
  pthread_mutex_unlock(&mutex);

  printf("Cliente %ld compra roupa %d\n", tid, comprando.Codigo);

  int random_tempo = rand() % 4;
  sleep(random_tempo);
  if (tid % 2)
  {
    // Cliente doa a peça de roupa para o bazar
    int len = sizeof(roupas_reparo);
    ROUPA nova_roupa = criar_random_roupa();

    pthread_mutex_lock(&mutex);
    add_roupas_venda(nova_roupa);
    pthread_mutex_unlock(&mutex);

    printf("Cliente %ld doa roupa %d\n", tid, nova_roupa.Codigo);
  }
  else
  {
    // Cliente decide comprar uma nova roupa
    int len_venda = sizeof(roupas_venda);

    pthread_mutex_lock(&mutex);
    ROUPA comprando = remove_ultima_roupas_venda();
    pthread_mutex_unlock(&mutex);

    // reconstruir array
    printf("Cliente %ld compra roupa %d\n", tid, comprando.Codigo);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  roupas_venda = (struct LINKED_LIST *)malloc(sizeof(struct LINKED_LIST));
  roupas_reparo = (struct LINKED_LIST *)malloc(sizeof(struct LINKED_LIST));

  pthread_t threads_clientes[C_CLIENTES];
  pthread_t threads_voluntarios[D_VOLUNTARIOS];
  int cliente;
  int voluntario;
  int i;
  long t;

  pthread_mutex_init(&mutex, NULL);
  for (t = 0; t < D_VOLUNTARIOS; t++)
  {
    voluntario = pthread_create(&threads_voluntarios[t], NULL, cria_voluntario, (void *)t);
    if (voluntario)
    {
      printf("ERROR; return code from pthread_create() is %d\n", voluntario);
      exit(-1);
    }
  }

  for (t = 0; t < C_CLIENTES; t++)
  {
    cliente = pthread_create(&threads_clientes[t], NULL, cria_cliente, (void *)t);
    if (cliente)
    {
      printf("ERROR; return code from pthread_create() is %d\n", cliente);
      exit(-1);
    }
  }

  for (t = 0; t < D_VOLUNTARIOS; t++)
  {
    pthread_join(threads_voluntarios[t], NULL);
  }
  for (t = 0; t < C_CLIENTES; t++)
  {
    pthread_join(threads_clientes[t], NULL);
  }

  pthread_exit(NULL);
  pthread_mutex_destroy(&mutex);
}