#include <iostream>
#include <thread>
#include <chrono> // 用于模拟耗时

using namespace std;

void process_image(const string& filename){
    cout<<"[" <<filename<<"]开始处理，线程ID"<<this_thread::get_id()<<endl;

    this_thread::sleep_for(chrono::seconds(10));

    cout << "[" << filename << "] 处理完成，结果已保存。" << endl;
}


int main(){
    string user_upload = "photo_12345.jpg";
    cout << "[主程序] 接收到图片上传请求：" << user_upload << "，主线程ID: " << this_thread::get_id() << endl;

    thread worker_t(process_image,user_upload);

    cout << "[主程序] 已经将处理任务交给工作线程，主程序可以继续监控状态或处理其他请求..." << endl;

    worker_t.join();

    cout << "[主程序] 工作线程已完成并返回。现在可以向用户发送“处理成功”的通知。" << endl;

    return 0;
}
