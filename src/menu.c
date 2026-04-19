#include "./include/menu.h"
#include "include/battle.h"
#include "include/game_date.h"
#include "include/menu_and_cheat.h"
#include <stdio.h>
#include <stdlib.h>

static void exit_game(GameData *game) {
  printf("感谢游玩！再见！\n");
  exit(0);
}

static void easter_egg(GameData *game) {
  printf("哼哼哼啊啊啊啊啊啊！！！！！！\n");
}

void main_menu(GameData *game) {
  static const MenuItem menu_items[] = {{1, "查看状态", show_status},
                                        {2, "移动", move},
                                        {3, "寻找敌人", battle},
                                        {4, "与NPC交谈", talk_to_npc},
                                        {5, "查看背包", show_inventory},
                                        {6, "使用物品", use_item},
                                        {7, "休息", rest},
                                        {8, "学习技能", learn_skills},
                                        {9, "保存游戏", save_game},
                                        {0, "退出游戏", exit_game},
                                        {666, "作弊模式", cheat_game},
                                        {114514, "彩蛋", easter_egg}};
  const int menu_count = sizeof(menu_items) / sizeof(menu_items[0]);
  int choice;

  while (1) {
    printf("\n========== 主菜单 ==========\n");
    printf("当前地点：%s\n", game->locations[game->current_location].name);

    for (int i = 0; i < menu_count - 2; i++) {
      printf("%d. %s\n", menu_items[i].choice, menu_items[i].description);
    }

    printf("请选择: ");

    if (scanf("%d", &choice) != 1) {
      printf("输入无效，请输入数字。\n");
      while (getchar() != '\n') {
      };
      continue;
    }

    int found = 0;
    for (int i = 0; i < menu_count; i++) {
      if (menu_items[i].choice == choice) {
        menu_items[i].action(game);
        found = 1;
        break;
      }
    }

    if (!found) {
      printf("无效选择，请重新输入。\n");
    }
  }
}

void show_status(GameData *game) {
  printf("\n========== 角色状态 ==========\n");
  printf("姓名: %s\n", game->player.name);
  printf("等级: %ld\n", game->player.level);
  printf("经验值: %ld/%ld\n", game->player.exp, game->player.level * 100);
  printf("生命值: %ld/%ld\n", game->player.hp, game->player.max_hp);
  printf("魔法值: %ld/%ld\n", game->player.mp, game->player.max_mp);
  printf("攻击力: %ld (基础: %ld)\n", game->player.attack,
         game->player.base_attack);
  printf("防御力: %ld (基础: %ld)\n", game->player.defense,
         game->player.base_defense);
  printf("敏捷: %ld\n", game->player.agility);
  printf("智力: %ld\n", game->player.intelligence);
  printf("金币: %ld\n", game->player.money);

  if (game->player.equipped_weapon >= 0) {
    printf("当前武器: 已装备 (+%d攻击)\n", game->player.equipped_weapon);
  } else {
    printf("当前武器: 无\n");
  }

  if (game->player.equipped_armor >= 0) {
    printf("当前防具: 已装备 (+%d防御)\n", game->player.equipped_armor);
  } else {
    printf("当前防具: 无\n");
  }

  printf("=============================\n");
}

void move(GameData *game) {
  int i, choice;

  printf("\n========== 可去地点 ==========\n");
  for (i = 0; i < MAX_LOCATIONS; i++) {
    if (game->locations[i].name[0] != '\0' && i != game->current_location) {
      printf("%d. %s - %s\n", i + 1, game->locations[i].name,
             game->locations[i].description);
    }
  }
  printf("请选择目的地 (输入对应数字): ");

  if (scanf("%d", &choice) != 1) {
    while (getchar() != '\n')
      ;
    printf("输入无效。\n");
    return;
  }

  choice--;

  if (choice >= 0 && choice < MAX_LOCATIONS &&
      choice != game->current_location &&
      game->locations[choice].name[0] != '\0') {
    game->current_location = choice;
    printf("你来到了%s。\n", game->locations[game->current_location].name);
  } else if (choice == 666) {
    cheat_game(game);
  } else {
    printf("无效的选择。\n");
  }
}

void rest(GameData *game) {
  int location_type = game->locations[game->current_location].type;

  // 0=城镇, 4=王城, 5=沙漠绿洲
  if (location_type == 0 || location_type == 4 || location_type == 5) {
    int restore_hp = game->player.max_hp - game->player.hp;
    int restore_mp = game->player.max_mp - game->player.mp;

    game->player.hp = game->player.max_hp;
    game->player.mp = game->player.max_mp;

    printf("你在这里好好休息了一番...\n");
    printf("恢复了%d点生命值和%d点魔法值！\n", restore_hp, restore_mp);
  } else {
    printf("只有在城镇、王城或绿洲等地才能休息！\n");
  }
}
