#pragma once
#include "game_type.h"

void battle(GameData *game);
void level_up(GameData *game);
int calculate_damage(int attacker_attack, int defender_defense);
void show_ending();
int estimate_enemy_level(Enemy *enemy);
