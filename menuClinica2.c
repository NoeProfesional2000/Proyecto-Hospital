#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFSIZE 128
#define TAG 0

int opc,opcion, opcion2,opcion3,opcion4;

int main(int argc, char *argv[])
{
  do{
    system("clear");
    puts("\n\t\t******************CLINICA NEBA******************\n\n");
    puts("\t\t1.- Materiales.\n");
    puts("\t\t2.- Area Requiriente.\n");
    puts("\t\t3.- Almacen.\n");
    puts("\t\t4.- Reportes.\n");
    puts("\t\t5.- Salir.\n");
    printf("\t\tSeleccione una opcion: ");
    scanf("%d", &opc);

    switch(opc){
      case 1:
        do{
          system("clear");
          puts("\n\t\t******************MATERIALES******************\n\n");
          puts("\t\t1.- Capturar Pedido.\n");
          puts("\t\t2.- Alta Material.\n");
          puts("\t\t3.- Baja Material.\n");
          puts("\t\t4.- Consulta Material.\n");
          puts("\t\t5.- Actualizar datos.\n");
          puts("\t\t6.- Ver los datos.\n");
          puts("\t\t7.- Salir.\n");
          printf("\t\tSeleccione una opcion: ");
          scanf("%d", &opcion);

          switch(opcion){
            case 1:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 2:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 3:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 4:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;  
            case 5:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 6:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 7:
            break;
            default:
              puts("\n\t\t\t*** Opcion No Valida ***");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
          } 
        }while(opcion !=7);
      break;
      case 2:
        do{
          system("clear");
          puts("\n\t\t******************AREA REQUIRIENTE******************\n\n");
          puts("\t\t1.- Alta Modulo o departamento.\n");
          puts("\t\t2.- Baja Modulo.\n");
          puts("\t\t3.- Consulta Modulo.\n");
          puts("\t\t4.- Actualizar Modulo.\n");
          puts("\t\t5.- Salir.\n");
          printf("\t\tSeleccione una opcion: ");
          scanf("%d", &opcion2);

          switch(opcion2){
            case 1:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 2:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 3:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 4:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 5:
            break;  
            default:
              puts("\n\t\t\t*** Opcion No Valida ***");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
          } 
        }while(opcion2 != 5);
      break;
      case 3:
        do{
          system("clear");
          puts("\n\t\t******************ALMACEN******************\n\n");
          puts("\t\t1.- Capturar recepcion de material.\n");
          puts("\t\t2.- Baja de recepcion de material.\n");
          puts("\t\t3.- Actualizacion de recepcion de material.\n");
          puts("\t\t4.- Consulta de insumos.\n");
          puts("\t\t5.- Salir.\n");
          printf("\t\tSeleccione una opcion: ");
          scanf("%d", &opcion3);

          switch(opcion3){
            case 1:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 2:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 3:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 4:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
              break;
            case 5:
            break;  
            default:
              puts("\n\t\t\t*** Opcion No Valida ***");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
          }
        }while(opcion3 != 5);
      break;
      case 4:
        do{
          system("clear");
          puts("\n\t\t******************REPORTES******************\n\n");
          puts("\t\t1.- Reporte 1.\n");
          puts("\t\t2.- Reporte 2.\n");
          puts("\t\t3.- Reporte 3.\n");
          puts("\t\t4.- Salir.\n");
          printf("\t\tSeleccione una opcion: ");
          scanf("%d", &opcion4);
          
          switch(opcion4){
            case 1:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 2:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 3:
              system("clear");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
            case 4:
            break;  
            default:
              puts("\n\t\t\t*** Opcion No Valida ***");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
          } 
        }while(opcion4 != 4);
      break;
      case 5:
      break;
      default:
        puts("\n\t\t\t*** Opcion No Valida ***");
        printf("\n\t\t\tPresione '0' para continuar... ");
        while(getchar() != '0');
      break;
    }
  }while(opc != 5);
}
