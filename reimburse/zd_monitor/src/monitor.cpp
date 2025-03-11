#include "rclcpp/rclcpp.hpp"


class MonitorNode:public rclcpp::Node
{
public:
    MonitorNode(std::string name):Node(name)
    {
        

    }

private:

    
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}