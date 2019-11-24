#ifndef _MENU_H_
#define _MENU_H_

#include <curses.h>
#include "../../include/logic/game.h"

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 24
#define NUM_MENU_ITEMS 2
#define STATUS_PLAY 0
#define STATUS_EXIT 1

struct Menu_ {
  WINDOW *menu_wnd;
  WINDOW *menu_items[NUM_MENU_ITEMS];
  int current_idx;
};
typedef struct Menu_ Menu;

void sig_winch(int signo);
void check_terminal_size();

void ncurses_init();
void menu_init(Menu *menu);
void menu_destroy(Menu *menu);

void menu_go_up(Menu *menu);
void menu_go_down(Menu *menu);
int menu_move(Menu *menu);

int menu_act_on_item(Menu *menu);

int menu_do();

void draw_waiting_for_connection();
void draw_waiting_for_player();

WINDOW *draw_game_field();

void erase_entity(WINDOW *game_field, const struct point *entity_positon, const char *entity_model);
void draw_entity(WINDOW *game_field, const struct point *entity_positon, const char *entity_model);

#endif // _MENU_H_
