#include "nbtmap.h"

int main()
{
    NBTCompound creeper ("{powered: 0b, ExplosionRadius: 3b, Fuse: 30s, ignited: 0b, Pos: [123.456f, 63.0f, 789.0f]}");
    NBTList pos (creeper.get("Pos"));
    std::cout<<"NBTCompound creeper has the following data:\n";
    for (auto it = creeper.begin(), ite = creeper.end(); it != ite; ++it)
        std::cout<<it->first<<" = "<<it->second<<std::endl;
    std::cout<<"\nNBTList pos has the following data:\n";
    for (int i = 0; i < pos.size(); ++i)
        std::cout<<"pos["<<i<<"] = "<<pos[i]<<std::endl;
    return 0;
}

