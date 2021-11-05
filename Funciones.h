
#include <fcntl.h>
#include <unistd.h>
#include <libpq-fe.h>
#include <string.h>
#include <sys/time.h>

/*Para hacer uso de esta funcion, debemos hacer lo siguiente:
  1.- Declarar un tiempo de inicio, mandarlo al struct y 
  	  pasarlo como parametro a Ejecucion final de la siguiente forma:
  	  -- Iniciando el tiempo...
	  struct timeval begin;
      gettimeofday(&begin, 0);
      -- Operaciones a realizar --
      -- Al terminar la operacion debemos pasar al metodo las partes del struct
         que nos interesa, que solo son dos, con eso, la funcion ya puede calcular
         el final y el tiempo de ejecución en segundos. --
      Ejecucion_Final(begin.tv_sec,begin.tv_usec);
*/
    
void Ejecucion_Final(long tv_sec, long tv_usec){
	struct timeval end;
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - tv_sec;
    long microseconds = end.tv_usec - tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    printf("Tiempo De Ejecucion: %f segundos.\n", elapsed);
}

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
