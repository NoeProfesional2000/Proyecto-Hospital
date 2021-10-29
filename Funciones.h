
#include <fcntl.h>
#include <unistd.h>
#include <libpq-fe.h>
#include <string.h>

/*Metodo para la conexion a la bd*/
void conexion(){
    PGconn *conn;
    PGresult *resultado;
    
    conn=PQsetdbLogin("localhost","5432",NULL,NULL,"ProyectoHospital","postgres","1234");
	if(PQstatus(conn) != CONNECTION_BAD)
    {
		/*Si se conecta aqui haremos los movimientos*/
    }else{
        /*Si no se conecta mandaremos un mensaje de error*/
    }
	PQfinish(conn);
    
}