#ifndef ABSTRACT_MAP_GENERATOR_INTERFACE_23748_HHH_H99912938_H_
#define ABSTRACT_MAP_GENERATOR_INTERFACE_23748_HHH_H99912938_H_

#include "Map.h"

namespace Data{
    template <std::size_t Dimensions, typename CodeType>
    class Map_Generator;

    template <typename CodeType>
    class Map_Generator<2, CodeType>{
        public:
            using map_type  = Map<2, CodeType>;
            using size_type = typename map_type::size_type;
            using code_type = typename map_type::code_type;

            map_type* operator() (size_type x, size_type y) const
                {return this->generate(x, y);}

            void operator()
                (map_type& map, size_type x, size_type y) const
            {this->generate(map, x, y);}

            void replace_code
                (map_type& map, code_type old_code, code_type new_code)
            const{this->replace_code_concrete(map, old_code, new_code);}

            virtual ~Map_Generator(){}

        private:
            virtual map_type* generate
                (size_type x, size_type y) const = 0;

            virtual void generate
                (map_type& map, size_type x, size_type y) const = 0;

        protected:
            virtual void replace_code_concrete
                (map_type& map, code_type old_code, code_type new_code)
            const = 0;
    };
}

#endif