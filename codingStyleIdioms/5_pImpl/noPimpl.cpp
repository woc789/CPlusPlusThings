#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

// class C {
//     vector<int> v;
//     string s;
// };
// class D {
//     string s;
// };

// class X {
// private:
//     C c;
//     D d;
// };


// int main() {

//     X x;
// }

class NetworkConfig {
public:
    string ssid;    
    string passwd;

    NetworkConfig(): ssid("Default_IoT_AP"),passwd("password123"){

    }

    NetworkConfig(const string& s,const string& p):ssid(s),passwd(p){   
        cout << "[NetConfig] Customized settings applied (SSID:" << ssid <<").\n";
    }

    string get_info() const{
        return "SSID:" + ssid + ", Password length:" + to_string(passwd.length());
    }

    bool check_health() const{
        if(passwd.length()<8){
            cout<<"[Net Health] WARNING: Password is too short (Length < 8).\n";
            return false;
        }
        cout << "[Net Health] Network configuration looks secure.\n";
        return true;
    }

    ~NetworkConfig(){
        cout << "[NetworkConfig] is shutting down.\n";
    }
};

class SensorParams{
public:
    vector<double> calibration_data;

    SensorParams(){
        calibration_data = {0.0, 0.0};
    }

    SensorParams(const vector<double>& data) :calibration_data(data){
        cout << "[SensorParams] Custom calibration loaded (" << data.size() << " points).\n";
    }

    string get_info()const{
        stringstream ss;
        ss << "Calibration Data Size: " << calibration_data.size();
        return ss.str();
    }

    bool check_health()const{
        if(calibration_data.size()<=2){
            cout << "[Sensor Health] WARNING: Insufficient calibration points (Need > 2).\n";
            return false;
        }
        for(double var : calibration_data){
            if(abs(var)>=0.01){
                cout << "[Sensor Health] Calibration data is present and varied.\n";
                return true;
            }
        }
        cout << "[Sensor Health] WARNING: Calibration data is all near zero.\n";
        return false;
    }

    ~SensorParams(){
        cout << "[SensorParams] is shutting down.\n";
    }

};


class DeviceSetting{
private:
    NetworkConfig net_config;
    SensorParams sensor;
    int device_id;

public:
    DeviceSetting(int id, const string& ssid, const string& pwd, const vector<double>& data)
    :device_id(id),
     net_config(ssid,pwd),
     sensor(data){
        cout <<"[DeviceSettings] Device" << device_id << "setup complete.\n";
    } 

    ~DeviceSetting(){
        cout << "[DeviceSettings] Device " << device_id << " is shutting down.\n";
    }
    
    void display_status()const{
        cout << "\n======================================\n";
        cout << "Device ID: " << device_id << "\n";
        cout << "--- Network Config ---\n";
        cout << net_config.get_info() << "\n"; // 访问组合对象的公共接口
        cout << "--- Sensor Parameters ---\n";
        cout << sensor.get_info() << "\n"; // 访问组合对象的公共接口
        cout << "======================================\n";
    }

    void run_health_check()const{
        cout << "\n[Health Check] Starting Check for Device " << device_id << "...\n";
        bool net_ok= net_config.check_health();
        bool sensor_ok=sensor.check_health();

        if(net_ok&&sensor_ok){
            cout << "[Health Check] RESULT: Device " << device_id << " is healthy (OK).\n";
        }else{
            cout << "[Health Check] RESULT: Device " << device_id << " requires attention (WARN).\n";
        }
    }
};

int main(){
    cout << "--- Starting Device Configuration ---\n";

    DeviceSetting device1(101,"Home_Mesh_5G","wdx051511",{0.01,-0.05,0.01,0.22});

    device1.display_status();
    device1.run_health_check();

    cout << "\n--- Program Finished ---\n";

    return 0;
}