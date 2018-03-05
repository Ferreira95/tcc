#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

#define BUFFER 512
#define LOGIN "SELECT password FROM volunteer WHERE name = ?;\0"
#define INSERT_DATA "INSERT INTO data(value, project) VALUES (?,?)\0"
#define INSERT_RESULT "INSERT INTO result(key, value) VALUES (?,?)\0"
#define RECOVERY_DATA "SELECT"
#define RECOVERY_PROJECT "SELECT path FROM project WHERE id = ?\0"

int statement_exe(MYSQL *connect, char *query, MYSQL_BIND *param) // Executa a ação
{
	MYSQL_STMT *stmt;
	MYSQL_RES *result;

	if(!(stmt = mysql_stmt_init(connect)))
		return -1;
	
	if(mysql_stmt_prepare(stmt, query, strlen(query)))
		return -1;

	if(mysql_stmt_bind_param(stmt, param))
	{
		perror("bind");
		return -1;
	}

	if(mysql_stmt_execute(stmt))
	{
		perror("execute");
//		printf("%s",mysql_stmt_error(stmt));
		return -1;
	}

	if( (result = mysql_store_result(connect)) == NULL)
	{
		perror(mysql_error(connect));
		return -1;
	}
	mysql_free_result(result);

	return 0;
}

void param_config(MYSQL_BIND *param, int type, char *buffer, int b_length, unsigned long int *v_length) // configurar dados
{
	memset(param, 0, sizeof(param));
	param->buffer_type = type;
	param->buffer = buffer;
	param->buffer_length = BUFFER;
	param->is_null = 0;
	param->length = v_length;
}

int base_config(MYSQL *connect) // Inicialização e configuração do banco
{
//	char addr[30];
//	char port[10];
//	char user[30];
//	char pass[30];
//	char base[30];
	MYSQL_RES *result;

	mysql_init(connect);
	if(mysql_real_connect(connect, "localhost", "", "", "paralel_net", 0, NULL, 0 ))
		return 1;
	else
		exit (0);
}

int login_user(MYSQL *connect, char *name, char *password, unsigned long int d_length) // Login
{
	MYSQL_BIND param[1];
	MYSQL_RES *result;
	MYSQL_ROW row;

	param_config(&param[0], MYSQL_TYPE_STRING, name, BUFFER, &d_length);

	if(statement_exe(connect, LOGIN, param) < 0)
	{
		perror("Login");
		return -1;
	}

//	mysql_real_query(connect,LOGIN, sizeof(LOGIN));
	if( (result = mysql_store_result(connect)) == NULL)
	{
		perror(mysql_error(connect));
		return -1;
	}
	perror("2");
	if(mysql_num_rows(result) < 0)
	{
		perror("Result");
		return -1;
	}
	perror("3");
	if( (row = mysql_fetch_row(result)) == NULL)
	{
		perror("Fetch Row");
		return -1;
	}
	int unsigned long *num;
	num = mysql_fetch_lengths(result);	
	perror("ok");
	write(STDOUT_FILENO, row[0], num[0]);
}


int data_insert(MYSQL *connect, char *data, unsigned long int d_length, int project) // Inserção de dados MAP
{
	MYSQL_BIND param[2];

	param_config(&param[0], MYSQL_TYPE_STRING, data, BUFFER, &d_length);
	param_config(&param[1], MYSQL_TYPE_LONG, (char *)&project, 0, 0);

	return statement_exe(connect, INSERT_DATA, param);
}

int data_recovery(MYSQL *connect, int project, char *data) // Recuperação de dados para distribuição
{
	MYSQL_BIND param[1];

	param_config(&param[0], MYSQL_TYPE_LONG, (char *)&project, 0, 0);

	return statement_exe(connect, RECOVERY_DATA, param);
}

int result_insert(MYSQL *connect, int key, char *result, unsigned long int r_length) // Inserção do resultado
{
	MYSQL_BIND param[2];

	param_config(&param[0], MYSQL_TYPE_LONG, (char *)&key, 0, 0);
	param_config(&param[1], MYSQL_TYPE_STRING, result, BUFFER, &r_length);

	return statement_exe(connect, INSERT_RESULT, param);
}

int file_recovery(MYSQL *connect, int project, char *path) // Recuperação do programa de processamento
{
	MYSQL_BIND param[1];

	param_config(&param[0], MYSQL_TYPE_LONG, (char *)&project, 0, 0);

	return statement_exe(connect, RECOVERY_PROJECT, param);
}

int main() // database start
{
	MYSQL connect;
	base_config(&connect);
//	data_insert(&connect, "test1\0",5, 19);
	login_user(&connect, "tst", "pass", 8);
}

