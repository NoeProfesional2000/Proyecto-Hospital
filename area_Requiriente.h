/*--- Declaración de funcion para crear un area requiriente, dar de baja y consultar el área por nombre -----*/
void alta_Area_Requiriente(char nombre_Area[40], char descripcion[50]);
void baja_Area_Requiriente(char nombre_Area[40], char descripcion[50]);
void ver_Area_Requiriente(char nombre[40]);

void alta_Area_Requiriente(char nombre_Area[40], char descripcion[50]){
    char tab[50], cad[1020];
    PGconn *conn;
    PGresult *resultado;
    int i,j;
// Se realiza la conexión e inserción de datos requeridos para dar de alta al Área Requiriente. //
	puts("\n\t\t ------------ALTA DE AREA REQUIRIENTE------------\n\n");
	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","123");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
// Se conecta con el PL para poder realizar la inserción y validaciones al realizar la operación. //
     sprintf(cad, "SELECT Requiriente('%d','%s','%s');",1,nombre_Area,descripcion);
	 resultado = PQexec(conn, cad);
      if(PQntuples(resultado) == 1){
			printf("\t\t**** ALTA EXITOSA!! ****\n");
		}else{
			printf("\t\t***Error en el servidor***\n");
		}
    }else{
    	puts("\n***Error en el sistema***\n");
    }
	PQfinish(conn);
} //Cierra función de Alta área requiriente

void baja_Area_Requiriente(char nombre_Area[40], char descripcion[50]){
    char tab[50], cad[1020];
    PGconn *conn;
    PGresult *resultado;
    int i,j;
// Conexión a base de datos. //
	puts("\n\t\t ------------BAJA DE AREA REQUIRIENTE------------\n\n");
	conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","123");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
  // Se realiza la baja del Área Requiriente, se cambia el estatus a 0. //  
 // Se conecta con el PL para poder realizar la inserción y validaciones al realizar la operación. //
     sprintf(cad, "SELECT Requiriente('%d','%s','%s');",2,nombre_Area,descripcion);
	 resultado = PQexec(conn, cad);
      if(PQntuples(resultado) == 1){
			printf("\t\t**** BAJA EXITOSA!! ****\n");
		}else{
			printf("\t\t***Error en el servidor***\n");
		}
    }else{
    	puts("\n***Error en el sistema***\n");
    }
	PQfinish(conn);
}//Cierra función de Baja área requiriente

void ver_Area_Requiriente(char nombre[40]){

  char tab[50], cad[1020];
  PGconn *conn;
  PGresult *resultado;
  PGresult *res;
  int i,j;
  
   puts("\n\t\t --------Consulta de Area Requiriente------- \n\n");
   conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyectohospital","postgres","123");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
    // Se realiza consulta de datos de acuerdo al nombre del área requiriente. //
    sprintf(cad, "select id_area_requiriente, nombre_area, descripcion, estatus from area_requiriente where nombre_area = '%s' and estatus = 1;", nombre);
     resultado = PQexec(conn, cad);
     //Si no se obtiene ningún resultado, se envía un mensaje al usuario. //
    if(PQntuples(PQexec(conn, cad)) == 0){
    
    puts("\n\t\t No existe el Area o se ha dado de baja\n\n");
    // Si obtiene resultado se muestra por medio de un ciclo for. //
     }else if(PQntuples(PQexec(conn, cad)) == 1){
        	puts("------------------------------------------------------------------\n");
     	puts("\t ID                 NOMBRE                       DESCRIPCION              ESTATUS\n\n");
      for (i = 0; i < PQntuples(resultado); i++){ 
            for (j = 0; j < PQnfields(resultado); j++){
	    	 printf("\t%s\t    ",PQgetvalue(resultado,i,j));
		}
		puts("\n");
		}
	      puts("---------------------------------------------------------------------\n");
    
    } //else if existe resultado de consulta
    }else{
    	puts("\t\t***Error en el sistema***\n");
    }
	PQfinish(conn);
	
	puts("\nPresiona '0' para continuar.");
	while(getchar() != '0');

}//Cierre función consulta de área requiriente
