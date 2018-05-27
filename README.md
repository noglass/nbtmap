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
    NBTCompound creeper ("{powered: 0b, ExplosionRadius: 3b, Fuse: 30s, ignited: 0b, Pos: [123.456f, 63.0f, 789.0f], fake: [{foo: bar, list: [0, 1, 2]},{foo: foo, list: [3, 4, 5]}]}");
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
```
Output:
```
nigel@dontdeleteme:~/nbtmap$ ./example 
NBTCompound creeper has the following data:
creeper["fake"] = [{foo: bar, list: [0, 1, 2]},{foo: foo, list: [3, 4, 5]}]
creeper["Pos"] = [123.456f, 63.0f, 789.0f]
creeper["powered"] = 0b
creeper["ExplosionRadius"] = 3b
creeper["Fuse"] = 30s
creeper["ignited"] = 0b

NBTList pos has the following data:
pos[0] = 123.456f
pos[1] = 63.0f
pos[2] = 789.0f

NBTWrapper contained has the following data:
contained["Fuse"] = 30s
contained["powered"] = 0b
contained["Pos[1]"] = 63.0f
contained["Pos"] = [123.456f, 63.0f, 789.0f]
contained["fake[1].foo"] = foo
contained["fake[1].list[2]"] = 5
contained["fake[1].list[1]"] = 4
contained["fake[0].list"] = [0, 1, 2]
contained["fake[1].list"] = [3, 4, 5]
contained["fake"] = [{foo: bar, list: [0, 1, 2]},{foo: foo, list: [3, 4, 5]}]
contained["Pos[2]"] = 789.0f
contained["Pos[0]"] = 123.456f
contained["fake[0]"] = {foo: bar, list: [0, 1, 2]}
contained["fake[1].list[0]"] = 3
contained["ExplosionRadius"] = 3b
contained["fake[0].list[1]"] = 1
contained["ignited"] = 0b
contained["fake[0].list[2]"] = 2
contained["fake[0].list[0]"] = 0
contained["fake[0].foo"] = bar
contained["fake[1]"] = {foo: foo, list: [3, 4, 5]}

```
