# vtol-learning

PX4 + Gazebo + ROS2 无人机仿真学习仓库，W1 任务：环境搭建与首次起飞。

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
cd ~/PX4-Autopilot
make px4_sitl gz_x500
```

启动后用 QGC 连接，手动解锁并起飞悬停。

## 遇到的问题与解决

> 按时间顺序记录，遇到一条补一条。

| 日期 | 问题 | 原因 | 解决办法 |
|---|---|---|---|
| 2026-10-19 | `claude-code --version` 提示找不到命令 | 包名是 `@anthropic-ai/claude-code`，可执行命令是 `claude` | 正确命令为 `claude --version` |
| 2026-10-20 | `git add README.md` 报"路径规格未匹配任何文件" | 文件尚未创建，add 一个不存在的文件 | 先创建 `README.md` 再 `git add` |
| 2026-10-20 | `git init` 后出现黄色提示 | Git 默认初始分支为 `master`，仅提示可改名，非报错 | 执行 `git branch -m main` 改名 |

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

### 常用辅助命令

```bash
git status                 # 查看当前哪些改动已暂存、哪些未暂存（最该常敲）
git restore --staged 文件  # 从暂存区撤出（文件内容不变）
git remote -v              # 查看远程仓库地址
```

### 首次推送完整流程

```bash
cd ~/vtol-learning
git init
git add .
git commit -m "第一次提交：初始化仓库与 README"
git branch -m main
git remote add origin git@github.com:用户名/vtol-learning.git
git push -u origin main
```

### 日常循环

```bash
git status
git add .
git commit -m "今天干了啥"
git push
```

### 关于分支

分支 = 平行的存档线。默认在 `main`（主线），想做有风险的实验就开一条支线，搞砸了直接丢弃，主线毫发无损；成功了再 `git merge` 回来。

```bash
git branch              # 列出分支，* 为当前分支
git switch -c test      # 新建并切换到 test
git merge test          # 把 test 合并回当前分支
```

### 建议的 .gitignore

```gitignore
build/
*.log
*.o
__pycache__/
.vscode/
```

避免 `git add .` 把编译产物和调试文件一并提交。

## 待办

- [x] 环境核对并记录版本
- [x] `make px4_sitl gz_x500` 跑通
- [ ] QGC 连接，手动解锁起飞悬停 30 秒
- [x] GitHub 建仓并完成第一次提交
- [x] 学习 Git 最小可用集
- [ ] 把常用启动命令写成 shell 脚本