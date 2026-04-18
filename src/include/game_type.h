#pragma once

#define MAX_NAME_LENGTH 60
#define MAX_INVENTORY 30
#define MAX_SKILLS 20
#define MAX_LOCATIONS 30
#define MAX_ENEMIES 30
#define MAX_NPCS 50
#define MAX_SHOP_ITEMS 30

typedef struct {
  char name[MAX_NAME_LENGTH];
  long hp;
  long max_hp;
  long mp;
  long max_mp;
  long exp;
  long level;
  long money;
  long base_attack;    // 基础攻击力
  long base_defense;   // 基础防御力
  long attack;         // 总攻击力（包含装备加成）
  long defense;        // 总防御力（包含装备加成）
  long agility;        // 敏捷，影响闪避和先攻
  long intelligence;   // 智力，影响魔法攻击和魔法值
  int equipped_weapon; // 当前装备的武器索引（-1表示无）
  int equipped_armor;  // 防具索引（-1表示无）
} Player;

typedef struct {
  char name[MAX_NAME_LENGTH];
  int type;  // 0=武器, 1=防具, 2=消耗品
  int value; // 根据类型表示攻击力、防御力、恢复量的数值等
  int price;
} Item;

// 技能
typedef struct {
  char name[MAX_NAME_LENGTH];
  int mp_cost;
  int damage;
  int heal;
  int required_level; // 学习所需等级
} Skill;

// 地点
typedef struct {
  char name[MAX_NAME_LENGTH];
  char description[200];
  int type; // 0=城镇, 1=野外, 2=洞穴等
} Location;

// 敌人
typedef struct {
  char name[MAX_NAME_LENGTH];
  int hp;
  int max_hp;
  int attack;
  int defense;
  int exp_reward;
  int money_reward;
} Enemy;

// 任务
typedef struct {
  int id;
  char name[MAX_NAME_LENGTH];
  char description[200];
  int completed;  // 是否完成 (0=未完成, 1=完成)
  int reward_exp; // 奖励
  int reward_gold;
  int reward_item;
} Quest;

// NPC
typedef struct {
  char name[MAX_NAME_LENGTH];
  char dialog[200];
  char additional_dialogs[5][200]; // 添加额外对话
  int additional_dialogs_count;
  int item_to_sell; // -1表示不卖物品
  int item_price;
  int shop_items[MAX_SHOP_ITEMS];
  int shop_item_count;
} Npc;

// 游戏数据
typedef struct {
  Player player;
  Item inventory[MAX_INVENTORY];
  Skill skills[MAX_SKILLS];
  Location locations[MAX_LOCATIONS];
  Enemy enemies[MAX_ENEMIES];
  Npc npcs[MAX_NPCS];
  Item items[MAX_INVENTORY];
  Quest quests[10];
  int dragon_defeated; // 恶龙是否被击败
  int current_location;
  int inventory_count;
  int learned_skills[MAX_SKILLS]; // 已学习技能
  int learned_skill_count;
} GameData;

typedef void (*MenuAction)(GameData *game);

typedef struct {
  int choice;
  const char *description;
  MenuAction action;
} MenuItem;
