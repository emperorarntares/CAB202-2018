/********************************
   TeensyPewPew RTZM
   By Kevin Duong
   Student ID: n9934731
*********************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>

#include <stdbool.h>
#include <graphics.h>
#include <sprite.h>
#include <macros.h>
#include "lcd_model.h"

#include "usb_serial.h"

bool menu = true;
bool pause = false;
bool game_over = false;

int health = 100;
int speed = 0;
float fuel = 100;
float distance = 0;

int seed = 1;

int seconds = 0;
int delay_count = 0;

int refuel_timer = 0;
int refuel_count = 0;

/*SETUP GAME-------------------------------------------------------------*/

void setup() {
	set_clock_speed(CPU_8MHz);
	lcd_init(LCD_DEFAULT_CONTRAST);
	clear_screen();
	show_screen();
}
/*SPRITE CONFIGURATIONS--------------------------------------------------*/
Sprite player;
static uint8_t player_image[] = {
	0b01111110,
	0b11000011,
	0b11011011,
	0b01111110,
	0b01011010,
	0b11000011,
	0b11000011,
	0b01111110,
};

void setup_player(void) {
	
	CLEAR_BIT(DDRD, 1); //JOYSTICK UP
	CLEAR_BIT(DDRB, 7); //JOYSTICK DOWN
	CLEAR_BIT(DDRB, 1); //JOYSTICK LEFT
	CLEAR_BIT(DDRD, 0); //JOYSTICK RIGHT
	CLEAR_BIT(DDRB, 0); //JOYSTICK CENTRE
	
	CLEAR_BIT(DDRF, 6); //SWITCH LEFT
	CLEAR_BIT(DDRF, 5); //SWITCH RIGHT
	
	//POSITION PLAYER
	int W = 8, H = 8;
	
	sprite_init(&player, (LCD_X - W) / 2, (LCD_Y - H) / 1.2 , W, H, player_image);
	sprite_draw(&player);
}

int spriteCount = 5;
/*OBSTACLES--------------------------------------------------------------*/

uint8_t zombie_image[] =
{
  0b11111000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b11111000
};

uint8_t sign_image[] =
{
  0b10000100,
  0b11111100,
  0b11111100,
  0b10000100,
  0b10000100
};

uint8_t blockade_image[] =
{
	0b01111110,
	0b11111111,
	0b11111111,
};

Sprite obstacle;
void create_obstacle() {
	
	uint8_t obstacle_width;
	uint8_t obstacle_height;
	uint8_t *obstacle_image;
	
	srand(seed*794);
	int obstacle_num = rand()%3;
	
	if (obstacle_num == 1) {
		obstacle_width = 5;
		obstacle_height = 5;
		obstacle_image = zombie_image;
	}
	else if (obstacle_num == 2) {
		obstacle_width = 6;
		obstacle_height = 5;
		obstacle_image = sign_image;
	}
	else {
		obstacle_width = 8;
		obstacle_height = 3;
		obstacle_image = blockade_image;
	}
	int spawn_distance = LCD_Y/3;
	int obstacle_x = rand()%(LCD_X/3 - obstacle_width) + (LCD_X - LCD_X/3)/2;
	int obstacle_y = -rand()%(spawn_distance) - obstacle_height;
	
	sprite_init(&obstacle, obstacle_x, obstacle_y, obstacle_width, obstacle_height, obstacle_image);
}

Sprite obstacle2;
void create_obstacle2() {
	
	uint8_t obstacle2_width;
	uint8_t obstacle2_height;
	uint8_t *obstacle2_image;
	
	srand(seed*1325);
	int obstacle2_num = rand()%3;
	
	if (obstacle2_num == 1) {
		obstacle2_width = 5;
		obstacle2_height = 5;
		obstacle2_image = zombie_image;
	}
	else if (obstacle2_num == 2) {
		obstacle2_width = 6;
		obstacle2_height = 5;
		obstacle2_image = sign_image;
	}
	else {
		obstacle2_width = 8;
		obstacle2_height = 3;
		obstacle2_image = blockade_image;
	}
	int spawn_distance = LCD_Y/3;
	int obstacle2_x = rand()%(LCD_X/3 - obstacle2_width) + (LCD_X - LCD_X/3)/2;
	int obstacle2_y = -rand()%(spawn_distance) - obstacle2_height;
	
	sprite_init(&obstacle2, obstacle2_x, obstacle2_y, obstacle2_width, obstacle2_height, obstacle2_image);
}

Sprite obstacle3;
void create_obstacle3() {
	
	uint8_t obstacle3_width;
	uint8_t obstacle3_height;
	uint8_t *obstacle3_image;
	
	srand(seed*15);
	int obstacle3_num = rand()%3;
	
	if (obstacle3_num == 1) {
		obstacle3_width = 5;
		obstacle3_height = 5;
		obstacle3_image = zombie_image;
	}
	else if (obstacle3_num == 2) {
		obstacle3_width = 6;
		obstacle3_height = 5;
		obstacle3_image = sign_image;
	}
	else {
		obstacle3_width = 8;
		obstacle3_height = 3;
		obstacle3_image = blockade_image;
	}
	int spawn_distance = LCD_Y/3;
	int obstacle3_x = rand()%(LCD_X/3 - obstacle3_width) + (LCD_X - LCD_X/3)/2;
	int obstacle3_y = -rand()%(spawn_distance) - obstacle3_height;
	
	sprite_init(&obstacle3, obstacle3_x, obstacle3_y, obstacle3_width, obstacle3_height, obstacle3_image);
}

/*SCENERY----------------------------------------------------------------*/
uint8_t tree_image[] =
{
  0b00100000,
  0b00100000,
  0b01110000,
  0b01110000,
  0b11111000,
  0b00100000,
  0b00100000
};	

uint8_t house_image[] =
{
  0b00011000,
  0b00100100,
  0b01000010,
  0b11111111,
  0b10000001,
  0b10011001,
  0b10011001,
  0b11111111
};

Sprite sceneryLeft;
void create_sceneryLeft() {
	
	uint8_t sceneryLeft_width;
	uint8_t sceneryLeft_height;
	uint8_t *sceneryLeft_image;
	
	srand(seed*1348);
	int sceneryLeft_num = rand()%2;
	
	if (sceneryLeft_num == 1) {
		sceneryLeft_width = 5;
		sceneryLeft_height = 7;
		sceneryLeft_image = tree_image;
	}
	else {
		sceneryLeft_width = 8;
		sceneryLeft_height = 8;
		sceneryLeft_image = house_image;
	}
	int spawn_distance = LCD_Y/3;
	int sceneryLeft_x = rand()%((LCD_X - LCD_X/3)/2 - sceneryLeft_width);
	int sceneryLeft_y = -rand()%(spawn_distance) - sceneryLeft_height;
	
	sprite_init(&sceneryLeft, sceneryLeft_x, sceneryLeft_y, sceneryLeft_width, sceneryLeft_height, sceneryLeft_image);
}

Sprite sceneryLeft2;
void create_sceneryLeft2() {
	
	int8_t sceneryLeft2_width;
	uint8_t sceneryLeft2_height;
	uint8_t *sceneryLeft2_image;
	
	srand(seed*1711);
	int sceneryLeft2_num = rand()%2;
	
	if (sceneryLeft2_num == 1) {
		sceneryLeft2_width = 5;
		sceneryLeft2_height = 7;
		sceneryLeft2_image = tree_image;
	}
	else {
		sceneryLeft2_width = 8;
		sceneryLeft2_height = 8;
		sceneryLeft2_image = house_image;
	}
	int spawn_distance = LCD_Y/3;
	int sceneryLeft2_x = rand()%((LCD_X - LCD_X/3)/2 - sceneryLeft2_width);
	int sceneryLeft2_y = -rand()%(spawn_distance) - sceneryLeft2_height;
	
	sprite_init(&sceneryLeft2, sceneryLeft2_x, sceneryLeft2_y, sceneryLeft2_width, sceneryLeft2_height, sceneryLeft2_image);
}

Sprite sceneryLeft3;
void create_sceneryLeft3() {
	
	int8_t sceneryLeft3_width;
	uint8_t sceneryLeft3_height;
	uint8_t *sceneryLeft3_image;
	
	srand(seed*1987);
	int sceneryLeft3_num = rand()%2;
	
	if (sceneryLeft3_num == 1) {
		sceneryLeft3_width = 5;
		sceneryLeft3_height = 7;
		sceneryLeft3_image = tree_image;
	}
	else {
		sceneryLeft3_width = 8;
		sceneryLeft3_height = 8;
		sceneryLeft3_image = house_image;
	}
	int spawn_distance = LCD_Y/3;
	int sceneryLeft3_x = rand()%((LCD_X - LCD_X/3)/2 - sceneryLeft3_width);
	int sceneryLeft3_y = -rand()%(spawn_distance) - sceneryLeft3_height;
	
	sprite_init(&sceneryLeft3, sceneryLeft3_x, sceneryLeft3_y, sceneryLeft3_width, sceneryLeft3_height, sceneryLeft3_image);
}

Sprite sceneryRight;
void create_sceneryRight() {
	
	uint8_t sceneryRight_width;
	uint8_t sceneryRight_height;
	uint8_t *sceneryRight_image;
	
	srand(seed*1564);
	int sceneryRight_num = rand()%2;
	
	if (sceneryRight_num == 1) {
		sceneryRight_width = 5;
		sceneryRight_height = 7;
		sceneryRight_image = tree_image;
	}
	else {
		sceneryRight_width = 8;
		sceneryRight_height = 8;
		sceneryRight_image = house_image;
	}
	int spawn_distance = LCD_Y/3;
	int sceneryRight_x = rand()%((LCD_X - LCD_X/3)/2 - sceneryRight_width) + (LCD_X + LCD_X/3)/2 - 1;
	int sceneryRight_y = -rand()%(spawn_distance) - sceneryRight_height;
	
	sprite_init(&sceneryRight, sceneryRight_x, sceneryRight_y, sceneryRight_width, sceneryRight_height, sceneryRight_image);
}

Sprite sceneryRight2;
void create_sceneryRight2() {
	
	uint8_t sceneryRight2_width;
	uint8_t sceneryRight2_height;
	uint8_t *sceneryRight2_image;
	
	srand(seed*1633);
	int sceneryRight2_num = rand()%2;
	
	if (sceneryRight2_num == 1) {
		sceneryRight2_width = 5;
		sceneryRight2_height = 7;
		sceneryRight2_image = tree_image;
	}
	else {
		sceneryRight2_width = 8;
		sceneryRight2_height = 8;
		sceneryRight2_image = house_image;
	}
	int spawn_distance = LCD_Y/3;
	int sceneryRight2_x = rand()%((LCD_X - LCD_X/3)/2 - sceneryRight2_width) + (LCD_X + LCD_X/3)/2 - 1;
	int sceneryRight2_y = -rand()%(spawn_distance) - sceneryRight2_height;
	
	sprite_init(&sceneryRight2, sceneryRight2_x, sceneryRight2_y, sceneryRight2_width, sceneryRight2_height, sceneryRight2_image);
}

Sprite sceneryRight3;
void create_sceneryRight3() {
	
	uint8_t sceneryRight3_width;
	uint8_t sceneryRight3_height;
	uint8_t *sceneryRight3_image;
	
	srand(seed*1747);
	int sceneryRight3_num = rand()%2;
	
	if (sceneryRight3_num == 1) {
		sceneryRight3_width = 5;
		sceneryRight3_height = 7;
		sceneryRight3_image = tree_image;
	}
	else {
		sceneryRight3_width = 8;
		sceneryRight3_height = 8;
		sceneryRight3_image = house_image;
	}
	int spawn_distance = LCD_Y/3;
	int sceneryRight3_x = rand()%((LCD_X - LCD_X/3)/2 - sceneryRight3_width) + (LCD_X + LCD_X/3)/2 - 1;
	int sceneryRight3_y = -rand()%(spawn_distance) - sceneryRight3_height;
	
	sprite_init(&sceneryRight3, sceneryRight3_x, sceneryRight3_y, sceneryRight3_width, sceneryRight3_height, sceneryRight3_image);
}

/*FUELDEPOT--------------------------------------------------------------*/
uint8_t fuelDepot_img[] =
{
  0b11111110,
  0b10000010,
  0b10111010,
  0b10100010,
  0b10110010,
  0b10100010,
  0b10100010,
  0b11111110
};

Sprite fuelDepotLeft;
Sprite fuelDepotRight;

void create_fuelDepotLeft() {
	
	uint8_t fuelDepot_width = 7;
	uint8_t fuelDepot_height = 8;
	
	srand(seed*141.3);
	uint8_t spawn_distance = 200;	
	int fuelDepot_x = (LCD_X - LCD_X/3)/2 - fuelDepot_width - 1;
	int fuelDepot_y = -rand()%(60) - fuelDepot_height - spawn_distance;	
	

	sprite_init(&fuelDepotLeft, fuelDepot_x, fuelDepot_y, fuelDepot_width, fuelDepot_height, fuelDepot_img);
}

void create_fuelDepotRight() {
	
	uint8_t fuelDepot_width = 7;
	uint8_t fuelDepot_height = 8;
	
	srand(seed*141.3);
	uint8_t spawn_distance = 200;
	int fuelDepot_x = (LCD_X + LCD_X/3)/2 + 2;
	int fuelDepot_y = -rand()%(60) - fuelDepot_height - spawn_distance;	

	sprite_init(&fuelDepotRight, fuelDepot_x, fuelDepot_y, fuelDepot_width, fuelDepot_height, fuelDepot_img);
}

/*FINISH DESTINATION-----------------------------------------------------*/
uint8_t ZM_image[] =
{
	0b11111111,
	0b00000000,
	0b11111111
};
uint8_t finishline_width = 8;
uint8_t	finishline_height = 3;
int finishline_y = 2;	

Sprite finishline1;
void spawn_finishline1() {

	int finishline1_x = LCD_X/3 + 2;		
	sprite_init(&finishline1, finishline1_x, finishline_y, finishline_width, finishline_height, ZM_image);
}

Sprite finishline2;
void spawn_finishline2() {

	int finishline2_x = LCD_X/3 + 10;	
	sprite_init(&finishline2, finishline2_x, finishline_y, finishline_width, finishline_height, ZM_image);
}

Sprite finishline3;
void spawn_finishline3() {

	int finishline3_x = LCD_X/3 + 18;	
	sprite_init(&finishline3, finishline3_x, finishline_y, finishline_width, finishline_height, ZM_image);
}

/*CREATE SPRITES ON LOAD-------------------------------------------------*/
void create_sprites() {
	
	clear_screen();
	

	int spawn_distance = LCD_Y/3;
	
	create_obstacle();
	obstacle.y = obstacle.y;
	create_obstacle2();
	obstacle2.y = obstacle2.y - spawn_distance;
	create_obstacle3();
	obstacle3.y = obstacle3.y - spawn_distance*2;
	
	create_sceneryLeft();
	sceneryLeft.y = sceneryLeft.y;
	create_sceneryLeft2();
	sceneryLeft2.y = sceneryLeft2.y - spawn_distance;
	create_sceneryLeft3();
	sceneryLeft3.y = sceneryLeft3.y - spawn_distance*2;
	
	create_sceneryRight();
	sceneryRight.y = sceneryRight.y;
	create_sceneryRight2();
	sceneryRight2.y = sceneryRight2.y - spawn_distance;
	create_sceneryRight3();
	sceneryRight3.y = sceneryRight3.y - spawn_distance*2;
	
	create_fuelDepotLeft();
	create_fuelDepotRight();
	
	spawn_finishline1();
	spawn_finishline2();
	spawn_finishline3();
}

/*SPAWN SPRITES INTO MAP-------------------------------------------------*/
void spawn_sprites() {
	
	//MOVE SPRITES
	if (speed > 0) {
		obstacle.y += 0.15*speed;
		obstacle2.y += 0.15*speed;
		obstacle3.y += 0.15*speed;
		
		sceneryLeft.y += 0.15*speed;
		sceneryLeft2.y += 0.15*speed;
		sceneryLeft3.y += 0.15*speed;
		
		sceneryRight.y += 0.15*speed;
		sceneryRight2.y += 0.15*speed;
		sceneryRight3.y += 0.15*speed;
		
		fuelDepotLeft.y += 0.15*speed;
		fuelDepotRight.y += 0.15*speed;
	}
	
	if (distance >= 4900) {
			finishline1.y += 0.15*speed;
			finishline2.y += 0.15*speed;
			finishline3.y += 0.15*speed;
	}

	//SPAWN SPRITES
	sprite_draw(&obstacle);
	sprite_draw(&obstacle2);
	sprite_draw(&obstacle3);
	
	sprite_draw(&sceneryLeft);
	sprite_draw(&sceneryLeft2);
	sprite_draw(&sceneryLeft3);
	
	sprite_draw(&sceneryRight);
	sprite_draw(&sceneryRight2);
	sprite_draw(&sceneryRight3);
	
	sprite_draw(&fuelDepotLeft);
	sprite_draw(&fuelDepotRight);
	
	if (distance >= 4900) {
		sprite_draw(&finishline1);
		sprite_draw(&finishline2);
		sprite_draw(&finishline3);		
	}
	
	// RESTART SPRITES
	if (!game_over) {
		if (obstacle.y > LCD_Y) {
			create_obstacle();
		}
		if (obstacle2.y > LCD_Y) {
			create_obstacle2();
		}
		if (obstacle3.y > LCD_Y) {
			create_obstacle3();
		}
		if (sceneryLeft.y > LCD_Y) {
			create_sceneryLeft();
		}
		if (sceneryLeft2.y > LCD_Y) {
			create_sceneryLeft2();
		}
		if (sceneryLeft3.y > LCD_Y) {
			create_sceneryLeft3();
		}
		if (sceneryRight.y > LCD_Y) {
			create_sceneryRight();
		}
		if (sceneryRight2.y > LCD_Y) {
			create_sceneryRight2();
		}
		if (sceneryRight3.y > LCD_Y) {
			create_sceneryRight3();
		}
		
		if (fuelDepotLeft.y > LCD_Y) {
			create_fuelDepotLeft();
		}
		
		if (fuelDepotRight.y > LCD_Y) {
			create_fuelDepotRight();
		}
	}
}
/*COLLISION--------------------------------------------------------------*/
bool collided ( Sprite player, Sprite sprite ) 
{
	int top_player = player.y;
	int left_player = player.x;
	int right_player = left_player + player.width - 1;
	int bottom_player = top_player + player.height - 1;
	
	int top_object = sprite.y;
	int left_object = sprite.x;
	int right_object = left_object + sprite.width - 1;
	int bottom_object = top_object + sprite.height - 1;
	
	if ( top_object > bottom_player ) return false;
	if ( top_player > bottom_object ) return false;
	if ( left_player > right_object ) return false;
	if ( left_object > right_player ) return false;
	
	return true;
}

bool refuel_left ( Sprite player, Sprite fuelDepotLeft ) {
	int top_player = player.y;
	int left_player = player.x;
	int right_player = left_player + player.width - 1;
	int bottom_player = top_player + player.height - 1;
	
	int top_fuel_l = fuelDepotLeft.y;
	int left_fuel_l = fuelDepotLeft.x;
	int right_fuel_l = left_fuel_l + fuelDepotLeft.width;
	int bottom_fuel_l = top_fuel_l + fuelDepotLeft.height - 7;
	
	if ( top_fuel_l > bottom_player ) return false;
	if ( top_player > bottom_fuel_l ) return false;
	if ( left_player > right_fuel_l ) return false;
	if ( left_fuel_l > right_player ) return false;
	
	return true;
}

bool refuel_right ( Sprite player, Sprite fuelDepotRight ) {
	int top_player = player.y;
	int left_player = player.x;
	int right_player = left_player + player.width - 1;
	int bottom_player = top_player + player.height - 1;
	
	int top_fuel_r = fuelDepotRight.y;
	int left_fuel_r = fuelDepotRight.x - 1;
	int right_fuel_r = left_fuel_r + fuelDepotRight.width - 1;
	int bottom_fuel_r = top_fuel_r + fuelDepotRight.height - 7;
	
	if ( top_fuel_r > bottom_player ) return false;
	if ( top_player > bottom_fuel_r ) return false;
	if ( left_player > right_fuel_r ) return false;
	if ( left_fuel_r > right_player ) return false;
	
	return true;
}
/*BORDER-----------------------------------------------------------------*/
void border(void) {
	
	uint8_t W = LCD_X, H = LCD_Y;
	
	draw_line(0, 8, W-2, 8, FG_COLOUR); //TOP BORDER
	draw_line(0, H-1, W-1, H-1, FG_COLOUR); //BOTTOM BORDER
	draw_line(0, 8, 0, H-1, FG_COLOUR); //LEFT BORDER
	draw_line(W-1, 8, W-1, H-1, FG_COLOUR); //RIGHT BORDER
	
	draw_line((W-1)/3, 9, (W-1)/3, H-2, FG_COLOUR); //LEFT ROAD
	draw_line((W-1)/1.5, 9, (W-1)/1.5, H-2, FG_COLOUR); //RIGHT ROAD
	
	sprite_draw(&player);
	show_screen();
}
/*SPLASH SCREEN----------------------------------------------------------*/
void splash_screen() {
	
	clear_screen();
	
	draw_string(0, 5, "WELCOME TO RTZM", FG_COLOUR);
	draw_string(0, 15, "KEVIN DUONG", FG_COLOUR);
	draw_string(0, 25, "N9934731", FG_COLOUR);
	draw_string(0, 35, "->MIDDLE STICK", FG_COLOUR);
	
	show_screen();	
	
	//PLAY THE GAME
	if ( BIT_IS_SET(PINB, 0) ) clear_screen(), menu = false;
	
	//REPOSITION PLAYER
	sprite_init(&player, (LCD_X - 8) / 2, (LCD_Y - 8) / 1.2 , 8, 8, player_image);
	sprite_draw(&player);
}
/*-----------------------------------------------------------------------*/
char buffer[10];

void draw_int(uint8_t x, uint8_t y, int t) {
	snprintf( buffer, 10, "%d", t );
	draw_string( x, y, buffer, FG_COLOUR );
}

/*DASHBOARD--------------------------------------------------------------*/
void player_hud() {
	
	draw_string(0, 0, "H:   ", FG_COLOUR);
	draw_int( 10, 0, health );
	draw_string(32, 0, "S:  ", FG_COLOUR);
	draw_int( 42, 0, speed );
	draw_string(59, 0, "F:   ", FG_COLOUR);
	draw_int( 69, 0, fuel );
	
	sprite_draw(&player);
	show_screen();
	
}
/*DISTANCE---------------------------------------------------------------*/
void distance_traveled() {
	
	if (speed == 0) {
		return;
	} else {
		distance += 0.5 * speed;
	}
}
/*FUEL CONSUMPTION-------------------------------------------------------*/
void fuel_consumption() {
	
	if (fuel <= 0) {
		game_over = true;
	} else if (speed == 0) {
		return;
	} else {
		fuel -= 0.02 * speed; 
	}
}
/*TIME ELAPSED-----------------------------------------------------------*/
void timer() 
{
	delay_count++;
	if (delay_count == 18) 
	{
		seconds++;
		delay_count = 0;
	}
}

/*PAUSEMODE--------------------------------------------------------------*/
void pausemenu() {

	clear_screen();
	draw_string((LCD_X - 55) / 2, 10, "GAME PAUSED", FG_COLOUR);
	draw_string(0, 30, "DISTANCE", FG_COLOUR);
	draw_int(LCD_X - 20, 30, distance);
	draw_string(0, 40, "TIME", FG_COLOUR);
	draw_int(LCD_X - 20, 40, seconds);
	
	if ( BIT_IS_SET(PINF, 6) ) {
		pause = false; //RESUME GAME
		clear_screen();
	}
	
	show_screen();
}
/*GAMEOVER---------------------------------------------------------------*/
void end_game() {
	clear_screen();
	if (health <= 0 || fuel <= 0){
		draw_string((LCD_X - 45) / 2, 10, "GAME OVER", FG_COLOUR);
	} else {
		draw_string((LCD_X - 34) / 2, 10, "YOU WIN!", FG_COLOUR);
	}
	
	draw_string(0, 20, "DISTANCE", FG_COLOUR);
	draw_int(LCD_X - 20, 20, distance);
	draw_string(0, 30, "TIME", FG_COLOUR);
	draw_int(LCD_X - 20, 30, seconds);
	draw_string((LCD_X - 70) / 2, 40, "SW2 TO RESTART", FG_COLOUR);
	show_screen();
}
/*CONTROLS---------------------------------------------------------------*/
void controls(void) {
	
	int dx = 0;
	
	if ( BIT_IS_SET(PINB, 1) ) dx = -1; //MOVE LEFT
	if ( BIT_IS_SET(PIND, 0) ) dx = 1;  //MOVE RIGHT
	
	if ( BIT_IS_SET(PIND, 1) && speed != 10 ) speed++; //INCREASE SPEED
	if ( BIT_IS_SET(PINB, 7) && speed != 0 ) speed--; //DECREASE SPEED
	
	if ( BIT_IS_SET(PINF, 5) ) pause = true; //PAUSE GAME
	
	if ( dx ) {
		if ( speed == 0 ) {
			return; //NO LATERAL MOTION
		} else {
			player.x += dx * speed * 0.5; //MOVE PLAYER
		}
	}
	//MOVE PLAYER
	sprite_draw(&player);
	
	//LEFT BORDER BOUNDRY
	if (player.x < 1) {
		
		sprite_init(&player, 1, (LCD_Y - 8) / 1.2 , 8, 8, player_image);
	}
	
	//RIGHT BORDER BOUNDRY
	if (player.x > LCD_X - 9) {
		
		sprite_init(&player, LCD_X - 9, (LCD_Y - 8) / 1.2 , 8, 8, player_image);
	}
	
	//OFFROAD
	if ((player.x < (LCD_X - 1) / 3 || player.x > (LCD_X - 12) / 1.5) && (speed > 3)) {
		
		speed-= 0.000001;
		if (speed <= 3) {
			speed = 3;
		}
	}
	
}
/*DAMAGE SYSTEM----------------------------------------------------------*/
void damage_function() {
	
	if ( collided (player, obstacle) || collided(player, obstacle2) || collided(player, obstacle3) ||
		 collided(player, sceneryLeft) || collided(player, sceneryLeft2) || collided(player, sceneryLeft3) ||
	     collided(player, sceneryRight) || collided(player, sceneryRight2) || collided(player, sceneryRight3) 
		) {
		
		//CLEAR PATH FOR PLAYER
		create_obstacle();
		obstacle.y = obstacle.y;
		create_obstacle2();
		obstacle2.y = obstacle2.y - LCD_Y/3;
		create_obstacle3();
		obstacle3.y = obstacle3.y - LCD_Y/3*2;
	
		health -= 10;
			
		fuel = 100;
		speed = 0;
		
		refuel_timer = 0;
		refuel_count = 0;
		
		sprite_init(&player, (LCD_X - 8) / 2, (LCD_Y - 8) / 1.2 , 8, 8, player_image);
		sprite_draw(&player);
	}
	
	if (collided (player, fuelDepotLeft) || collided (player, fuelDepotRight) ) {
		health = 0;
		game_over = true;
	}
}
/*REFUEL SYSTEM----------------------------------------------------------*/
void refuel_function() {
	if ( refuel_left(player, fuelDepotLeft) || refuel_right(player, fuelDepotRight) ) {	
		
		speed = 0;
		refuel_count++;
		fuel++;
		if (refuel_count >= 10) {
			refuel_timer++;
			refuel_count = 0;
		}

		if (refuel_timer == 3 || fuel >= 100) {
			fuel = 100;
			
			if ( refuel_left(player, fuelDepotLeft) ) {	
				player.x += 1;
			}
				
			if ( refuel_right(player, fuelDepotRight) ) {	
				player.x += -1;
			}
			
			refuel_timer = 0;
			refuel_count = 0;
		}
	}
}
/*PROCESS FUNCTIONS------------------------------------------------------*/
void process ( void ) {
	clear_screen();
	
	spawn_sprites();	
	
	controls();
	player_hud();
	border();
	distance_traveled();
	fuel_consumption();
	damage_function();
	refuel_function();
	timer();
	
	if (health <= 0 || distance >= 5000) {
		game_over = true;
	}
	show_screen();
}
/*-----------------------------------------------------------------------*/
int main(void) {
    setup();
	setup_player();
	
	for ( ;; ) {
		if (menu) {
			splash_screen();
			create_sprites();
		} else if (pause) {
			pausemenu();
		} else if (game_over) {
			end_game();
			
			if ( BIT_IS_SET(PINF, 6) ) {
				//RESTART GAME
				menu = true;
				game_over = false;
				
				health = 100;
				fuel = 100;
				speed = 0;
				distance = 0;
				seconds = 0;
			}
			
		} else {
			seed++;
			process();
		}
	}
}
