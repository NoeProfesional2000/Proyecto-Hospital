#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>
#include "Funciones.h"
#define PORT 3550
// Se declara variables para uso de funcion de area requiriente //
struct area_requiriente{
    char opcion_secundaria[5];
    char nombre[40];
    char nombre_Area[40];
    char descripcion[80];
    char Mensaje[50];
};

int main(int argc, char *argv[]){
    /*Variables del Socket*/
    int FileDescriptor;
    struct hostent *he;
    struct sockaddr_in server;

    /*Uso del struct*/
    struct area_requiriente area_requiriente;

    /*Variables normales*/
    char opc[5],opcion[5],opcion2[5],opcion3[5],opcion4[5], cad[100], cad1[100];
    struct timeval tiempo_general;

    if (argc !=2) {
        /*Si en consola no ingresas la IP o ingresas algo de mas, aparecerà esto*/
        printf("Haga Uso De Esta Estructura: %s <Dirección IP>\n",argv[0]);
        exit(-1);
    }

    if ((he=gethostbyname(argv[1]))==NULL){
        /* llamada a gethostbyname() */
        printf("gethostbyname() error\n");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(server.sin_zero),8);

    gettimeofday(&tiempo_general, 0);
    do{
        system("clear");
        MenuPrincipal();
        scanf("%s",opc);
        /*¿Acaso es una letra lo que ha ingresado?*/
        if(Validar_Opcion(opc) == 1){
            switch(atoi(opc)){
                case 1:
                    do{
                    system("clear");
                    menuMateriales();
                    scanf("%s",opcion);
                        /*¿Acaso es una letra lo que ha ingresad0?*/
                        if(Validar_Opcion(opcion) == 1){
                            sprintf(area_requiriente.opcion_secundaria,"%s",opcion);
                            switch(atoi(opcion)){
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
                                    printf("\n\t\t\t   *** ELIJA UNA OPCION EXISTENTE ***\n");
                                    printf("\n\t\t\t  Presione '0' para continuar... ");
                                    while(getchar() != '0');
                                break;
                            }
                        }else{
                            printf("\n\t\t\t   *** NO SE ACEPTAN LETRAS ***\n");
                            printf("\n\t\t\t  Presione '0' para continuar... ");
                            while(getchar() != '0');
                        }
                    }while(atoi(opcion)!=7);
                break;
                case 2:
                    do{
                        system("clear");
                        menuAreaRequiriente();
                        scanf("%s",opcion2);
                        /*¿Acaso es una letra lo que ha ingresad0?*/
                        if(Validar_Opcion(opcion2) == 1){
                            sprintf(area_requiriente.opcion_secundaria,"%s",opcion2);
                            switch(atoi(opcion2)){
                                case 1:
                                    // Limpiar pantalla //
                                     system("clear");
                                     // Se pide nombre y descripcion de área //
                                     printf("\tIngrese el nombre: ");
	                             scanf(" %2048[0-9a-zA-Z ]s", area_requiriente.nombre_Area);
	                             printf("\tIngrese una descripcion del Area: ");
	                             scanf(" %2048[0-9a-zA-Z ]s", area_requiriente.descripcion);
	                             // Se decara tiempo de inicio //
                                     struct timeval begin_alta;
                                     gettimeofday(&begin_alta, 0);
                                     // Escribe y envía datos a servidor //  
	                             FileDescriptor = Conexion_Socket(server);
	                             write(FileDescriptor,opc,sizeof(opc));
	                             write(FileDescriptor,&area_requiriente,sizeof(area_requiriente));
                                     // Lee datos enviaos desde servidor //  
	                             read(FileDescriptor,cad,sizeof(cad));
	                             printf("Servidor:%s\n",cad);
	                 //Se pasan los parámetro necesarios al método para marcar final y calcular tiempo de ejecución. //
	                             Ejecucion_Final(begin_alta.tv_sec,begin_alta.tv_usec);
	                             printf("\n\t\t\t  Presione '0' para continuar... ");
	                             
                                while(getchar() != '0');
                                break;
                                case 2:
                                    // Limpiar pantalla //
                                    system("clear");
                                    // Se pide nombre y descripcion de área //
                                    printf("\tIngrese el nombre: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", area_requiriente.nombre_Area);
                                    printf("\tIngrese una descripcion del Area: ");
	                            scanf(" %2048[0-9a-zA-Z ]s", area_requiriente.descripcion);
	                            // Se decara tiempo de inicio //
                                     struct timeval begin_baja;
                                     gettimeofday(&begin_baja, 0);
                                    // Escribe y envía datos a servidor // 
                                    FileDescriptor = Conexion_Socket(server);
	                            write(FileDescriptor,opc,sizeof(opc));
	                            write(FileDescriptor,&area_requiriente,sizeof(area_requiriente));
	                            // Lee datos enviaos desde servidor //    
	                            read(FileDescriptor,cad1,sizeof(cad1));
	                            printf("Servidor:%s\n",cad1);
	                             //Se pasan los parámetro necesarios al método para marcar final y calcular tiempo de ejecución. //
	                             Ejecucion_Final(begin_baja.tv_sec,begin_baja.tv_usec);
	                             printf("\n\t\t\t  Presione '0' para continuar... ");

                                    while(getchar() != '0');
                                break;
                                case 3:
                                   // Limpiar pantalla //
                                    system("clear");
                                    /* Se usa expresión regular para aceptar letras, numeros y espacios únicamente. */
                                    puts("\tIngrese el nombre: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", area_requiriente.nombre);
                                    puts("\n");
                                    // Se decara tiempo de inicio //
                                     struct timeval begin_ver;
                                     gettimeofday(&begin_ver, 0);
                                    // Escribe y envía datos a servidor // 
                                    FileDescriptor = Conexion_Socket(server);
	                             write(FileDescriptor,opc,sizeof(opc));
	                             write(FileDescriptor,&area_requiriente,sizeof(area_requiriente));
	                           // Impresión de consulta de datos de Área Requiriente //
	                             printf("Servidor:\n ");
	                             printf("\n\n\t--------- Datos de Area Requiriente ----------");
                                     puts("\n\n\t ID             NOMBRE             DESCRIPCION            ESTATUS\n");
                                     // Lee datos enviaos desde servidor //  
	                             read(FileDescriptor,cad,sizeof(cad));
	                             printf("\n\t %s \n",cad);
	                              //Se pasan los parámetro necesarios al método para marcar final y calcular tiempo de ejecución. //
	                             Ejecucion_Final(begin_ver.tv_sec,begin_ver.tv_usec);
	                             printf("\n\t\t\t  Presione '0' para continuar... ");

                                while(getchar() != '0');
                                break;
                                case 4:
                                break;
                                default:
                                    printf("\n\t\t\t   *** ELIJA UNA OPCION EXISTENTE ***\n");
                                    printf("\n\t\t\t  Presione '0' para continuar... ");
                                    while(getchar() != '0');
                                break;
                            }
                        }else{
                            printf("\n\t\t\t   *** NO SE ACEPTAN LETRAS ***\n");
                            printf("\n\t\t\t  Presione '0' para continuar... ");
                            while(getchar() != '0');
                        }
                    }while(atoi(opcion2) != 4);
                break;
                case 3:
                    do{
                        system("clear");
                        menuAlmacen();
                        scanf("%s",opcion3);
                        /*¿Acaso es una letra lo que ha ingresad0?*/
                        if(Validar_Opcion(opcion3) == 1){
                            sprintf(area_requiriente.opcion_secundaria,"%s",opcion3);
                            switch(atoi(opcion3)){
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
                                    printf("\n\t\t\t   *** ELIJA UNA OPCION EXISTENTE ***\n");
                                    printf("\n\t\t\t  Presione '0' para continuar... ");
                                    while(getchar() != '0');
                                break;
                            }
                        }else{
                            printf("\n\t\t\t   *** NO SE ACEPTAN LETRAS ***\n");
                            printf("\n\t\t\t  Presione '0' para continuar... ");
                            while(getchar() != '0');
                        }
                    }while(atoi(opcion3)!=5);
                break;
                case 4:
                    do{
                        system("clear");
                        menuReportes();
                        scanf("%s",opcion4);
                        /*¿Acaso es una letra lo que ha ingresad0?*/
                        if(Validar_Opcion(opcion4) == 1){
                            sprintf(area_requiriente.opcion_secundaria,"%s",opcion4);
                            switch(atoi(opcion4)){
                                case 1:
                                break;
                                case 2:
                                break;
                                case 3:
                                break;
                                default:
                                    printf("\n\t\t\t   *** ELIJA UNA OPCION EXISTENTE ***\n");
                                    printf("\n\t\t\t  Presione '0' para continuar... ");
                                    while(getchar() != '0');
                                break;
                            }
                            // Si se ingresa letras, se envían los mensajes. //
                        }else{
                            printf("\n\t\t\t   *** NO SE ACEPTAN LETRAS ***\n");
                            printf("\n\t\t\t  Presione '0' para continuar... ");
                            while(getchar() != '0');
                        }
                    }while(atoi(opcion4)!=4);
                break;
                case 5:
                break;
                default:
                    printf("\n\t\t\t   *** ELIJA UNA OPCION EXISTENTE ***\n");
                    printf("\n\t\t\t  Presione '0' para continuar... ");
                    while(getchar() != '0');
                break;
            }
            // Si se ingresa letras, se envían los mensajes. //
        }else{
            printf("\n\t\t\t   *** NO SE ACEPTAN LETRAS ***\n");
            printf("\n\t\t\t  Presione '0' para continuar... ");
            while(getchar() != '0');
        }
    }while(atoi(opc) != 5);

    Ejecucion_Final(tiempo_general.tv_sec,tiempo_general.tv_usec);
    printf("\n\t\t--- LA CONEXION A TERMINADO ---\n");
    return 0;
}//Cierre de programa Cliente.c //
