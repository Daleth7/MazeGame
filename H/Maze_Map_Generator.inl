#define MTEMPL_ template <typename CodeType>
#define MINST_ Maze_Map_Generator<2, CodeType>

#include <cstdlib>

#ifndef NDEBUG
    #include <iostream>
#endif

namespace Data{
    MTEMPL_
    MINST_::Maze_Map_Generator(
        const code_type& new_floor, const code_type& new_wall,
        const code_type& new_player, const code_type& new_exit,
        const code_type& new_path, const code_type& new_prep,
        size_type new_difficulty, bool mult_solutions,
        map_type* new_path_logger, const code_type& new_plfill
    )
        : base_type::Maze_Tile_Map_Generator(
            new_floor, new_wall, new_player, new_exit, new_path,
            new_prep, new_difficulty, mult_solutions,
            new_path_logger, new_plfill)
    {}

    MTEMPL_
    void MINST_::generate
        (map_type& map, size_type x, size_type y)
    const{
        map.fill(m_prep);
        map.resize(x, y, m_prep);
        map.set_borders(m_wall);
        this->generate_main_path(map, gen_dir());
        this->generate_false_path(map);
        if(m_have_mult_sol) this->connect_paths(map);
        this->replace_code_concrete(map, m_prep, m_wall);
        this->log_path(map);
#ifndef NDEBUG
        std::clog << "Finished generating." << std::endl;
#endif
    }

    MTEMPL_
    void MINST_::generate_main_path
        (map_type& map, Orientation::code side_start)
    const{
        size_type p_x(0), p_y(0), pf_x(1), pf_y(1);
        auto align_with_player = []
            (size_type lim, size_type& p_N, size_type& pf_N)
        {
            do{p_N = std::rand()%lim;}while(p_N > lim-2u|| p_N < 1u);
            pf_N = p_N;
        };
        switch(side_start){
            case Orientation::code::South:
                p_y = map.height()-1u;
                pf_y = map.height()-2u;
            case Orientation::code::North:
                align_with_player(map.width(), p_x, pf_x);
                break;
            case Orientation::code::East:
                p_x = map.width()-1u;
                pf_x = map.width()-2u;
            case Orientation::code::West:
                align_with_player(map.height(), p_y, pf_y);
                break;
            default:
                break;
        }
        map.set(p_x, p_y, m_player);
        map.set(pf_x, pf_y, m_path);

        side_start = Orientation::reverse(side_start);
#ifndef NDEBUG
        size_type attempt_n(0);
        std::clog << "Difficulty: " << this->difficulty() << '\n';
#endif
        while(!this->generate_path
            (map, pf_x, pf_y, side_start, m_path, true))
#ifndef NDEBUG
        {std::clog << "\tPath attempt #" << (++attempt_n) << " failed.\n";}
        std::clog << '\n';
        attempt_n = 0;
#else
        ;
#endif
    }

    MTEMPL_
    void MINST_::generate_false_path(map_type& map)const{
#ifndef NDEBUG
        size_type attempt_n(0u);
#endif
        for(size_type y(2u); y < map.height()-2u; y+=map.height()/60u+2u){
            for(size_type x(2u); x < map.width()-2u; x+=map.width()/60u+2u){
                if(map.get(x, y) != m_path)
#ifndef NDEBUG
                {
#endif
                    generate_path(map, x, y, gen_dir(), m_floor, false);
#ifndef NDEBUG
                    std::clog << "\tGenerated false path #" << (++attempt_n) << ".\n";
                }
#endif
            }
        }
    }

    MTEMPL_
    void MINST_::log_path(const map_type& map)const{
        if(m_path_logger == nullptr)    return;
        m_path_logger->fill(m_plfill);
        m_path_logger->resize(map.width(), map.height(), m_plfill);
        for(size_type y = 1u; y < map.height(); ++y){
            for(size_type x = 1u; x < map.width(); ++x){
                if(map.get(x, y) == m_path)
                    m_path_logger->set(x, y, m_path);
            }
        }
    }

    MTEMPL_
    void MINST_::connect_paths(map_type& map)const{
        for(size_type y(3u); y < map.height()-3u; y+=map.height()/60u+2u){
            for(size_type x(3u); x < map.width()-3u; x+=map.width()/60u+2u){
                if(
                    (
                        map.get(x+1u, y) == m_floor &&
                        map.get(x-1u, y) == m_floor &&
                        base_type::is_empty(map, x, y+1u) &&
                        base_type::is_empty(map, x, y-1u)
                    ) ||
                    (
                        base_type::is_empty(map, x+1u, y) &&
                        base_type::is_empty(map, x-1u, y) &&
                        map.get(x, y+1u) == m_floor &&
                        map.get(x, y-1u) == m_floor
                    )
                )   map.set(x, y, m_floor);
            }
        }
    }

    MTEMPL_
    bool MINST_::generate_path(
        map_type& map, size_type dx, size_type dy,
        Orientation::code first_dir, const code_type& pcode,
        bool do_branches
    )const{
            // Location related
        Orientation::code last_dir;
        size_type start_x(dx), start_y(dy);

            // Limit related
        const size_type lim(map.width()*map.height() >> 3);
        size_type counter(0), path_counter(0);

            // Branching related
        branch_seeds_type path_branches;
        bool good_to_branch = 0x0;

            // Generate the main path
        place_tile(map, dx, dy, first_dir, path_counter, pcode);
        auto reset_main_path = [
            &counter, &path_counter, &map,
            &dx, &dy, &start_x, &start_y, &path_branches
            ](code_type filler_code, code_type path_code){
                dx = start_x;
                dy = start_y;
                for(size_type xi(1); xi < map.width()-1u; ++xi){
                    for(size_type yi(1); yi < map.height()-1u; ++yi){
                        map.set(xi, yi, filler_code);
                    }
                }
                counter = path_counter = 0;
                map.set(dx, dy, path_code);
                path_branches = branch_seeds_type();
            };
        size_type
            last_pcounter(path_counter),
            no_change_counter(0u)
        ;
        while(place_tile(
            map, dx, dy, last_dir = gen_dir(first_dir,
                100u*(map.width()+map.height())/120u),
            path_counter, pcode
        )){
            if(do_branches){
                if(good_to_branch ^= 0x01){
                    seed_branch(
                        map, path_branches,
                        dx, dy, last_dir
                    );
                }
            }else{
                no_change_counter += last_pcounter == path_counter;
                if(no_change_counter == m_difficulty/2u)
                    break;
                last_pcounter = path_counter;
            }
            if(++counter == lim){
                if(!do_branches)    break;
                reset_main_path(m_prep, pcode);
                last_dir = first_dir;
            }
        }
        if(!do_branches)    return true;
        if(path_counter < m_difficulty){
#ifndef NDEBUG
            std::clog
                << "\t\tpath_counter: " << path_counter
                << "\t|\tm_difficulty: " << m_difficulty
            << "\n";
#endif
            reset_main_path(m_prep, pcode);
            return false;
        }
        place_exit(last_dir, map, dx, dy);

            // Generate branching paths
        while(!path_branches.empty()){
            auto spos = path_branches.front();
            path_branches.pop();
            path_counter = 0;
            counter = std::rand()
                % m_difficulty
                + (m_difficulty/2u);
            while(
                (++path_counter) < counter &&
                place_tile(
                    map, spos.first, spos.second,
                    last_dir = gen_dir(), start_x, m_floor
                )
            );
        }

        return true;
    }

    MTEMPL_
    void MINST_::seed_branch(
        map_type& map, branch_seeds_type& seeds,
        size_type x, size_type y, Orientation::code dir
    )const{
        const size_type chance = 2u;
        switch(dir){
            case Orientation::code::North:
            case Orientation::code::South:
                if(
                    map.get(x+1u, y) == m_prep &&
                    ((std::rand()%chance) == 0) &&
                    (x == map.width()-2u
                        || map.get(x+2u, y) != m_path)
                )   seeds.push({x, y});
                if(
                    map.get(x-1u, y) == m_prep &&
                    ((std::rand()%chance) == 0) &&
                    (x == 1u || map.get(x-2u, y) != m_path)
                )   seeds.push({x, y});
                break;
            case Orientation::code::West:
            case Orientation::code::East:
                if(
                    map.get(x, y+1u) == m_prep &&
                    ((std::rand()%chance) == 0) &&
                    (y == map.height()-2u
                        || map.get(x, y+2u) != m_path)
                )   seeds.push({x, y});
                if(
                    map.get(x, y-1u) == m_prep &&
                    ((std::rand()%chance) == 0) &&
                    (y == 1u || map.get(x, y-2u) != m_path)
                )   seeds.push({x, y});
                break;
            default:
                break;
        }
    }
}

#undef MTEMPL_
#undef MINST_