#ifndef ORIENTATION_ENUMS_H___HHH228388837747_H_
#define ORIENTATION_ENUMS_H___HHH228388837747_H_

namespace Data{
    namespace Orientation{
        typedef unsigned char raw_type;
        enum class code : raw_type{
            North = 0, South, East, West, Zenith, Nadir
        };

        constexpr code reverse(code c){
            return  (static_cast<raw_type>(c)%2)
                    ? static_cast<code>(static_cast<raw_type>(c)-1u)
                    : static_cast<code>(static_cast<raw_type>(c)+1u);
        }
    }
}

#endif