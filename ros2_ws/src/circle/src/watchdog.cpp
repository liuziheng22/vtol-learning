#include <rclcpp/rclcpp.hpp>
#include <px4_msgs/msg/offboard_control_mode.hpp>

#include <chrono>

using namespace std::chrono_literals;
using OffboardControlMode = px4_msgs::msg::OffboardControlMode;

class OffboardWatchdog : public rclcpp::Node
{
public:
    OffboardWatchdog() : Node("offboard_watchdog")
    {
        // 订阅 circle 节点正在发布的同一个话题
        subscription_ = this->create_subscription<OffboardControlMode>(
            "/fmu/in/offboard_control_mode", 10,
            [this](const OffboardControlMode::SharedPtr /*msg*/) {
                last_msg_time_ = std::chrono::steady_clock::now();
                // 如果之前处于超时状态，现在恢复了，记录一条恢复日志
                if (is_timed_out_) {
                    RCLCPP_INFO(this->get_logger(),
                                "Offboard 信号恢复，circle 节点重新上线。");
                    is_timed_out_ = false;
                }
            });

        // 启动时先把“最后收到时间”设为当前，避免一启动就误报
        last_msg_time_ = std::chrono::steady_clock::now();

        // 每 200ms 检查一次；正常周期是 100ms，200ms 检查一次足够及时
        check_timer_ = this->create_wall_timer(200ms, [this]() {
            this->check_timeout();
        });

        RCLCPP_INFO(this->get_logger(),
                    "看门狗已启动，监视 /fmu/in/offboard_control_mode ...");
    }

private:
    void check_timeout()
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                           now - last_msg_time_)
                           .count();

        // 0.5 秒 = 500 毫秒
        if (elapsed > 500) {
            if (!is_timed_out_) {
                is_timed_out_ = true;
                RCLCPP_ERROR(this->get_logger(),
                             "Offboard 心跳超时！最后一条消息在 %ld ms 之前。"
                             "PX4 的 COM_OF_LOSS_T 默认约 1 秒，看门狗已提前触发。",
                             elapsed);
                // 第一版只打日志。安全动作留到验证通过后再接。
            }
        }
    }

    rclcpp::Subscription<OffboardControlMode>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr check_timer_;
    std::chrono::steady_clock::time_point last_msg_time_;
    bool is_timed_out_ = false;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OffboardWatchdog>());
    rclcpp::shutdown();
    return 0;
}