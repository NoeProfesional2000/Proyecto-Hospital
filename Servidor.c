#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <libpq-fe.h>
#include <fcntl.h>
#include "area_Requiriente.h"
#include "almacen.h"

#define PORT 3550
#define BACKLOG 2 /* El número de conexiones permitidas */

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

int main(){

    int fd,fd2; //La primera crea el socket, la segunda recoge a los clientes de la lista de espera....
    struct sockaddr_in server; //Informacion de la direccion del servidor
    struct sockaddr_in client;
    int sin_size;
    char cad[100],cad1[100];

    /*Uso del struct*/
    struct area_requiriente area_requiriente;
    struct almacen almacen;

   /*Variables normales*/
   char opc[5],cadena[1020], pedido_despachado[5];

    //Viene la parte para trabajar con sockets
    if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        printf("\n\t--- Error al crear el socket :( ---\n");
        exit(-1);
    }

    bzero(&(server.sin_zero),8);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    /*Tenemos abierto el socket y vamos atender a los clientes*/
    if(bind(fd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1) {
        printf("\n\t\t--- ERROR EN BIND() ---\n");
        exit(-1);
    }

    /*Iniciar el servicio de escuchar pero sin aceptar a nadie*/
    if(listen(fd,BACKLOG) == -1) {
        printf("\n\t\t--- ERROR EN LISTEN() ---\n");
        exit(-1);
    }

    printf("\n\t|---------------- COMENZAMOS LAS OPERACIONES ----------------|\n");

    while(1){
        sin_size=sizeof(struct sockaddr_in);
        if ((fd2 = accept(fd,(struct sockaddr *)&client,&sin_size))==-1) {
            printf("\n\t\t--- NO SE PUDO ACEPTAR ESA CONEXION ---\n");
            exit(-1);
        }
        printf("\n\t\t··········································");
        printf("\n\t\t·SE OBTUVO UNA CONEXION DESDE [%s]·\n", inet_ntoa(client.sin_addr) );
        printf("\t\t··········································");

        read(fd2,opc,sizeof(opc));

        printf("\n\t\t=== INICIANDO OPERACION DE CLIENTE CON IP [%s] ===\n",inet_ntoa(client.sin_addr));
        switch(atoi(opc)){
            case 1:
                /*Switch de materiales*/
                read(fd2,&almacen,sizeof(almacen));
                switch(atoi(almacen.opcion_secundaria)){
                     case 1:
                      // Se limpia pantalla, obtiene datos para realizar el pedido //
                      system("clear");
                      printf("\n\t--------------- REALIZAR PEDIDO --------------\n");
                      if(strstr(almacen.validar_entrada,"areas_requiriente")){
                        bzero(cadena,sizeof(cadena));
                        sprintf(cadena,"%s",buscar_areas_requiriente());
                        write(fd2,cadena,sizeof(cadena));
                      }else if(strstr(almacen.validar_entrada,"insumos")){
                        bzero(cadena,sizeof(cadena));
                        sprintf(cadena,"%s",alta_pedido(atoi(almacen.areaRequiriente),almacen.descripcion));
                        write(fd2,cadena,sizeof(cadena));
                      }else if(strstr(almacen.validar_entrada,"ultimo")){
                        sprintf(almacen.ultimo_pedido,"%s", buscar_ultimo_pedido());
                        write(fd2,&almacen, sizeof(almacen));
                      }else{
                        printf("\n\tConsulta: %s",almacen.consulta);
                        sprintf(cad,"%s",alta_detalle_pedido(atoi(almacen.ultimo_pedido),almacen.consulta));
                        write(fd2,cad, sizeof(cad));
                      }
                     break;
                     case 2:
                     // Se limpia pantalla, obtiene datos dar de alta un material //
                        system("clear");
                        printf("\n\t--------------- ALTA DE MATERIAL --------------\n");
                        printf("\n\tArea: %s",almacen.areaRequiriente);
                        printf("\n\tDescripcion: %s",almacen.nombreMaterial);
                        sprintf(cad,"%s", buscar_area_requiriente(almacen.areaRequiriente, almacen.nombreMaterial));
                        write(fd2,cad, sizeof(cad));
                    break;

                    case 3:
                        system("clear");
                        printf("\n\t--------------- LEVANTAR PEDIDO --------------\n");
                        if(strstr(almacen.validar_entrada,"pedido_despachado")){
                        bzero(cadena,sizeof(cadena));
                        sprintf(cadena,"%s",buscar_pedido_pendiente());
                        write(fd2,cadena,sizeof(cadena));  
                        }else if(strstr(almacen.validar_entrada,"despachar")){
                        bzero(cadena,sizeof(cadena));
                        printf("\n\tvalor: %s",almacen.pedido_despachado);
                        sprintf(cadena,"%s", buscar_insumo_despachados(atoi(almacen.pedido_despachado)));
                        write(fd2,cadena,sizeof(cadena));
                        }else if(strstr(almacen.validar_entrada,"contar_productos")){
                        bzero(cadena,sizeof(cadena));
                        sprintf(cadena,"%s",contar_insumo_despachados(atoi(almacen.pedido_despachado)));
                        printf("\n\tvalor: %s",cadena);
                        write(fd2,cadena,sizeof(cadena));
                        }else{
                            printf("\n\tConsulta1: %s",almacen.consulta);
                            printf("\n\tConsulta2: %s",almacen.consulta_concatenar);
                            sprintf(cad,"%s",alta_almacen(atoi(almacen.pedido_despachado),almacen.consulta,almacen.consulta_concatenar));
                            write(fd2,cad, sizeof(cad));
                        }

                    break;

                    case 4:
                     // Se limpia pantalla, obtiene datos ingresar la entrada de un inventario //
                        system("clear");
                        printf("\n\t--------------- ENTRADA INVENTARIO --------------\n");
                        printf("\n\tNombre Material: %s",almacen.nombreMaterial);
                        printf("\n\tStock: %s",almacen.stock);
                        sprintf(cad,"%s", buscar_insumo(almacen.nombreMaterial, atoi(almacen.stock)));
                        write(fd2,cad, sizeof(cad));
                    break;
                }
            break;
            case 2:
                read(fd2,&area_requiriente,sizeof(area_requiriente));
                switch(atoi(area_requiriente.opcion_secundaria)){
                    case 1: 
                    // Se limpia pantalla, obtiene datos para Alta de Área, envía mensaje de confirmación de ALta //
                        system("clear");
                        printf("\n\t--------------- ALTA AREA REQUIRIENTE -------------\n");
                        printf("\n\tNombre: %s",area_requiriente.nombre_Area);
                        printf("\n\tDescripcion: %s",area_requiriente.descripcion);
                        sprintf(cad,"%s", alta_Area_Requiriente(area_requiriente.nombre_Area,area_requiriente.descripcion));
                        write(fd2,cad, sizeof(cad));
                    break;
                    case 2:
                     // Se limpia pantalla, obtiene datos para Baja de Área, envía mensaje de confirmación de ALta //
                        system("clear");
                        printf("\n\t--------------- BAJA AREA REQUIRIENTE --------------\n");
                        printf("\n\tNombre: %s",area_requiriente.nombre_Area);
                        sprintf(cad1, "%s", baja_Area_Requiriente(area_requiriente.nombre_Area, "descrip"));
                        sprintf(cad1,"%s", baja_Area_Requiriente(area_requiriente.nombre_Area, area_requiriente.descripcion));
                        write(fd2,cad1, sizeof(cad1));
                    break;
                    case 3:
                     // Se limpia pantalla, obtiene datos para Consulta de Área, Devuelve datos de consulta //
                        system("clear");
                        printf("\n\t--------------- VER AREA REQUIRIENTE ------------------\n");
                        printf("\n\tNombre: %s",area_requiriente.nombre);
                        sprintf(cad,"%s", ver_Area_Requiriente(area_requiriente.nombre));
                        write(fd2,cad, sizeof(cad));

                    break;
                }
            break;
            case 3:
                /*Switch de Almacen*/
            break;
            case 4:
                /*Switch de Reportes*/
            break;
        }
        printf("\n\n\t      #################################################");
        printf("\n\t      #LA CONEXION CON LA IP[%s] SE HA CERRADO.#\n",inet_ntoa(client.sin_addr));
        printf("\t      #################################################\n");
        printf("\n\t      *** ESTAMOS EN ESCUCHA DE MAS CONEXIONES... ***\n");
        close(fd2);
    }
    close(fd);
}   
