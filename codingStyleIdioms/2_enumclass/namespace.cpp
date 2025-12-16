// //
// // Created by light on 19-12-9.
// //

// #include <iostream>

// using namespace std;
// // 在创建枚举时，将它们放在名称空间中，以便可以使用有意义的名称访问它们:
// namespace EntityType {
//     enum Enum {
//         Ground = 0,
//         Human,
//         Aerial,
//         Total
//     };
// }

// void foo(EntityType::Enum entityType)
// {
//     if (entityType == EntityType::Ground) {
//         /*code*/
//     }
// }

// // enum class
// enum class EntityType1 {
//     Ground = 0,
//     Human,
//     Aerial,
//     Total
// };

// void foo(EntityType1 entityType)
// {
//     if (entityType == EntityType1::Ground) {
//         /*code*/
//     }
// }

// int main() {

//     return 0;
// }
#include <iostream>
#include <string>

using namespace std;

enum class AttackType{   //基础类型伤害数值
    Fire = 10,
    Ice = 20,
    Poison = 5
};

enum class DefenseEntity{
    Plant,
    Rock,
    Water
};

double calculate_damage_multiplier(AttackType attack , DefenseEntity defense){
    switch (defense)
    {
    case DefenseEntity::Plant:
        if(attack == AttackType::Fire){
            return 1.5;
        }else if(attack == AttackType::Poison){
            return 0.5;
        }
        break;
    /*code*/
    default:
        break;
    }
    return 1.0;
}

int main(){
    AttackType attack_fire = AttackType::Fire;
    DefenseEntity defense_plant = DefenseEntity::Plant;
    int base_fire_damage = static_cast<int>(attack_fire);

    cout << "---伤害计算示例---" <<endl;

    double multi_1=calculate_damage_multiplier(attack_fire,defense_plant);
    double final_damage=multi_1*base_fire_damage;

    cout << "最终伤害为" <<final_damage <<endl;

    return 0;
}