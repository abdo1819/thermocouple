/*
 * avr_train01.c
 *
 * Created: 8/23/2017 5:12:30 PM
 * Author : abdo
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int seven_sgment(int x){
	int y =0;
	switch (x){
		case 0:
		y = ~0b11111100;
		break;
		case 1:
		y = ~0b01100000;
		break;
		case 2:
		y = ~0b11011010;
		break;
		case 3:
		y = ~0b11110010;
		break;
		case 4:
		y = ~0b01100110;
		break;
		case 5:
		y = ~0b10110110;
		break;
		case 6:
		y = ~0b10111110;
		break;
		case 7:
		y = ~0b11100000;
		break;
		case 8:
		y = ~0b11111110;
		break;
		case 9:
		y = ~0b11110110;
		break;
	}
	return y;
}



int spi_sck = 7;
int spi_ss = 4;
int spi_mosi = 5;

int b = 0;
int16_t v;
double temp;
//double FIRST;

void serial_avr(char *str){
	UCSRB = (1<<TXEN);
	UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
	UBRRL = 51;
	for (unsigned int i =0 ; str[i]!=0;i++){
		UDR = str[i];
		while (!(UCSRA&(1<<UDRE)));
		
		
	}
	_delay_ms(500);
}
int spi_get (void){
	b=0;
	for (int i=0 ;i<8;i++){
		PORTB &= ~(1<<spi_sck);
		_delay_ms(1);
		if(PINB & (1<<spi_mosi)){
		b |= (1<<i)	;
		}
	
		PORTB |= (1<<spi_sck);
	}
	return b;
}

double read_cel(void){
	PORTB &= ~(1<<spi_ss);
    
	v=0;
	v= spi_get();
	v <<= 8 ;
	v |= spi_get();
	
    PORTB |= (1<<spi_ss);	

	v >>= 3;
	
	return v*0.25;
}

int main(void)
{
	DDRB = 0;
	DDRB |= (1<<spi_sck)|(1<<spi_ss);
    DDRA = 0xFF;
	DDRC = 0xFF;
   
    serial_avr("temp");  
    while (1) 
    {
		_delay_ms(500);
		
	  temp = read_cel();
	  
	  for(int i =1 ; i<100; i++){
		PORTA = seven_sgment((i-(i%10))/10);
		PORTC = seven_sgment(i%10);
		_delay_ms(500);
		  
	  
	  }  
	  
    }
}

