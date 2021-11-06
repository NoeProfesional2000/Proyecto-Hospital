#include <unistd.h>
#include <sys/time.h>

void MenuPrincipal(){
    puts("\n\t\t******************CLINICA NEBA******************\n\n");
    puts("\t\t1.- Materiales.\n");
    puts("\t\t2.- Area Requiriente.\n");
    puts("\t\t3.- Almacen.\n");
    puts("\t\t4.- Reportes.\n");
    puts("\t\t5.- Salir.\n");
    printf("\t\tSeleccione una opcion: ");
}

void menuMateriales(){
    puts("\n\t\t******************MATERIALES******************\n\n");
    puts("\t\t1.- Capturar Pedido.\n");
    puts("\t\t2.- Alta Material.\n");
    puts("\t\t3.- Baja Material.\n");
    puts("\t\t4.- Consulta Material.\n");
    puts("\t\t5.- Actualizar datos.\n");
    puts("\t\t6.- Ver los datos.\n");
    puts("\t\t7.- Salir.\n");
    printf("\t\tSeleccione una opcion: ");
}

void menuAreaRequiriente(void){
	puts("\n\t\t**************** AREA REQUIRIENTE ***************\n\n");
	puts("\t1.- Alta de Area Requiriente\n");
	puts("\t2.- Baja de Area Requiriente.\n");
	puts("\t3.- Consultar Area Requiriente.\n");
	puts("\t4.- Salir.\n");
	puts("\tSeleccione una opcion: ");
}

void menuAlmacen(){
    puts("\n\t\t******************ALMACEN******************\n\n");
    puts("\t\t1.- Capturar recepcion de material.\n");
    puts("\t\t2.- Baja de recepcion de material.\n");
    puts("\t\t3.- Actualizacion de recepcion de material.\n");
    puts("\t\t4.- Consulta de insumos.\n");
    puts("\t\t5.- Salir.\n");
    printf("\t\tSeleccione una opcion: ");
}

void menuReportes(){
    puts("\n\t\t******************REPORTES******************\n\n");
    puts("\t\t1.- Reporte 1.\n");
    puts("\t\t2.- Reporte 2.\n");
    puts("\t\t3.- Reporte 3.\n");
    puts("\t\t4.- Salir.\n");
    printf("\t\tSeleccione una opcion: ");
}
void Ejecucion_Final(long tv_sec, long tv_usec){
	struct timeval end;
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - tv_sec;
    long microseconds = end.tv_usec - tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    printf("\n\t\tTiempo De Ejecucion: %f segundos.\n", elapsed);
}

/*Enlazamos conexion a sockets*/
int Conexion_Socket(struct sockaddr_in server){
    int fd;
    if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
        /* llamada a socket() */
        printf("socket() error\n");
        exit(-1);
    }

    if(connect(fd, (struct sockaddr *)&server,sizeof(struct sockaddr))==-1){
        /* llamada a connect() */
        printf("connect() error\n");
        exit(-1);
    }

    return fd;
}

/*¿Ingresò letras en las opciones?*/
int Validar_Opcion(char opcion[10]){
    if(strcmp(opcion,"0") != 0){
        if(atoi(opcion) == 0){
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}
