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

struct almacen{
    char opcion_secundaria[5];
    char nombreMaterial[40];
    char areaRequiriente[40];
    char stock[40];
    char validar_entrada[80];
    /*para la parte de pedidos*/
    char insumo[5];
    char piezas[5];
    char descripcion[100];
    char consulta[1020];
    char consulta_concatenar[1020];
    char ultimo_pedido[5];
    char pedido_despachado[5];
};

int main(int argc, char *argv[]){
    /*Variables del Socket*/
    int FileDescriptor;
    struct hostent *he;
    struct sockaddr_in server;

    /*Uso del struct*/
    struct area_requiriente area_requiriente;
    struct almacen almacen;

    /*Variables normales*/
    char opc[5],opcion[5],opcion2[5],opcion3[5],opcion4[5], cad[100], cad1[100],cadena[800],cadenaApoyo[500],apoyo_2[500];
    struct timeval tiempo_general;
    int cantidad = 0;

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
                    menuAlmacen();
                    scanf("%s",opcion);
                        /*¿Acaso es una letra lo que ha ingresad0?*/
                        if(Validar_Opcion(opcion) == 1){
                            sprintf(almacen.opcion_secundaria,"%s",opcion);
                            switch(atoi(opcion)){
                                case 1:
                                    system("clear");// Limpiar pantalla //
                                    // Se decara tiempo de inicio //
                                    struct timeval begin_pedido;
                                    gettimeofday(&begin_pedido, 0);
                                    
                                    // Escribe y envía datos a servidor //  
                                    FileDescriptor = Conexion_Socket(server);
                                    sprintf(almacen.validar_entrada, "areas_requiriente");
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                    //traemos datos desde el servidor //
                                    bzero(cadena,sizeof(cadena));
                                    read(FileDescriptor,cadena,sizeof(cadena));
                                    //mostramos todas las areas que existen //
                                    printf("-----------------------------------------------------------");
                                    printf("\n\tID\tAREA\n");
                                    printf("%s\n",cadena);

                                    //pedimos los datos para hacer la insercion en pedidos//
                                    printf("-----------------------------------------------------------");
                                    printf("\n\tIngrese el id del area: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", almacen.areaRequiriente);
                                    printf("\n\tIngrese una descripcion: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", almacen.descripcion);
                                    // abrimos otra conexion al servidor //  
                                    FileDescriptor = Conexion_Socket(server);
                                    sprintf(almacen.validar_entrada, "insumos");
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                    bzero(cadena,sizeof(cadena));
                                    read(FileDescriptor,cadena,sizeof(cadena));
                                    //traemos todo los insumos que correspondan a esa area //
                                    printf("-----------------------------------------------------------");
                                    printf("\n\tID\tPRODUCTO\n");
                                    printf("%s\n",cadena);

                                    //Antes de pedir vamos a traer el id del pedido insertado//
                                    FileDescriptor = Conexion_Socket(server);
                                    sprintf(almacen.validar_entrada, "ultimo");
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                    read(FileDescriptor,&almacen,sizeof(almacen));

                                    //pedimos los datos para hacer la insercion en detalle pedidos//
                                    printf("-----------------------------------------------------------");
                                    //Asignado primera parte...
                                    printf("\nCuantos materiales va a ingresar: ");
                                    scanf("%d",&cantidad);
                                    
                                    bzero(cadenaApoyo,sizeof(cadenaApoyo));
                                    bzero(almacen.consulta,sizeof(almacen.consulta));
                                    for(int i = 0; i < cantidad; i++){                      
                                        printf("\tIngrese el id del material: ");
                                        scanf(" %2048[0-9a-zA-Z ]s", almacen.nombreMaterial);
                                        printf("\tIngrese la cantidad del material: ");
                                        scanf(" %2048[0-9a-zA-Z ]s", almacen.stock);

                                        sprintf(cadenaApoyo,"(%d,%d,%d)",atoi(almacen.ultimo_pedido),atoi(almacen.nombreMaterial),atoi(almacen.stock));
                                        strcat(almacen.consulta,cadenaApoyo);

                                        if(i != (cantidad-1)){
                                            strcat(almacen.consulta,",");
                                        }else{
                                            strcat(almacen.consulta,";");
                                        }
                                        memset(cadenaApoyo,0,sizeof(cadenaApoyo));
                                    }
                                    FileDescriptor = Conexion_Socket(server);
                                    sprintf(almacen.validar_entrada, "diferente");
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                    // Lee datos enviaos desde servidor //  
                                    read(FileDescriptor,cad,sizeof(cad));
                                    printf("\n\tServidor:%s\n",cad);
                                    //Se pasan los parámetro necesarios al método para marcar final y calcular tiempo de ejecución. //
                                    Ejecucion_Final(begin_pedido.tv_sec,begin_pedido.tv_usec);
                                    printf("\n\t\t\t  Presione '0' para continuar... ");                    
                                    while(getchar() != '0');      
                                break;
                                case 2:
                                    system("clear");// Limpiar pantalla //
                                     // Se pide nombre y descripcion de área //
                                    printf("\tIngrese el nombre del area: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", almacen.areaRequiriente);
                                    printf("\tIngrese el nombre del material: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", almacen.nombreMaterial);

                                    // Se decara tiempo de inicio //
                                    struct timeval begin_alta;
                                    gettimeofday(&begin_alta, 0);
                                    // Escribe y envía datos a servidor //  
                                    FileDescriptor = Conexion_Socket(server);
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                     // Lee datos enviaos desde servidor //  
                                    read(FileDescriptor,cad,sizeof(cad));
                                    printf("\n\tServidor:%s\n",cad);
                                    //Se pasan los parámetro necesarios al método para marcar final y calcular tiempo de ejecución. //
                                    Ejecucion_Final(begin_alta.tv_sec,begin_alta.tv_usec);
                                    printf("\n\t\t\t  Presione '0' para continuar... ");                    
                                    while(getchar() != '0');


                                break;
                                case 3:
                                    system("clear");
                                    struct timeval begin_pedido_pendiente;
                                    gettimeofday(&begin_pedido_pendiente, 0);
                                    // Escribe y envía datos a servidor //  
                                    FileDescriptor = Conexion_Socket(server);
                                    sprintf(almacen.validar_entrada, "pedido_despachado");
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                    //traemos datos desde el servidor //
                                    bzero(cadena,sizeof(cadena));
                                    read(FileDescriptor,cadena,sizeof(cadena));
                                    //mostramos todas las areas que existen //
                                    printf("-----------------------------------------------------------");
                                    printf("\n\tID\tDescripcion\tFecha\tHora\n");
                                    printf("%s\n",cadena);

                                     //pedimos los datos para hacer la insercion en pedidos//
                                    printf("-----------------------------------------------------------");
                                    printf("\n\tIngrese el id del pedido que desea levantar: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", almacen.pedido_despachado);
                                   
                                    // abrimos otra conexion al servidor //  
                                    FileDescriptor = Conexion_Socket(server);
                                    sprintf(almacen.validar_entrada, "despachar");
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                    bzero(cadena,sizeof(cadena));
                                    read(FileDescriptor,cadena,sizeof(cadena));
                                    //traemos todo los insumos que correspondan a esa area //
                                    printf("-----------------------------------------------------------");
                                    printf("\n----Productos que corresponden al pedido seleccionado----");
                                    printf("\n\tID\tPIEZAS\tPRODUCTO\n");
                                    printf("%s\n",cadena);
                                    printf("-----------------------------------------------------------");

                                    // abrimos otra conexion al servidor //  
                                    FileDescriptor = Conexion_Socket(server);
                                    sprintf(almacen.validar_entrada, "contar_productos");
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                    bzero(cadena,sizeof(cadena));
                                    read(FileDescriptor,cadena,sizeof(cadena));
                                    printf("\n----recuerde seleccionar todo los materiales que se muestran anteriormente----");
                                    for(int i = 0; i < atoi(cadena); i++){
                                        printf("\nIngrese el id del material: ");
                                        scanf(" %2048[0-9a-zA-Z ]s", almacen.nombreMaterial);
                                        printf("\n--la cantidad a ingresar debe ser menor o igual a las piezas mostradas");
                                        printf("\nIngrese la cantidad de material que ingresada: ");
                                        scanf(" %2048[0-9a-zA-Z ]s", almacen.stock);

                                        sprintf(apoyo_2,"UPDATE insumos SET stock = (stock - %d) WHERE id_insumos = %d;",atoi(almacen.stock),atoi(almacen.nombreMaterial));
                                        strcat(almacen.consulta_concatenar,apoyo_2);
                                        memset(apoyo_2,0,sizeof(apoyo_2));

                                        sprintf(cadenaApoyo,"(%d,%d,%d)",atoi(almacen.pedido_despachado),atoi(almacen.nombreMaterial),atoi(almacen.stock));
                                        strcat(almacen.consulta,cadenaApoyo);

                                        if(i != (atoi(cadena)-1)){
                                            strcat(almacen.consulta,",");
                                        }else{
                                            strcat(almacen.consulta,";");
                                        }
                                        memset(cadenaApoyo,0,sizeof(cadenaApoyo));
                                    }
                                    FileDescriptor = Conexion_Socket(server);
                                    sprintf(almacen.validar_entrada, "diferente");
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                    // Lee datos enviaos desde servidor //  
                                    read(FileDescriptor,cad,sizeof(cad));
                                    printf("\n\tServidor:%s\n",cad);
                                    Ejecucion_Final(begin_pedido_pendiente.tv_sec,begin_pedido_pendiente.tv_usec);
                                    printf("\n\t\t\t  Presione '0' para continuar... ");                    
                                    while(getchar() != '0');
                                break;
                                case 4:

                                    system("clear");// Limpiar pantalla //
                                     // Se pide nombre y descripcion de área //
                                    printf("\tIngrese el nombre del material: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", almacen.nombreMaterial);
                                    printf("\tIngrese la cantidad del material: ");
                                    scanf(" %2048[0-9a-zA-Z ]s", almacen.stock);

                                    // Se decara tiempo de inicio //
                                    struct timeval begin_alta_entrada;
                                    gettimeofday(&begin_alta_entrada, 0);
                                    // Escribe y envía datos a servidor //  
                                    FileDescriptor = Conexion_Socket(server);
                                    write(FileDescriptor,opc,sizeof(opc));
                                    write(FileDescriptor,&almacen,sizeof(almacen));
                                     // Lee datos enviaos desde servidor //  
                                    read(FileDescriptor,cad,sizeof(cad));
                                    printf("\n\tServidor:%s\n",cad);
                                    //Se pasan los parámetro necesarios al método para marcar final y calcular tiempo de ejecución. //
                                    Ejecucion_Final(begin_alta_entrada.tv_sec,begin_alta.tv_usec);
                                    printf("\n\t\t\t  Presione '0' para continuar... ");                    
                                    while(getchar() != '0');
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
                    }while(atoi(opcion)!=5);
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
                                 printf("\n\tServidor:%s\n",cad);
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
                                // Se decara tiempo de inicio //
                                     struct timeval begin_baja;
                                     gettimeofday(&begin_baja, 0);
                                    // Escribe y envía datos a servidor // 
                                    FileDescriptor = Conexion_Socket(server);
                                write(FileDescriptor,opc,sizeof(opc));
                                write(FileDescriptor,&area_requiriente,sizeof(area_requiriente));
                                // Lee datos enviaos desde servidor //    
                                read(FileDescriptor,cad1,sizeof(cad1));
                                printf("\n\tServidor:%s\n",cad1);
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
                case 4:
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
    }while(atoi(opc) != 4);

    Ejecucion_Final(tiempo_general.tv_sec,tiempo_general.tv_usec);
    printf("\n\t\t--- LA CONEXION A TERMINADO ---\n");
    return 0;
}//Cierre de programa Cliente.c //