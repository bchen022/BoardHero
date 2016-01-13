/*
 * Brendan_Cheng_Guitar_Hero.c
 *
 * Created: 5/26/2015 2:56:21 PM
 *  Author: Brendan
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "C:\Users\Brendan\Desktop\cs120b_final_proj\io.h"
#include "C:\Users\Brendan\Desktop\cs120b_final_proj\io.c"
#include "C:\Users\Brendan\Desktop\cs120b_final_proj\timer.h"
//pwm



unsigned char character_arr[] = {
	0B00100,
	0B00110,
	0B00101,
	0B00100,
	0B00100,
	0B11100,
	0B11100,
	0B11100
};

unsigned char character_arr2[] = {
        0B00000,
        0B00000,
        0B00000,
        0B01111,
        0B01001,
        0B01001,
        0B11011,
        0B11011
};

unsigned char character_arr3[] = {
        0B00000,
        0B01010,
        0B01010,
        0B01010,
        0B00000,
        0B10001,
        0B10001,
        0B01110
};

unsigned char character_arr4[] = {
	        0B00000,
	        0B01010,
	        0B01010,
	        0B01010,
	        0B00000,
	        0B01110,
	        0B10001,
	        0B10001	
};

unsigned char * song_sel = "1. Easy 2. Hard 3. Expert";
unsigned char * start_screen = "READY FOR BOARD HERO?!? " ;
unsigned char song = 0;
unsigned char game_finished = 0;
unsigned char total_score = 0;
unsigned char * total_score_message = "Total Score: ";
unsigned char * congrats_message = "Winner! ";
unsigned char * game_over_message = "Game Over... " ;
unsigned char * first_song = "1. Easy ";
unsigned char * second_song = "2. Hard ";
unsigned char * third_song = "3. Expert ";
unsigned char start_button = 0x00;
unsigned char scroll_button = 0x00;
unsigned char song_on = 0;
unsigned char last_note_missed = 0;

unsigned char button1 = 0x00;
unsigned char button2 = 0x00;
unsigned char button3 = 0x00;
unsigned char button4 = 0x00;
unsigned char arr[] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE, 0xFF};
unsigned char arr_notes_A[] = {0x30, 0x03, 0xC0, 0x0C, 0x03, 0x30, 0xC0, 0x0C, 0x30, 0x0C};
unsigned char arr_notes_B[] = {0x0C, 0x03, 0x0C, 0x30, 0xC0, 0x30, 0xC0, 0xC0, 0x0C, 0x30};
unsigned char arr_notes_C[] = {0x33, 0x3C, 0xC3, 0x0C, 0xC0, 0x3C, 0xC3, 0x30, 0x33, 0xCC};
unsigned char count = 0;
unsigned char count_notes = 0;
unsigned char num_misses = 0;
unsigned char * score_message = "Score: ";
unsigned char * misses_message = "Missed: ";
unsigned char notes_speaker_count = 0;
//double notes_speaker_A[] = {261.63, 293.66, 261.63, 329.63, 329.63, 349.23, 329.63, 392.00, 293.66, 261.63 };


void transmit_data(unsigned char data) {
	int i;
	for (i = 0; i < 8 ; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		//PORTC = 0x08;
		PORTB = 0x08;
		
		// set SER = next bit of data to be sent.
		//PORTC |= ((data >> i) & 0x01);
		PORTB |= (((data >> i) & 0x01))/*<<4*/;
		
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		//PORTC |= 0x02;
		PORTB |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	//PORTC |= 0x04;
	PORTB |= 0x04;
	
	// clears all lines in preparation of a new transmission
	//PORTC = 0x00;
	PORTB = 0x00; // or 0xFF?
}


enum menu_states {init, song_selection, wait1, wait2, wait3, wait4, wait5, wait6, wait7, wait8, wait9, song_A, song_B, song_C, play_A, play_B, play_C, game_ended, scoreboard, waitreset, reset} menu_state;	
void menu_tick() {
	start_button = ~PINA & 0x04; //connect button to PA3
	scroll_button = ~PINA & 0x08;

	switch (menu_state) {		
		case init:
		if (!start_button) {
			menu_state = init;
		}
		else if (start_button) {
			menu_state = wait1;
		}
		break;
		
		case wait1:
		if (start_button) {
			menu_state = wait1;
		}
		else if (!start_button) {
			menu_state = song_selection;
		}
		break;
		
		case song_selection:
		if (scroll_button) {
			menu_state = wait2;
		}
		else {
			menu_state = song_selection;
		}
		break;
		
		case wait2:
		if (scroll_button) {
			menu_state = wait2;
		}
		else if (!scroll_button) {
			menu_state = song_A;
		}
		break;
		
		case song_A:
		if (start_button) {
			menu_state = wait3;
		}
		else if (scroll_button) {
			menu_state = wait4;			
		}
		else {
			menu_state = song_A;
		}
		break;
		
		case wait3:
		if (start_button) {
			menu_state = wait3;
		}
		else if (!start_button) {
			menu_state = play_A;
		}
		break;
		
		case wait4:
		if (scroll_button) {
			menu_state = wait4;
		}
		else if (!scroll_button) {
			menu_state = song_B;
		}
		break;
		
		case song_B:
		if (start_button) {
			menu_state = wait5;
		}
		else if (scroll_button) {
			menu_state = wait6;		
		}
		else {
			menu_state = song_B;
		}
		break;
		
		case wait5:
		if (start_button) {
			menu_state = wait5;
		}
		else if (!start_button) {
			menu_state = play_B;
		}
		break;
		
		case wait6:
		if (scroll_button) {
			menu_state = wait6;
		}
		else if (!scroll_button) {
			menu_state = song_C;
		}
		break;
		
		case song_C:
		if (start_button) {
			menu_state = wait7;
		}
		else if (scroll_button) {
			menu_state = wait8;	
		}
		else {
			menu_state = song_C;
		}
		break;
		
		case wait7:
		if (start_button) {
			menu_state = wait7;
		}
		else if (!start_button) {
			menu_state = play_C;
		}
		break;
		
		case wait8:
		if (scroll_button) {
			menu_state = wait8;
		}
		else if (!scroll_button) {
			menu_state = song_A;
		}
		break;
		
		case play_A:
		if (num_misses < 5) {
			if (game_finished == 1) {
				menu_state = game_ended;
			}
			else if (start_button) {
				menu_state = waitreset;
			}
			else {
				TimerSet(200);
				menu_state = play_A;
			}
		}
		else if (num_misses >= 5) {
			//song_on = 0;
			menu_state = game_ended;
		}
		break;
		
		case play_B:
		if (num_misses < 5) {
			if (game_finished == 1) {
				menu_state = game_ended;
			}
			else if (start_button) {
				menu_state = waitreset;
			}
			else {
				TimerSet(100);
				menu_state = play_B;
			}
		}
		else if (num_misses >= 5) {
			//song_on = 0;
			menu_state = game_ended;
		}
		break;
			
		case play_C:
		if (num_misses < 5) {
			if (game_finished == 1) {
				menu_state = game_ended;
			}
			else if (start_button) {
				menu_state = waitreset;
			}
			else {
				TimerSet(100);
				menu_state = play_C;
			}
		}
		else if (num_misses >= 5) {
			//song_on = 0;
			menu_state = game_ended;
		}
		break;
		
		case game_ended:
		if (start_button) {
			menu_state = wait9;
		}
		else {
			menu_state = scoreboard;
		}
		break;
		
		case scoreboard:
		if (start_button) {
			menu_state = wait9;
		}
		else {
			menu_state = game_ended;
		}
		break;
		
		case wait9:
		if (start_button) {
			menu_state = wait9;
		}
		else if (!start_button) {
			menu_state = init;
		}
		break;
		
		case waitreset:
		if (start_button) {
			menu_state = waitreset;
		}
		else if (!start_button) {
			menu_state = init;
		}

		
		default:
		menu_state = init;
		break;		
		
	}
	
	switch (menu_state) {		
		case init:
		count_notes = 0;
		song_on = 0;
		count = 0;
		game_finished = 0;
		num_misses = 0;
		last_note_missed = 0;
		//set_PWM(0);
//		PORTB = 0x00;
		transmit_data(0x00);
		PORTC = 0x00;
		TimerOn();
		TimerSet(50);
		total_score = 0;
		LCD_init();
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_DisplayString(1, start_screen);
		LCD_WriteData(0);
		LCD_WriteData(1);
		LCD_WriteData(0);
		break;
		
		case song_selection:
		LCD_init();
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_DisplayString(1, song_sel);
		break;
		
		case song_A:
		LCD_init();
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_DisplayString(1, first_song);
		LCD_WriteData(0);
		break;
		
		case song_B:
		LCD_init();
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_DisplayString(1, second_song);
		LCD_WriteData(0);
		LCD_WriteData(0);		
		break;
		
		case song_C:
		LCD_init();
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_DisplayString(1, third_song);
		LCD_WriteData(0);
		LCD_WriteData(0);	
		LCD_WriteData(0);	
		break;
		
		case play_A:
		song_on = 1;
		song = 1;
		break;
		
		case play_B:
		song_on = 1;
		song = 2;
		break;
		
		case play_C:
		song_on = 1;
		song = 3;
		break;
		
		case game_ended:
		LCD_init();
		LCD_ClearScreen();
		LCD_Cursor(1);
		if (game_finished == 1) {
			LCD_DisplayString(1, congrats_message);
			LCD_WriteData(2);
		}
		else {
			LCD_DisplayString(1, game_over_message);
			LCD_WriteData(3);
		}
		break;
		
		case scoreboard:
		LCD_init();
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_DisplayString(1, total_score_message);
		if (total_score == 10) {
			LCD_WriteData(1 + '0');
			LCD_WriteData(0 + '0');
		}
		else {
			LCD_WriteData(total_score + '0');
		}		
		break;

		
		
		default:
		break;	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

enum song_states {init_one, traverse, miss, hit, light_end } song_state;
void song_tick() {
	button1 = ~PINA & 0x10; //0001 0000
	button2 = ~PINA & 0x20;
	button3 = ~PINA & 0x40;
	button4 = ~PINA & 0X80;
	
	switch(song_state) { //transitions
		case init_one:
		if (song == 0){
			song_state = init_one;
		}
		else if (song == 1 || song == 2 || song == 3) {
			song_state = traverse;
		}
		break;
		
		case traverse:
		if (song_on == 1) {
			count++;
			if ((count != 6) && (button1 || button2 || button3 || button4)) {
				song_state = miss;
			}
			else if (count == 6) {
				if (song == 1) {
					if (count_notes == 0 || count_notes == 5 || count_notes == 8) {
						if (button3) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 1 || count_notes == 4) {
						if (button1) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 2 || count_notes == 6) {
						if (button4) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}				
					}
					else if (count_notes == 3 || count_notes == 7 || count_notes == 9) {
						if (button2) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}				
					}	
				}
				else if (song == 2) {
					if (count_notes == 3 || count_notes == 5 || count_notes == 9) {
						if (button3) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 1) {
						if (button1) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 4 || count_notes == 6 || count_notes == 7) {
						if (button4) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 0 || count_notes == 2 || count_notes == 8) {
						if (button2) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}				
				}
				if (song == 3) {
					if (count_notes == 0) {
						if (button1 && button3) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 1 || count_notes == 5) {
						if (button3 && button2) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 2 || count_notes == 6) {
						if (button4 && button1) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 3) {
						if (button2) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 4) {
						if (button4) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 7) {
						if (button3) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 8) {
						if (button3 && button1) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}
					else if (count_notes == 9) {
						if (button4 && button2) {
							song_state = hit;
						}
						else {
							song_state = miss;
						}
					}					
				}
			}
			else {
				song_state = traverse;	
			}
		}
		break;			
		
		case miss:
		num_misses++;
		if (num_misses >= 5){
			TimerSet(1000);
			song_on = 0;
			LCD_init();
			LCD_ClearScreen();
			LCD_Cursor(1);
			LCD_DisplayString(1, score_message);
			LCD_WriteData(total_score + '0');
			LCD_DisplayString_noclr(17, misses_message);
			LCD_WriteData(num_misses + '0');
		}
		count++;
		song_state = light_end;
		break;
		
		case hit:
		total_score++;
		count = 8;
		song_state = light_end;
		break;
		
		case light_end:
		song_state = init_one;
		break;

		default:
		init_one;
		break;
		
	}

	switch (song_state) { //actions
		case init_one:
		count = 0;
		PORTC = 0x00;
		transmit_data(0x00);
		break;		
	
		case traverse:
		if (game_finished != 1 && song_on == 1) {
		    if (count_notes == 10) {
				TimerSet(500);
			}
			LCD_init();
			LCD_ClearScreen();
			LCD_Cursor(1);
			LCD_DisplayString(1, score_message);
			if (total_score == 10) {
				LCD_WriteData(1 + '0');
				LCD_WriteData(0 + '0');
			}
			else {
				LCD_WriteData(total_score + '0');
			}
	
			LCD_DisplayString_noclr(17, misses_message);
			LCD_WriteData(num_misses + '0');
			//
		}
		if (count_notes < 10 && song_on == 1) {
			transmit_data(arr[count]);
			if (song == 1) {
				PORTC = arr_notes_A[count_notes];
//				set_PWM(notes_speaker_A[notes_speaker_count]);
			}
			else if (song == 2) {
				PORTC = arr_notes_B[count_notes];
			}
			else if (song == 3) {
				PORTC = arr_notes_C[count_notes];
			}
			
		}
		else if (count_notes >= 10 && num_misses < 5) {
			TimerSet(1000);
			game_finished = 1;
			num_misses = 0;
			transmit_data(0x00);
			PORTC = 0x00;						
		}		
		break;
			
		case miss:
		if (song == 1) {
			PORTC = arr_notes_A[count_notes];
		}
		else if (song == 2) {
			PORTC = arr_notes_B[count_notes];
		}
		else if (song == 3) {
			PORTC = arr_notes_C[count_notes];
		}
		transmit_data(arr[count]);
		break;
		
		case hit:
		if (song == 1) {
			PORTC = arr_notes_A[count_notes];
		}
		else if (song == 2) {
			PORTC = arr_notes_B[count_notes];
		}
		else if (song == 3) {
			PORTC = arr_notes_C[count_notes];
		}
		transmit_data(arr[count]);
		break;

		case light_end:
		if (song == 1) {
			PORTC = arr_notes_A[count_notes];
		}
		else if (song == 2) {
			PORTC = arr_notes_B[count_notes];
		}
		else if (song == 3) {
			PORTC = arr_notes_C[count_notes];
		}
		transmit_data(arr[count]);
		count = 0;
		count_notes++;

		notes_speaker_count++;
		break;		
		
		default:
		break;		
		
	}
	
	
}

int main(void)
{
	//DDRA = 0xFF; PORTA = 0x00;
	DDRA = 0x03; PORTA = 0xFC;
	DDRD = 0xFF; PORTD = 0x00;
	
	//port B controls ground
	DDRB = 0xFF; 
//	PORTB = 0x00;
	transmit_data(0x00);
	
	//port C controls power
	DDRC = 0xFF; PORTC = 0x00;
	
	TimerSet(50);
	TimerOn();
	//PWM_on();

	LCD_WriteCommand(0x40);//locations 0x40,0x48,0x50,0x58,0x60,68,70,78
	for(unsigned char i=0; i<8; i++){
		LCD_WriteData(character_arr[i]);
	}
	LCD_WriteCommand(0x80);
	
	LCD_WriteCommand(0x48);
	for(unsigned char i=0; i<8; i++){
		LCD_WriteData(character_arr2[i]);
	}
	LCD_WriteCommand(0x80);	
	
	LCD_WriteCommand(0x50);
	for(unsigned char i=0; i<8; i++){
		LCD_WriteData(character_arr3[i]);
	}
	LCD_WriteCommand(0x80);	
	
	LCD_WriteCommand(0x58);
	for(unsigned char i=0; i<8; i++){
		LCD_WriteData(character_arr4[i]);
	}
	LCD_WriteCommand(0x80);
	

	
    while(1)
    {
		menu_tick();
		song_tick();
		while(!TimerFlag);
		TimerFlag = 0;

    }
}

