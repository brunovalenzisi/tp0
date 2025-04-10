#include "client.h"



int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	if(logger==NULL){abort();}; 

		 
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	if(config==NULL){abort();}; 
		valor=config_get_string_value(config,"CLAVE");
		ip=config_get_string_value(config,"IP");
		puerto=config_get_string_value(config,"PUERTO");
		
		log_info(logger,valor);

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("./tp0.log","Testlog",true,LOG_LEVEL_TRACE);


	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config=config_create("./cliente.config");
	config_set_value(nuevo_config,"CLAVE","Hola!, soy un log desde config");
	return nuevo_config;
}

 leer_consola(t_log* logger)
{
	char* leido;

    while ((leido = readline("> ")) != NULL && strcmp(leido, "") != 0)
    {
        log_info(logger, leido);
        free(leido);
    }

   
    if (leido != NULL)
        free(leido);

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	paquete=crear_paquete();

	
	// Leemos y esta vez agregamos las lineas al paquete

    while ((leido = readline("> ")) != NULL && strcmp(leido, "") != 0)
    {
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
     	free(leido);
    }

   
    if (leido != NULL)

		
		enviar_paquete(paquete,conexion);
        free(leido);
		eliminar_paquete(paquete);





	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{

	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
