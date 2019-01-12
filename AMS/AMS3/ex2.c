#include <stdlib.h>
#include <cab202_timers.h>
#include <cab202_graphics.h>

//  (a) Declare four global integer variables, as follows:
//      l - the horizontal location of the left edge of the rectangle
//      t - the vertical location of the top edge of the rectangle 
//      cols - the width of the rectangle.
//      rows - the height of the rectangle.
int l;
int t;
int cols;
int rows;

//	(b) Declare a global variable of type char called symbol.
//      This is the character that is to be used to render the outline of the
//      rectangle.
char symbol;

void fill_rect(void) {
    //  (c) Test to see if either of cols or rows is less than 1.
    //      If so, the function should stop immediately and draw nothing.
	if (cols >= 1 && rows >= 1) {
    //  (d) Calculate the x-coordinate of the right-hand side of the rectangle.
    //      Store the value in an integer variable called rect_right.
		int rect_right = l+cols-1;
    //  (e) Calculate the y coordinate of the bottom edge of the rectangle.
    //      Store the result in an integer variable called rect_base.
		int rect_base = t+rows-1;
    //  (f.a) Set up for loop that uses an integer variable called y_ctr to 
    //      iterate from the top of the rectangle to the bottom of the rectangle.
    //      Initially y_ctr should be equal to t.
    //      The loop body should run while y_ctr is less than or equal to rect_base.
		for (int y_ctr = t; y_ctr <= rect_base; y_ctr++) {
        //  (g) Draw a horizontal line from l to rect_right, with 
        //      y-coordinate equal to y_ctr, using the character specified by 
        //      symbol.
			draw_line(l,y_ctr,rect_right,y_ctr,symbol);
    //  (f.b) End the loop.
		}
	}
}

int main(void) {
    setup_screen();

    // draw a box.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 1 + rand() % (screen_width() - l - 1);
    rows = 1 + rand() % (screen_height() - t - 1);
    symbol = '@';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 1 + rand() % (screen_width() - l - 1);
    rows = 1 + rand() % (screen_height() - t - 1);
    symbol = '&';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box with zero width.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 0;
    rows = 1 + rand() % (screen_height() - t - 1);
    symbol = '*';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 1 + rand() % (screen_width() - l - 1);
    rows = 1 + rand() % (screen_height() - t - 1);
    symbol = '#';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box with negative width.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = -rand() % screen_width();
    rows = 1 + rand() % (screen_height() - t - 1);
    symbol = '!';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 1 + rand() % (screen_width() - l - 1);
    rows = 1 + rand() % (screen_height() - t - 1);
    symbol = '+';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box with zero height.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 1 + rand() % (screen_width() - l - 1);
    rows = 0;
    symbol = 'a';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 1 + rand() % (screen_width() - l - 1);
    rows = 1 + rand() % (screen_height() - t - 1);
    symbol = 'b';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box with negative width.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 1 + rand() % (screen_width() - t - 1);
    rows = -rand() % screen_height();
    symbol = 'c';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    l = 1 + rand() % (screen_width() - 1) / 2;
    t = 1 + rand() % (screen_height() - 1) / 2;
    cols = 1 + rand() % (screen_width() - l - 1);
    rows = 1 + rand() % (screen_height() - t - 1);
    symbol = 'd';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        l, t, cols, rows
        );
    fill_rect();
    show_screen();
    wait_char();

    timer_pause(5000);
    cleanup_screen();
    return 0;
}
