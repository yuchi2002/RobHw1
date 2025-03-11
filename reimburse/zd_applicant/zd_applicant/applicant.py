import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class ApplicantNode(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("I'm %s. Can I submit claim now?" % name)
        
        # 订阅审批状态
        self.status_sub = self.create_subscription(
            String,
            '/approval_status',
            self.status_callback,
            10
        )
        
        # 创建用于发送申请的发布器
        self.application_pub = self.create_publisher(
            String,
            '/claim_requests',
            10
        )
        
        # 发送初始申请
        self.publish_claim()

    def publish_claim(self):
        msg = String()
        msg.data = f"Claim request from {self.get_name()}"
        self.application_pub.publish(msg)
        self.get_logger().info(f"已发送申请: {msg.data}")

    def status_callback(self, msg):
        self.get_logger().info(f"收到审批结果: {msg.data}")
        # 收到回复后可以继续处理...

def main(args=None):
    rclpy.init(args=args)
    node = ApplicantNode("Yu")
    rclpy.spin(node)
    rclpy.shutdown()