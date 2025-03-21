cmake_minimum_required(VERSION 3.8)
project(zd_finance)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(finance_node src/finance.cpp)
ament_target_dependencies(finance_node
  rclcpp
  std_msgs)
  
# 需要添加以下内容
target_link_libraries(finance_node
  ${rclcpp_LIBRARIES}
  std_msgs::std_msgs__rosidl_typesupport_cpp  # 显式链接消息支持库
)

install(TARGETS
  finance_node
  DESTINATION lib/${PROJECT_NAME}  # 添加包名子目录
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
