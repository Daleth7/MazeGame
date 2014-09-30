#ifndef MAZE_TILEMAP_GENERATOR_INTERFACE_ABSTRACT_HHH_HSHD99393022_H_
#define MAZE_TILEMAP_GENERATOR_INTERFACE_ABSTRACT_HHH_HSHD99393022_H_

#include "Map_Generator.h"
#include "Tile_Map.h"
#include "Orientation_Codes.h"

namespace Data{
    template <std::size_t Dimensions, typename CodeType>
    class Maze_Tile_Map_Generator;

    template <typename CodeType>
    class Maze_Tile_Map_Generator<2, CodeType>
        : public Map_Generator<2, CodeType>
    {
        public:
            using base_type = Map_Generator<2, CodeType>;
            using typename base_type::map_type;
            using typename base_type::size_type;
            using typename base_type::code_type;
            using tile_map_type = Tile_Map<2, CodeType>;
/* Inherited
            map_type* operator() (size_type x, size_type y) const;
            void operator()
                (map_type& map, size_type x, size_type y) const;
            void replace_code
                (map_type& map, code_type old_code, code_type new_code)
            const;
*/
        // Read-only
            const code_type& floor()const;

            const code_type& wall()const;

            const code_type& player()const;

            const code_type& exit()const;

            const code_type& path()const;

            const code_type& prep()const;

            size_type difficulty()const;

            const code_type& path_logger_fill()const;

            bool has_mult_solutions()const;

        // Modifiers
            void floor(const code_type& new_floor);

            void wall(const code_type& new_wall);

            void player(const code_type& new_player);

            void exit(const code_type& new_exit);

            void path(const code_type& new_path);

            void prep(const code_type& new_prep);

            void difficulty(size_type new_difficulty);

            void path_logger(map_type& new_logger);

            void path_logger_fill(const code_type& new_fill);

            void has_mult_solutions(bool new_mult);

            Maze_Tile_Map_Generator(
                const code_type& new_floor, const code_type& new_wall,
                const code_type& new_player, const code_type& new_exit,
                const code_type& new_path, const code_type& new_prep,
                size_type new_difficulty, bool mult_solutions = false,
                map_type* new_path_logger = nullptr,
                const code_type& new_plfill = static_cast<code_type>(0)
            );

            virtual ~Maze_Tile_Map_Generator(){}

        private:
            virtual map_type* generate(size_type x, size_type y)
                const override;
/* Inherited
            virtual void generate
                (map_type& map, size_type x, size_type y) const = 0;
*/
        protected:
            virtual void replace_code_concrete
                (map_type& map, code_type old_code, code_type new_code)
            const override;

            virtual bool place_tile(
                map_type& map, size_type& dx, size_type& dy,
                Orientation::code dir, size_type& path_counter,
                const code_type& new_tile
            )const;

            virtual void place_exit(
                Orientation::code dir, map_type& map,
                size_type& dx, size_type& dy
            )const;

            virtual short check_empty(
                const map_type& map,
                size_type dx, size_type dy,
                Orientation::code dir
            )const;

            virtual bool is_empty
                (const map_type& map, size_type x, size_type y)
            const;

            static constexpr Orientation::code gen_dir();
            static constexpr Orientation::code gen_dir
                (Orientation::code bias, size_type bias_chance);

            code_type
                m_floor, m_wall, m_player,
                m_exit, m_path, m_prep
            ;
            size_type m_difficulty;
            map_type* m_path_logger;
            code_type m_plfill;
            bool m_have_mult_sol;
    };
}

#include "Maze_Tile_Map_Generator.inl"

#endif
