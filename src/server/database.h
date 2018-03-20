#include <mysql/mysql.h>

// Função de configuração do banco de dados
// Carrega os dados do arquivo de configuração
// Banco padrão MYSQL
// Recebe o ponteiro para a estrutura MYSQL
// retorn 0 em sucesso e -1 em erro

int base_config(MYSQL *connect);

//Função que configura os buffers
//Parametros para query
//Resultados da query
//Recebe a EStrutura de paramentros, constante do tipo d dado,  buffer, tamanho dos dados e total
//Retorna 0 em sucesso e -1 em erro

int bind_config(MYSQL_BIND *param, int type, char *buffer, int b_lenght, unsigned long int *v_lenght);

//Função que executata as declarações
//Definições nas constantes do database.c
//recebe a estrutura MYSQL, a query, parametros e resultados
//Retorna 0 em sucesso e -1 em erro

int statement_exe(MYSQL *connect, char query, MYSQL_BIND *param, MYSQL_BIND *result);

//Função que verifica o hash do user
//Recebe a estrutura MYSQL e o hash
//retorna a id em sucesso e -1 em erro

int user_check(MYSQL *connect, char *hash);

//Função que insere o hash de sessão do user
//Recebe a estrutura mysql, o hash e id
//Retorna 0 em sucesso e -1 em erro

int hash_user(MYSQL *connect, char *hash, int id_user);

//Função que realiza o login do user
//Recebe a estrutura MYSQL, o name, password e uma variável de resultado hash
//Retorna 0 em sucesso e -1 em erro

int login_user(MYSQL *connect, char *name, char *password, char *hash);
