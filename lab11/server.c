#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int compare_func(const void *a, const void *b)
{
  return *((int *)b) - *((int *)a);
}

int main(int argc, char* argv[])
{
    int port = atoi(argv[1]); // 1 аргумент командной строки переводим с помощью функции atoi в число и запоминаем в переменную port
    char message[1024]; 
    struct sockaddr_in server_addr, client_addr; // структура сервера и клиента

    memset(&server_addr, 0, sizeof(server_addr));//сбрасываем структуру сервера в 0
    server_addr.sin_family = AF_INET;//организовываем подключение TCP
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);// задаём что может подключаться любой адрес
    server_addr.sin_port = htons(port);//настраиваем структуру сервера с помощью функции htons

    int sock = socket(PF_INET, SOCK_DGRAM, 0);//создаём сокет
    if (sock < 0)
    {
        perror("Socket error");
        return -1;
    }                                         // если сокет не создался выводим ошибку
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) //bind чтобы сервер получил ip по порту
    {
        server_addr.sin_port = 0;//если бинд не выполнился , то сбрасываем порт в 0
        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            perror("Bind error");
            return -1;
        }
    }

    socklen_t server_len = sizeof(server_addr);// узнаём размер структуры
    getsockname(sock, (struct sockaddr *)&server_addr, &server_len);//получает название сервера
    printf("Listening on port: %d\n", ntohs(server_addr.sin_port));// пишем порт на котором работает сервер

    while (1)
    {
        socklen_t client_len = sizeof(client_addr);
        int n = recvfrom(sock, message, 1024, 0, (struct sockaddr *)&client_addr, &client_len);// с нашего сокета получает сообщение размером 1024
        qsort(message, n / sizeof(int), sizeof(int), compare_func);//сортировка
        sendto(sock, message, n * sizeof(int), 0, (struct sockaddr *)&client_addr, client_len); // отправляем обратно по сокету сообщение
    }
}
