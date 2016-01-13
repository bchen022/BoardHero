# BoardHero
##Overview
BoardHero is an embedded system project of a game similar to the popular video game, Guitar Hero, implemented in C. It utilizes a breadboard that holds an LCD screen, LED matrix, a shift register, and an ATmega1284 microcontroller. The program files were written in Atmel Studios. 
##User Guide
* Controls: There are 6 buttons, 2 along a top row and 4 along the bottom row. 
 * The top two buttons are the navigation buttons. 
   * The right one acts as a start button for both the game and to start a song. It resets a game during gameplay if the player wishes to no longer continue the song. After completing the song, the start button is used to start the game again.
    * The left one acts as a scrolling button to navigate between songs to play in the selection screen. Each press will bring up the next song in sequential order.
 * The bottom four buttons are used during gameplay. 
   * Each button corresponds to a note, or a column, of the LED matrix (each column consists of two led lights). The leftmost button corresponds to the left most note, the next button corresponds to the next note to the right, and so forth.

* Rules: 
