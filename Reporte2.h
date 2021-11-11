/*Definimos librerias*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Primero necesito pedir un rango de fechas.X
//Extraer los pedidos entre ese rango de fechas.X
//MostrarlosX
//Pedir que ingrese el ID para sacar la informacion.X
//Si el estatus es pendiente, le digo que es lo que esta pidiendo y cuantoX
//Si el estatus es realizado, tengo que extraer y comparar.
//Hasta aqui por el momento
const char* ValidarFechas(char fecha_i[11], char fecha_f[11]);
const char* MostrarPedidos(char fecha_i[11], char fecha_f[11]);
const char* MostrarPedidos(char fecha_i[11], char fecha_f[11]);
const char* DefinirEstatus(int id);
const char* ObtenerPedidoPendiente(int id);
const char* ObtenerPedidoRealizado(int id);
void CabeceraReporte2(int validar);
void CuerpoReporte2(FILE *reporte,int i);

struct pedidosCompletos{
    char id[3];
    char descripcion[100];
    char estatus[11];
    char fecha[11];
    int total;
}pedidosCompletos[30];

struct pedidosCompletosPendientes{
    char nombre_area[100];
    char descripcion[100];
    char estatus[11];
    char fecha[11];
    char nombre_insumos[50];
    char piezas[4];
    int total;
}pedidosCompletosPendientes[30];

struct pedidosCompletosRealizados{
    char fecha_atendido[11];
    char nombre_insumos[50];
    char piezas[4];
    int total;
}pedidosCompletosRealizados[30];

/*Validamos fechas*/
const char* ValidarFechas(char fecha_i[11], char fecha_f[11]){
    char consulta[200];
    char auxiliar[100];
    int contador = 0;
	PGconn *conn;
	PGresult *resultado;
	int i,j;

	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta, "SELECT age(timestamp '%s',date('%s'));",fecha_f,fecha_i);
	 resultado = PQexec(conn, consulta);
		if(resultado != NULL){
			sprintf(auxiliar,"%s",PQgetvalue(resultado,0,0));
		}

        if(PQresultStatus(resultado) != PGRES_TUPLES_OK){
			return "\n\t\t\t***Esa fecha no es valida ***\n";
		}else if(PQntuples(resultado) == 0){
            return "\n\t\t\t***Esa fecha no es valida ***\n";
        }else{
            for(int i = 0; i < strlen(auxiliar); i++){
                if(auxiliar[i] == '-'){
                    contador++;
                    break;
                }
            }
            if(contador == 0){
                return "continue";
            }else{
                return "\n\t\t\t*** La fecha inicial debe ser menor ***\n";
            }
        }
    }else{
    	return "\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n";
    }
	PQfinish(conn);
}


/*Buscamos el cliente, y retornamos el mensaje correspondiente*/
const char* MostrarPedidos(char fecha_i[11], char fecha_f[11]){
    char consulta[1020];
	PGconn *conn;
	PGresult *resultado;
	int i,j;

	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta, "SELECT pd.id_pedidos_despachados, p.descripcion, pd.estatus, pd.fecha_recibido FROM pedidos_despachados pd INNER JOIN pedidos p ON pd.id_pedidos=p.id_pedidos AND pd.fecha_recibido >= '%s' AND fecha_recibido <= '%s' ORDER BY pd.id_pedidos_despachados ASC;",fecha_i,fecha_f);
	 resultado = PQexec(conn, consulta);
		if(resultado != NULL){
			puts("\n-------------------------------------------\n");
	        for (i = 0; i < PQntuples(resultado); i++){
	            sprintf(pedidosCompletos[i].id,"%s",PQgetvalue(resultado,i,0));
	            sprintf(pedidosCompletos[i].id,"%s",PQgetvalue(resultado,i,0));
                sprintf(pedidosCompletos[i].descripcion,"%s",PQgetvalue(resultado,i,1));
                sprintf(pedidosCompletos[i].estatus,"%s",PQgetvalue(resultado,i,2));
                sprintf(pedidosCompletos[i].fecha,"%s",PQgetvalue(resultado,i,3));
			}
            pedidosCompletos[0].total = PQntuples(resultado);
			puts("-------------------------------------------\n");
		}
		if(PQresultStatus(resultado) != PGRES_TUPLES_OK){
			return "\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n";
		}else if(PQntuples(resultado) == 0){
            return "\n\t\t\t*** NO EXISTEN REGISTROS EN ESE PERIODO ***\n";
        }else if(PQntuples(resultado) > 0){
            return "obtenido";
        }
    }else{
    	return "\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n";
    }
	PQfinish(conn);
}

const char* DefinirEstatus(int id){
    char consulta[1020];
    char variable[11];
	PGconn *conn;
	PGresult *resultado;
	int i,j;

	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta,"SELECT estatus FROM pedidos_despachados WHERE id_pedidos_despachados='%d';",id);
	 resultado = PQexec(conn, consulta);
		if(resultado != NULL){
			puts("\n-------------------------------------------\n");
            sprintf(variable,"%s",PQgetvalue(resultado,0,0));
			puts("-------------------------------------------\n");
		}
		if(PQresultStatus(resultado) != PGRES_TUPLES_OK){
			sprintf(validarReporte,"\n\t\t\t*** ERROR EN LA CONSULTA ***\n");
		}else if(PQntuples(resultado) == 0){
            sprintf(validarReporte,"\n\t\t\t*** NO EXISTEN REGISTROS EN ESE PEDIDO ***\n");
        }else if(PQntuples(resultado) > 0){
            if(strstr(variable,"pendiente")){
                ObtenerPedidoPendiente(id);
                CabeceraReporte2(1);
            }else{
                ObtenerPedidoPendiente(id);
                ObtenerPedidoRealizado(id);
                CabeceraReporte2(2);
            }
        }
    }else{
    	sprintf(validarReporte,"\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n");
    }
	PQfinish(conn);
}

const char* ObtenerPedidoPendiente(int id){
    char consulta[1020];
	PGconn *conn;
	PGresult *resultado;
	int i,j;

	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta, "SELECT ar.nombre_area, p.descripcion, pd.estatus, pd.fecha_recibido,i.nombre_producto, dp.piezas FROM pedidos_despachados pd INNER JOIN pedidos p ON pd.id_pedidos_despachados = '%d' AND p.id_pedidos=pd.id_pedidos INNER JOIN detalle_pedidos dp ON dp.id_pedidos=p.id_pedidos INNER JOIN insumos i ON dp.id_insumos=i.id_insumos INNER JOIN area_requiriente ar ON p.id_area_requiriente=ar.id_area_requiriente ORDER BY i.nombre_producto;",id);
	 resultado = PQexec(conn, consulta);
		if(resultado != NULL){
			puts("\n-------------------------------------------\n");
	        for (i = 0; i < PQntuples(resultado); i++){
	            sprintf(pedidosCompletosPendientes[i].nombre_area,"%s",PQgetvalue(resultado,i,0));
	            sprintf(pedidosCompletosPendientes[i].descripcion,"%s",PQgetvalue(resultado,i,1));
                sprintf(pedidosCompletosPendientes[i].estatus,"%s",PQgetvalue(resultado,i,2));
                sprintf(pedidosCompletosPendientes[i].fecha,"%s",PQgetvalue(resultado,i,3));
                sprintf(pedidosCompletosPendientes[i].nombre_insumos,"%s",PQgetvalue(resultado,i,4));
                sprintf(pedidosCompletosPendientes[i].piezas,"%s",PQgetvalue(resultado,i,5));
			}
            pedidosCompletosPendientes[0].total = PQntuples(resultado);
			puts("-------------------------------------------\n");
		}
		if(PQresultStatus(resultado) != PGRES_TUPLES_OK){
			sprintf(validarReporte,"\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n");
		}else if(PQntuples(resultado) == 0){
            sprintf(validarReporte,"\n\t\t\t*** NO EXISTEN REGISTROS EN ESE PERIODO ***\n");
        }
    }else{
    	sprintf(validarReporte,"\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n");
    }
	PQfinish(conn);
}

const char* ObtenerPedidoRealizado(int id){
    char consulta[1020];
	PGconn *conn;
	PGresult *resultado;
	int i,j;

	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta, "SELECT pd.fecha_recibido, i.nombre_producto, a.piezas FROM pedidos_despachados pd INNER JOIN almacen a ON pd.id_pedidos_despachados = '%d' AND a.id_pedidos_despachados = pd.id_pedidos_despachados INNER JOIN insumos i ON i.id_insumos=a.id_insumos ORDER BY i.nombre_producto;",id);
	 resultado = PQexec(conn, consulta);
		if(resultado != NULL){
			puts("\n-------------------------------------------\n");
	        for (i = 0; i < PQntuples(resultado); i++){
	            sprintf(pedidosCompletosRealizados[i].fecha_atendido,"%s",PQgetvalue(resultado,i,0));
	            sprintf(pedidosCompletosRealizados[i].nombre_insumos,"%s",PQgetvalue(resultado,i,1));
                sprintf(pedidosCompletosRealizados[i].piezas,"%s",PQgetvalue(resultado,i,2));
			}
            pedidosCompletosRealizados[0].total = PQntuples(resultado);
			puts("-------------------------------------------\n");
		}
		if(PQresultStatus(resultado) != PGRES_TUPLES_OK){
			sprintf(validarReporte,"\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n");
		}else if(PQntuples(resultado) == 0){
            sprintf(validarReporte,"\n\t\t\t*** NO EXISTEN REGISTROS EN ESE PERIODO ***\n");
        }
    }else{
    	sprintf(validarReporte,"\n\t\t\t*** NO SE PUDO CONECTAR A LA BASE DE DATOS :c ***\n");
    }
	PQfinish(conn);
}

void CabeceraReporte2(int validar){
	FILE *reporte;
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char fecha[11], hora[11];
	int contador = 0;

	//Extraemos fecha y hora de nuestro ordenador
	strftime(fecha,11,"%d/%m/%y",tlocal);
	strftime(hora,11,"%H:%M:%S",tlocal);

	//Comenzamos
	if((reporte = fopen("ReporteIndividual.txt", "w")) == NULL){
		sprintf(validarReporte,"\t\t\t*** Error al generar reporte ***\n");
	}else{
		fprintf(reporte,"--------------------------------------------------------------------------------\n");
		fprintf(reporte, "\n                  *** INFORMACION DE PEDIDOS INDIVIDUALES ***\n");
		fprintf(reporte, "\n                              *** HOSPITAL GENERAL ****");
		fprintf(reporte, "\n                      TAPACHULA DE CORDOVA Y ORDOÑEZ, CHIAPAS.\n");
		fprintf(reporte,"                       CARR. ANTIGUO AEROPUERTO S/N – 30700.\n");
		fprintf(reporte,"\n                                                                Fecha: %s.",fecha);
		fprintf(reporte,"\n                                                                Hora: %s.\n",hora);
		fprintf(reporte,"\n\n--------------------------------------------------------------------------------\n");

		CuerpoReporte2(reporte,validar);
	}
}

void CuerpoReporte2(FILE *reporte,int validar){
	fprintf(reporte,"\n    EL PEDIDO SELECCIONADO ESTÁ CON ESTATUS '%s'.\n",pedidosCompletosPendientes[0].estatus);
	if(validar == 2){
	    fprintf(reporte,"\n    FUÉ CREADO EL DÍA: '%s' Y FUÉ ATENDIDO EL DÍA: %s.\n",pedidosCompletosPendientes[0].fecha,pedidosCompletosRealizados[0].fecha_atendido);
	    fprintf(reporte,"\n    SOLICITADO POR EL AREA DE '%s'.",pedidosCompletosPendientes[0].nombre_area);
	}else{
	    fprintf(reporte,"\n    FUÉ CREADO EL DÍA: '%s'. SOLICITADO POR EL AREA DE '%s'.\n",pedidosCompletosPendientes[0].fecha,pedidosCompletosPendientes[0].nombre_area);
	}
	fprintf(reporte,"\n    DESCRIPCIÓN GENERAL DEL PEDIDO: %s.\n",pedidosCompletosPendientes[0].descripcion);
	fprintf(reporte,"\n--------------------------------------------------------------------------------\n");
	fprintf(reporte,"\n     ***LOS INSUMOS QUE FUERON ASIGNADOS AL PEDIDO FUERON LOS SIGUIENTES ***");
	fprintf(reporte,"\n\n             --- MATERIAl --                       -- Piezas ---\n\n");
	for(int i = 0; i < pedidosCompletosPendientes[0].total; i++){
	fprintf(reporte,"     -----------------------------------------------------------------------\n");
	    fprintf(reporte,"                 %s                                 %s\n",pedidosCompletosPendientes[i].nombre_insumos,pedidosCompletosPendientes[i].piezas);
	    fprintf(reporte,"     -----------------------------------------------------------------------\n");
	}

    if(validar == 2){
        fprintf(reporte,"\n\n     ***LOS INSUMOS QUE FUERON CAPTURADOS AL PEDIDO FUERON LOS SIGUIENTES ***");
        fprintf(reporte,"\n\n             --- MATERIAl --                       -- Piezas ---\n\n");
	    for(int i = 0; i < pedidosCompletosRealizados[0].total; i++){
	    fprintf(reporte,"     -----------------------------------------------------------------------\n");
	        fprintf(reporte,"                 %s                                 %s\n",pedidosCompletosRealizados[i].nombre_insumos,pedidosCompletosRealizados[i].piezas);
	        fprintf(reporte,"     -----------------------------------------------------------------------\n");
	    }

	    for(int i = 0; i < pedidosCompletosPendientes[0].total; i++){
            if(pedidosCompletosPendientes[i].piezas != pedidosCompletosRealizados[i].piezas){
                contador++;
                break;
            }
	    }
        fprintf(reporte,"\n\n--------------------------------------------------------------------------------\n");
        fprintf(reporte,"\n                             *** CONCLUSIÓN ***\n\n");
        if(contador == 0){
            fprintf(reporte,"\n            EL PEDIDO FUE DESPACHADO DE MANERA SATISFACTORIA\n");
        }else{
            contador = 0;
            for(int i = 0; i < pedidosCompletosPendientes[0].total; i++){
                if(atoi(pedidosCompletosPendientes[i].piezas) != atoi(pedidosCompletosRealizados[i].piezas)){ //Algo pasó
                    if(atoi(pedidosCompletosPendientes[i].piezas) > atoi(pedidosCompletosRealizados[i].piezas)){
                        if((atoi(pedidosCompletosPendientes[i].piezas) - atoi(pedidosCompletosRealizados[i].piezas)) == 1){
                            fprintf(reporte,"\n     DEL PRODUCTO '%s' FALTÓ %d PIEZA.", pedidosCompletosPendientes[i].nombre_insumos,atoi(pedidosCompletosPendientes[i].piezas) - atoi(pedidosCompletosRealizados[i].piezas));
                        }else{
                            fprintf(reporte,"\n     DEL PRODUCTO '%s' FALTARON %d PIEZAS.", pedidosCompletosPendientes[i].nombre_insumos,atoi(pedidosCompletosPendientes[i].piezas) - atoi(pedidosCompletosRealizados[i].piezas));
                        }
                    }else{
                        if((atoi(pedidosCompletosRealizados[i].piezas) - atoi(pedidosCompletosPendientes[i].piezas)) == 1){
                        fprintf(reporte,"\n     DEL PRODUCTO '%s' SE MANDÓ %d PIEZA EXTRA.", pedidosCompletosPendientes[i].nombre_insumos,atoi(pedidosCompletosRealizados[i].piezas) - atoi(pedidosCompletosPendientes[i].piezas));
                        }else{
                            fprintf(reporte,"\n     DEL PRODUCTO '%s' SE MANDARON %d PIEZAS EXTRAS.", pedidosCompletosPendientes[i].nombre_insumos,atoi(pedidosCompletosRealizados[i].piezas) - atoi(pedidosCompletosPendientes[i].piezas));
                        }
                    }
                }
            }
        }
    }

	fprintf(reporte,"\n--------------------------------------------------------------------------------\n");
	sprintf(validarReporte,"\n\t\t\t\t*** REPORTE CREADO ***\n\n");
	fclose(reporte);
}
