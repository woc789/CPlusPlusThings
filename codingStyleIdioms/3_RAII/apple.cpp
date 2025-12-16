#include <iostream>
using namespace std;

class Apple{
private:    
    int people[100];
public:
    const int apple_number;
    Apple (int i):apple_number(i){};
    void take(int num) const{
        cout << "take func" <<num <<endl;
    }
    void add (int num) const{
        take(num);
    }
    void add(int num){
        take(num);
    }

    int getCount() const{
        take(1);

        return apple_number;
    }

};

int main(){
    Apple a(2);
    cout << a.apple_number << endl;
    a.add(10);
    const Apple b(3);
    b.add(100);
    b.getCount();
    return 0;
}

