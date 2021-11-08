const char* alta_material(int id_area_requiriente, char nombre_producto[100]);
const char* buscar_area_requiriente(char nombre[100], char nombre_producto[100]);
const char* actualizar_entrada_inventario(int id, int cantidad);
const char* buscar_insumo(char nombre[100], int cantidad);
const char* buscar_areas_requiriente();

// Se realiza la conexi�n e inserci�n de datos para dar de alta un material //
const char* alta_material(int id_area_requiriente, char nombre_producto[100]){
    char tab[50], insercion[1020];
    PGconn *conn;
    PGresult *resultado;


    conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
		sprintf(insercion, "INSERT INTO insumos(id_area_requiriente,nombre_producto,stock,estatus) VALUES ('%d','%s',0,0)",id_area_requiriente, nombre_producto);
	    resultado = PQexec(conn, insercion);

     	if(PQresultStatus(resultado) == PGRES_COMMAND_OK){
			return "----Se ha hecho la alta material de manera exitosa----";
		}else{
			return "----Fallo la alta----";
		}
    }else{
    	return "----Error en el servidor----";
    }
	PQfinish(conn);  
}

// Se realiza la conexi�n y busqueda de un area requiriente en especifico. //
const char* buscar_area_requiriente(char nombre[100], char nombre_producto[100]){
    char consulta[1020];
    char id[100];
    bzero(id,sizeof(id));
    PGconn *conn;
    PGresult *resultado;
    PGresult *res;
    int i,j;

    conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
    if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta, "select id_area_requiriente from area_requiriente where nombre_area = '%s'",nombre);
     resultado = PQexec(conn, consulta);
        if(resultado != NULL){
            puts("\n-------------------------------------------\n");
            for (i = 0; i < PQntuples(resultado); i++){
                for (j = 0; j < PQnfields(resultado); j++){
                  strcat(id,PQgetvalue(resultado,i,j));  
                  printf("  [%s]",PQgetvalue(resultado,i,j));
                }
                puts("\n");
            }
            puts("-------------------------------------------\n");
        }
        if(PQresultStatus(resultado) != PGRES_TUPLES_OK){
            return "----Error en el servidor----";
        }else if(PQntuples(resultado) == 0){
            return "----No existe esa area----";
        }else if(PQntuples(resultado) > 0){
           return alta_material (atoi(id), nombre_producto);
            
        }
    }else{
        return "----Error en el servidor----";
    }
    printf("%s",id );
    PQfinish(conn);
}

// Se realiza la conexi�n y actualizacion de los datos del inventario //
const char* actualizar_entrada_inventario(int id, int cantidad){
    char tab[50], insercion[1020];
    PGconn *conn;
    PGresult *resultado;


    conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
    if(PQstatus(conn) != CONNECTION_BAD)
    {
        sprintf(insercion, "UPDATE insumos set stock= (stock+'%d') WHERE id_insumos='%d'",cantidad, id);
        resultado = PQexec(conn, insercion);

        if(PQresultStatus(resultado) == PGRES_COMMAND_OK){
            return "----Se ha hecho la entrada de inventario de manera exitosa----";
        }else{
            return "----Fallo la alta----";
        }
    }else{
        return "----Error en el servidor----";
    }
    PQfinish(conn);  
}

// Se realiza la conexi�n y busqueda de insumos//
const char* buscar_insumo(char nombre[100], int cantidad){
    char consulta[1020];
    char id[100];
    bzero(id,sizeof(id));
    PGconn *conn;
    PGresult *resultado;
    PGresult *res;
    int i,j;
    conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
    if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta, "select id_insumos from insumos where nombre_producto = '%s'",nombre);
     resultado = PQexec(conn, consulta);
        if(resultado != NULL){
            puts("\n-------------------------------------------\n");
            for (i = 0; i < PQntuples(resultado); i++){
                for (j = 0; j < PQnfields(resultado); j++){
                  strcat(id,PQgetvalue(resultado,i,j));  
                  printf("  [%s]",PQgetvalue(resultado,i,j));
                }
                puts("\n");
            }
            puts("-------------------------------------------\n");
        }
        if(PQresultStatus(resultado) != PGRES_TUPLES_OK){
            return "----Error en el servidor----";
        }else if(PQntuples(resultado) == 0){
            return "----No existe ese material----";
        }else if(PQntuples(resultado) > 0){
           return actualizar_entrada_inventario(atoi(id), cantidad);
            
        }
    }else{
        return "----Error en el servidor----";
    }
    PQfinish(conn);
}

// Se realiza la conexi�n y busqueda de toda las areas requiriente en existencia //
const char* buscar_areas_requiriente(){
    char consulta[1020];
    char todo[1020];
    bzero(todo,sizeof(todo));
	PGconn *conn;
	PGresult *resultado;
	PGresult *res;
	int i,j;

	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","12345");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
     sprintf(consulta, "SELECT (id_area_requiriente,nombre_area) from area_requiriente");
	 resultado = PQexec(conn, consulta);
		if(resultado != NULL){
			puts("\n-------------------------------------------\n");
	        for (i = 0; i < PQntuples(resultado); i++){
		        for (j = 0; j < PQnfields(resultado); j++){
                  strcat(todo,PQgetvalue(resultado,i,j));
                  strcat(todo,"\t");
                  printf("  [%s]",PQgetvalue(resultado,i,j));
				}
				puts("\n");
			}
			puts("-------------------------------------------\n");
		}
		if(PQresultStatus(resultado) != PGRES_TUPLES_OK){
            sprintf(todo,"----Error en el servidor----");
		}else if(PQntuples(resultado) == 0){
            sprintf(todo,"----No existe la matricula----");
        }
    }else{
        sprintf(todo,"----Error en el servidor----");
    	
    }
    return todo;
	PQfinish(conn);
}