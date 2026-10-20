# vtol-learning

PX4 + Gazebo + ROS2 无人机仿真学习仓库。
Week 1 任务：环境搭建与首次起飞。

## 环境信息

| 项目 | 版本 / 说明 |
|---|---|
| 操作系统 | Ubuntu 22.04.5 LTS |
| C++ 编译器 | g++ (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0（支持 C++17） |
| PX4 版本 | v1.15.2 |
| 仿真器 | 7.9.0 Gazebo Harmonic（`gz_x500` 四旋翼模型） |
| ROS2 | Humble |
| QGC | QGroundControl V4.4.4 AppImage |

## 快速开始

编译 PX4 SITL 并启动四旋翼仿真：

```bash
cd ~/px4
make px4_sitl gz_x500
```

启动后用 QGC 连接，手动解锁并起飞悬停。


## Git 基本操作

### 核心概念：三个区域

```
工作区            暂存区            本地仓库           GitHub
(你改的文件)  →   (add 放进来)  →   (commit 存档)  →   (push 上传)
```

### 最小可用命令集

| 命令 | 作用 | 示例 |
|---|---|---|
| `git init` | 初始化仓库，生成 `.git` 目录，每个项目只需一次 | `git init` |
| `git add` | 把改动放进暂存区（提交前的"购物车"） | `git add .` |
| `git commit` | 打包存档，生成本地快照 | `git commit -m "说明"` |
| `git push` | 把本地提交同步到 GitHub | `git push` |
| `git branch` | 查看 / 新建 / 切换分支 | `git switch -c test` |
| `git diff` | 查看具体改了什么 | `git diff` |
| `git log` | 查看提交历史 | `git log --oneline` |

### Git Branch

分支 = 指向最新提交的**指针**，不存代码。`HEAD` 标记你当前在哪条分支。

| 命令 | 作用 |
|---|---|
| `git branch` | 查看分支，`*` 为当前 |
| `git switch -c test` | 新建并切换 |
| `git switch test` | 切换分支 |
| `git merge test` | 把 test 合并进当前分支 |
| `git branch -D test` | 删除分支 |

> `git branch test` 只创建不切换，`git switch` 才切换。

### 工作流

```bash
git switch -c test        # 1. 开支线
git add . && git commit -m "试试"   # 2. 随便改、随便提交，主线不动

git switch main && git merge test   # 3. 满意 → 合并
git switch main && git branch -D test   # 4. 不满意 → 作废
```

**原则：main 永远保持能跑，实验都丢分支里。**

主线没动时合并是**快进**，不产生新提交、不冲突，最简单。
