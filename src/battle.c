#include "./include/battle.h"
#include <stdio.h>
#include <stdlib.h>

void level_up(GameData *game) {
  while (game->player.exp >= game->player.level * 100) {
    game->player.level++;
    game->player.max_hp += 20;
    game->player.hp = game->player.max_hp;
    game->player.max_mp += 10;
    game->player.mp = game->player.max_mp;
    game->player.base_attack += 5;
    game->player.base_defense += 2;
    game->player.attack += 5;
    game->player.defense += 2;
    game->player.agility += 3;
    game->player.intelligence += 2;

    printf("恭喜升级到 %ld 级！\n", game->player.level);
    printf("生命值 +20，魔法值 +10  ");
    printf("攻击力 +5，防御力 +2  ");
    printf("敏捷 +3，智力 +2\n");
  }
}

int calculate_damage(int attack, int defense) {
  int base = attack - (defense / 2);
  if (base < 1)
    base = 1;

  int variance = base / 4;
  if (variance < 1)
    variance = 1;

  int damage = base + (rand() % (variance * 2)) - variance;
  return damage < 1 ? 1 : damage;
}

int estimate_enemy_level(Enemy *enemy) {
  int level = (enemy->hp + enemy->attack * 10) / 50;
  return level < 1 ? 1 : level;
}

void show_ending() {
  printf("\n=====================================\n");
  printf("                结局\n");
  printf("=====================================\n");
  printf("经过一番激烈的战斗，你终于击败了恶龙！\n");
  printf("王国重新恢复了和平，人民不再生活在恐惧中。\n");
  printf("你的名字将被永远铭记在历史中，成为传说中的英雄！\n");
  printf("感谢您的游玩！\n");
  printf("=====================================\n");
}

static int get_enemy_type(GameData *game) {
  switch (game->current_location) {
  case 0:
  case 4:
  case 13:
    return -1;
  case 1:
    return rand() % 3 == 2 ? 11 : rand() % 2;
  case 2:
    return rand() % 2 ? 2 : 16;
  case 3:
    return 3;
  case 5:
    return 4;
  case 6:
    return rand() % 2 ? 5 : 17;
  case 7:
    return 8 + (rand() % 2);
  case 8:
    return rand() % 2 ? 7 : 16;
  case 9:
    return 6;
  case 10:
    return rand() % 2 ? 10 : 19;
  case 11:
    return 21 + (rand() % 3);
  case 12:
    return rand() % 2 ? 11 : 12;
  case 14:
    return rand() % 2 ? 12 : 18;
  case 15:
    return 24;
  default:
    return rand() % 10;
  }
}

static void handle_enemy_defeat(GameData *game, Enemy *enemy, int is_dragon) {
  printf("你击败了%s！\n", enemy->name);
  game->player.exp += enemy->exp_reward;
  game->player.money += enemy->money_reward;
  printf("获得了%d经验值和%d金币！\n", enemy->exp_reward, enemy->money_reward);

  if (is_dragon && !game->dragon_defeated) {
    game->dragon_defeated = 1;
    show_ending();
  }

  if (game->player.exp >= game->player.level * 100)
    level_up(game);
}

static void player_attack(GameData *game, Enemy *enemy, int is_dragon) {
  int damage = calculate_damage(game->player.attack, enemy->defense);
  enemy->hp -= damage;
  printf("你对%s造成了%d点伤害！\n", enemy->name, damage);

  if (enemy->hp <= 0)
    handle_enemy_defeat(game, enemy, is_dragon);
}

static void player_use_skill(GameData *game, Enemy *enemy, int is_dragon) {
  printf("\n可用技能:\n");
  int count = 0;
  int skills[MAX_SKILLS];
  int choice;
  Skill *skill;
  int int_bonus;
  int damage;

  for (int i = 0; i < game->learned_skill_count; i++) {
    int idx = game->learned_skills[i];
    skill = &game->skills[idx];

    if (game->player.level < skill->required_level)
      continue;

    if (game->player.mp >= skill->mp_cost)
      printf("%d. %s (消耗%d MP)\n", count + 1, skill->name, skill->mp_cost);
    else
      printf("%d. %s (消耗%d MP) [MP不足]\n", count + 1, skill->name,
             skill->mp_cost);

    skills[count++] = idx;
  }

  if (count == 0) {
    printf("你目前没有可以使用的技能！\n");
    return;
  }

  printf("请选择技能 (0返回): ");
  scanf("%d", &choice);

  if (choice == 0)
    return;

  choice--;
  if (choice < 0 || choice >= count) {
    printf("无效的技能选择。\n");
    return;
  }

  skill = &game->skills[skills[choice]];

  if (game->player.mp < skill->mp_cost) {
    printf("MP不足，无法使用此技能！\n");
    return;
  }

  game->player.mp -= skill->mp_cost;

  int_bonus = game->player.intelligence / 2;
  damage = skill->damage + game->player.attack + int_bonus;

  enemy->hp -= damage;
  printf("你使用%s对%s造成了%d点伤害！(技能伤害%d + 攻击力%ld + 智力加成%d)\n",
         skill->name, enemy->name, damage, skill->damage, game->player.attack,
         int_bonus);

  if (skill->heal > 0) {
    game->player.hp += skill->heal;
    if (game->player.hp > game->player.max_hp)
      game->player.hp = game->player.max_hp;
    printf("你使用%s恢复了%d点生命值！\n", skill->name, skill->heal);
  }

  if (enemy->hp <= 0)
    handle_enemy_defeat(game, enemy, is_dragon);
}

static int try_escape(GameData *game, Enemy *enemy) {
  int enemy_level = estimate_enemy_level(enemy);
  int chance = 50 + (game->player.level - enemy_level) * 5;
  chance += (game->player.agility / 10) * 5;

  if (chance < 10)
    chance = 10;
  if (chance > 90)
    chance = 90;

  if (rand() % 100 < chance) {
    printf("你成功逃跑了！(逃跑率: %d%%)\n", chance);
    return 1;
  }

  printf("逃跑失败！(逃跑率: %d%%)\n", chance);
  return 0;
}

static void enemy_turn(GameData *game, Enemy *enemy) {
  if (enemy->hp <= 0)
    return;

  int dodge_chance = (game->player.agility / 5) - estimate_enemy_level(enemy);
  if (dodge_chance > 90)
    dodge_chance = 90;
  if (dodge_chance < 0)
    dodge_chance = 0;

  if (rand() % 100 < dodge_chance) {
    printf("%s试图攻击你，但你敏捷地闪避开了！(闪避率: %d%%)\n", enemy->name,
           dodge_chance);
    return;
  }

  int damage = calculate_damage(enemy->attack, game->player.defense);
  game->player.hp -= damage;
  printf("%s对你造成了%d点伤害！\n", enemy->name, damage);

  if (game->player.hp <= 0) {
    printf("你被%s击败了...\n", enemy->name);
    printf("游戏结束！\n");
    exit(0);
  }
}

void battle(GameData *game) {
  if (game->dragon_defeated && game->current_location == 3) {
    printf("恶龙已经被你击败了，龙之城堡现在是一片废墟。\n");
    return;
  }

  int enemy_type = get_enemy_type(game);
  if (enemy_type == -1) {
    const char *msg;
    if (game->current_location == 0)
      msg = "村庄里没有敌人。";
    else if (game->current_location == 4)
      msg = "在王城里很安全，没有敌人。";
    else
      msg = "魔法学院里没有敌人。";
    printf("%s\n", msg);
    return;
  }

  Enemy enemy = game->enemies[enemy_type];
  int is_dragon = (enemy_type == 3);
  printf("\n遭遇了%s！\n", enemy.name);

  while (game->player.hp > 0 && enemy.hp > 0) {
    printf("\n---------- 战斗信息 ----------\n");
    printf("%s 生命值: %d/%d\n", enemy.name, enemy.hp, enemy.max_hp);
    printf("%s 生命值: %ld/%ld\n", game->player.name, game->player.hp,
           game->player.max_hp);
    printf("魔法值: %ld/%ld\n", game->player.mp, game->player.max_mp);
    printf("-----------------------------\n");

    printf("1. 普通攻击\n");
    printf("2. 使用技能\n");
    printf("3. 逃跑\n");
    printf("请选择行动: ");

    int choice;
    if (scanf("%d", &choice) != 1) {
      while (getchar() != '\n')
        ;
      printf("输入无效，请输入数字。\n");
      continue;
    }

    switch (choice) {
    case 1:
      player_attack(game, &enemy, is_dragon);
      break;
    case 2:
      player_use_skill(game, &enemy, is_dragon);
      continue;
    case 3:
      if (is_dragon) {
        printf("恶龙的强大气息让你无法移动！\n");
        continue;
      }
      if (try_escape(game, &enemy))
        return;
      break;
    default:
      printf("无效的选择。\n");
      continue;
    }

    enemy_turn(game, &enemy);
  }
}