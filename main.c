#include <stdio.h>
#include <conio.h>
int main(void)
{
    
  struct cliente
  {
    int id;
    char nome[30]; 
    char roupas[30];
  };
  
  struct voluntario
  {
    int id;
    char nome[30];
  };
  
  char *entrada = "";
  
  printf("\nDeseja logar como cliente ou voluntário?\n");
  
  printf("\n- Cliente: Digite '1'\n");
  
  printf("\n- Voluntário: Digite '2'\n");
    
  fflush(stdin);
  
  fgets(entrada, 30, stdin);
  
  getch();
  return(0);
}