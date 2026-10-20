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
