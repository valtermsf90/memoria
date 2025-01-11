#include <stdio.h>
#include "pico/stdlib.h"

#define LED_R 13
#define LED_B 12
#define LED_G 11
#define BUZZER_B 10
#define BUZZER_A 21
#define BUTTON_A 5
#define BUTTON_B 6

char segredo[10];
char botao;
bool acerto;

void iniciaComponentes(){
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    //inciando buzzers
    gpio_init(BUZZER_A);
    gpio_set_dir(BUZZER_A, GPIO_OUT);
    gpio_init(BUZZER_B);
    gpio_set_dir(BUZZER_B, GPIO_OUT);
    //iniciando botoes
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
}
void luzInicial(){
    
    //VERMELHO
    gpio_put(BUZZER_A, 1);
    gpio_put(BUZZER_B, 0);
    gpio_put(LED_R, 1); 
    gpio_put(LED_B, 0);  
    gpio_put(LED_G, 0); 
    sleep_ms(200);

    //CIANO
    gpio_put(BUZZER_A, 0);
    gpio_put(BUZZER_B, 1);
    gpio_put(LED_R, 0);  
    gpio_put(LED_B, 1); 
    gpio_put(LED_G, 1); 
    sleep_ms(200);

    //AMARELO
    gpio_put(BUZZER_A, 1);
    gpio_put(BUZZER_B, 0);
    gpio_put(LED_R, 1);
    gpio_put(LED_B, 0);
    gpio_put(LED_G, 1); 
    sleep_ms(200);

    //ROSA
    gpio_put(BUZZER_A, 0);
    gpio_put(BUZZER_B, 1);
    gpio_put(LED_R, 1); 
    gpio_put(LED_B, 1);  
    gpio_put(LED_G, 0);
    sleep_ms(200);

    //AZUL
    gpio_put(BUZZER_A, 1);
    gpio_put(BUZZER_B, 0);
    gpio_put(LED_R, 0); 
    gpio_put(LED_B, 1); 
    gpio_put(LED_G, 0); 
    sleep_ms(200);

    //VERDE
    gpio_put(BUZZER_A, 0);
    gpio_put(BUZZER_B, 1);
    gpio_put(LED_R, 0);  
    gpio_put(LED_B, 0); 
    gpio_put(LED_G, 1); 
    sleep_ms(200);

    //BRANCO
    gpio_put(BUZZER_A, 1);
    gpio_put(BUZZER_B, 0);
    gpio_put(LED_R, 1);  
    gpio_put(LED_B, 1); 
    gpio_put(LED_G, 1); 
    sleep_ms(200);

    //TODOS APAGADOS
    gpio_put(BUZZER_A, 0);
    gpio_put(BUZZER_B, 0);
    gpio_put(LED_R, 0); 
    gpio_put(LED_B, 0); 
    gpio_put(LED_G, 0); 
}
void enigma(){
    for(int i = 0;i < 10; i++){
        if(i % 3){
            segredo[i] = 'B';
        }else{
            segredo[i] = 'A';
        }
        }
}

int main() {
stdio_init_all();
iniciaComponentes();
enigma();
while (true) { 
    acerto = true; 
    int i = 0;     
    luzInicial();

    while (acerto && i < 10) {
        char botao = '\0';
        if(gpio_get(BUTTON_A) == 0){
            gpio_put(LED_B, 1);
            botao = 'A';
            sleep_ms(100);
            gpio_put(LED_B, 0);
        }else if(gpio_get(BUTTON_B) == 0){
            gpio_put(LED_B, 1);
            botao = 'B';
            sleep_ms(100);
            gpio_put(LED_B, 0);
        }
        if (botao != '\0') {
            if(botao == segredo[i]){
                gpio_put(LED_G, 1);
                sleep_ms(200);
                gpio_put(LED_G, 0);
                i++;
                if(i == 10){
                    for(int x = 0; x < 10; x++){
                    gpio_put(LED_G, 1);
                    sleep_ms(200);
                    gpio_put(LED_G, 0);
                    sleep_ms(200);
                    }
                }
            }else{ 
                for(int x = 0; x < 10; x++){
                    gpio_put(LED_R, 1);
                    sleep_ms(200);
                    gpio_put(LED_R, 0);
                    sleep_ms(200);
                }
                acerto = false;
            }
        }
    }
}       
}
