#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

#define C_CLIENTES 5
#define D_VOLUNTARIOS 5

int roupas_venda[1];
int roupas_reparo[1];

void *cria_voluntario(void *threadid);

int criar_random_id(void)
{
  return rand() % 89;
}

void *cria_voluntario(void *threadid)
{
  sleep(3);
  long tid = (long)threadid;
  if (tid % 3)
  {
    // Remove roupa mais antiga da lista de roupas a venda
    int len = sizeof(roupas_venda);
    int removendo = roupas_venda[0];

    pthread_mutex_lock(&mutex);
    roupas_venda[0] = NULL;
    pthread_mutex_unlock(&mutex);

    // reconstruir array
    printf("Voluntário %d remove a roupa mais antiga (%d) da lista de roupas à venda\n", threadid, removendo);
  }
  else if (tid % 2)
  {
    // Doa roupa nova
    int len = sizeof(roupas_venda);
    int random_id = criar_random_id();

    pthread_mutex_lock(&mutex);
    roupas_venda[len] = random_id;
    pthread_mutex_unlock(&mutex);

    printf("Voluntário %d doa roupa nova: %d\n", threadid, random_id);
  }
  else
  {
    // Move roupas da lista de reparo para a lista de roupas a venda
    int len_reparo = sizeof(roupas_reparo);
    int len_venda = sizeof(roupas_venda);
    int movendo = roupas_reparo[len_reparo - 1];

    pthread_mutex_lock(&mutex);
    roupas_reparo[len_reparo - 1] = NULL;
    roupas_venda[len_venda] = movendo;
    pthread_mutex_unlock(&mutex);

    printf("Voluntário %d move roupa %d de reparo para venda\n", threadid, movendo);
  }
  pthread_exit(NULL);
}

void *cria_cliente(void *threadid)
{
  long tid = (long)threadid;

  int len_venda = sizeof(roupas_venda);
  printf("%d\n", len_venda);

  int random = rand() % len_venda;
  printf("%d\n", random);

  int loop;

  for (loop = 0; loop < len_venda; loop++)
    printf("%d ", roupas_venda[loop]);

  int comprando = roupas_venda[random];

  pthread_mutex_lock(&mutex);
  roupas_venda[random] = NULL;
  pthread_mutex_unlock(&mutex);

  // reconstruir array
  printf("Cliente %d compra roupa %d\n", threadid, comprando);
  int random_tempo = rand() % 4;
  sleep(random_tempo);
  if (tid % 2)
  {
    // Cliente doa a peça de roupa para o bazar
    int len = sizeof(roupas_reparo);
    int roupa_id = criar_random_id();

    pthread_mutex_lock(&mutex);
    roupas_reparo[len] = roupa_id;
    pthread_mutex_unlock(&mutex);

    printf("Cliente %d doa roupa %d\n", threadid, roupa_id);
  }
  else
  {
    // Cliente decide comprar uma nova roupa
    int len_venda = sizeof(roupas_venda);
    int comprando = roupas_venda[len_venda - 1];

    pthread_mutex_lock(&mutex);
    roupas_venda[len_venda - 1] = NULL;
    pthread_mutex_unlock(&mutex);

    // reconstruir array
    printf("Cliente %d compra roupa %d\n", threadid, comprando);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads_clientes[C_CLIENTES];
  pthread_t threads_voluntarios[D_VOLUNTARIOS];
  int cliente;
  int voluntario;
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