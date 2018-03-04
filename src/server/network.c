#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <confuse.h>

void error (char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int new_server() // Inicia um server no endereço e porta definidos e retorna o identificador
{
	int sockfd;
	char *port, *addr;
	struct addrinfo hints, *res, *res_top;

	port = NULL;
	addr = NULL;

		// Carrega as configurações do arquivo

	cfg_t *cfg;
	cfg_opt_t opts[] =
	{
		CFG_SIMPLE_STR("addr", &addr),
		CFG_SIMPLE_STR("port", &port),
		CFG_END()
	};


	cfg = cfg_init(opts, 0);
	cfg_parse(cfg, "server.conf");

		// Configuração e chamada da addrinfo

	memset(&hints , 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if(getaddrinfo(addr, port, &hints, &res_top))
		error("Getaddrinfo: ");

		// Busca por endereço válido

	for(res = res_top ; res; res = res->ai_next)
	{
		if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) > 0)
		{
			setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
			setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &(int){ 1 }, sizeof(int));
			setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &(int){ 1 }, sizeof(int));

			if(!bind(sockfd, res->ai_addr, res->ai_addrlen))
				if(!listen(sockfd, 20))
					break;
			
		}
		close(sockfd);
	}

	if(!res)
		error("Server Start: ");

	freeaddrinfo(res_top);
	cfg_free(cfg);

	return sockfd;	
}

int rec_msg(int sock, char *msg, int len) // Recebimento de info
{
        int rec_len;

	do
        {
	        if( (rec_len = recv(sock, msg, len, 0)) < 0)
		{
			switch(errno)
			{
				case EINTR: 
					continue;    
			}
                        return -1;
                }

		msg+=rec_len;
		len-=rec_len;

	}while(len > 0);
	
	return len;
}

int send_msg(int sock, char *msg) // Envio de info
{
	int len, send_len;

	len = strlen(msg);

	do
        {
                if( (send_len = write(sock, msg, len)) < 0 )
                {
			if(errno == EINTR)
				continue;
			return -1;
		}
	
	 	msg+=send_len;
	        len-=send_len;  

	}while(len > 0);

        return len;
}

int new_client(int sockfd) // retorna o próximo cliente da fila
{
	int clientfd, client_len;
	struct sockaddr_storage client;
		
	client_len = sizeof(struct sockaddr_in);
	if((clientfd = accept(sockfd, (struct sockaddr *)&client, &client_len)) < 0)
	{
		if(errno == ECONNABORTED || errno == EINTR)
			return -1;
		error("Accept: ");
	}	

	return clientfd;
}
