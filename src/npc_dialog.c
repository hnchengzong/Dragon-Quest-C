#include "./include/npc_dialog.h"
#include "./include/menu_and_cheat.h"
#include "./include/shop.h"
#include <stdio.h>

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
