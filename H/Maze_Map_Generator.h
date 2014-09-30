#ifndef MAZE_MAP_GENERATOR_INTERFACE_002394889_HHH_HSHD99393022_H_
#define MAZE_MAP_GENERATOR_INTERFACE_002394889_HHH_HSHD99393022_H_

#include "Maze_Tile_Map_Generator.h"

#include <queue>
#include <utility>

namespace Data{
    template <std::size_t Dimensions, typename CodeType>
    class Maze_Map_Generator;

    template <typename CodeType>
    class Maze_Map_Generator<2, CodeType>
        : public Maze_Tile_Map_Generator<2, CodeType>
    {
        public:
            using base_type = Maze_Tile_Map_Generator<2, CodeType>;
            using typename base_type::map_type;
            using typename base_type::size_type;
            using typename base_type::code_type;
            using typename base_type::tile_map_type;

/* Inherited
            map_type* operator() (size_type x, size_type y) const;
            void operator()
                (map_type& map, size_type x, size_type y) const;
            void replace_code
                (map_type& map, code_type old_code, code_type new_code)
            const;
*/
        // Read-only
/* Inherited
            const code_type& floor()const;
            const code_type& wall()const;
            const code_type& player()const;
            const code_type& exit()const;
            const code_type& path()const;
            const code_type& prep()const;
            size_type difficulty()const;
            const code_type& path_logger_fill()const;
            bool has_mult_solutions()const;
*/

        // Modifiers
/* Inherited
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
*/

            Maze_Map_Generator(
                const code_type& new_floor, const code_type& new_wall,
                const code_type& new_player, const code_type& new_exit,
                const code_type& new_path, const code_type& new_prep,
                size_type new_difficulty, bool mult_solutions = false,
                map_type* new_path_logger = nullptr,
                const code_type& new_plfill = static_cast<code_type>(0)
            );

            virtual ~Maze_Map_Generator(){}

/* Inherited
        private:
            virtual map_type* generate(size_type x, size_type y)
                const override;

        protected:
            virtual void replace_code_concrete
                (map_type& map, code_type old_code, code_type new_code)
            const override;

            virtual bool generate_path(
                map_type& map, size_type dx, size_type dy,
                Orientation::code first_dir,
                const code_type& pcode, bool do_branches
            )const;

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
                (Orientation::code bias);
*/
        protected:
            virtual void generate
                (map_type& map, size_type x, size_type y)
            const override;

            virtual void generate_main_path
                (map_type& map, Orientation::code dir)const;

            virtual void generate_false_path(map_type& map)const;

            virtual void log_path(const map_type&)const;

            virtual void connect_paths(map_type&)const;

            virtual bool generate_path(
                map_type& map, size_type dx, size_type dy,
                Orientation::code first_dir, const code_type& pcode, 
                bool do_branches
            )const;

            typedef std::queue<std::pair<size_type, size_type> >
                branch_seeds_type;

            void seed_branch(
                map_type& map, branch_seeds_type& seeds,
                size_type x, size_type y, Orientation::code dir
            )const;

            using base_type::place_tile;
            using base_type::place_exit;

            using base_type::m_floor;
            using base_type::m_wall;
            using base_type::m_player;
            using base_type::m_exit;
            using base_type::m_path;
            using base_type::m_prep;
            using base_type::m_difficulty;
            using base_type::m_path_logger;
            using base_type::m_plfill;
            using base_type::m_have_mult_sol;

            using base_type::gen_dir;
    };
}

#include "Maze_Map_Generator.inl"

#endif
