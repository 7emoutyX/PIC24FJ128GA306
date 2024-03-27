/*
 * File:   main.c
 * Author: hemouty
 *
 * Created on March 7, 2024, 2:40 PM
 */


// CONFIG2
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC Oscillator (FRC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG port is enabled)

#include <xc.h>
#include "FreeRTOS.h"
#include "task.h"
#include "list.h"


void delay(void);
void vTask1(void *pv1); // NB : le type de l?argument et le type retourné (voir cours)
void vTask2(void *pv2);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ); 

void delay(void){
unsigned int Compt=0X0FFF ;
while(Compt--) ;
}

int main(int argc, char** argv) {
xTaskCreate(vTask1, "Task1", 150, NULL, 1, NULL );
xTaskCreate( vTask2, "Task2", 150, NULL, 1, NULL );
// Lancer le scheduler
vTaskStartScheduler ();
// On atteint ce point si le scheduler s?est arrêté à cause d?un problème ou il a été arrêté explicitement par le code
return (0);
}



void vTask1(void *pv1){ // Blinking PortA
TRISA=0; // Setup PortA as digital Outputs
while(1){ // une tâche est une boucle infinie
PORTA=0x00; delay();
PORTA = 0xFF; delay(); }
// ne retourne rien
}
// ***********************************************
void vTask2(void *pv2) { // Blinking PortD
TRISD=0;
while(1){ // une tâche est une boucle infinie
PORTD=0x00; delay();
PORTD = 0xFF; delay(); }
// ne retourne rien
}
void vApplicationIdleHook(void) {
/* si on souhaite que la tâche idle 
  execute un code on le met ici */
}
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ){
//Que faire en cas de débordement de pile ?
}