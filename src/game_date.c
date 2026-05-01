#include "include/game_date.h"
#include <stdio.h>

#define SAVE_FILE "savegame.dat"
void save_game(GameData *game) {
  FILE *file = fopen(SAVE_FILE, "wb");
  if (file == NULL) {
    printf("无法保存游戏！\n");
    return;
  }

  fwrite(game, sizeof(GameData), 1, file);
  fclose(file);
  printf("游戏已保存。\n");
}

void load_game(GameData *game) {
  FILE *file = fopen(SAVE_FILE, "rb");
  if (file == NULL) {
    printf("无法加载游戏。\n");
    return;
  }

  fread(game, sizeof(GameData), 1, file);
  fclose(file);
  printf("游戏已加载。\n");
}

int file_exists(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file) {
    fclose(file);
    return 1;
  }
  return 0;
}
