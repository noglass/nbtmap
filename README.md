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
    NBTCompound creeper ("{powered: 0b, ExplosionRadius: 3b, Fuse: 30s, ignited: 0b, Pos: [123.456f, 63.0f, 789.0f], fake: [{foo: bar, list: [0, 1, 2]},{foo: foo, list: [3, 4, 5]}], 2d: [[0, 1, 2], [3, 4, 5], [6, 7, 8]]}");
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
creeper["2d"] = [[0, 1, 2], [3, 4, 5], [6, 7, 8]]
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
contained["ExplosionRadius"] = 3b
contained["Pos[0]"] = 123.456f
contained["Pos"] = [123.456f, 63.0f, 789.0f]
contained["fake[1].list[0]"] = 3
contained["ignited"] = 0b
contained["2d[1][1]"] = 4
contained["2d[1][2]"] = 5
contained["2d[0][2]"] = 2
contained["Pos[2]"] = 789.0f
contained["2d[0]"] = [0, 1, 2]
contained["fake[1].list"] = [3, 4, 5]
contained["fake[1].foo"] = foo
contained["2d[0][0]"] = 0
contained["2d"] = [[0, 1, 2], [3, 4, 5], [6, 7, 8]]
contained["2d[1][0]"] = 3
contained["fake[1].list[1]"] = 4
contained["fake"] = [{foo: bar, list: [0, 1, 2]},{foo: foo, list: [3, 4, 5]}]
contained["fake[1].list[2]"] = 5
contained["2d[0][1]"] = 1
contained["2d[2]"] = [6, 7, 8]
contained["fake[0].foo"] = bar
contained["2d[2][0]"] = 6
contained["2d[2][1]"] = 7
contained["powered"] = 0b
contained["fake[0].list[0]"] = 0
contained["2d[2][2]"] = 8
contained["Fuse"] = 30s
contained["fake[0]"] = {foo: bar, list: [0, 1, 2]}
contained["fake[0].list"] = [0, 1, 2]
contained["Pos[1]"] = 63.0f
contained["2d[1]"] = [3, 4, 5]
contained["fake[0].list[1]"] = 1
contained["fake[0].list[2]"] = 2
contained["fake[1]"] = {foo: foo, list: [3, 4, 5]}

```
