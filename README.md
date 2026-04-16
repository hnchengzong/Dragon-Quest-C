# Dragon-Quest-C

![C](https://img.shields.io/badge/Language-C-blue.svg)
![xmake](https://img.shields.io/badge/Build-xmake-orange.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

该项目源自早期个人练习作品，现在对其进行模块化重构，稍稍修改，并使用`xmake`构建。使用了AI工具进行代码审查，并对一些潜在问题进行修复。

## 🚀编译与运行

```bash

git clone --depth 1 https://github.com/hnchengzong/Dragon-Quest-C.git

cd ./Dragon-Quest-C

# 运行
xmake run

# 切换到调试模式。
xmake f -m debug

# 进行编译，结果输出到./bin目录下。
xmake build

```

## 下面是原来的README.md

---

## 文字冒险游戏：勇者斗恶龙（Dragon Quest）

- 这是一个由c语言编写的简短的文字冒险游戏，以经典的勇者斗恶龙为模板。  

- 该项目适用于Windows或Linux系统，为Cli程序。  

- 如果你在Windows系统下运行时出现乱码，这是因为cmd的默认编码是GBK，而该项目的默认编码是UTF-8。你可以在cmd中运行`chcp 65001`来改变编码,再在cmd中打开可执行文件，或使用Windows版本的应用程序。  

- 如果你与敌人战斗时攻击后闪退，是因为生命值归零自动结束了游戏。请升到一定的等级再战斗。

- 内置有作弊菜单

> 繁荣与和平已在这片土地持续数百年。然而，这份宁静被一头突然出现的恶龙打破。它袭击城镇，掠夺财宝，所到之处生灵涂炭，横尸遍野。王国派出最精锐的战士前往讨伐，却在龙焰下皆化作白骨。阴云笼罩了整个王国。而你，一名生活在偏远宁静的小村庄中的默默无闻的战士，在村民们混杂着担忧与期盼的目光中，毅然挺身而出......您的史诗，就此展开。
