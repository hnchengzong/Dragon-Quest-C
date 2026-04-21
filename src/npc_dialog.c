#include "./include/npc_dialog.h"
#include "./include/menu_and_cheat.h"
#include "./include/shop.h"
#include <stdio.h>
#include <stdlib.h>

static void show_npc_dialog(GameData *game, int npc_index) {
  if (game->dragon_defeated) {
    switch (npc_index) {
    case 1:
      printf("\n%s: \"伟大的勇者！你拯救了我们所有人！\"", game->npcs[npc_index].name);
      printf("\n%s: \"整个村庄都在庆祝你的胜利！\"", game->npcs[npc_index].name);
      return;
    case 5:
      printf("\n%s: \"伟大的英雄！您拯救了整个王国！人民将永远铭记你的功绩。\"", game->npcs[npc_index].name);
      printf("\n%s: \"王国的和平与繁荣都归功于你！\"", game->npcs[npc_index].name);
      printf("\n%s: \"你的事迹将被各地传颂。\"", game->npcs[npc_index].name);
      return;
    case 12:
      printf("\n%s:恭喜！你我都圆满完成各自的使命！", game->npcs[npc_index].name);
      return;
    case 14:
      printf("\n%s: \"你果然做到了，打破了既定的命运！\"", game->npcs[npc_index].name);
      printf("\n%s: \"但你仍需小心前方的道路。\"", game->npcs[npc_index].name);
      return;
    case 16:
      printf("\n%s: \"英雄！感谢你拯救了我们的村庄！\"", game->npcs[npc_index].name);
      printf("\n%s: \"你将是我们传说中永远的英雄！\"", game->npcs[npc_index].name);
      return;
    case 17:
      printf("\n%s: \"力量会随岁月流逝，但勇气不会。\"", game->npcs[npc_index].name);
      return;
    case 19:
      printf("\n%s: \"命运的轨迹已经改变，光明重新回到了这个世界。\"", game->npcs[npc_index].name);
      printf("\n%s: \"你的勇气将被永远铭记\"", game->npcs[npc_index].name);
      return;
    }
  }

  printf("\n%s: \"%s\"\n", game->npcs[npc_index].name, game->npcs[npc_index].dialog);

  for (int i = 0; i < game->npcs[npc_index].additional_dialogs_count; i++)
    printf("%s: \"%s\"\n", game->npcs[npc_index].name,
           game->npcs[npc_index].additional_dialogs[i]);
}

static void handle_inn(GameData *game, int npc_index) {
  printf("\n%s: \"在我的旅店里休息一晚，就能完全恢复你的精力。\"",
         game->npcs[npc_index].name);
  printf("\n是否要休息一晚？(费用: %d金币) (y/n): ",
         game->npcs[npc_index].item_price);

  char choice;
  scanf(" %c", &choice);
  if (choice != 'y' && choice != 'Y')
    return;

  if (game->player.money < game->npcs[npc_index].item_price) {
    printf("金币不足！需要%d金币。\n", game->npcs[npc_index].item_price);
    return;
  }

  game->player.money -= game->npcs[npc_index].item_price;
  int restore_hp = game->player.max_hp - game->player.hp;
  int restore_mp = game->player.max_mp - game->player.mp;
  game->player.hp = game->player.max_hp;
  game->player.mp = game->player.max_mp;

  printf("你在旅店里好好休息了一番...\n");
  printf("恢复了%d点生命值和%d点魔法值！\n", restore_hp, restore_mp);
}

static void handle_shop(GameData *game, int npc_index) {
  printf("\n%s愿意与你交易。\n", game->npcs[npc_index].name);
  printf("是否要看看他的商品？(y/n): ");

  char choice;
  scanf(" %c", &choice);
  if (choice == 'y' || choice == 'Y')
    shop_menu(game, npc_index);
}

static void handle_skill_learn(GameData *game, int npc_index) {
  printf("\n%s可以教你新技能。\n", game->npcs[npc_index].name);
  printf("是否要学习新技能？(y/n): ");

  char choice;
  scanf(" %c", &choice);
  if (choice == 'y' || choice == 'Y')
    learn_skills(game);
}

typedef void (*NpcAction)(GameData *, int);

static NpcAction get_npc_action(int behavior) {
  switch (behavior) {
  case NPC_INN:
    return handle_inn;
  case NPC_SHOP:
    return handle_shop;
  case NPC_SKILL:
    return handle_skill_learn;
  default:
    return NULL;
  }
}

void talk_to_npc(GameData *game) {
  int npc_count = 0;
  int npc_indices[15];

  switch (game->current_location) {
  case 0:
    npc_indices[0] = 0;
    npc_indices[1] = 1;
    npc_indices[2] = 2;
    npc_indices[3] = 3;
    npc_indices[4] = 16;
    npc_indices[5] = 17;
    npc_indices[6] = 18;
    npc_indices[7] = 19;
    npc_count = 8;
    break;
  case 4:
    npc_indices[0] = 2;
    npc_indices[1] = 3;
    npc_indices[2] = 4;
    npc_indices[3] = 5;
    npc_indices[4] = 8;
    npc_indices[5] = 11;
    npc_count = 6;
    break;
  case 8:
    npc_indices[0] = 4;
    npc_indices[1] = 7;
    npc_count = 2;
    break;
  case 9:
    npc_indices[0] = 0;
    npc_indices[1] = 6;
    npc_indices[2] = 10;
    npc_count = 3;
    break;
  case 10:
  case 12:
    npc_indices[0] = 12;
    npc_count = 1;
    break;
  case 13:
    npc_indices[0] = 4;
    npc_indices[1] = 11;
    npc_indices[2] = 13;
    npc_indices[3] = 14;
    npc_count = 4;
    break;
  default:
    printf("这里没有能交谈的NPC。\n");
    return;
  }

  printf("==========可以交谈的NPC==========\n");
  for (int i = 0; i < npc_count; i++)
    printf("%d. %s\n", i + 1, game->npcs[npc_indices[i]].name);

  printf("请选择要交谈的人物：\n");
  int choice;
  scanf("%d", &choice);

  if (choice == 0)
    return;

  choice--;
  if (choice < 0 || choice >= npc_count) {
    printf("无效的选择。\n");
    return;
  }

  int npc_index = npc_indices[choice];
  show_npc_dialog(game, npc_index);

  NpcAction action = get_npc_action(game->npcs[npc_index].behavior);
  if (action)
    action(game, npc_index);
}
