#include <stdlib.h>
#include <cab202_graphics.h>

//  (a) Begin the definition a function called fill_rect that returns nothing, 
//      but requires the following arguments:
//      left - an integer that specifies the absolute horizontal location 
//          of the left hand side of the rectangle.
//      top - an integer that specifies the absolute vertical location 
//          of the upper edge of the rectangle.
//      right - an integer that specifies the absolute horizontal location 
//          of the right hand side of the rectangle.
//      bottom - an integer that specifies the absolute vertical location 
//          of the lower edge of the rectangle.
//      ch = a character value that will be used to draw the
//          display the rectangle.
void fill_rect(int left, int top, int right, int bottom, char ch) {
    //  (c) Test to see if either the width or height of the rectangle is less 
    //      than 1. If so, the function should stop immediately and draw nothing.
	int width = right - left;
	int height = bottom - top;
	bool draw = true;
	
	if (width < 0|| height < 0) {
		draw = false;
	}
    //  (d) Use statements of your own choice to fill the region defined by the
    //      first four arguments with the designated character value. 
	if (draw == true) {
		int i;
		for (i=top; i<=bottom; i++) {	
			draw_line(left,i,left+width,i,ch);
        }
	}
//  (b) End the definition of fill_rect.
}

void hrule( void );
void vrule( void );

int main( void ) {
    setup_screen();

    // draw a box.
    int left = 2 + rand() % ( screen_width() - 2 ) / 2;
    int top = 2 + rand() % ( screen_height() - 2 ) / 2;
    int right = left + 1 + rand() % ( screen_width() - left - 1 );
    int bottom = top + 1 + rand() % ( screen_height() - top - 1 );
    int ch = '@';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left + 1 + rand() % ( screen_width() - left - 1 );
    bottom = top + 1 + rand() % ( screen_height() - top - 1 );
    ch = '&';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box with zero width.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left - 1;
    bottom = top + 1 + rand() % ( screen_height() - top - 1 );
    ch = '*';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left + 1 + rand() % ( screen_width() - left - 1 );
    bottom = top + 1 + rand() % ( screen_height() - top - 1 );
    ch = '#';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box with negative width.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left - 2;
    bottom = top + 1 + rand() % ( screen_height() - top - 1 );
    ch = '!';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left + 1 + rand() % ( screen_width() - left - 1 );
    bottom = top + 1 + rand() % ( screen_height() - top - 1 );
    ch = '+';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box with zero height.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left + 1 + rand() % ( screen_width() - left - 1 );
    bottom = top - 1;
    ch = 'a';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left + 1 + rand() % ( screen_width() - left - 1 );
    bottom = top + 1 + rand() % ( screen_height() - top - 1 );
    ch = 'b';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box with negative right.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left + 1 + rand() % ( screen_width() - left - 1 );
    bottom = top - 2;
    ch = 'c';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    // draw a box.
    left = 2 + rand() % ( screen_width() - 2 ) / 2;
    top = 2 + rand() % ( screen_height() - 2 ) / 2;
    right = left + 1 + rand() % ( screen_width() - left - 1 );
    bottom = top + 1 + rand() % ( screen_height() - top - 1 );
    ch = 'd';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        left, top, right, bottom
        );
    fill_rect( left, top, right, bottom, ch );
    show_screen();
    wait_char();

    cleanup_screen();
    return 0;
}

void hrule( void ) {
    for ( int x = 0; x < screen_width(); x++ ) {
        draw_char( x, 0, '0' + ( x % 10 ) );
    }
}

void vrule( void ) {
    for ( int y = 0; y < screen_height(); y++ ) {
        draw_char( 0, y, '0' + ( y % 10 ) );
    }
}
