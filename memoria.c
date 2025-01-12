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
            segredo[i] = 'C';
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
            azul();
            sleep_ms(500);
            apagar();
            sleep_ms(500);
        }
        else if (segredo[i] == 'B')
        {
            amarelo();
            sleep_ms(500);
            apagar();
            sleep_ms(500);
        }
        else if (segredo[i] == 'C')
        {
            rosa();
            sleep_ms(500);
            apagar();
            sleep_ms(500);
        }
    }
    gpio_put(BUZZER_A, 1);
    gpio_put(BUZZER_B, 1);
    branco();   
    sleep_ms(1000);
    gpio_put(BUZZER_A, 0);
    gpio_put(BUZZER_B, 0);
    apagar();
}

int main()
{
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
                // gpio_put(LED_B, 1);
                azul();
                botao = 'A';
                sleep_ms(300);
                apagar();
                sleep_ms(300);
            }
            else if (gpio_get(BUTTON_B) == 0)
            {
                amarelo();
                botao = 'B';
                sleep_ms(300);
                apagar();
                sleep_ms(300);
            }
            else if (gpio_get(BUTTON_J) == 0)
            {
                rosa();
                botao = 'C';
                sleep_ms(300);
                apagar();
                sleep_ms(300);
            }
            if (botao != '\0')
            {
                if (botao == segredo[i])
                {
                    /* gpio_put(LED_G, 1);
                    sleep_ms(200);       CONFIRMAÇÃO DE BOTÃO CERTO COM LED VERDE
                    gpio_put(LED_G, 0);*/
                    i++;
                    if (i == tamanho)
                    {
                        for (int x = 0; x < 10; x++)
                        {
                            verde();
                            sleep_ms(200);
                            apagar();
                            sleep_ms(200);
                        }
                    }
                }
                else
                {
                    for (int x = 0; x < 10; x++)
                    {
                        vermelho();
                        sleep_ms(200);
                        gpio_put(LED_R, 0);
                        apagar();
                    }
                    acerto = false;
                    tamanho = 0;
                }
            }
        }
    }
}
