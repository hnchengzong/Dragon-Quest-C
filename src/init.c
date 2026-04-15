#include "./include/init.h"
#include <stdio.h>
#include <string.h>

void init_game(GameData *game) {
  init_player(&game->player);
  init_world(game);
  game->current_location = 0;
  game->inventory_count = 0;
  game->learned_skill_count = 2; // 已学习技能
  game->learned_skills[0] = 0;
  game->learned_skills[1] = 1;

  strcpy(game->inventory[0].name, "铁剑");
  game->inventory[0].type = 0;
  game->inventory[0].value = 10;
  game->inventory_count++;

  strcpy(game->inventory[1].name, "皮甲");
  game->inventory[1].type = 1;
  game->inventory[1].value = 5;
  game->inventory_count++;

  strcpy(game->inventory[2].name, "生命药水");
  game->inventory[2].type = 2;
  game->inventory[2].value = 50;
  game->inventory_count++;
}

void init_player(Player *player) {
  printf("请输入你的名字: ");
  scanf("%59s", player->name);

  player->hp = 120;
  player->max_hp = 120;
  player->mp = 60;
  player->max_mp = 60;
  player->exp = 0;
  player->level = 1;
  player->money = 20;
  player->base_attack = 15;
  player->base_defense = 5;
  player->attack = 15;
  player->defense = 5;
  player->intelligence = 8;
  player->agility = 5;
  player->equipped_weapon = -1; // 未装备武器
  player->equipped_armor = -1;  // 未装备防具
}

void init_world(GameData *game) {
  strcpy(game->locations[0].name, "瓦纳卡村");
  strcpy(game->locations[0].description,
         "一个宁静的小村庄，承载了你儿时的记忆，是你冒险旅程的起点。");
  game->locations[0].type = 0;

  strcpy(game->locations[1].name, "野外森林");
  strcpy(game->locations[1].description, "野外的森林，经常有怪物出没。");
  game->locations[1].type = 1;

  strcpy(game->locations[2].name, "洞穴");
  strcpy(game->locations[2].description, "阴森的洞穴。");
  game->locations[2].type = 2;

  strcpy(game->locations[3].name, "龙巢");
  strcpy(game->locations[3].description, "恶龙的巢穴，最终决战的地方。");
  game->locations[3].type = 3;

  strcpy(game->locations[4].name, "王城");
  strcpy(game->locations[4].description, "王国的首都。");
  game->locations[4].type = 4;

  strcpy(game->locations[5].name, "沙漠绿洲");
  strcpy(game->locations[5].description, "沙漠中的绿洲，可以休息。");
  game->locations[5].type = 5;

  strcpy(game->locations[6].name, "雪山");
  strcpy(game->locations[6].description,
         "寒冷的雪山，据说藏着宝藏，但有雪怪出没。");
  game->locations[6].type = 6;

  strcpy(game->locations[7].name, "地下城");
  strcpy(game->locations[7].description, "古老的地下城，充满了危险与机遇。");
  game->locations[7].type = 7;

  strcpy(game->locations[8].name, "精灵之森");
  strcpy(game->locations[8].description, "精灵居住的森林。也潜伏着黑暗");
  game->locations[8].type = 8;

  strcpy(game->locations[9].name, "海盗港湾");
  strcpy(game->locations[9].description, "海盗聚集的港湾。");
  game->locations[9].type = 9;

  strcpy(game->locations[10].name, "火山口");
  strcpy(game->locations[10].description, "炽热的火山地带。");
  game->locations[10].type = 10;

  strcpy(game->locations[11].name, "古代遗迹");
  strcpy(game->locations[11].description, "失落文明的遗迹，（难度较高）");
  game->locations[11].type = 11;

  strcpy(game->locations[12].name, "黑暗沼泽");
  strcpy(game->locations[12].description, "阴暗潮湿的沼泽地。");
  game->locations[12].type = 12;

  strcpy(game->locations[13].name, "魔法学院");
  strcpy(game->locations[13].description, "学习高级魔法的学府。");
  game->locations[13].type = 13;

  strcpy(game->locations[14].name, "幽灵之地");
  strcpy(game->locations[14].description, "充满了幽灵的森林。");
  game->locations[14].type = 14;

  strcpy(game->locations[15].name, "决斗场");
  strcpy(game->locations[15].description, "与英雄决斗的场地。（难度较高）");
  game->locations[15].type = 15;

  // ---------------物品------------------
  strcpy(game->items[0].name, "铁剑");
  game->items[0].type = 0;
  game->items[0].value = 10;
  game->items[0].price = 50;

  strcpy(game->items[1].name, "皮甲");
  game->items[1].type = 1;
  game->items[1].value = 5;
  game->items[1].price = 30;

  strcpy(game->items[2].name, "生命药水");
  game->items[2].type = 2;
  game->items[2].value = 50;
  game->items[2].price = 20;

  strcpy(game->items[3].name, "钢剑");
  game->items[3].type = 0;
  game->items[3].value = 320;
  game->items[3].price = 3200;

  strcpy(game->items[4].name, "锁子甲");
  game->items[4].type = 1;
  game->items[4].value = 800;
  game->items[4].price = 2000;

  strcpy(game->items[5].name, "高级生命药水");
  game->items[5].type = 2;
  game->items[5].value = 2000;
  game->items[5].price = 400;

  strcpy(game->items[6].name, "魔法药水");
  game->items[6].type = 2;
  game->items[6].value = 400;
  game->items[6].price = 800;

  strcpy(game->items[7].name, "双手剑");
  game->items[7].type = 0;
  game->items[7].value = 4567;
  game->items[7].price = 8000;

  strcpy(game->items[8].name, "板甲");
  game->items[8].type = 1;
  game->items[8].value = 40;
  game->items[8].price = 500;

  strcpy(game->items[9].name, "超级生命药水");
  game->items[9].type = 2;
  game->items[9].value = 16000;
  game->items[9].price = 1000;

  strcpy(game->items[10].name, "传说之剑");
  game->items[10].type = 0;
  game->items[10].value = 8000;
  game->items[10].price = 24000;

  strcpy(game->items[11].name, "龙鳞甲");
  game->items[11].type = 1;
  game->items[11].value = 4000;
  game->items[11].price = 24000;

  strcpy(game->items[12].name, "短剑");
  game->items[12].type = 0;
  game->items[12].value = 13;
  game->items[12].price = 100;

  strcpy(game->items[13].name, "长矛");
  game->items[13].type = 0;
  game->items[13].value = 40;
  game->items[13].price = 400;

  strcpy(game->items[14].name, "战斧");
  game->items[14].type = 0;
  game->items[14].value = 80;
  game->items[14].price = 800;

  strcpy(game->items[15].name, "精灵弓");
  game->items[15].type = 0;
  game->items[15].value = 180;
  game->items[15].price = 1800;

  strcpy(game->items[16].name, "法杖");
  game->items[16].type = 0;
  game->items[16].value = 320;
  game->items[16].price = 2800;

  strcpy(game->items[17].name, "布衣");
  game->items[17].type = 1;
  game->items[17].value = 3;
  game->items[17].price = 60;

  strcpy(game->items[18].name, "布甲");
  game->items[18].type = 1;
  game->items[18].value = 12;
  game->items[18].price = 120;

  strcpy(game->items[19].name, "链甲");
  game->items[19].type = 1;
  game->items[19].value = 120;
  game->items[19].price = 800;

  strcpy(game->items[20].name, "骑士铠甲");
  game->items[20].type = 1;
  game->items[20].value = 600;
  game->items[20].price = 2400;

  strcpy(game->items[21].name, "法师之袍");
  game->items[21].type = 1;
  game->items[21].value = 879;
  game->items[21].price = 3000;

  strcpy(game->items[23].name, "中级生命药水");
  game->items[23].type = 2;
  game->items[23].value = 800;
  game->items[23].price = 200;

  strcpy(game->items[24].name, "高级魔法药水");
  game->items[24].type = 2;
  game->items[24].value = 1000;
  game->items[24].price = 1800;

  strcpy(game->items[26].name, "力量药剂");
  game->items[26].type = 2;
  game->items[26].value = 0;
  game->items[26].price = 800;

  strcpy(game->items[27].name, "敏捷药剂");
  game->items[27].type = 2;
  game->items[27].value = 0;
  game->items[27].price = 800;

  strcpy(game->items[28].name, "智力药剂");
  game->items[28].type = 2;
  game->items[28].value = 0;
  game->items[28].price = 800;

  strcpy(game->skills[0].name, "重击");
  game->skills[0].mp_cost = 10;
  game->skills[0].damage = 27;
  game->skills[0].heal = 0;
  game->skills[0].required_level = 1;

  strcpy(game->skills[1].name, "治疗");
  game->skills[1].mp_cost = 15;
  game->skills[1].damage = 0;
  game->skills[1].heal = 33;
  game->skills[1].required_level = 1;

  strcpy(game->skills[2].name, "火焰术");
  game->skills[2].mp_cost = 20;
  game->skills[2].damage = 38;
  game->skills[2].heal = 0;
  game->skills[2].required_level = 3;

  strcpy(game->skills[3].name, "冰霜术");
  game->skills[3].mp_cost = 25;
  game->skills[3].damage = 47;
  game->skills[3].heal = 0;
  game->skills[3].required_level = 5;

  strcpy(game->skills[4].name, "惊雷");
  game->skills[4].mp_cost = 55;
  game->skills[4].damage = 93;
  game->skills[4].heal = 0;
  game->skills[4].required_level = 8;

  strcpy(game->skills[5].name, "高效治疗");
  game->skills[5].mp_cost = 60;
  game->skills[5].damage = 0;
  game->skills[5].heal = 300;
  game->skills[5].required_level = 10;

  strcpy(game->skills[6].name, "旋风斩");
  game->skills[6].mp_cost = 60;
  game->skills[6].damage = 155;
  game->skills[6].heal = 0;
  game->skills[6].required_level = 15;

  strcpy(game->skills[7].name, "沐浴");
  game->skills[7].mp_cost = 80;
  game->skills[7].damage = 0;
  game->skills[7].heal = 800;
  game->skills[7].required_level = 25;

  strcpy(game->skills[8].name, "审判");
  game->skills[8].mp_cost = 800;
  game->skills[8].damage = 1800;
  game->skills[8].heal = 0;
  game->skills[8].required_level = 50;

  strcpy(game->skills[9].name, "神之祝福");
  game->skills[9].mp_cost = 200;
  game->skills[9].damage = 0;
  game->skills[9].heal = 1600;
  game->skills[9].required_level = 60;

  strcpy(game->skills[10].name, "突袭");
  game->skills[10].mp_cost = 120;
  game->skills[10].damage = 480;
  game->skills[10].heal = 0;
  game->skills[10].required_level = 60;

  strcpy(game->skills[11].name, "生命汲取");
  game->skills[11].mp_cost = 80;
  game->skills[11].damage = 300;
  game->skills[11].heal = 300;
  game->skills[11].required_level = 30;

  strcpy(game->skills[12].name, "冻结之魔弹");
  game->skills[12].mp_cost = 140;
  game->skills[12].damage = 800;
  game->skills[12].heal = 0;
  game->skills[12].required_level = 65;

  strcpy(game->skills[13].name, "雷霆之威严");
  game->skills[13].mp_cost = 300;
  game->skills[13].damage = 2000;
  game->skills[13].heal = 0;
  game->skills[13].required_level = 70;

  strcpy(game->skills[14].name, "旋风斩");
  game->skills[14].mp_cost = 300;
  game->skills[14].damage = 600;
  game->skills[14].heal = 0;
  game->skills[14].required_level = 40;

  strcpy(game->skills[15].name, "回溯");
  game->skills[15].mp_cost = 1200;
  game->skills[15].damage = 0;
  game->skills[15].heal = 18000;
  game->skills[15].required_level = 75;

  strcpy(game->skills[16].name, "风暴");
  game->skills[16].mp_cost = 700;
  game->skills[16].damage = 3300;
  game->skills[16].heal = 0;
  game->skills[16].required_level = 80;

  strcpy(game->skills[17].name, "万剑归一");
  game->skills[17].mp_cost = 800;
  game->skills[17].damage = 3900;
  game->skills[17].heal = 0;
  game->skills[17].required_level = 90;

  strcpy(game->skills[18].name, "造物惩击");
  game->skills[18].mp_cost = 1600;
  game->skills[18].damage = 15000;
  game->skills[18].heal = 0;
  game->skills[18].required_level = 100;

  // ---------------敌人-------------------
  strcpy(game->enemies[0].name, "哥布林");
  game->enemies[0].hp = 30;
  game->enemies[0].max_hp = 30;
  game->enemies[0].attack = 10;
  game->enemies[0].defense = 2;
  game->enemies[0].exp_reward = 20;
  game->enemies[0].money_reward = 10;

  strcpy(game->enemies[1].name, "狼");
  game->enemies[1].hp = 40;
  game->enemies[1].max_hp = 40;
  game->enemies[1].attack = 15;
  game->enemies[1].defense = 5;
  game->enemies[1].exp_reward = 30;
  game->enemies[1].money_reward = 15;

  strcpy(game->enemies[2].name, "骷髅战士");
  game->enemies[2].hp = 800;
  game->enemies[2].max_hp = 800;
  game->enemies[2].attack = 250;
  game->enemies[2].defense = 80;
  game->enemies[2].exp_reward = 500;
  game->enemies[2].money_reward = 40;

  strcpy(game->enemies[3].name, "恶龙");
  game->enemies[3].hp = 120000;
  game->enemies[3].max_hp = 120000;
  game->enemies[3].attack = 16000;
  game->enemies[3].defense = 1800;
  game->enemies[3].exp_reward = 50000;
  game->enemies[3].money_reward = 50000;

  strcpy(game->enemies[4].name, "沙漠蝎子");
  game->enemies[4].hp = 440;
  game->enemies[4].max_hp = 440;
  game->enemies[4].attack = 80;
  game->enemies[4].defense = 45;
  game->enemies[4].exp_reward = 100;
  game->enemies[4].money_reward = 40;

  strcpy(game->enemies[5].name, "雪怪");
  game->enemies[5].hp = 1200;
  game->enemies[5].max_hp = 1200;
  game->enemies[5].attack = 90;
  game->enemies[5].defense = 68;
  game->enemies[5].exp_reward = 590;
  game->enemies[5].money_reward = 40;

  strcpy(game->enemies[6].name, "海盗");
  game->enemies[6].hp = 980;
  game->enemies[6].max_hp = 980;
  game->enemies[6].attack = 192;
  game->enemies[6].defense = 29;
  game->enemies[6].exp_reward = 620;
  game->enemies[6].money_reward = 80;

  strcpy(game->enemies[7].name, "精灵法师");
  game->enemies[7].hp = 2600;
  game->enemies[7].max_hp = 2600;
  game->enemies[7].attack = 4600;
  game->enemies[7].defense = 15;
  game->enemies[7].exp_reward = 1000;
  game->enemies[7].money_reward = 90;

  strcpy(game->enemies[8].name, "石像鬼");
  game->enemies[8].hp = 990;
  game->enemies[8].max_hp = 990;
  game->enemies[8].attack = 99;
  game->enemies[8].defense = 99;
  game->enemies[8].exp_reward = 860;
  game->enemies[8].money_reward = 100;

  strcpy(game->enemies[9].name, "恶魔");
  game->enemies[9].hp = 650;
  game->enemies[9].max_hp = 650;
  game->enemies[9].attack = 175;
  game->enemies[9].defense = 60;
  game->enemies[9].exp_reward = 666;
  game->enemies[9].money_reward = 666;

  strcpy(game->enemies[10].name, "火焰巨人");
  game->enemies[10].hp = 400;
  game->enemies[10].max_hp = 400;
  game->enemies[10].attack = 120;
  game->enemies[10].defense = 30;
  game->enemies[10].exp_reward = 460;
  game->enemies[10].money_reward = 180;

  strcpy(game->enemies[11].name, "毒蛇");
  game->enemies[11].hp = 20;
  game->enemies[11].max_hp = 20;
  game->enemies[11].attack = 30;
  game->enemies[11].defense = 7;
  game->enemies[11].exp_reward = 30;
  game->enemies[11].money_reward = 20;

  strcpy(game->enemies[12].name, "幽灵");
  game->enemies[12].hp = 600;
  game->enemies[12].max_hp = 600;
  game->enemies[12].attack = 50;
  game->enemies[12].defense = 80;
  game->enemies[12].exp_reward = 180;
  game->enemies[12].money_reward = 160;

  strcpy(game->enemies[13].name, "石头人");
  game->enemies[13].hp = 8000;
  game->enemies[13].max_hp = 8000;
  game->enemies[13].attack = 20;
  game->enemies[13].defense = 850;
  game->enemies[13].exp_reward = 860;
  game->enemies[13].money_reward = 150;

  strcpy(game->enemies[14].name, "黑暗法师");
  game->enemies[14].hp = 850;
  game->enemies[14].max_hp = 850;
  game->enemies[14].attack = 1280;
  game->enemies[14].defense = 25;
  game->enemies[14].exp_reward = 450;
  game->enemies[14].money_reward = 230;

  strcpy(game->enemies[15].name, "地狱犬");
  game->enemies[15].hp = 800;
  game->enemies[15].max_hp = 800;
  game->enemies[15].attack = 85;
  game->enemies[15].defense = 48;
  game->enemies[15].exp_reward = 480;
  game->enemies[15].money_reward = 160;

  strcpy(game->enemies[16].name, "木乃伊");
  game->enemies[16].hp = 120;
  game->enemies[16].max_hp = 120;
  game->enemies[16].attack = 25;
  game->enemies[16].defense = 20;
  game->enemies[16].exp_reward = 120;
  game->enemies[16].money_reward = 40;

  strcpy(game->enemies[17].name, "冰霜巨龙");
  game->enemies[17].hp = 7200;
  game->enemies[17].max_hp = 7200;
  game->enemies[17].attack = 620;
  game->enemies[17].defense = 660;
  game->enemies[17].exp_reward = 4100;
  game->enemies[17].money_reward = 750;

  strcpy(game->enemies[18].name, "刺客");
  game->enemies[18].hp = 440;
  game->enemies[18].max_hp = 440;
  game->enemies[18].attack = 200;
  game->enemies[18].defense = 20;
  game->enemies[18].exp_reward = 500;
  game->enemies[18].money_reward = 780;

  strcpy(game->enemies[19].name, "熔岩元素");
  game->enemies[19].hp = 660;
  game->enemies[19].max_hp = 660;
  game->enemies[19].attack = 95;
  game->enemies[19].defense = 50;
  game->enemies[19].exp_reward = 320;
  game->enemies[19].money_reward = 300;

  strcpy(game->enemies[20].name, "远古巨魔");
  game->enemies[20].hp = 1000;
  game->enemies[20].max_hp = 1000;
  game->enemies[20].attack = 150;
  game->enemies[20].defense = 80;
  game->enemies[20].exp_reward = 1000;
  game->enemies[20].money_reward = 900;

  strcpy(game->enemies[21].name, "堕天使");
  game->enemies[21].hp = 15000;
  game->enemies[21].max_hp = 15000;
  game->enemies[21].attack = 2000;
  game->enemies[21].defense = 100;
  game->enemies[21].exp_reward = 8500;
  game->enemies[21].money_reward = 1400;

  strcpy(game->enemies[22].name, "混沌体");
  game->enemies[22].hp = 38000;
  game->enemies[22].max_hp = 38000;
  game->enemies[22].attack = 5000;
  game->enemies[22].defense = 300;
  game->enemies[22].exp_reward = 8800;
  game->enemies[22].money_reward = 0;

  strcpy(game->enemies[23].name, "虚空行者");
  game->enemies[23].hp = 12000;
  game->enemies[23].max_hp = 12000;
  game->enemies[23].attack = 8800;
  game->enemies[23].defense = 8000;
  game->enemies[23].exp_reward = 9600;
  game->enemies[23].money_reward = 600;

  strcpy(game->enemies[24].name, "奥赛罗");
  game->enemies[24].hp = 67600;
  game->enemies[24].max_hp = 67600;
  game->enemies[24].attack = 8800;
  game->enemies[24].defense = 6000;
  game->enemies[24].exp_reward = 20000;
  game->enemies[24].money_reward = 3000;

  // -----------NPC-----------------
  strcpy(game->npcs[0].name, "武器商人");
  strcpy(game->npcs[0].dialog, "欢迎光临！看看我的武器吧。");
  game->npcs[0].item_to_sell = -1;
  game->npcs[0].item_price = 0;
  game->npcs[0].shop_items[0] = 0;  // 铁剑
  game->npcs[0].shop_items[1] = 3;  // 钢剑
  game->npcs[0].shop_items[2] = 7;  // 双手剑
  game->npcs[0].shop_items[3] = 12; // 短剑
  game->npcs[0].shop_items[4] = 13; // 院长矛
  game->npcs[0].shop_items[5] = 14; // 战斧
  game->npcs[0].shop_items[6] = 15; // 精灵弓
  game->npcs[0].shop_items[7] = 16; // 法杖
  game->npcs[0].shop_item_count = 8;

  strcpy(game->npcs[1].name, "村长");
  strcpy(game->npcs[1].dialog,
         "勇士，感谢你为我们挺身而出。你一定能击败恶龙！");
  game->npcs[1].item_to_sell = -1;
  game->npcs[1].item_price = 0;
  game->npcs[1].shop_item_count = 0;

  strcpy(game->npcs[2].name, "防具商人");
  strcpy(game->npcs[2].dialog, "高质量的防具能让你在战斗中生存更久。");
  game->npcs[2].item_to_sell = -1;
  game->npcs[2].item_price = 0;
  game->npcs[2].shop_items[0] = 1;  // 皮甲
  game->npcs[2].shop_items[1] = 4;  // 锁子甲
  game->npcs[2].shop_items[2] = 8;  // 板甲
  game->npcs[2].shop_items[3] = 11; // 龙鳞甲
  game->npcs[2].shop_items[4] = 17; // 布衣
  game->npcs[2].shop_items[5] = 18; // 鳞甲
  game->npcs[2].shop_items[6] = 19; // 链甲
  game->npcs[2].shop_items[7] = 20; // 骑士铠甲
  game->npcs[2].shop_items[8] = 21; // 法师袍
  game->npcs[2].shop_item_count = 9;

  strcpy(game->npcs[3].name, "药剂师");
  strcpy(game->npcs[3].dialog, "生命药水和魔法药水，冒险必备！");
  game->npcs[3].item_to_sell = -1;
  game->npcs[3].item_price = 0;
  game->npcs[3].shop_items[0] = 2;  // 生命药水
  game->npcs[3].shop_items[1] = 5;  // 高级生命药水
  game->npcs[3].shop_items[2] = 9;  // 超级生命药水
  game->npcs[3].shop_items[3] = 6;  // 魔法药水
  game->npcs[3].shop_items[4] = 23; // 中级生命药水
  game->npcs[3].shop_items[5] = 24; // 高级魔法药水
  game->npcs[3].shop_items[6] = 26; // 力量药剂
  game->npcs[3].shop_items[7] = 27; // 敏捷药剂
  game->npcs[3].shop_items[8] = 28; // 智力药剂
  game->npcs[3].shop_item_count = 9;

  strcpy(game->npcs[4].name, "技能导师");
  strcpy(game->npcs[4].dialog, "我可以教你更强大的技能，但你需要足够的等级。");
  game->npcs[4].item_to_sell = -1;
  game->npcs[4].item_price = 0;
  game->npcs[4].shop_item_count = 0;

  strcpy(game->npcs[5].name, "国王");
  strcpy(game->npcs[5].dialog, "无畏的勇者，希望你能成功讨伐恶龙！");
  game->npcs[5].item_to_sell = -1;
  game->npcs[5].item_price = 0;
  game->npcs[5].shop_item_count = 0;

  strcpy(game->npcs[6].name, "船长");
  strcpy(game->npcs[6].dialog, "想要出海探险吗？这片海域非常危险。");
  game->npcs[6].item_to_sell = -1;
  game->npcs[6].item_price = 0;
  game->npcs[6].shop_item_count = 0;

  strcpy(game->npcs[7].name, "精灵长老");
  strcpy(game->npcs[7].dialog, "古老的魔法正在消失，我们需要你的帮助。");
  strcpy(game->npcs[7].additional_dialogs[0],
         "很久以前，这片土地上充满了魔法的力量。");
  strcpy(game->npcs[7].additional_dialogs[1],
         "但随着时光流逝，魔法逐渐衰弱，我们需要你的力量来恢复它。");
  game->npcs[7].additional_dialogs_count = 2;
  game->npcs[7].item_to_sell = -1;
  game->npcs[7].item_price = 0;
  game->npcs[7].shop_item_count = 0;

  strcpy(game->npcs[8].name, "铁匠");
  strcpy(game->npcs[8].dialog, "我可以用最好的材料为你打造武器和防具。");
  strcpy(
      game->npcs[8].additional_dialogs[0],
      "我曾经为国王打造过武器，如果你有足够的金币，我可以为你打造任何武器。");
  strcpy(game->npcs[8].additional_dialogs[1],
         "最近，我找到了一些稀有的矿石，可以制作出非常强大的装备。");
  game->npcs[8].additional_dialogs_count = 2;
  game->npcs[8].item_to_sell = -1;
  game->npcs[8].item_price = 0;
  game->npcs[8].shop_items[0] = 7;  // 双手剑
  game->npcs[8].shop_items[1] = 8;  // 板甲
  game->npcs[8].shop_items[2] = 10; // 传说之剑
  game->npcs[8].shop_items[3] = 11; // 龙鳞甲
  game->npcs[8].shop_items[4] = 14; // 战斧
  game->npcs[8].shop_items[5] = 16; // 法杖
  game->npcs[8].shop_items[6] = 20; // 骑士铠甲
  game->npcs[8].shop_item_count = 7;

  strcpy(game->npcs[9].name, "神秘商人");
  strcpy(game->npcs[9].dialog, "我这里有一些奇特的商品，但价格不菲。");
  strcpy(game->npcs[9].additional_dialogs[0],
         "这些商品是从世界各地收集来的，每一件都有独特的用途。");
  strcpy(game->npcs[9].additional_dialogs[1],
         "如果你有足够的金币，我可以卖给你真正强大的物品。");
  game->npcs[9].additional_dialogs_count = 2;
  game->npcs[9].item_to_sell = -1;
  game->npcs[9].item_price = 0;
  game->npcs[9].shop_items[0] = 9;  // 超级生命药水
  game->npcs[9].shop_items[1] = 10; // 传说之剑
  game->npcs[9].shop_items[2] = 11; // 龙鳞甲
  game->npcs[9].shop_items[4] = 26; // 力量药剂
  game->npcs[9].shop_items[5] = 27; // 敏捷药剂
  game->npcs[9].shop_items[6] = 28; // 智力药剂
  game->npcs[9].shop_item_count = 7;

  strcpy(game->npcs[10].name, "老渔夫");
  strcpy(game->npcs[10].dialog, "这片海域隐藏着许多秘密。");
  strcpy(game->npcs[10].additional_dialogs[0],
         "我在这片海上打渔几十年了，见过许多奇怪的事情。");
  strcpy(game->npcs[10].additional_dialogs[1],
         "据说在深海中有一座沉没的城市，但到现在都没人能找到它。");
  game->npcs[10].additional_dialogs_count = 2;
  game->npcs[10].item_to_sell = -1;
  game->npcs[10].item_price = 0;
  game->npcs[10].shop_item_count = 0;

  strcpy(game->npcs[11].name, "图书管理员");
  strcpy(game->npcs[11].dialog, "书籍是知识的源泉。");
  strcpy(game->npcs[11].additional_dialogs[0],
         "在这些古老的书籍中，记录着许多失传的法术和秘密。");
  strcpy(game->npcs[11].additional_dialogs[1],
         "如果你愿意花时间学习，我可以教你一些有用的技能。");
  game->npcs[11].additional_dialogs_count = 2;
  game->npcs[11].item_to_sell = -1;
  game->npcs[11].item_price = 0;
  game->npcs[11].shop_item_count = 0;

  strcpy(game->npcs[12].name, "赏金猎人");
  strcpy(game->npcs[12].dialog, "我正在追踪一个危险的罪犯。");
  strcpy(game->npcs[12].additional_dialogs[0],
         "就不必劳烦你了，我自己会找到他的。");
  strcpy(game->npcs[12].additional_dialogs[1],
         "他最后一次出现在黑暗沼泽附近，小心点。");
  game->npcs[12].additional_dialogs_count = 2;
  game->npcs[12].item_to_sell = -1;
  game->npcs[12].item_price = 0;
  game->npcs[12].shop_item_count = 0;

  strcpy(game->npcs[13].name, "炼金术士");
  strcpy(game->npcs[13].dialog, "我可以将材料转化为珍贵的药水和物品。");
  strcpy(game->npcs[13].additional_dialogs[0],
         "炼金术是一门深奥的学问，需要精确的配方和技巧。");
  strcpy(game->npcs[13].additional_dialogs[1],
         "如果你能用等价的金钱交易，我可以为你制作强大的药水。");
  game->npcs[13].additional_dialogs_count = 2;
  game->npcs[13].item_to_sell = -1;
  game->npcs[13].item_price = 0;
  game->npcs[13].shop_items[0] = 5;  // 高级生命药水
  game->npcs[13].shop_items[1] = 6;  // 魔法药水
  game->npcs[13].shop_items[2] = 9;  // 超级生命药水
  game->npcs[13].shop_items[3] = 23; // 中级生命药水
  game->npcs[13].shop_items[4] = 24; // 高级魔法药水
  game->npcs[13].shop_items[5] = 26; // 力量药剂
  game->npcs[13].shop_items[6] = 27; // 敏捷药剂
  game->npcs[13].shop_items[7] = 28; // 智力药剂
  game->npcs[13].shop_item_count = 8;

  strcpy(game->npcs[14].name, "占卜师");
  strcpy(game->npcs[14].dialog, "我能预见未来，虽然命运往往难以改变。");
  strcpy(game->npcs[14].additional_dialogs[0],
         "我看到了恶龙的爪牙正在集结，世界只有你才能拯救。");
  strcpy(game->npcs[14].additional_dialogs[1],
         "小心前方的道路，危险正等着你。");
  game->npcs[14].additional_dialogs_count = 2;
  game->npcs[14].item_to_sell = -1;
  game->npcs[14].item_price = 0;
  game->npcs[14].shop_item_count = 0;

  strcpy(game->npcs[16].name, "村民");
  strcpy(game->npcs[16].dialog, "最近我听说在迷雾森林里出现了很多狼。");
  strcpy(game->npcs[16].additional_dialogs[1],
         "如果你需要补给，村里的商人们会提供帮助。");
  game->npcs[16].additional_dialogs_count = 2;
  game->npcs[16].item_to_sell = -1;
  game->npcs[16].item_price = 0;
  game->npcs[16].shop_item_count = 0;

  strcpy(game->npcs[17].name, "老者");
  strcpy(game->npcs[17].dialog, "年轻人，这个世界比你想象的更加复杂。");
  strcpy(game->npcs[17].additional_dialogs[0],
         "我年轻时也曾像你一样勇敢，但岁月不饶人。");
  game->npcs[17].additional_dialogs_count = 1;
  game->npcs[17].item_to_sell = -1;
  game->npcs[17].item_price = 0;
  game->npcs[17].shop_item_count = 0;

  strcpy(game->npcs[18].name, "旅店老板");
  strcpy(game->npcs[18].dialog,
         "欢迎来到我的旅店！需要休息一晚吗？只需50金币。");
  strcpy(game->npcs[18].additional_dialogs[0],
         "在我的旅店里休息一晚，就能完全恢复你的精力。");
  strcpy(game->npcs[18].additional_dialogs[1],
         "旅途劳累，好好休息才能迎接更大的挑战。");
  game->npcs[18].additional_dialogs_count = 2;
  game->npcs[18].item_to_sell = -1;
  game->npcs[18].item_price = 50; // 休息费用
  game->npcs[18].shop_item_count = 0;

  strcpy(game->npcs[19].name, "神秘女子");
  strcpy(game->npcs[19].dialog, "我能感受到你身上的特殊气息...");
  strcpy(game->npcs[19].additional_dialogs[0], "命运正引导着你，年轻的勇者。");
  strcpy(game->npcs[19].additional_dialogs[1], "小心隐藏在阴影中的敌人。");
  game->npcs[19].additional_dialogs_count = 2;
  game->npcs[19].item_to_sell = -1;
  game->npcs[19].item_price = 0;
  game->npcs[19].shop_item_count = 0;

  game->dragon_defeated = 0; // 恶龙未被击败
}