#include <stdio.h>
#include <curses.h>
#include "../include/graphics/menu.h"
#include "../include/network/client.h"

int main(int argc, char **argv)
{
  char *enemy_model = "###";
  char *bullet_model = "!";
  struct point enemy_position;
  struct point bullet_position;

  ncurses_init();

  int ret_act = menu_do();

  if (ret_act == STATUS_PLAY) {
    /*
     * экран ожидания(подключение к серверу)
     */

    draw_waiting_for_connection();

    init_client(argc, argv);

    int stat_connect_to_serv = 0;


    stat_connect_to_serv = reception();
    draw_waiting_for_player();

    struct message_transmitting message = wait_start_of_game();

    if (message.status == STRT_GS) {
      /*
       * отрисовать поле игры
       */
      
      struct game *game = game_init();
      game->user->id = message.id_user;
      /*
       * отправить сереру свои координаты
       */

      /*
       * Функция draw_game_field не полная.
       * Осталось отрисовать врагов
       */
      WINDOW *game_field = draw_game_field(game);

      while (1) {
        //читаем с клавы
        int status = get_player_action_from_keyboard(game_field,
                     game,
                     &bullet_position,
                     bullet_model);

        if (status == STATUS_EXIT) {
          break;
        }

        //смотрим (неблокирующе) есть ли пакет от сервера
      }

      delwin(game_field);
    }

  }

  endwin();

  return 0;
}
