#include "network.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HEAD_LEN 512
#define HASH_LEN 40
#define MAX_PARAM 5
#define LOG_PARAM 4
#define RESULT_PARAM 5
#define DATA_PARAM 3
#define PROG_PARAM 3

typedef void proto(char **params, char *resp);

void zero(char *head_final)
{
	int i;
	char *str;

	i = strlen(head_final);
	str = head_final;
	str+=i;
	memset(str, 0, HEAD_LEN - i);
	write(STDOUT_FILENO, head_final, HEAD_LEN);
}

void resp_config(char *type, char **param, int len, char *resp)
{
	int i;
	strncat(resp, type, strlen(type));
	for(i = 0; i < len; i++)
	{
		strncat(resp, param[i], strlen(param[i]));
		strncat(resp, "\n", 1);
	}
	strncat(resp, "\0", 1);
}

void  login(char **param, char *resp)  //(char *name, char *password, char *resp) // Login do usuário
{
	char hash[HASH_LEN];
	char *param_resp[1];
	MYSQL db;
	base_config(&db);
	if(login_user(&db, param[1], param[2], hash) < 0)
	{
		resp_config("login_failure", param_resp, 0, resp);
		return;
	}
	param_resp[0] = hash;
	resp_config("login_ok\n\0", param_resp, 1, resp);	
}

void result(char **param, char *resp)  //(char *hash_project, char *res, char *resp) // Recebe os resultados
{
	perror("RESULTADO_TESTE");
}

void req_data(char **param, char *resp) //(char *hash_id, char *resp) // Responde a requisição dos dados
{
	perror("REQUISIÇão TESTE");
	//Verifica o hash no banco
	//cria hash para id e project
	//requisita os dados
	//adiciona os dados a resp
}

void req_prog(char **param, char *resp) //(char *hash_id, char *resp) // Responde a requisição do software
{
	//verifica o hash
	//verifica o caminho
	//abre o arquivo
	//envia o arquivo
}

void main() // realiza a troca de dados entre servidor e cliente
{
	int server,  param_len, client;
	char head[HEAD_LEN], resp[HEAD_LEN], *param[MAX_PARAM], *data;
	proto *type;

	server = new_server();
	param_len = 0;
	type = NULL;

	client = new_client(server);	
	if(rec_msg(client, head, HEAD_LEN) != 0) //Recebe o head padrão de tamanho 512
	{
		perror("no data");
		return;
	}
	data = head;
	do // Trata a string recebida
	{
		if( (param[param_len] = strsep(&data,"\n")) == NULL)
		       break;
		param_len++;

	}while(param_len < MAX_PARAM);

	if(strcmp(param[0], "login") == 0)
	{
		if(param_len == LOG_PARAM)
			type = login;
	}

	else if(strcmp(param[0], "rec_data") == 0)
	{
		if(param_len == DATA_PARAM)
			type = req_data;
	}	
	else if(strcmp(param[0], "req_prog") == 0)
	{
		if(param_len == PROG_PARAM)
			type = req_prog;
	}
	else if(strcmp(param[0], "result") == 0)
	{
		if(param_len == RESULT_PARAM)
			type = result;
	}

	if(type == NULL)
	{
		perror("Error");
		return;
	}

	type(param, resp);
	zero(resp);
	send_msg(client, resp, HEAD_LEN);
}

