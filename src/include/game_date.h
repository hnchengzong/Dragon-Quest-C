#pragma once

#include "game_type.h"

void save_game(GameData *game);
void load_game(GameData *game);
int file_exists(const char *filename);
