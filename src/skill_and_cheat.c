#include "./include/skill_and_cheat.h"
#include "./include/menu.h"
#include "include/battle.h"
#include <stdio.h>

void cheat_game(GameData *game) {
  printf("========== 修改列表 ==========\n");
  printf("1. 添加5000点经验\n");
  printf("2. 添加3000点金币\n");
  printf("3. 添加500点生命值\n");
  printf("4. 添加500点魔法值\n");
  printf("5. 添加500点攻击力\n");
  printf("6. 添加500点防御力\n");
  printf("7. 添加300点敏捷\n");
  printf("8. 添加300点智力\n");
  printf("请选择修改项目 (0返回): ");

  int choice;
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    game->player.exp += 5000;
    printf("已添加5000点经验！\n");
    if (game->player.exp >= game->player.level * 100)
      level_up(game);
    break;
  case 2:
    game->player.money += 3000;
    printf("已添加3000点金币！\n");
    break;
  case 3:
    game->player.max_hp += 500;
    game->player.hp += 500;
    printf("已添加500点生命值！\n");
    break;
  case 4:
    game->player.max_mp += 500;
    game->player.mp += 500;
    if (game->player.mp > game->player.max_mp)
      game->player.mp = game->player.max_mp;
    printf("已添加500点魔法值！\n");
    break;
  case 5:
    game->player.attack += 500;
    printf("已添加500点攻击力！\n");
    break;
  case 6:
    game->player.defense += 500;
    printf("已添加500点防御力！\n");
    break;
  case 7:
    game->player.agility += 300;
    printf("已添加300点敏捷！\n");
    break;
  case 8:
    game->player.intelligence += 300;
    printf("已添加300点智力！\n");
    break;
  case 0:
    main_menu(game);
    return;
  default:
    printf("无效的选择。\n");
    main_menu(game);
    return;
  }
}

void learn_skills(GameData *game) {
  printf("\n========== 可学习的技能 ==========\n");

  int available_count = 0;
  int available_skills[MAX_SKILLS];

  for (int i = 0; i < MAX_SKILLS && i < 19; i++) {
    int learned = 0;
    for (int j = 0; j < game->learned_skill_count; j++) {
      if (game->learned_skills[j] == i) {
        learned = 1;
        break;
      }
    }

    if (learned || game->player.level < game->skills[i].required_level)
      continue;

    printf("%d. %s (需要等级: %d)", available_count + 1, game->skills[i].name,
           game->skills[i].required_level);

    if (game->skills[i].damage > 0)
      printf(" - 造成%d点伤害", game->skills[i].damage);
    if (game->skills[i].heal > 0)
      printf(" - 恢复%d点生命", game->skills[i].heal);
    printf("\n");

    available_skills[available_count++] = i;
  }

  if (available_count == 0) {
    printf("当前没有可学习的新技能。\n");
    return;
  }

  printf("请选择要学习的技能 (0返回): ");
  int choice;
  scanf("%d", &choice);

  if (choice == 0)
    return;

  if (choice < 1 || choice > available_count) {
    printf("无效的选择。\n");
    return;
  }

  if (game->learned_skill_count >= MAX_SKILLS) {
    printf("技能栏已满！\n");
    return;
  }

  int skill_index = available_skills[choice - 1];
  game->learned_skills[game->learned_skill_count++] = skill_index;
  printf("你学会了新技能：%s！\n", game->skills[skill_index].name);
}
