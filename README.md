# nbtmap
Easy Library for Parsing Minecraft NBT Strings

Simple and easy header only library for parsing and building NBT compounds and lists.  

Requires at least C++11.  

All components are kept as strings, no internal conversions are made, and the library assumes all NBT is valid. Primarily meant for processing `data get` and `entitydata` output.  

Usage:
```C++
#include "nbtmap.h"

int main()
{
    NBTCompound creeper ("{powered: 0b, ExplosionRadius: 3b, Fuse: 30s, ignited: 0b, Pos: [123.456f, 63.0f, 789.0f]}");
    NBTList pos (creeper.get("Pos"));
    std::cout<<"NBTCompound creeper has the following data:\n";
    for (auto it = creeper.begin(), ite = creeper.end(); it != ite; ++it)
        std::cout<<"creeper[\""<<it->first<<"\"] = "<<it->second<<std::endl;
    std::cout<<"\nNBTList pos has the following data:\n";
    for (int i = 0; i < pos.size(); ++i)
        std::cout<<"pos["<<i<<"] = "<<pos[i]<<std::endl;
    return 0;
}
```
Output:
```
NBTCompound creeper has the following data:
creeper["Pos"] = [123.456f, 63.0f, 789.0f]
creeper["powered"] = 0b
creeper["ExplosionRadius"] = 3b
creeper["Fuse"] = 30s
creeper["ignited"] = 0b

NBTList pos has the following data:
pos[0] = 123.456f
pos[1] = 63.0f
pos[2] = 789.0f

```
