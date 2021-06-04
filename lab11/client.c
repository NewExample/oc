#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

void take_ip(char* args, char* ip, size_t pointer)
{
    memset(ip, 0, pointer + 1);
    for (size_t i = 0; i < pointer; ++i)
    {
        ip[i] = args[i];
    }
}

void random_digits(int* digits, int size, int mind, int maxd)
{
    srand(time(NULL));
    for (size_t i = 0; i < size; ++i)
    {
        digits[i] = mind + rand() % (maxd - mind + 1);
    }
}

int main(int argc, char* argv[])
{
    char* args = argv[1];//аргумент командной строки
    char* port = strchr(args, ':');
    size_t pointer = port - args;
    char ip[pointer + 1];
    take_ip(args, ip, pointer);
    printf("%s:%s\n", ip, port + 1); // разделение на порт и ip

    int size, mind, maxd;
    int digits[size];
    printf("Укажите размер и диапазон (например, 10 1 10): ");
    scanf("%d %d %d", &size, &mind, &maxd);// указываем размер массива принимающего минимальный и максимальный порог
    random_digits(digits, size, mind, maxd);//заполняем массив рандомными числами
    printf("Вами сгенерированы следующие числа: ");
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", digits[i]); //пишется массив
    }
    printf("\n");
    struct sockaddr_in server_addr, client_addr;

    int sock = socket(PF_INET, SOCK_DGRAM, 0); //сокет создаётся на сервере и на клиента
    if (sock < 0)
    {
        perror("Socket error");
        return -1;
    }

    memset(&client_addr, 0, sizeof(client_addr));
    memset(&server_addr, 0, sizeof(server_addr));// сбрасываем структуры в 0

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(0);
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        perror("Bind error");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port + 1));
    inet_aton(ip, &server_addr.sin_addr); // переводит ip из текстового вида в нормальный

    time_t startTime = time(NULL);
    int n = sendto(sock, digits, size * sizeof(int), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));// отправляем по нашему сокету массив с размером
    recvfrom(sock, digits, size * sizeof(int), 0, (struct sockaddr *)NULL, NULL);// отправляем по нашему сокету массив с размером
    time_t endTime = time(NULL);
    printf("Обработанный массив чисел:\n");
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", digits[i]); //выводим отсортированный масив
    }
    printf("\n");
    printf("На обработку затрачено %ld времени\n", endTime - startTime);//выводим сколько времени нам потребовалось
    close(sock);
    return 0;
}
