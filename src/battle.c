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
    printf("生命值 +%d，魔法值 +%d  ", 20, 10);
    printf("攻击力 +%d，防御力 +%d  ", 5, 2);
    printf("敏捷 +%d，智力 +%d\n", 3, 2);
  }
}

int calculate_damage(int attacker_attack, int defender_defense) {
  int base_damage = attacker_attack - (defender_defense / 2);
  if (base_damage < 1)
    base_damage = 1;

  int variance = base_damage / 4;
  if (variance < 1)
    variance = 1;

  int final_damage = base_damage + (rand() % (variance * 2)) - variance;
  if (final_damage < 1)
    final_damage = 1;

  return final_damage;
}

int estimate_enemy_level(Enemy *enemy) {

  // 基于敌人的综合属性估算等级，综合考虑HP和攻击
  int power_score = (enemy->hp + enemy->attack * 10) / 50;
  int estimated_level = power_score;
  if (estimated_level < 1)
    estimated_level = 1;

  return estimated_level;
}

void show_ending(GameData *game) {
  printf("\n=====================================\n");
  printf("                结局\n");
  printf("=====================================\n");
  printf("经过一番激烈的战斗，你终于击败了恶龙！\n");
  printf("王国重新恢复了和平，人民不再生活在恐惧中。\n");
  printf("你的名字将被永远铭记在历史中，成为传说中的英雄！\n");
  printf("感谢您的游玩！\n");
  printf("=====================================\n");
}
void battle(GameData *game) {
  // 如果恶龙已被击败
  if (game->dragon_defeated && game->current_location == 3) {
    printf("恶龙已经被你击败了，龙之城堡现在是一片废墟。\n");
    return;
  }

  int enemy_type;
  switch (game->current_location) {
  case 0: // 村庄
    printf("村庄里没有敌人。\n");
    return;
  case 1: // 森林 - 哥布林、狼或毒蛇
    enemy_type = rand() % 3;
    if (enemy_type == 2)
      enemy_type = 11; // 毒蛇
    break;
  case 2: // 洞穴 - 骷髅战士或木乃伊
    enemy_type = (rand() % 2) ? 2 : 16;
    break;
  case 3: // 城堡 - 恶龙
    enemy_type = 3;
    break;
  case 4: // 王城 - 安全
    printf("在王城里很安全，没有敌人。\n");
    return;
  case 5: // 沙漠绿洲 - 沙漠蝎子
    enemy_type = 4;
    break;
  case 6: // 雪山之巅 - 雪怪或冰霜巨龙
    enemy_type = (rand() % 2) ? 5 : 17;
    break;
  case 7: // 地下城 - 石像鬼或恶魔
    enemy_type = 8 + (rand() % 2);
    break;
  case 8: // 精灵之森 - 精灵法师
    enemy_type = (rand() % 2) ? 7 : 16;
    break;
  case 9: // 海盗港湾 - 海盗
    enemy_type = 6;
    break;
  case 10: // 火山口 - 火焰巨人或熔岩元素
    enemy_type = (rand() % 2) ? 10 : 19;
    break;
  case 11: // 古代遗迹 - 堕天使或混沌体或虚空行者
    enemy_type = (rand() % 3) + 21;
    break;
  case 12: // 黑暗沼泽 - 幽灵或石头人或黑暗法师
    enemy_type = (rand() % 2) ? 11 : 12;
    break;
  case 13: // 魔法学院
    printf("魔法学院里没有敌人。\n");
    return;
  case 14: // 幽灵船 - 幽灵或刺客
    enemy_type = (rand() % 2) ? 12 : 18;
    break;

  case 15: // 决斗场 - 奥赛罗
    enemy_type = 24;
    break;
  default:
    enemy_type = rand() % 10;
  }

  Enemy enemy = game->enemies[enemy_type];
  printf("\n遭遇了%s！\n", enemy.name);

  while (game->player.hp > 0 && enemy.hp > 0) {
    int choice, damage;

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

    if (scanf("%d", &choice) != 1) {
      while (getchar() != '\n')
        ;
      printf("输入无效，请输入数字。\n");
      continue;
    }

    switch (choice) {
    case 1: // 普通攻击
      damage = calculate_damage(game->player.attack, enemy.defense);
      enemy.hp -= damage;
      printf("你对%s造成了%d点伤害！\n", enemy.name, damage);
      // 击败恶龙
      if (enemy_type == 3 && enemy.hp <= 0 && !game->dragon_defeated) {
        printf("你击败了%s！\n", enemy.name);
        game->player.exp += enemy.exp_reward;
        game->player.money += enemy.money_reward;
        printf("获得了%d经验值和%d金币！\n", enemy.exp_reward,
               enemy.money_reward);

        game->dragon_defeated = 1;

        show_ending(game);

        if (game->player.exp >= game->player.level * 100) {
          level_up(game);
        }

        return;
      }

      if (enemy.hp <= 0) {
        printf("你击败了%s！\n", enemy.name);
        game->player.exp += enemy.exp_reward;
        game->player.money += enemy.money_reward;
        printf("获得了%d经验值和%d金币！\n", enemy.exp_reward,
               enemy.money_reward);

        if (game->player.exp >= game->player.level * 100) {
          level_up(game);
        }
        return;
      }
      break;

    case 2: // 使用技能
    {
      printf("\n可用技能:\n");
      int skill_count = 0;
      int available_skills[20];

      for (int i = 0; i < game->learned_skill_count; i++) {
        int skill_index = game->learned_skills[i];
        Skill *skill = &game->skills[skill_index];

        if (game->player.level >= skill->required_level) {
          if (game->player.mp >= skill->mp_cost) {
            printf("%d. %s (消耗%d MP)\n", skill_count + 1, skill->name,
                   skill->mp_cost);
          } else {
            printf("%d. %s (消耗%d MP) [MP不足]\n", skill_count + 1,
                   skill->name, skill->mp_cost);
          }
          available_skills[skill_count] = skill_index;
          skill_count++;
        }
      }

      if (skill_count == 0) {
        printf("你目前没有可以使用的技能！\n");
        continue;
      }

      printf("请选择技能 (0返回): ");
      int skill_choice;
      scanf("%d", &skill_choice);

      if (skill_choice == 0)
        continue;

      skill_choice--;

      if (skill_choice >= 0 && skill_choice < skill_count) {
        Skill *skill = &game->skills[available_skills[skill_choice]];

        if (game->player.mp >= skill->mp_cost) {
          game->player.mp -= skill->mp_cost;

          int base_damage =
              skill->damage + game->player.attack; // 技能伤害+玩家攻击
          int intelligence_bonus =
              game->player.intelligence / 2; // 智力每2点增加1点技能伤害
          damage = base_damage + intelligence_bonus;

          enemy.hp -= damage;
          printf("你使用%s对%s造成了%d点伤害！(技能伤害%d + 攻击力%ld + "
                 "智力加成%d)\n",
                 skill->name, enemy.name, damage, skill->damage,
                 game->player.attack, intelligence_bonus);

          if (skill->heal > 0) {
            int heal_amount = skill->heal;
            game->player.hp += heal_amount;
            if (game->player.hp > game->player.max_hp) {
              game->player.hp = game->player.max_hp;
            }
            printf("你使用%s恢复了%d点生命值！\n", skill->name, heal_amount);
          }

          // 击败恶龙
          if (enemy_type == 3 && enemy.hp <= 0 && !game->dragon_defeated) {
            printf("你击败了%s！\n", enemy.name);
            game->player.exp += enemy.exp_reward;
            game->player.money += enemy.money_reward;
            printf("获得了%d经验值和%d金币！\n", enemy.exp_reward,
                   enemy.money_reward);

            game->dragon_defeated = 1;

            show_ending(game);

            if (game->player.exp >= game->player.level * 100) {
              level_up(game);
            }

            return;
          }

          if (enemy.hp <= 0) {
            printf("你击败了%s！\n", enemy.name);
            game->player.exp += enemy.exp_reward;
            game->player.money += enemy.money_reward;
            printf("获得了%d经验值和%d金币！\n", enemy.exp_reward,
                   enemy.money_reward);

            if (game->player.exp >= game->player.level * 100) {
              level_up(game);
            }
            return;
          }
        } else {
          printf("MP不足，无法使用此技能！\n");
          continue;
        }
      } else {
        printf("无效的技能选择。\n");
        continue;
      }
    } break;

    case 3: // 逃跑
      if (enemy_type == 3) {
        printf("恶龙的强大气息让你无法移动！\n");
      } else {
        int enemy_level = estimate_enemy_level(&enemy);

        // 根据等级与敌人等级差计算逃跑率
        int escape_chance = 50 + (game->player.level - enemy_level) * 5;

        escape_chance += (game->player.agility / 10) * 5;

        if (escape_chance < 10)
          escape_chance = 10;
        if (escape_chance > 90)
          escape_chance = 90;

        if (rand() % 100 < escape_chance) {
          printf("你成功逃跑了！(逃跑率: %d%%)\n", escape_chance);
          return;
        } else {
          printf("逃跑失败！(逃跑率: %d%%)\n", escape_chance);
        }
      }
      break;

    default:
      printf("无效的选择。\n");
      continue;
    }

    if (enemy.hp > 0) {
      int enemy_level = estimate_enemy_level(&enemy);
      int dodge_chance = (game->player.agility / 5 - enemy_level);
      if (dodge_chance > 90)
        dodge_chance = 90;
      if (dodge_chance < 0)
        dodge_chance = 0;

      if (rand() % 100 < dodge_chance) {
        printf("%s试图攻击你，但你敏捷地闪避开了！(闪避率: %d%%)\n", enemy.name,
               dodge_chance);
      } else {
        int damage = calculate_damage(enemy.attack, game->player.defense);
        game->player.hp -= damage;
        printf("%s对你造成了%d点伤害！\n", enemy.name, damage);
      }

      if (game->player.hp <= 0) {
        printf("你被%s击败了...\n", enemy.name);
        printf("游戏结束！\n");
        exit(0);
      }
    }
  }
}