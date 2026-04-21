#include "./include/inventory.h"
#include <stdio.h>
#include <string.h>

static void remove_item(GameData *game, int index) {
  for (int i = index; i < game->inventory_count - 1; i++)
    game->inventory[i] = game->inventory[i + 1];
  game->inventory_count--;
}

void show_inventory(GameData *game) {
  printf("\n========== 背包 ==========\n");
  if (game->inventory_count == 0) {
    printf("背包是空的。\n");
    return;
  }

  for (int i = 0; i < game->inventory_count; i++) {
    printf("%d. %s", i + 1, game->inventory[i].name);
    switch (game->inventory[i].type) {
    case ITEM_WEAPON:
      printf(" (武器: +%d攻击)", game->inventory[i].value);
      break;
    case ITEM_ARMOR:
      printf(" (防具: +%d防御)", game->inventory[i].value);
      break;
    case ITEM_CONSUMABLE:
      printf(" (消耗品: 恢复%d HP)", game->inventory[i].value);
      break;
    }
    printf("\n");
  }
  printf("========================\n");
}

static void use_consumable(GameData *game, Item *item) {
  if (strcmp(item->name, "力量药剂") == 0) {
    game->player.attack += 5;
    printf("你使用了%s，永久增加了5点攻击力！\n", item->name);
    return;
  }

  if (strcmp(item->name, "敏捷剂") == 0) {
    game->player.agility += 5;
    printf("你使用了%s，永久增加了5点敏捷！\n", item->name);
    return;
  }

  if (strcmp(item->name, "智力药剂") == 0) {
    game->player.intelligence += 5;
    game->player.max_mp += 20;
    game->player.mp += 20;
    if (game->player.mp > game->player.max_mp)
      game->player.mp = game->player.max_mp;
    printf("你使用了%s，永久增加了5点智力和20点最大魔法值！\n", item->name);
    return;
  }

  game->player.hp += item->value;
  if (game->player.hp > game->player.max_hp)
    game->player.hp = game->player.max_hp;
  printf("你使用了%s，恢复了%d点生命值！\n", item->name, item->value);
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
  if (choice < 0 || choice >= game->inventory_count) {
    printf("无效的选择。\n");
    return;
  }

  Item *item = &game->inventory[choice];

  switch (item->type) {
  case 0:
    game->player.attack += item->value;
    printf("你装备了%s，攻击力增加了%d点！当前总攻击力: %ld\n", item->name,
           item->value, game->player.attack);
    break;
  case 1:
    game->player.defense += item->value;
    printf("你装备了%s，防御力增加了%d点！当前总防御力: %ld\n", item->name,
           item->value, game->player.defense);
    break;
  case 2:
    use_consumable(game, item);
    break;
  }

  remove_item(game, choice);
}
