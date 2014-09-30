#define MTEMPL_ template <typename CodeType>
#define MINST_ Maze_Tile_Map_Generator<2, CodeType>

#include <cstdlib>

#ifndef NDEBUG
    #include <iostream>
#endif

namespace Data{
    MTEMPL_
    auto MINST_::floor()const -> const code_type&
        {return m_floor;}

    MTEMPL_
    auto MINST_::wall()const -> const code_type&
        {return m_wall;}

    MTEMPL_
    auto MINST_::player()const -> const code_type&
        {return m_player;}

    MTEMPL_
    auto MINST_::exit()const -> const code_type&
        {return m_exit;}

    MTEMPL_
    auto MINST_::path()const -> const code_type&
        {return m_path;}

    MTEMPL_
    auto MINST_::prep()const -> const code_type&
        {return m_prep;}

    MTEMPL_
    auto MINST_::path_logger_fill()const -> const code_type&
        {return m_plfill;}

    MTEMPL_
    auto MINST_::difficulty()const -> size_type
        {return m_difficulty >> 2;}

    MTEMPL_
    bool MINST_::has_mult_solutions()const
        {return m_have_mult_sol;}

// Modifiers
    MTEMPL_
    void MINST_::floor(const code_type& new_floor)
        {m_floor = new_floor;}

    MTEMPL_
    void MINST_::wall(const code_type& new_wall)
        {m_wall = new_wall;}

    MTEMPL_
    void MINST_::player(const code_type& new_player)
        {m_player = new_player;}

    MTEMPL_
    void MINST_::exit(const code_type& new_exit)
        {m_exit = new_exit;}

    MTEMPL_
    void MINST_::path(const code_type& new_path)
        {m_path = new_path;}

    MTEMPL_
    void MINST_::prep(const code_type& new_prep)
        {m_prep = new_prep;}

    MTEMPL_
    void MINST_::path_logger_fill(const code_type& new_fill)
        {m_plfill = new_fill;}

    MTEMPL_
    void MINST_::difficulty(size_type new_difficulty)
        {m_difficulty = new_difficulty << 2;}

    MTEMPL_
    void MINST_::path_logger(map_type& new_logger)
        {m_path_logger = &new_logger;}

    MTEMPL_
    void MINST_::has_mult_solutions(bool new_mult)
        {m_have_mult_sol = new_mult;}

    MTEMPL_
    MINST_::Maze_Tile_Map_Generator(
        const code_type& new_floor, const code_type& new_wall,
        const code_type& new_player, const code_type& new_exit,
        const code_type& new_path, const code_type& new_prep,
        size_type new_difficulty, bool new_mult,
        map_type* new_path_logger, const code_type& new_plfill
    )
        : base_type::Map_Generator()
        , m_floor(new_floor)
        , m_wall(new_wall)
        , m_player(new_player)
        , m_exit(new_exit)
        , m_path(new_path)
        , m_prep(new_prep)
        , m_difficulty(new_difficulty << 2)
        , m_path_logger(new_path_logger)
        , m_plfill(new_plfill)
        , m_have_mult_sol(new_mult)
    {}

    MTEMPL_
    auto MINST_::generate(size_type x, size_type y)const -> map_type* {
        map_type* toreturn = new tile_map_type();
        (*this)(*toreturn, x, y);
        return toreturn;
    }

    MTEMPL_
    void MINST_::replace_code_concrete
        (map_type& map, code_type old_code, code_type new_code)
    const{
        for(size_type y(0); y < map.height(); ++y){
            for(size_type x(0); x < map.width(); ++x){
                if(map.get(x, y) == old_code)
                    map.set(x, y, new_code);
            }
        }
    }

    MTEMPL_
    bool MINST_::place_tile(
        map_type& map, size_type& dx, size_type& dy,
        Orientation::code dir, size_type& path_counter,
        const code_type& new_tile
    )const{
        switch(check_empty(map, dx, dy, dir)){
            case -1:    return false;
            case 1:
                switch(dir){
                    case Orientation::code::North:
                        map.set(dx, --dy, new_tile);
                        break;
                    case Orientation::code::South:
                        map.set(dx, ++dy, new_tile);
                        break;
                    case Orientation::code::East:
                        map.set(++dx, dy, new_tile);
                        break;
                    case Orientation::code::West:
                        map.set(--dx, dy, new_tile);
                        break;
                    default:
                        break;
                }
                ++path_counter;
            case 0:     return true;
            default:    break;
        }
        return false;
    }

    MTEMPL_
    void MINST_::place_exit(
        Orientation::code dir, map_type& map,
        size_type& dx, size_type& dy
    )const{
        switch(dir){
            case Orientation::code::North:
                map.set(dx, --dy, m_exit);
                break;
            case Orientation::code::South:
                map.set(dx, ++dy, m_exit);
                break;
            case Orientation::code::East:
                map.set(++dx, dy, m_exit);
                break;
            case Orientation::code::West:
                map.set(--dx, dy, m_exit);
                break;
            default:    break;
        }
    }

    MTEMPL_
    short MINST_::check_empty(
        const map_type& map,
        size_type dx, size_type dy,
        Orientation::code dir
    )const{
        switch(dir){
            case Orientation::code::North:
                if(dy == 1) return -1;
                return
                    is_empty(map, dx, dy-1) &&
                    is_empty(map, dx, dy-2) &&
                    is_empty(map, dx-1, dy-1) &&
                    is_empty(map, dx+1, dy-1) &&
                    is_empty(map, dx-1, dy-2) &&
                    is_empty(map, dx+1, dy-2)
                ;
            case Orientation::code::South:
                if(dy == map.height()-2u) return -1;
                return
                    is_empty(map, dx, dy+1) &&
                    is_empty(map, dx, dy+2) &&
                    is_empty(map, dx-1, dy+1) &&
                    is_empty(map, dx+1, dy+1) &&
                    is_empty(map, dx-1, dy+2) &&
                    is_empty(map, dx+1, dy+2)
                ;
            case Orientation::code::East:
                if(dx == map.width()-2u) return -1;
                return
                    is_empty(map, dx+1, dy) &&
                    is_empty(map, dx+2, dy) &&
                    is_empty(map, dx+1, dy-1) &&
                    is_empty(map, dx+1, dy+1) &&
                    is_empty(map, dx+2, dy-1) &&
                    is_empty(map, dx+2, dy+1)
                ;
            case Orientation::code::West:
                if(dx == 1) return -1;
                return
                    is_empty(map, dx-1, dy) &&
                    is_empty(map, dx-2, dy) &&
                    is_empty(map, dx-1, dy-1) &&
                    is_empty(map, dx-1, dy+1) &&
                    is_empty(map, dx-2, dy-1) &&
                    is_empty(map, dx-2, dy+1)
                ;
            default:
                return false;
        }
    }

    MTEMPL_
    bool MINST_::is_empty
        (const map_type& map, size_type x, size_type y)
    const{
        return
            map.get(x, y) != m_player &&
            map.get(x, y) != m_path && (
            x == 0 || x == map.width()-1u ||
            y == 0 || y == map.height()-1u ||
            map.get(x, y) == m_prep)
        ;
    }

    MTEMPL_
    constexpr Orientation::code MINST_::gen_dir()
        {return static_cast<Orientation::code>(std::rand()%4u);}

    MTEMPL_
    constexpr Orientation::code MINST_::gen_dir
        (Orientation::code bias, size_type bias_chance)
    {return (std::rand()%bias_chance ? gen_dir() : bias);}
}

#undef MTEMPL_
#undef MINST_