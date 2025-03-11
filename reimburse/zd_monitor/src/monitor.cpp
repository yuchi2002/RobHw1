#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MonitorNode : public rclcpp::Node
{
public:
    MonitorNode(std::string name) : Node(name)
    {
        // 初始化日志
        RCLCPP_INFO(this->get_logger(), "%s started monitoring...", name.c_str());
        
        // 创建对申请请求的订阅
        claim_sub_ = this->create_subscription<std_msgs::msg::String>(
            "/claim_requests",
            10,
            [this](const std_msgs::msg::String::SharedPtr msg) {
                this->handle_claim(msg);
            });
        
        // 创建对审批状态的订阅
        status_sub_ = this->create_subscription<std_msgs::msg::String>(
            "/approval_status",
            10,
            [this](const std_msgs::msg::String::SharedPtr msg) {
                this->handle_approval(msg);
            });
    }

private:
    // 处理申请请求的回调
    void handle_claim(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), 
            "[Claim Monitor] 收到申请: %s", 
            msg->data.c_str());
    }

    // 处理审批状态的回调
    void handle_approval(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(),
            "[Approval Monitor] 收到状态: %s",
            msg->data.c_str());
    }

    // 成员变量
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr claim_sub_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr status_sub_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MonitorNode>("ClaimMonitor"); // 创建节点实例
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}