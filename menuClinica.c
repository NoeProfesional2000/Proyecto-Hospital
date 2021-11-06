#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "Funciones.h"
#include "area_Requiriente.h"
#include <sys/wait.h>
#include <libpq-fe.h>
#include <fcntl.h>

#define BUFSIZE 128
#define TAG 0
#define TCADENA 100 

/* Funci�n para Men� de �rea Requiriente */
void menuAreaRequiriente(void);
/*El archivo Funciones.h contiene la conexion hacia la bd, se debe compilar con la ruta hacia postgres*/
int opc,opcion, opcion2,opcion3,opcion4;

int main(int argc, char *argv[])
{
/* variables para m�dulo de �rea Requiriente */
char nombre[40];
char nombre_Area[40], descripcion[40];

/* Men� con las opciones principales que contendr� el sistema de cl�nica. */
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
/* Primer submen� del m�dulo de Materiales donde se hace la recepci�n de pedidos y el registro de los tipos de materiales que se manejar�.*/
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
/* Opciones a desarrollar en m�dulo de Materiales */
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
/* Segundo submen� de �rea requiriente donde se dar� de alta a las distintas �reas que solicite el cliente para posteriormente atenderlas.*/
        do{
          system("clear");
          menuAreaRequiriente();
          scanf("%d", &opcion2);
/* Opciones a desarrollar en m�dulo de �rea requiriente */
          switch(opcion2){
          /* Opci�n 1: solicita nombre y descripci�n para Alta de �rea Requiriente. */
            case 1:
            system("clear");
            /* Se usa expresi�n regular para aceptar letras, numeros y espacios �nicamente. */
            printf("\tIngrese el nombre: ");
	    scanf(" %2048[0-9a-zA-Z ]s", nombre_Area);
	    printf("\tIngrese una descripcion del Area: ");
	    scanf(" %2048[0-9a-zA-Z ]s", descripcion);
	     alta_Area_Requiriente(nombre_Area, descripcion);
            break;
           /* Opci�n 2: solicita nombre y descripci�n (no es necesario que sea la misma)para Baja de �rea Requiriente. */ 
            case 2:
              system("clear");
              /* Se usa expresi�n regular para aceptar letras, numeros y espacios �nicamente. */
              printf("\tIngrese el nombre: ");
	      scanf(" %2048[0-9a-zA-Z ]s", nombre_Area);
	      printf("\tIngrese una descripcion del Area (puede ser distinta): ");
	      scanf(" %2048[0-9a-zA-Z ]s", descripcion);
              baja_Area_Requiriente(nombre_Area, descripcion);
              break;
           /* Opci�n 3: Visualizar un �rea requiriente por medio del nombre. */
              case 3:
                 system("clear");
                 /* Se usa expresi�n regular para aceptar letras, numeros y espacios �nicamente. */
                 puts("\tIngrese el nombre: ");
	         scanf(" %2048[0-9a-zA-Z ]s", nombre);
	         ver_Area_Requiriente(nombre);
              break;
              
            case 4:
            break;
            default:
              puts("\n\t\t\t*** Opcion No Valida ***");
              printf("\n\t\t\tPresione '0' para continuar... ");
              while(getchar() != '0');
            break;
          } 
        }while(opcion2 != 4);
      break;
      case 3:
/* Tercer m�dulo de Almac�n donde se controla los insumos que llegan y se despachan, as� como los proveedores.*/
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
/* Opciones a desarrollar en m�dulo de Almacen */
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
/* �ltimo m�dulo, donde se generan reportes donde se plama datos que proveer�n informaci�n importante acerca de las operaciones en la cl�nica.*/
        do{
          system("clear");
          puts("\n\t\t******************REPORTES******************\n\n");
          puts("\t\t1.- Reporte 1.\n");
          puts("\t\t2.- Reporte 2.\n");
          puts("\t\t3.- Reporte 3.\n");
          puts("\t\t4.- Salir.\n");
          printf("\t\tSeleccione una opcion: ");
          scanf("%d", &opcion4);
  /* Opciones a desarrollar en m�dulo de Reportes */        
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
}// FIn de main //
// Funcion para Menu principal de �rea requiriente //
void menuAreaRequiriente(void){
	puts("\n\t\t**************** AREA REQUIRIENTE ***************\n\n");
	puts("\t1.- Alta de Area Requiriente\n");
	puts("\t2.- Baja de Area Requiriente.\n");
	puts("\t3.- Consultar Area Requiriente.\n");
	puts("\t4.- Salir.\n");
	puts("\tSeleccione una opcion: ");
}
