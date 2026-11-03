# vtol-learning

PX4 + Gazebo + ROS2 无人机仿真学习仓库。

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

启动px4及其gazebo仿真：

```bash
cd ~/px4
make px4_sitl gz_x500
```

启动QGC地面站：

```bash
cd ~
./QGroundControlV4.4.4.AppImage
```

启动通信：

```bash
cd ~
MicroXRCEAgent udp4 -p 8888
```

启动ROS2节点。
可以用以下指令测试
```bash
cd ~/vtol-learning/ros2_ws
ros2 run px4_ros_com offboard_control
```

## 测试结果

一、offboard_control测试能正常起飞（起飞时会有振动，幅度比较大，导致不是垂直起飞）以及悬停，中断节点后，无人机垂直降落。

二、不启动circle节点，起飞时略有磕绊（即振动幅度更大），起飞之后正常绕圈，中断节点后，无人机垂直降落。

## 遇到的问题

问题一：上述两个测试存在不稳定的情况，即偶尔会起飞失败或者是任务进行中莫名返航。考虑原因是PX4 STIL、Gazebo或者QGC的问题。