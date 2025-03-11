import rclpy
from rclpy.node import Node

class ApplicantNode(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("I'm %s.Can I submit claim now?" %name) #Enter name


def main(args=None):
    rclpy.init(args=args)
    node = ApplicantNode("Yu") #Name
    rclpy.spin(node)
    rclpy.shutdown()