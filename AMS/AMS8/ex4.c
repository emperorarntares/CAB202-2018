#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <graphics.h>
#include <lcd.h>
#include <macros.h>
#include "lcd_model.h"

//	Helper functions.
void draw_test_pattern(void);
void refresh_bank(int bank);
void refresh_col(int col);
void xor_bank(int bank, uint8_t bit_pattern);
void xor_col(int col, uint8_t bit_pattern);

void setup() {
	set_clock_speed(CPU_8MHz);

	//	(a) Enable input from the Left, Right, Up, and Down switches
	//	of the joystick.
	CLEAR_BIT(DDRB, 1);
	CLEAR_BIT(DDRD, 0);
	CLEAR_BIT(DDRD, 1);
	CLEAR_BIT(DDRB, 7);
	//	(b) Initialise the LCD display using the default contrast setting.
	lcd_init(LCD_DEFAULT_CONTRAST);
	// Do not change the following instruction.
	draw_test_pattern();
}

//	(c) Declare a pair of global variables of type int called 
//	xc and yc which will store the horizontal and vertical position 
//	of the centre of the cross hair. Initially place the cross-hair at 
//	(LCD_X / 2, LCD_Y / 2). AMS uses these variables to set up tests. 
int xc = LCD_X / 2;
int yc = LCD_Y / 2;
 
void process() {
	//	(d) Using the formula in Topic 8 lecture notes, and the
	//	variables (xc, yc), calculate the bank (cursor row) in which 
	//	the horizontal stroke of the cross-hair is currently drawn. 
	uint8_t x = xc;
	uint8_t y = yc / 8;
	//	(e) Assuming that the cross-hair is about to move, we must
	//	restore the parts of the image obscured by the horizontal and 
	//	vertical strokes. Call refresh_bank, passing bank as argument, to 
	//	restore the pixels covered by the horizontal stroke. Call refresh_col
	//	with xc as argument to restore the pixels covered by the vertical stroke.
	refresh_bank(y);
	refresh_col(x);
	//	(f) Determine if the Up joystick switch is closed. 
	//	If the switch is closed and the cross-hair is not already 
	//	in the top row of pixels, move it up one pixel.
	if (BIT_IS_SET(PIND, 1) && yc > 0) {
		yc--;
	}
	//	(g) OTHERWISE, determine if the Down joystick switch 
	//	is closed. If it is, and the cross-hair is not already in the 
	//	bottom row of pixels, move it down one pixel.
	else if (BIT_IS_SET(PINB, 7) && yc < 47) {
		yc++;
	}
	//	(h) OTHERWISE, determine if the Left joystick switch 
	//	is closed. If it is, and the cross-hair is not already in the 
	//	left-most row of pixels, move it left one pixel.
	else if (BIT_IS_SET(PINB, 1) && xc > 0) {
		xc--;
	}
	//	(i) OTHERWISE, determine if the Right joystick switch 
	//	is closed. If it is, and the cross-hair is not already in the 
	//	right-most row of pixels, move it right one pixel.
	else if (BIT_IS_SET(PIND, 0) && xc < 83) {
		xc++;
	}
	//	(j) Using the formula in Topic 8 lecture notes, and the
	//	variables (xc, yc), calculate the updated bank (cursor row) in 
	//	which the horizontal stroke of the cross-hair will be drawn and 
	//	the pixel position within the bank that will be covered. Store 
	//	the bank in variable new_bank, and store the pixel position in 
	//	variable pixel_pos.
	int new_bank = yc / 8;
	int pixel_pos = yc % 8;
	//	(k) Invert the pixels in the display covered by the 
	//	horizontal stroke of the cross-hair. Create an 8-bit mask which has 
	//	zeros at every position except pixel_pos, and a 1 at pixel_pos.
	//	Call xor_bank to invert the pixels, sending new_bank and the
	//	bit mask as arguments.
	uint8_t horiz_mask = (1 << pixel_pos);
	xor_bank(new_bank, horiz_mask);
	//	(l) Invert the pixels in the display covered by the 
	//	vertical stroke of the cross-hair. Create an 8-bit mask which has 
	//	ones at every position. Call xor_col to invert the pixels in column
	//	xc. The second argument will be an 8-bit mask with a 1 in every 
	//	bit position.
	uint8_t vert_mask = 0b11111111;
	xor_col(xc, vert_mask);
}

// Draw a test pattern to the Teensy.
// NB: When the unit test executes in AMS, a different test pattern
// will be drawn.
void draw_test_pattern() {
	int x0 = LCD_X / 2;
	int y0 = LCD_Y / 2;

	LCD_CMD(lcd_set_x_addr, 0);
	LCD_CMD(lcd_set_y_addr, 0);

	for ( int bank = 0; bank < LCD_Y / 8; bank++ ) {
		for ( int x = 0; x < LCD_X; x++ ) {
			uint8_t byte_to_write = 0;

			for ( int bit_pos = 0; bit_pos < 8; bit_pos++ ) {
				int y = 8 * bank + bit_pos;
				double dx = (x - x0) / 2.0;
				double dy = (y - y0);

				if ( dx * dx + dy * dy < 20 * 20 ) SET_BIT(byte_to_write, bit_pos);
			}

			LCD_DATA(byte_to_write);

			// Stash a copy in the screen buffer for later.
			screen_buffer[bank*LCD_X + x] = byte_to_write;
		}
	}
}

//	Helper function to transfer a bank of pixel data from the screen
//	buffer to the LCD.
void refresh_bank(int bank) {
	if ( bank < 0 || bank >= LCD_Y / 8 ) return;

	LCD_CMD(lcd_set_x_addr, 0);
	LCD_CMD(lcd_set_y_addr, bank);

	for ( int col = 0; col < LCD_X; col++ ) {
		LCD_DATA(screen_buffer[bank * LCD_X + col]);
	}
}

//	Helper function to transfer a one-pixel wide column of pixel data 
//	from the screen buffer to the LCD.
void refresh_col(int col) {
	if ( col < 0 || col >= LCD_X ) return;

	LCD_CMD(lcd_set_function, lcd_addr_vertical);
	LCD_CMD(lcd_set_x_addr, col);
	LCD_CMD(lcd_set_y_addr, 0);

	for ( int bank = 0; bank < LCD_Y / 8; bank++ ) {
		LCD_DATA(screen_buffer[bank * LCD_X + col]);
	}

	LCD_CMD(lcd_set_function, lcd_addr_horizontal);
}

//	Helper function to XOR a bank of pixel data from the screen
//	buffer with a bit pattern and send it to the LCD.
void xor_bank(int bank, uint8_t bit_pattern) {
	if ( bank < 0 || bank >= LCD_Y / 8 ) return;

	LCD_CMD(lcd_set_x_addr, 0);
	LCD_CMD(lcd_set_y_addr, bank);

	for ( int col = 0; col < LCD_X; col++ ) {
		LCD_DATA(screen_buffer[bank * LCD_X + col] ^ bit_pattern);
	}
}

//	Helper function to transfer a one-pixel wide column of pixel data 
//	from the screen buffer to the LCD.
void xor_col(int col, uint8_t bit_pattern) {
	if ( col < 0 || col >= LCD_X ) return;

	LCD_CMD(lcd_set_function, lcd_addr_vertical);
	LCD_CMD(lcd_set_x_addr, col);
	LCD_CMD(lcd_set_y_addr, 0);

	for ( int bank = 0; bank < LCD_Y / 8; bank++ ) {
		LCD_DATA(screen_buffer[bank * LCD_X + col] ^ bit_pattern);
	}

	LCD_CMD(lcd_set_function, lcd_addr_horizontal);
}


int main() {
	setup();

	for ( ;; ) {
		process();
		_delay_ms(33);
	}

	return 0;
}