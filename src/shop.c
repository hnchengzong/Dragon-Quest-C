#include "./include/shop.h"
#include <stdio.h>

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
