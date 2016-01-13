# BoardHero
##Overview
BoardHero is an embedded system project of a game similar to the popular video game, Guitar Hero, implemented in C. 

It utilizes:
* breadboard
* buttons
* wires
* resistors
* potentiometer
* LCD display screen
* dual color 8x8 LED matrix
* shift register
* ATmega1284 microcontroller

The program files were written in Atmel Studios 6.1. 

##User Guide
* Controls: There are 6 buttons, 2 along a top row and 4 along the bottom row. 
 * The top two buttons are the navigation buttons. 
   * The right one acts as a start button for both the game and to start a song. It resets a game during gameplay if the player wishes to no longer continue the song. After completing the song, the start button is used to start the game again.
    * The left one acts as a scrolling button to navigate between songs to play in the selection screen. Each press will bring up the next song in sequential order.
 * The bottom four buttons are used during gameplay. 
   * Each button corresponds to a note, or a column, of the LED matrix (each column consists of two LED lights). The leftmost button corresponds to the left most note, the next button corresponds to the next note to the right, and so forth.

* Rules: 
 * Notes, consisting of pairs of LED lights in a 1x2 dimension, will travel down the LED matrix. Different notes are represented by the column they are from. 
 * The player must press a button that corresponds to the note on screen when the note is on the second to bottom row. If the player presses any button before the note reaches or after it passes the second to bottom row, it will count as a miss. 
 * If the player reaches 5 misses, regardless of whether or not the song is completed, the player will lose the game. 
 * If the player can reach the end of the song before reaching 5 misses, they have completed the song, and their score will be displayed.

##Source Files
* io.h:
 * contains all functions that are used for the LCD display
* io.c:
 * implements the files described in io.h to be used for the LCD display
* timer.h:
 * in charge of the synchSMS's timers
* bit.h:
 * in charge of bit access and operation required for io.c 
 
##Schematic
![alt text](http://imgur.com/YaASjHF.png "Schematic")
