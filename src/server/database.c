#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include <mysql/mysql.h>
#include <confuse.h>

#define PASS_LEN 128
#define BUFFER 512
#define USER_CHECK "SELECT user FROM session WHERE hash = ?\0"
#define HASH_USER "REPLACE INTO session(user, hash) VALUES (?,?)\0"
#define LOGIN "SELECT  id FROM volunteer WHERE name = ? and password = ? LIMIT 1;\0"
#define INSERT_DATA "INSERT INTO data(value, project) VALUES (?,?)\0"
#define INSERT_RESULT "INSERT INTO result(key, value) VALUES (?,?)\0"
#define RECOVERY_DATA "SELECT"
#define RECOVERY_PROJECT "SELECT path FROM project WHERE id = ?\0"

int base_config(MYSQL *connect) // Inicialização e configuração do banco
{
	char *addr;
	char *port;
	char *user;
	char *pass;
	char *base;

	cfg_t *cfg;
	cfg_opt_t opts[] =
	{
		CFG_SIMPLE_STR("DB_addr", &addr),
		CFG_SIMPLE_STR("DB_port", &port),
		CFG_SIMPLE_STR("DB_user", &user),
		CFG_SIMPLE_STR("DB_pass", &pass),
		CFG_SIMPLE_STR("DB_base", &base),
		CFG_END()
	};
	cfg = cfg_init(opts, 0);
	cfg_parse(cfg, "db.conf");

	mysql_init(connect);
	if(mysql_real_connect(connect, addr, user, pass, base, 0, NULL, 0 ))
	{
		cfg_free(cfg);
		return 1;
	}
	else
		exit (0);
}

		//---------------- Funções de pesquisa, config de parâmetros e resultados -----------

void bind_config(MYSQL_BIND *param, int type, char *buffer, int b_length, unsigned long int *v_length) // configurar dados da query
{
	memset(param, 0, sizeof(param));
	param->buffer_type = type;
	param->buffer = buffer;
	param->buffer_length = b_length;  //BUFFER;
	param->is_null = 0;
	param->length = v_length;
}

int statement_exe(MYSQL *connect, char *query, MYSQL_BIND *param, MYSQL_BIND *result) // Executa a ação
{
	MYSQL_STMT *stmt;
	MYSQL_RES *meta;
	
	if(!(stmt = mysql_stmt_init(connect)))
	{
		perror("init");
		return -1;
	}
	
	if(mysql_stmt_prepare(stmt, query, strlen(query)))
	{
		perror(mysql_stmt_error(stmt));
		perror("Prepare");
		return -1;
	}

	if(mysql_stmt_bind_param(stmt, param))
	{
		perror(mysql_stmt_error(stmt));
		perror("bind");
		return -1;
	}

	if(mysql_stmt_execute(stmt))
	{
		perror("execute");
		perror(mysql_stmt_error(stmt));
		return -1;
	}

	if(result == NULL)
		return 0;
			
		// -------- EXE sem retorno ---------------	

	if((meta = mysql_stmt_result_metadata(stmt)) == NULL)
	{
		perror(mysql_stmt_error(stmt));
		perror("store");
		return -1;
	}
	
	if(mysql_stmt_bind_result(stmt, result))
	{
		perror("Result");
		return -1;
	}

	if(mysql_stmt_fetch(stmt) == 1)
	{
		perror("Rows");
		return -1;
	}

	mysql_stmt_close(stmt);
	return 0;
}

		//----------------- Funções de gerenciamento de users ----------------------

int user_check(MYSQL *connect, char *hash) // Verifica a sessão do usuário
{
	unsigned long int d_length;
	MYSQL_BIND param[1];
	MYSQL_RES *result;
	MYSQL_ROW row;


	d_length = strlen(hash);
	bind_config(&param[0], MYSQL_TYPE_STRING, hash, sizeof(*hash), &d_length);

	if(statement_exe(connect, USER_CHECK, param, NULL) < 0)
	{
		perror("Login");
		return -1;
	}
}

int hash_user(MYSQL *connect, char *hash, int id_user) // Inserção do hash id do user
{
	int i;
	unsigned long int d_length;
	MYSQL_BIND param[2];
	uuid_t uuid;

	bind_config(&param[0], MYSQL_TYPE_LONG, (char *)&id_user, 0, 0);
	bind_config(&param[1], MYSQL_TYPE_STRING, hash, sizeof(*hash), &d_length);

	uuid_generate(uuid);
	uuid_unparse_lower(uuid, hash);
	d_length = strlen(hash);

	if(statement_exe(connect, HASH_USER, param, NULL) < 0)
	{
		uuid_clear(uuid);
		return -1;	
	}
	
	return 0;
}
int login_user(MYSQL *connect, char *name, char *password, char *hash) // Login inicial, nova session
{
	unsigned long long id;
	unsigned long int name_length, pass_length;
	MYSQL_BIND param[2], result[2];
	MYSQL_ROW row;

	name_length = strlen(name);
	pass_length = strlen(password);

	bind_config(&param[0], MYSQL_TYPE_STRING, name, sizeof(*name), &name_length);
	bind_config(&param[1],MYSQL_TYPE_STRING, password, sizeof(*password), &pass_length);

	bind_config(&result[0], MYSQL_TYPE_LONGLONG, (char *)&id, 0, 0);

	if(statement_exe(connect, LOGIN, param, result) < 0)
	{
		perror("Login");
		return -1;
	}
	
	if(hash_user(connect, hash, id) < 0)
	{
		perror("Hash insert");
		return -1;
	}

	return 0;
}

			// ------------------- Funções de dados ---------------------

int data_recovery(MYSQL *connect, char *hash_project, char *hash_user, char *data) //Dados para distribuição
{
	MYSQL_BIND param[1];

//	bind_config(&param[0], MYSQL_TYPE_LONG, (char *)&project, 0, 0);

	return statement_exe(connect, RECOVERY_DATA, param, NULL);
}

int result_insert(MYSQL *connect, int key, char *result, unsigned long int r_length) // Inserção do resultado
{
	MYSQL_BIND param[2];

	bind_config(&param[0], MYSQL_TYPE_LONG, (char *)&key, 0, 0);
	bind_config(&param[1], MYSQL_TYPE_STRING, result, BUFFER, &r_length);

	return statement_exe(connect, INSERT_RESULT, param, NULL);
}

int file_recovery(MYSQL *connect, int project, char *path) // Recuperação do programa de processamento
{
	MYSQL_BIND param[1];

	bind_config(&param[0], MYSQL_TYPE_LONG, (char *)&project, 0, 0);

	return statement_exe(connect, RECOVERY_PROJECT, param, NULL);
}

int main() // database start
{
	char hash[290];
	MYSQL connect;
	base_config(&connect);
//	data_insert(&connect, "test1\0",5, 19);
//	hash_user(&connect, hash, 5);	
	login_user(&connect, "ferreira\0", "alfa12\0", hash);
//	user_check(&connect, "2a229166-5e14-4136-91dc-45998e0668ec\0");
}

