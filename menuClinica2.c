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
  puts("******************CLINICA NEBA******************\n\n");
  puts("1.- Materiales\n");
  puts("2.- Area Requiriente\n");
  puts("3.- Almacen\n");
  puts("4.- Reportes\n");
  puts("5.- Salir\n");
  puts("Seleccione una opcion: ");
  scanf("%d", &opc);

    switch(opc){
      case 1:
          do{
            puts("******************MATERIALES******************\n\n");
            puts("1.- Capturar Pedido\n");
            puts("2.- Alta Material\n");
            puts("3.- Baja Material\n");
            puts("4.- Consulta Material\n");
            puts("5.- Actualizar datos\n");
            puts("6.- Ver los datos\n");
            puts("7.- Salir\n");
            puts("Seleccione una opcion: ");
            scanf("%d", &opcion);

            switch(opcion){
              case 1:
                break;
              case 2:
                break;
              case 3:
                break;
              case 4:
                break;  
              case 5:
                break;
              case 6:
                break;
              case 7:
                break;
                default:
                puts("\t\t opcion no valida\n");
            } 
          }while(opcion !=7);
          break;
    case 2:
      do{
        puts("******************AREA REQUIRIENTE******************\n\n");
        puts("1.- Alta Modulo o departamento\n");
        puts("2.- Baja Modulo\n");
        puts("4.- Consulta Modulo\n");
        puts("3.- Actualizar Modulo\n");
        puts("5.- Salir\n");
        puts("Seleccione una opcion: ");
        scanf("%d", &opcion2);

          switch(opcion2){
            case 1:
              break;
            case 2:
              break;
            case 3:
              break;
            case 4:
              break;
            case 5:
              break;  
              default:
              puts("\t\t opcion no valida\n");
          } 
        }while(opcion2 != 5);
      break;

    case 3:

      do{
        puts("******************ALMACEN******************\n\n");
        puts("1.- Capturar recepcion de material\n");
        puts("2.- Baja de recepcion de material\n");
        puts("3.- Actualizacion de recepcion de material\n");
        puts("4.- Consulta de insumos\n");
        puts("5.- Salir\n");
        puts("Seleccione una opcion: ");
        scanf("%d", &opcion3);

          switch(opcion3){
            case 1:
              break;
            case 2:
              break;
            case 3:
              break;
            case 4:
              break;
            case 5:
              break;  
              default:
              puts("\t\t opcion no valida\n");
          }
      }while(opcion3 != 5);
      break;
    case 4:
      do{
        puts("******************REPORTES******************\n\n");
        puts("1.- Reporte 1\n");
        puts("2.- Reporte 2\n");
        puts("3.- Reporte 3\n");
        puts("4.- Salir\n");
        puts("Seleccione una opcion: ");
        scanf("%d", &opcion4);

          switch(opcion4){
            case 1:
              break;
            case 2:
              break;
            case 3:
              break;
            case 4:
              break;  
              default:
              puts("\t\t opcion no valida\n");
          } 
        }while(opcion4 != 4);
      break;
      
    case 5:
      break;
      default:
      puts("\t\t opcion no valida\n");
  }
  
}while(opc != 5);

}
