#include<sys/sem.h> //libreria para semaforos
#include<stdio.h>
#include<stdlib.h>

/*
  Funciones con semaforo
  semget: Crea el semaforo
  semctl: obtener el control del semaforo
  semop: Aplicar las operaciones de bloquero y desbloquero
*/

#define clave 4000 // de 3000 al infinito
int idsem=0;

int crear_semaforo()
{
    int val=1;
    if((idsem=semget(clave,1,IPC_CREAT | 0777))==-1) //  esta funcion crea el semaforo debe tener sem.h
    {
        perror("\n\t\t=== NO SE PUDO CREAR EL SEMAFORO === \n");
        exit(1);
    }

    if((semctl(idsem,0,SETVAL,val))==-1){
        printf("\n\t\t=== NO SE PUEDE TENER EL CONTROL DEL SEMAFORO ===\n");
        exit(1);
    }
    return idsem;
}

void remover_semaforo(int idsem)
{
    if((semctl(idsem,0,IPC_RMID))==-1)
    {
    perror("\n\t\t=== NO SE PUDO ELIMINAR EL SEMAFORO ===\n");
      exit(1);
    }else{
        printf("\n\t\t=== SEMAFORO ELIMINADO ===\n");
    }
}

void termina_semaforo (int idsem)
{
  struct sembuf listo={0,1,SEM_UNDO};
  if((semop(idsem,&listo,1))==-1)
  {
    perror("\n\t\t=== ERROR AL TERMINAR SEMAFORO ===\n");
    remover_semaforo(idsem);
    exit(1);
  }else{
    printf("\t\t=== SEMAFORO LIBERADO (VERDE) ===\n");
  }
}

void inicia_semaforo (int idsem) //bloquea el semaforo aqui va lo de actualizar update eliminar insertar meter en el down hacer la consulta y al salir hacer el up(id_sem)
{                       // -1 bloquea , 1 listo
  struct sembuf bloqueado = {0,-1,SEM_UNDO}; //
  if((semop(idsem,&bloqueado,1))==-1){
    perror("\n\t\tERROR AL TRATAR DE BLOQUEAR ===\n");
    remover_semaforo(idsem);
    exit(1);
  }else{
    printf("\n\t\t=== SEMAFORO EN ROJO, ESPERE... ===\n");
  }
}
