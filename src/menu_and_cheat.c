#include "./include/menu_and_cheat.h"
#include "./include/battle.h"
#include "./include/game_date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_inventory_item(GameData *game, int index) {
  for (int i = index; i < game->inventory_count - 1; i++) {
    game->inventory[i] = game->inventory[i + 1];
  }
  game->inventory_count--;
}

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
  int cheat_choice;
  scanf("%d", &cheat_choice);

  switch (cheat_choice) {
  case 1:
    game->player.exp += 5000;
    printf("已添加5000点经验！\n");
    if (game->player.exp >= game->player.level * 100) {
      level_up(game);
    }
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
    if (game->player.mp > game->player.max_mp) {
      game->player.mp = game->player.max_mp;
    }
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
    break;
  default:
    printf("无效的选择。\n");
    main_menu(game);
  }

  return;
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

void talk_to_npc(GameData *game) {
  int npc_count = 0;
  int npc_indices[15];

  switch (game->current_location) {
  case 0:                // 瓦纳卡村
    npc_indices[0] = 0;  // 武器商人
    npc_indices[1] = 1;  // 村长
    npc_indices[2] = 2;  // 防具商人
    npc_indices[3] = 3;  // 药剂师
    npc_indices[4] = 16; // 村民
    npc_indices[5] = 17; // 老者
    npc_indices[6] = 18; // 旅店老板
    npc_indices[7] = 19; // 神秘女子
    npc_count = 8;

    break;
  case 4:                // 王城
    npc_indices[0] = 2;  // 防具商人
    npc_indices[1] = 3;  // 药剂师
    npc_indices[2] = 4;  // 技能导师
    npc_indices[3] = 5;  // 国王
    npc_indices[4] = 8;  // 铁匠
    npc_indices[5] = 11; // 图书管理员
    npc_count = 6;
    break;
  case 8:               // 精灵之森
    npc_indices[0] = 4; // 技能导师
    npc_indices[1] = 7; // 精灵长老
    npc_count = 2;
    break;
  case 9:                // 海盗港湾
    npc_indices[0] = 0;  // 武器商人
    npc_indices[1] = 6;  // 船长
    npc_indices[2] = 10; // 老渔夫
    npc_count = 3;
    break;
  case 10:               // 火山口
    npc_indices[0] = 12; // 赏金猎人
    npc_count = 1;
    break;
  case 12:               // 黑暗沼泽
    npc_indices[0] = 12; // 赏金猎人
    npc_count = 1;
    break;
  case 13:               // 魔法学院
    npc_indices[0] = 4;  // 技能导师
    npc_indices[1] = 11; // 图书管理员
    npc_indices[2] = 13; // 炼金术士
    npc_indices[3] = 14; // 占卜师
    npc_count = 4;
    break;
  default:
    printf("这里没有能交谈的NPC。\n");
    return;
  }

  printf("==========可以交谈的NPC==========\n");
  for (int i = 0; i < npc_count; i++) {
    printf("%d. %s\n", i + 1, game->npcs[npc_indices[i]].name);
  }
  printf("请选择要交谈的人物：\n");

  int choice;
  scanf("%d", &choice);

  if (choice == 0)
    return;

  choice--;

  if (choice >= 0 && choice < npc_count) {
    int npc_index = npc_indices[choice];

    // 根据恶龙是否被击败显示不同的对话
    if (game->dragon_defeated && (npc_index == 1 || npc_index == 5 ||
                                  npc_index == 16 || npc_index == 19)) {
      // 恶龙被击败后
      switch (npc_index) {
      case 1: // 村长
        printf("\n%s: \"伟大的勇者！你拯救了我们所有人！\"",
               game->npcs[npc_index].name);
        printf("\n%s: \"整个村庄都在庆祝你的胜利！\"",
               game->npcs[npc_index].name);
        break;
      case 5: // 国王
        printf("\n%s: "
               "\"伟大的英雄！您拯救了整个王国！人民将永远铭记你的功绩。\"",
               game->npcs[npc_index].name);
        printf("\n%s: \"王国的和平与繁荣都归功于你！\"",
               game->npcs[npc_index].name);
        printf("\n%s: \"你的事迹将被各地传颂。\"", game->npcs[npc_index].name);
        break;
      case 12: // 赏金猎人
        printf("\n%s:恭喜！你我都圆满完成各自的使命！",
               game->npcs[npc_index].name);
        break;
      case 14: // 占卜师
        printf("\n%s: \"你果然做到了，打破了既定的命运！\"",
               game->npcs[npc_index].name);
        printf("\n%s: \"但你仍需小心前方的道路。\"",
               game->npcs[npc_index].name);
        break;
      case 16: // 村民
        printf("\n%s: \"英雄！感谢你拯救了我们的村庄！\"",
               game->npcs[npc_index].name);
        printf("\n%s: \"你将是我们传说中永远的英雄！\"",
               game->npcs[npc_index].name);
        break;
      case 17: // 老者
        printf("\n%s: \"力量会随岁月流逝，但勇气不会。！\"",
               game->npcs[npc_index].name);
        break;
      case 19: // 神秘女子
        printf("\n%s: \"命运的轨迹已经改变，光明重新回到了这个世界。\"",
               game->npcs[npc_index].name);
        printf("\n%s: \"你的勇气将被永远铭记\"", game->npcs[npc_index].name);
        break;
      }
    } else {
      printf("\n%s: \"%s\"\n", game->npcs[npc_index].name,
             game->npcs[npc_index].dialog);

      for (int i = 0; i < game->npcs[npc_index].additional_dialogs_count; i++) {
        printf("%s: \"%s\"\n", game->npcs[npc_index].name,
               game->npcs[npc_index].additional_dialogs[i]);
      }
    }

    if (npc_index == 18) { // 旅店老板
      printf("\n%s: \"在我的旅店里休息一晚，就能完全恢复你的精力。\"",
             game->npcs[npc_index].name);
      printf("\n是否要休息一晚？(费用: %d金币) (y/n): ",
             game->npcs[npc_index].item_price);
      char rest_choice;
      scanf(" %c", &rest_choice);
      if (rest_choice == 'y' || rest_choice == 'Y') {
        if (game->player.money >= game->npcs[npc_index].item_price) {
          game->player.money -= game->npcs[npc_index].item_price;
          int restore_hp = game->player.max_hp - game->player.hp;
          int restore_mp = game->player.max_mp - game->player.mp;
          game->player.hp = game->player.max_hp;
          game->player.mp = game->player.max_mp;
          printf("你在旅店里好好休息了一番...\n");
          printf("恢复了%d点生命值和%d点魔法值！\n", restore_hp, restore_mp);
        } else {
          printf("金币不足！需要%d金币。\n", game->npcs[npc_index].item_price);
        }
      }
    }

    if (npc_index == 0 || npc_index == 2 || npc_index == 3 || npc_index == 8 ||
        npc_index == 9 || npc_index == 13) {
      printf("\n%s愿意与你交易。\n", game->npcs[npc_index].name);
      printf("是否要看看他的商品？(y/n): ");
      char shop_choice;
      scanf(" %c", &shop_choice);
      if (shop_choice == 'y' || shop_choice == 'Y') {
        shop_menu(game, npc_index);
      }
    } else if (npc_index == 4) {
      printf("\n%s可以教你新技能。\n", game->npcs[npc_index].name);
      printf("是否要学习新技能？(y/n): ");
      char learn_choice;
      scanf(" %c", &learn_choice);
      if (learn_choice == 'y' || learn_choice == 'Y') {
        learn_skills(game);
      }
    }
  } else {
    printf("无效的选择。\n");
  }
}

void show_inventory(GameData *game) {
  printf("\n========== 背包 ==========\n");
  if (game->inventory_count == 0) {
    printf("背包是空的。\n");
  } else {
    for (int i = 0; i < game->inventory_count; i++) {
      printf("%d. %s", i + 1, game->inventory[i].name);
      switch (game->inventory[i].type) {
      case 0:
        printf(" (武器: +%d攻击)", game->inventory[i].value);
        break;
      case 1:
        printf(" (防具: +%d防御)", game->inventory[i].value);
        break;
      case 2:
        printf(" (消耗品: 恢复%d HP)", game->inventory[i].value);
        break;
      }
      printf("\n");
    }
  }
  printf("========================\n");
}

void use_item(GameData *game) {
  if (game->inventory_count == 0) {
    printf("背包是空的。\n");
    return;
  }

  show_inventory(game);
  printf("请选择要使用的物品 (输入编号，0取消): ");

  int choice;
  scanf("%d", &choice);

  if (choice == 0)
    return;

  choice--;

  if (choice >= 0 && choice < game->inventory_count) {
    Item *item = &game->inventory[choice];

    switch (item->type) {
    case 0: // 武器 - 直接从背包移除
      game->player.attack += item->value;
      printf("你装备了%s，攻击力增加了%d点！当前总攻击力: %ld\n", item->name,
             item->value, game->player.attack);
      remove_inventory_item(game, choice);
      break;

    case 1: // 防具 - 也直接从背包移除
      game->player.defense += item->value;
      printf("你装备了%s，防御力增加了%d点！当前总防御力: %ld\n", item->name,
             item->value, game->player.defense);
      remove_inventory_item(game, choice);
      break;
    case 2: // 消耗品
      if (strcmp(item->name, "力量药剂") == 0) {
        game->player.attack += 5;
        printf("你使用了%s，永久增加了5点攻击力！\n", item->name);
      } else if (strcmp(item->name, "敏捷药剂") == 0) {
        game->player.agility += 5;
        printf("你使用了%s，永久增加了5点敏捷！\n", item->name);
      } else if (strcmp(item->name, "智力药剂") == 0) {
        game->player.intelligence += 5;
        game->player.max_mp += 20;
        game->player.mp += 20;
        if (game->player.mp > game->player.max_mp) {
          game->player.mp = game->player.max_mp;
        }
        printf("你使用了%s，永久增加了5点智力和20点最大魔法值！\n", item->name);
      } else {
        game->player.hp += item->value;
        if (game->player.hp > game->player.max_hp) {
          game->player.hp = game->player.max_hp;
        }
        printf("你使用了%s，恢复了%d点生命值！\n", item->name, item->value);
      }
      break;
    }

    remove_inventory_item(game, choice);
  } else {
    printf("无效的选择。\n");
  }
}

void shop_menu(GameData *game, int npc_index) {
  Npc *npc = &game->npcs[npc_index];

  printf("\n========== %s的商店 ==========\n", npc->name);
  for (int i = 0; i < npc->shop_item_count; i++) {
    int item_index = npc->shop_items[i];
    Item *item = &game->items[item_index];
    printf("%d. %s - %d金币 ", i + 1, item->name, item->price);
    switch (item->type) {
    case 0:
      printf("(武器: +%d攻击)", item->value);
      break;
    case 1:
      printf("(防具: +%d防御)", item->value);
      break;
    case 2:
      printf("(消耗品: 恢复%d HP)", item->value);
      break;
    }
    printf("\n");
  }
  printf("你有%ld金币。\n", game->player.money);
  printf("请选择要购买的物品 (0返回): ");

  int choice;
  scanf("%d", &choice);

  if (choice == 0)
    return;

  choice--;

  if (choice >= 0 && choice < npc->shop_item_count) {
    int item_index = npc->shop_items[choice];
    Item *item = &game->items[item_index];

    if (game->player.money >= item->price) {
      if (game->inventory_count < MAX_INVENTORY) {
        game->player.money -= item->price;
        game->inventory[game->inventory_count] = *item;
        game->inventory_count++;
        printf("你购买了%s！\n", item->name);
      } else {
        printf("背包已满！\n");
      }
    } else {
      printf("金币不足！\n");
    }
  } else {
    printf("无效的选择。\n");
  }
}

void learn_skills(GameData *game) {
  printf("\n========== 可学习的技能 ==========\n");
  int available_skills = 0;
  int available_skill_indices[MAX_SKILLS];

  for (int i = 0; i < MAX_SKILLS && i < 19; i++) {
    int learned = 0;
    // 检查技能是否已学会
    for (int j = 0; j < game->learned_skill_count; j++) {
      if (game->learned_skills[j] == i) {
        learned = 1;
        break;
      }
    }

    if (!learned && game->player.level >= game->skills[i].required_level) {
      printf("%d. %s (需要等级: %d)", available_skills + 1,
             game->skills[i].name, game->skills[i].required_level);

      if (game->skills[i].damage > 0) {
        printf(" - 造成%d点伤害", game->skills[i].damage);
      }
      if (game->skills[i].heal > 0) {
        printf(" - 恢复%d点生命", game->skills[i].heal);
      }
      printf("\n");

      available_skill_indices[available_skills] = i;
      available_skills++;
    }
  }

  if (available_skills == 0) {
    printf("当前没有可学习的新技能。\n");
    return;
  }
  printf("请选择要学习的技能 (0返回): ");
  int choice;
  scanf("%d", &choice);

  if (choice == 0)
    return;

  if (choice > 0 && choice <= available_skills) {
    int skill_index = available_skill_indices[choice - 1];
    if (game->learned_skill_count < MAX_SKILLS) {
      game->learned_skills[game->learned_skill_count] = skill_index;
      game->learned_skill_count++;
      printf("你学会了新技能：%s！\n", game->skills[skill_index].name);
    } else {
      printf("技能栏已满！\n");
    }
  } else {
    printf("无效的选择。\n");
  }
}