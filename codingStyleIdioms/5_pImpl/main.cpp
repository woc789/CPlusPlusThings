#include <iostream>
#include "Logger.h" // 引用接口头文件

void perform_task(const Logger& logger){
    logger.log_message("Task starting.");
    //业务逻辑
    logger.log_message("Task finished successfully.");
}

int main() {
    std::cout << "--- Application Startup ---\n";

    // 创建 Logger 对象，文件名是 app_debug.log
    // 注意：客户端代码不需要知道 LoggerImpl 的任何细节！
    Logger app_logger("app_debug.log"); 

    app_logger.set_level(3);
    app_logger.log_message("Main module initialized.");
    
    perform_task(app_logger);

    std::cout << "--- Application Shutdown ---\n";

    return 0;
    // 当 main 退出时，app_logger 销毁，pImpl 自动调用 LoggerImpl 的析构函数
}