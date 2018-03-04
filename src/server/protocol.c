#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HEAD_LEN 512
#define MAX_PARAM 5

typedef int proto(char **params);

int login_user(char **param)  //(char *name, char *password, char *resp) // Login do usuário
{
	perror("LOGIN_TESTE");
	// checagem no banco
	// se verdadeiro adiciona hash, id a tabela
}

int result(char **param)  //(char *hash_project, char *res, char *resp) // Recebe os resultados
{
	perror("RESULTADO_TESTE");
}

int req_data(char **param) //(char *hash_id, char *resp) // Responde a requisição dos dados para processo
{
	perror("REQUISIÇão TESTE");
	//Verifica o hash no banco
	//cria hash para id e project
	//requisita os dados
	//adiciona os dados a resp
}

int req_prog(char **param) //(char *hash_id, char *resp) // Responde a requisição do software para trabalho
{
	//verifica o hash
	//verifica o caminho
	//abre o arquivo
	//envia o arquivo
}

void transmission(int server) // realiza a troca de dados entre servidor e cliente
{
	proto *type;
	char head[HEAD_LEN], resp[HEAD_LEN], *param[MAX_PARAM], *data;
	int i, j, client;

	i = 0;
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
		if( (param[i] = strsep(&data,"\n")) == NULL)
		       break;
		i++;

	}while(i < MAX_PARAM);
		
	if( i == 0) // Verificação de tipo e quantidade de parâmentros
		return;

	if(strcmp(param[0], "login") == 0)
	{
		if(i == 4)
			type = login_user;
	}

	else if(strcmp(param[0], "rec_data") == 0)
	{
		if(i == 3)
			type = req_data;
	}	
	else if(strcmp(param[0], "req_prog") == 0)
	{
		if(i == 3)
			type = req_prog;
	}
	else if(strcmp(param[0], "result") == 0)
	{
		if(i == 5)
			type = result;
	}

	if(type == NULL)
	{
		perror("Error");
		return;
	}
	
	if(type(param) > 0)
	{
		send_msg(client, resp, sizeof(resp));
		return;
	}
	
}

int main()
{
	int server;
	server = new_server();
	transmission(server);
}
