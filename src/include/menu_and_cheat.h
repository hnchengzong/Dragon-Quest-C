#pragma once

#include "game_type.h"
#include "inventory.h"
#include "menu.h"
#include "npc_dialog.h"
#include "shop.h"
#include "skill_and_cheat.h"

void main_menu(GameData *game);
void cheat_game(GameData *game);
void show_status(GameData *game);
void move(GameData *game);
void rest(GameData *game);
void talk_to_npc(GameData *game);
void show_inventory(GameData *game);
void use_item(GameData *game);
void shop_menu(GameData *game, int npc_index);
void learn_skills(GameData *game);
