#include <stdio.h>
#include "pico/stdlib.h"
#include "cores.h"

#define LED_R 13
#define LED_B 12
#define LED_G 11
#define BUZZER_B 10
#define BUZZER_A 21
#define BUTTON_A 5
#define BUTTON_B 6
#define BUTTON_J 22

void luzInicial(){
vermelho();
sleep_ms(200);
ciano();
sleep_ms(200);
amarelo();  
sleep_ms(200);
rosa();
sleep_ms(200);
azul();
sleep_ms(200);
verde();
sleep_ms(200);
branco();
sleep_ms(1000);
apagar(); 
sleep_ms(2000);
}

void apagar(){
gpio_put(LED_R, 0); 
gpio_put(LED_B, 0); 
gpio_put(LED_G, 0);
}
void ciano(){
gpio_put(LED_R, 0);  
gpio_put(LED_B, 1); 
gpio_put(LED_G, 1);
}
void branco(){
gpio_put(LED_R, 1);  
gpio_put(LED_B, 1); 
gpio_put(LED_G, 1);
}
void rosa(){
gpio_put(LED_R, 1); 
gpio_put(LED_B, 1);  
gpio_put(LED_G, 0);
}
void amarelo(){
gpio_put(LED_R, 1); 
gpio_put(LED_B, 0);  
gpio_put(LED_G, 1);
}
void vermelho(){
gpio_put(LED_R, 1); 
gpio_put(LED_B, 0);  
gpio_put(LED_G, 0);
}
void azul(){
gpio_put(LED_R, 0); 
gpio_put(LED_B, 1); 
gpio_put(LED_G, 0); 
}
void verde(){
gpio_put(LED_R, 0); 
gpio_put(LED_B, 0); 
gpio_put(LED_G, 1); 
}