/*Definimos librerias*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void CabeceraReporte(char fecha_inicio[11], char fecha_final[11], int numero);
void CuerpoReporte(FILE *reporte, char fecha_inicio[11], char fecha_final[11]);
void VisualizarReporte();
char nombreArchivo[30];

/*int main(int argc, char *argv[]){
	char fecha[11];
	printf("Ingrese una fecha: ");
	scanf("%s",fecha);
	CabeceraReporte(fecha,fecha,3);
	VisualizarReporte();
	printf("%s", nombreArchivo);
	
	return 0;
}*/

//Parte de arriba 
void CabeceraReporte(char fecha_inicio[11], char fecha_final[11], int numero){
	FILE *reporte;
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char fecha[11], hora[11];

	//Concatenamos la opcion con el nombre principal
	sprintf(nombreArchivo, "Reporte%d.txt",numero);

	//Extraemos fecha y hora de nuestro ordenador
	strftime(fecha,11,"%d/%m/%y",tlocal);
	strftime(hora,11,"%H:%M:%S",tlocal);

	//Comenzamos
	if((reporte = fopen(nombreArchivo, "w")) == NULL){
		printf("\t\t\t*** Error al generar reporte ***\n");
	}else{
		fprintf(reporte,"--------------------------------------------------------------------------------\n");
		fprintf(reporte, "\n                     *** MES EN EL QUE SE HACEN MAS PEDIDOS ***\n");
		fprintf(reporte, "\n                              *** HOSPITAL GENERAL ****");
		fprintf(reporte, "\n                      TAPACHULA DE CORDOVA Y ORDOÑEZ, CHIAPAS.\n");
		fprintf(reporte,"                       CARR. ANTIGUO AEROPUERTO S/N – 30700.\n");
		fprintf(reporte,"\n                                                                Fecha: %s.",fecha);
		fprintf(reporte,"\n                                                                Hora: %s.\n",hora);
		fprintf(reporte,"\n\n--------------------------------------------------------------------------------\n\n");
		CuerpoReporte(reporte, fecha_inicio, fecha_final);
	}
}

//El cuerpo va a tener conexion con la BD, para extraccion de datos.
//Necesito crear un struct dinamico para poder imprimir de manera ordenada los datos
//La cabecera, cuerpo y visualizacion ya estan funcionando.

void CuerpoReporte(FILE *reporte, char fecha_inicio[11], char fecha_final[11]){
	fprintf(reporte,"                                                  Referencia inicial: %s\n", fecha_inicio);
	fprintf(reporte,"                                                  Referencia final: %s\n\n", fecha_final);
	fprintf(reporte,"\n");
	fprintf(reporte,"\n\n--------------------------------------------------------------------------------\n\n");
	fclose(reporte);
}

//Al terminar de crear un reporte, lo mandamos a llamar.
void VisualizarReporte(){
	char lectura;
	FILE *reporte;

	reporte = fopen(nombreArchivo,"r");
	while(1){
		lectura = fgetc(reporte);
     	if(lectura == EOF)
      		break;
      	else
      	printf("%c",lectura);
   }
   fclose(reporte);
}
