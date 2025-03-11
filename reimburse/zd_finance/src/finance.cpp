#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class FinanceNode : public rclcpp::Node
{
public:
    FinanceNode(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "I'm %s, the finance officer.", name.c_str());
        
        // 创建审批结果发布器
        approval_pub_ = this->create_publisher<std_msgs::msg::String>(
            "/approval_status", 10);
            
        // 订阅申请请求
        claim_sub_ = this->create_subscription<std_msgs::msg::String>(
            "/claim_requests",
            10,
            std::bind(&FinanceNode::handle_claim, this, std::placeholders::_1));
            
        // 定时器示例（可选）
        timer_ = this->create_wall_timer(
            std::chrono::seconds(5),
            [this]() { this->publish_status(); });
    }

private:
    void handle_claim(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "收到申请: %s", msg->data.c_str());
        
        // 处理申请并回复
        auto response = std_msgs::msg::String();
        response.data = "Application approved by " + this->get_name();
        approval_pub_->publish(response);
    }

    void publish_status()
    {
        auto msg = std_msgs::msg::String();
        msg.data = "System status: Normal";
        approval_pub_->publish(msg);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr approval_pub_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr claim_sub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<FinanceNode>("Zhou");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}