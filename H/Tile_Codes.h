#ifndef TILE_DATA_ENUMERATION_TYPE_HHH221231225_HHHH_H_
#define TILE_DATA_ENUMERATION_TYPE_HHH221231225_HHHH_H_

namespace Data{
    namespace Tile{
        typedef short raw_type;
        enum class code : raw_type{
            Void = 0,
            Dirt, Water, Sand, Ice, Snow, Magma, Cloud,
            Rock, Grass, Mud, Stone, Soil, Clay,
            Air, Tree_Base, Tree_Trunk, Tree_Top, Bush_Left, Bush_Mid, Bush_Right,
            Tall_Grass, Cactus_Base, Cactus_Trunk, Cactus_Top, Leaves, Clear_Water,
            Muddy_Water, Acid, Quicksand, Rainbow, Space
        };
    }
}

#endif