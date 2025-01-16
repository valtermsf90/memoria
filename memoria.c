#include <stdio.h>
#include "pico/stdlib.h"
#include <time.h>
#include "include/cores.c"

#define LED_R 13
#define LED_B 12
#define LED_G 11
#define BUZZER_B 10
#define BUZZER_A 21
#define BUTTON_A 5
#define BUTTON_B 6
#define BUTTON_J 22

int tamanho = 0;
char segredo[10];
char botao;
bool acerto;
void enigma()
{
    srand(time(NULL));
    for (int i = 0; i < tamanho; i++)
    {
        int numeroAleatorio = rand() % 100 + 1;
        if (numeroAleatorio % 3 == 2)
        {
            segredo[i] = 'J';
        }
        else if (numeroAleatorio % 3 == 1)
        {
            segredo[i] = 'B';
        }
        else
        {
            segredo[i] = 'A';
        }
    }
}
void mostrarEnigma()
{
    for (int i = 0; i < tamanho; i++)
    {
        if (segredo[i] == 'A')
        {
            azul(500);
            apagar(500);
            printf("A");
        }
        else if (segredo[i] == 'B')
        {
            amarelo(500);
            apagar(500);
            printf("B");
        }
        else if (segredo[i] == 'J')
        {
            rosa(500);
            apagar(500);
            printf("J");
        }
    }
    gpio_put(BUZZER_A, 1);
    gpio_put(BUZZER_B, 1);
    branco(1000);
    gpio_put(BUZZER_A, 0);
    gpio_put(BUZZER_B, 0);
    apagar(0);
    printf("\n");
}

int main()
{
    printf("Iniciando...\n");
    stdio_init_all();
    iniciaComponentes();

    while (true)
    {
        tamanho = tamanho + 1;
        enigma();
        acerto = true;
        int i = 0;

        luzInicial();
        mostrarEnigma();

        while (acerto && i < tamanho)
        {
            char botao = '\0';
            if (gpio_get(BUTTON_A) == 0)
            {
                azul(300);
                botao = 'A';
                apagar(300);
            }
            else if (gpio_get(BUTTON_B) == 0)
            {
                amarelo(300);
                botao = 'B';
                apagar(300);
            }
            else if (gpio_get(BUTTON_J) == 0)
            {
                rosa(300);
                botao = 'J';
                apagar(300);
            }
            if (botao != '\0')
            {
                if (botao == segredo[i])
                {
                    sleep_ms(200);
                    gpio_put(LED_G, 0);

                    i++;
                    if (i == tamanho)
                    {
                        printf("Parabéns, você acertou!\n");
                        for (int x = 0; x < 10; x++)
                        {
                            verde(200);

                            apagar(200);
                        }
                    }
                }
                else
                {
                    printf("Você errou!\n");
                    for (int x = 0; x < 10; x++)
                    {
                        vermelho(200);
                        apagar(200);
                    }
                    system("cls");
                    acerto = false;
                    tamanho = 0;
                }
            }
        }
    }
}
