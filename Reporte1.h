/*Definimos librerias*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void CabeceraReporte();
void CuerpoReporte(FILE *reporte);
const char* ObtenerPedidos(char cadena[70]);
void VisualizarReporte();
char validarReporte[100];
int filasCero;
int contador = 0;

struct pedidos_pendientes{
    char id[3];
    char area_requiriente[100];
    char descripcion[100];
    char insumos[3];
    char fecha[11];
} pedidos_pendientes[10];

//Parte de arriba
void CabeceraReporte(){
	FILE *reporte;
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char fecha[11], hora[11];

	//Extraemos fecha y hora de nuestro ordenador
	strftime(fecha,11,"%d/%m/%y",tlocal);
	strftime(hora,11,"%H:%M:%S",tlocal);

	//Comenzamos
	if((reporte = fopen("ReportePedidos.txt", "w")) == NULL){
		sprintf(validarReporte,"\t\t\t*** Error al generar reporte ***\n");
	}else{
		fprintf(reporte,"--------------------------------------------------------------------------------\n");
		fprintf(reporte, "\n                     *** PEDIDOS PENDIENTES Y ATENDIDOS ***\n");
		fprintf(reporte, "\n                              *** HOSPITAL GENERAL ****");
		fprintf(reporte, "\n                      TAPACHULA DE CORDOVA Y ORDOÑEZ, CHIAPAS.\n");
		fprintf(reporte,"                       CARR. ANTIGUO AEROPUERTO S/N – 30700.\n");
		fprintf(reporte,"\n                                                                Fecha: %s.",fecha);
		fprintf(reporte,"\n                                                                Hora: %s.\n",hora);
		fprintf(reporte,"\n\n--------------------------------------------------------------------------------\n\n");
		CuerpoReporte(reporte);
	}
}

/*Parte del cuerpo, parte fuerte*/
void CuerpoReporte(FILE *reporte){
	fprintf(reporte,"  Pedidos Realizados = %s.\n",ObtenerPedidos("SELECT COUNT(*) FROM PEDIDOS_DESPACHADOS WHERE estatus = 'realizado'"));
	fprintf(reporte,"  Pedidos Pendientes = %s.\n",ObtenerPedidos("SELECT COUNT(*) FROM PEDIDOS_DESPACHADOS WHERE estatus ='pendiente'")); //Conteo de los pedidos pendientes.
    if(filasCero == 0){
	    fprintf(reporte,"\n                     *** Información de los pedidos pendientes ***\n\n");
	    fprintf(reporte,"  ID          Area           Descripcion      No.Insumos      Fecha creacion\n");
        for(int i = 0; i < contador; i++){
        fprintf(reporte,"\n--------------------------------------------------------------------------------\n");
            fprintf(reporte,"  %s         %s         %s        %s         %s\n",pedidos_pendientes[i].id,pedidos_pendientes[i].area_requiriente,pedidos_pendientes[i].descripcion,pedidos_pendientes[i].insumos,pedidos_pendientes[i].fecha);
        }
    }else{
        fprintf(reporte,"\n                          *** NO HAY PEDIDOS PENDIENTES ***\n\n");
    }
	//Aqui iria la lista de pedidos pendientes....


	fprintf(reporte,"--------------------------------------------------------------------------------\n");
	sprintf(validarReporte,"\n\t\t\t\t*** REPORTE CREADO ***\n\n");
	fclose(reporte);
}

/*Conexiones a base de datos*/

//Cuantos hay de cada uno
const char* ObtenerPedidos(char cadena[70]){
    char tab[50], insercion[70];
    PGconn *conn;
    PGresult *resultado;

    conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
	    resultado = PQexec(conn, cadena);
        return PQgetvalue(resultado,0,0);
    }else{
    	return "\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n";
    }
	PQfinish(conn);
}

//eExtraemos datos de pedidos pendientes
void busqueda_Cedula_Concatenar(){
    char consulta[2020];
	PGconn *conn;
	PGresult *resultado;
	PGresult *res;
	int i,j;

	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta, "SELECT p.id_pedidos, ar.nombre_area, p.descripcion, COUNT(*), p.fecha_creacion FROM pedidos_despachados pd INNER JOIN pedidos p ON pd.estatus='pendiente' AND pd.id_pedidos=p.id_pedidos INNER JOIN area_requiriente ar ON p.id_area_requiriente = ar.id_area_requiriente INNER JOIN detalle_pedidos dp ON dp.id_pedidos = p.id_pedidos GROUP BY (p.id_pedidos, ar.nombre_area, p.descripcion, p.fecha_creacion);");
	 resultado = PQexec(conn, consulta);
		if(resultado != NULL){
			puts("\n-------------------------------------------\n");
			contador = PQntuples(resultado);
	        for (i = 0; i < PQntuples(resultado); i++){
                  sprintf(pedidos_pendientes[i].id,"%s",PQgetvalue(resultado,i,0));
                  sprintf(pedidos_pendientes[i].area_requiriente,"%s",PQgetvalue(resultado,i,1));
                  sprintf(pedidos_pendientes[i].descripcion,"%s",PQgetvalue(resultado,i,2));
                  sprintf(pedidos_pendientes[i].insumos,"%s",PQgetvalue(resultado,i,3));
                  sprintf(pedidos_pendientes[i].fecha,"%s",PQgetvalue(resultado,i,4));
			}
			puts("\n-------------------------------------------\n");
		}

		if(PQntuples(resultado) == 0){
            sprintf(validarReporte,"\n\t\t\t*** NO EXISTE LA CEDULA :c ***\n");
            filasCero = 1;
        }else{
            filasCero = 0;
        }
    }
	PQfinish(conn);
}
