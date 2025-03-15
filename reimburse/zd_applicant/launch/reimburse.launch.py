from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # 启动 Finance 节点 (C++)
        Node(
            package='zd_finance',
            executable='finance_node',
            name='finance',
            parameters=[{'name': 'Zhou'}]
        ),

        # 启动 Applicant 节点 (Python)
        Node(
            package='zd_applicant',
            executable='applicant_node',
            name='applicant',
            parameters=[{'name': 'Yu'}]
        ),
        
        # 启动 Monitor 节点 (C++)
        Node(
            package='zd_monitor',
            executable='monitor_node',
            name='monitor',
            output='screen'  # 强制显示日志
        )
    ])