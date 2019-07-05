#include<18F4620.h> //Se incluye la librería del PIC 18F4620
#include <stdio.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT // EL HS es el high speed
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay (clock = 2000000)//frecuencia de reloj en 16 millones
#use RS232(BAUD=9600, XMIT= PIN_C6, RCV = PIN_C7, BITS = 8, PARITY = N, STOP=1, STREAM = PORT1)

char caracter[10];
int puntero=-1, c2=0;
int contador1=0, contador2=0;
int dato=0;
int separador=0, contar=0;
int16 contadorpalabra=0;
int calculo=0;

#INT_RDA
void serial_isr(){
    if(kbhit()){
    caracter[dato]=getch();
    dato++;
    separador=1,
    }

}

#int_timer0
void timer0(){
    contadorpalabra=1;
    set_timer0(27885);
}

void main(void){
  setup_oscillator(OSC_2MHZ);
   setup_adc_ports(NO_ANALOGS); 
   set_tris_c(0xff);
   setup_timer_0(T0_INTERNAL|rtcc_div_8);
   set_timer0(27885); //Esto se obtuvo con los cálculos.
   enable_interrupts(INT_TIMER0);
   enable_interrupts(int_rda);
   enable_interrupts(GLOBAL);
   
   while(1){
   
      if(kbhit()){ caracter[dato]=getch(); 
        if(caracter[dato]==32){ 
         if(contador1==1){
                separador=dato;
            
            do{
            
               if(kbhit()){
                   caracter[dato]=getch(); 
                   if(caracter[dato]==13){ 
                       printf("%c",caracter[dato]); 
                      if(caracter[dato]==13){ 
                         contador2=1;
                      } 
                           dato++; 
                   } 
              }
            }
              while(contador2!=1);
            if(contador2==1){
                switch(caracter[separador]){
                    case '1': 
                       do{
                        if(contadorpalabra==1){
                          puntero++;
                          printf("%c", caracter[puntero]);
                          contadorpalabra=0;
                        }
                         if(caracter[puntero]==32){
                             puntero=-1;
                              c2++;
                         }
                       }while(c2!=1);
                            clean(); 
                            break; 
                       case '2' :
                       do{ if(contadorpalabra==1){ 
                          puntero++; 
                          printf("%c",caracter[puntero]); 
                         contadorpalabra=0;
                       }
                         if(caracter[puntero]==32){
                             puntero=-1; 
                             c2++;
                        }
                      }while(c2!=3);
                          clean(); 
                           break; 
                }
            }
           
         } 
         
        } 
      }
   }
   
     
   

}
