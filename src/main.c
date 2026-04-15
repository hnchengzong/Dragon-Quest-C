#include "./include/game_date.h"
#include "./include/game_type.h"
#include "./include/init.h"
#include "./include/menu_and_cheat.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  GameData game;
  srand(time(NULL));

  printf("=====================================\n");
  printf("      勇者斗恶龙\n");
  printf("=====================================\n\n");

  printf("是否加载存档？(y/n): ");
  char choice;
  scanf(" %c", &choice);

  if (choice == 'y' || choice == 'Y') {
    if (file_exists("savegame.dat")) {
      load_game(&game);
      printf("欢迎回来，%s！\n", game.player.name);
    } else {
      printf("未找到存档文件，开始新游戏。\n");
      init_game(&game);
    }
  } else {
    init_game(&game);
  }

  printf("欢迎来到勇者斗恶龙的世界，%s！\n", game.player.name);
  printf(
      "和平与繁荣在这片土地上已持续了数百年，\n但这份宁静被一头突然出现的恶龙打"
      "破。\n恶龙所到之处，生灵涂炭，横尸遍野。\n无数勇者前去讨伐它，却化作龙巢"
      "前"
      "的累累白骨。\n你作为一名勇敢的战士，义无反顾地踏上了解救世界的旅程。");

  main_menu(&game);
  return 0;
}
