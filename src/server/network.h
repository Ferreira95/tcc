//Arquivo cabeçalho do network.c
//Autor: Adriano Ferreira
//Ultima modificação: 17/02/2018


// Função temporária para tratamento de erros
// A ser substituída em breva

void error(char *msg);

//Função responsável pela criação do socket ouvinte
//Busca as informações no arquivo de configuração

int new_server();

// Função de leitura de dados do soquete cliente
// Recebe o soquete do cliente,
// Ponteiro para a string de recepção,
// Tamanho do buffer

int rec_msg(int sock, char *msg, int len);

// Função de escrita de dados do soquete cliente
// Recebe o soquete do cliente,
// Ponteiro para string de envio,
// Tamanho do buffer

int send_msg(int sock, char *msg, int len);

// Função que aceita a conexão de um cliente 
// retorna o soquete identificador
// recebe o soquete ouvinte

int new_client(int sockfd);



