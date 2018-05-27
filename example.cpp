#include "nbtmap.h"

int main()
{
    NBTCompound creeper ("{powered: 0b, ExplosionRadius: 3b, Fuse: 30s, ignited: 0b, Pos: [123.456f, 63.0f, 789.0f], fake: [{foo: bar, list: [0, 1, 2]},{foo: foo, list: [3, 4, 5]}], 2d: [[0, 1, 2], [3, 4, 5], [6, 7, 8]], anotherList:[,,,, , , ,,, ,, , 1]}");
    NBTList pos (creeper.get("Pos"));
    std::cout<<"NBTCompound creeper has the following data:\n";
    for (auto it = creeper.begin(), ite = creeper.end(); it != ite; ++it)
        std::cout<<"creeper[\""<<it->first<<"\"] = "<<it->second<<std::endl;
    std::cout<<"\nNBTList pos has the following data:\n";
    for (int i = 0; i < pos.size(); ++i)
        std::cout<<"pos["<<i<<"] = "<<pos[i]<<std::endl;
    NBTWrapper contained (creeper);
    std::cout<<"\nNBTWrapper contained has the following data:\n";
    for (auto it = contained.begin(), ite = contained.end(); it != ite; ++it)
        std::cout<<"contained[\""<<it->first<<"\"] = "<<it->second<<std::endl;
    return 0;
}

