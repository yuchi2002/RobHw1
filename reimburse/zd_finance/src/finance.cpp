#include "rclcpp/rclcpp.hpp"


class FinanceNode:public rclcpp::Node
{
public:
    FinanceNode(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"I'm %s ,who is the finance officer.\n You can submit claim now.",name.c_str()); //finance's name

    }

private:

    
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<FinanceNode>("Zhou"); //finance's name
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}