#define TILE_INST_(N) Tile_Map<N, CodeType>

template <typename CodeType>
constexpr TILE_INST_(0)::Tile_Map(value_type new_val)
    : m_val(new_val)
{}

template <typename CodeType>
auto TILE_INST_(0)::get_concrete()const -> code_type
    {return m_val;}

template <typename CodeType>
void TILE_INST_(0)::set_concrete(code_type newTile)
    {m_val = newTile;}

template <typename CodeType>
void TILE_INST_(0)::fill_concrete(code_type filler)
    {m_val = filler;}

template <typename CodeType>
auto TILE_INST_(0)::cast_concrete()const -> code_type
    {return m_val;}

template <typename CodeType>
auto TILE_INST_(0)::cast_concrete() -> code_type&
    {return m_val;}

template <typename CodeType>
auto TILE_INST_(1)::operator[](size_type x)const -> const value_type&
    {return m_tiles[x];}

template <typename CodeType>
auto TILE_INST_(1)::operator[](size_type x) -> value_type&
    {return m_tiles[x];}

template <typename CodeType>
TILE_INST_(1)::Tile_Map(size_type new_width, code_type filler)
    : m_tiles(new_width, filler)
{}

template <typename CodeType>
auto TILE_INST_(1)::get_concrete(size_type x)const -> code_type
    {return m_tiles[x];}

template <typename CodeType>
auto TILE_INST_(1)::width_concrete()const -> size_type
    {return m_tiles.size();}

template <typename CodeType>
auto TILE_INST_(1)::count_tiles_concrete()const -> size_type
    {return m_tiles.size();}

template <typename CodeType>
void TILE_INST_(1)::set_concrete(
    size_type x,
    code_type newTile
) {m_tiles[x] = newTile;}

template <typename CodeType>
void TILE_INST_(1)::add_concrete
    (size_type dx, code_type filler)
{while(dx-- > 0)    m_tiles.push_back(filler);}

template <typename CodeType>
void TILE_INST_(1)::remove_concrete(size_type dx)
    {while(dx-- > 0)    m_tiles.pop_back();}

template <typename CodeType>
void TILE_INST_(1)::insert_concrete(
    size_type x, size_type dx,
    code_type filler
){m_tiles.insert(m_tiles.begin()+x, dx, filler);}

template <typename CodeType>
void TILE_INST_(1)::erase_concrete
    (size_type x, size_type dx)
{m_tiles.erase(m_tiles.begin()+x, m_tiles.begin()+x+dx);}

template <typename CodeType>
void TILE_INST_(1)::set_ends_concrete(code_type filler)
    {m_tiles.front() = m_tiles.back() = filler;}

template <typename CodeType>
void TILE_INST_(1)::resize_concrete(
    size_type new_width,
    code_type filler
) {
    if(new_width < m_tiles.size())
        this->remove_concrete(m_tiles.size()-new_width);
    else if(m_tiles.size() < new_width)
        this->add_concrete(new_width-m_tiles.size(), filler);
}

template <typename CodeType>
void TILE_INST_(1)::expand_concrete(
    size_type dx,
    code_type filler
) {this->add_concrete(dx, filler);}

template <typename CodeType>
void TILE_INST_(1)::shrink_concrete(size_type dx)
    {this->remove_concrete(dx);}

template <typename CodeType>
void TILE_INST_(1)::fill_concrete(code_type filler){
    for(size_type i(0); i < m_tiles.size(); ++i)
        m_tiles[i] = filler;
}

template <typename CodeType>
auto TILE_INST_(2)::operator[](size_type y)const -> const value_type&
    {return subscript_concrete(y);}

template <typename CodeType>
auto TILE_INST_(2)::operator[](size_type y) -> value_type&
    {return subscript_concrete(y);}

template <typename CodeType>
TILE_INST_(2)::Tile_Map(
    size_type new_width, size_type new_length,
    code_type filler
)
    : m_rows(new_length, value_type(new_width, filler))
{}

template <typename CodeType>
auto TILE_INST_(2)::get_concrete
    (size_type x, size_type y)const -> code_type
{return m_rows[y][x];}

template <typename CodeType>
auto TILE_INST_(2)::width_concrete()const -> size_type
    {return this->count_tiles_concrete() / m_rows.size();}

template <typename CodeType>
auto TILE_INST_(2)::width_concrete
    (size_type index)const -> size_type
{return m_rows[index].width();}

template <typename CodeType>
auto TILE_INST_(2)::height_concrete()const -> size_type
    {return m_rows.size();}

template <typename CodeType>
auto TILE_INST_(2)::count_tiles_concrete()const -> size_type {
    size_type toreturn(0);
    for(size_type i(0); i < m_rows.size(); ++i)
        toreturn += m_rows[i].width();
    return toreturn;
}

template <typename CodeType>
void TILE_INST_(2)::set_concrete(
    size_type x, size_type y,
    code_type newTile
){m_rows[y][x] = newTile;}

template <typename CodeType>
void TILE_INST_(2)::add_row_concrete(
    size_type dy,
    code_type filler
){
    while(dy-- > 0)
        m_rows.push_back(value_type(this->width(), filler));
}

template <typename CodeType>
void TILE_INST_(2)::add_column_concrete(
    size_type dx,
    code_type filler
){
    for(size_type i(0); i < m_rows.size(); ++i)
        m_rows[i].add(dx, filler);
}

template <typename CodeType>
void TILE_INST_(2)::remove_row_concrete(size_type dy)
    {while(dy-- > 0)    m_rows.pop_back();}

template <typename CodeType>
void TILE_INST_(2)::remove_column_concrete(size_type dx){
    for(size_type i(0); i < m_rows.size(); ++i){
        size_type copy(dx);
        while(copy-- > 0)   m_rows[i].remove();
    }
}

template <typename CodeType>
void TILE_INST_(2)::insert_column_concrete(
    size_type x, size_type dx,
    code_type filler
){
    for(size_type i(0); i < m_rows.size(); ++i)
        m_rows[i].insert(x, dx, filler);
}

template <typename CodeType>
void TILE_INST_(2)::insert_row_concrete(
    size_type y, size_type dy,
    code_type filler
){
    m_rows.insert(
        m_rows.begin()+y, dy,
        value_type(this->width(), filler)
    );
}

template <typename CodeType>
void TILE_INST_(2)::erase_column_concrete(
    size_type x,
    size_type dx
){
    for(size_type i(0); i < m_rows.size(); ++i)
        m_rows[i].erase(x, dx);
}

template <typename CodeType>
void TILE_INST_(2)::erase_row_concrete
    (size_type y, size_type dy)
{m_rows.erase(m_rows.begin()+y, m_rows.begin()+y+dy);}

template <typename CodeType>
void TILE_INST_(2)::set_corners_concrete(code_type filler){
    m_rows.front().set_ends(filler);
    m_rows.back().set_ends(filler);
}

template <typename CodeType>
void TILE_INST_(2)::set_borders_concrete(code_type filler){
    m_rows.front().fill(filler);
    m_rows.back().fill(filler);
    for(size_type i(1); i < m_rows.size()-1; ++i)
        m_rows[i][0] = m_rows[i][m_rows[i].width()-1] = filler;
}

template <typename CodeType>
void TILE_INST_(2)::resize_concrete(
    size_type new_width, size_type new_length,
    code_type filler
){
    if(new_length < m_rows.size())
        this->remove_row_concrete(m_rows.size()-new_length);
    for(size_type i(0); i < m_rows.size(); ++i){
        while(new_width > m_rows[i].width())    m_rows[i].add(filler);
        while(new_width < m_rows[i].width())    m_rows[i].remove();
    }
    if(m_rows.size() < new_length)
        this->add_row_concrete(new_length-m_rows.size(), filler);
}

template <typename CodeType>
void TILE_INST_(2)::expand_concrete(
    size_type dx, size_type dy,
    code_type filler
) {
    this->add_column_concrete(dx, filler);
    this->add_row_concrete(dy, filler);
}

template <typename CodeType>
void TILE_INST_(2)::shrink_concrete
    (size_type dx, size_type dy)
{
    this->remove_row_concrete(dy);
    this->remove_column_concrete(dx);
}

template <typename CodeType>
void TILE_INST_(2)::fill_concrete(code_type filler) {
    for(size_type i(0); i < m_rows.size(); ++i)
        m_rows[i].fill(filler);
}

template <typename CodeType>
auto TILE_INST_(2)::subscript_concrete
    (size_type y)const -> const value_type&
{return m_rows.at(y);}

template <typename CodeType>
auto TILE_INST_(2)::subscript_concrete(size_type y) -> value_type&
    {return m_rows[y];}

template<typename CodeType>
auto TILE_INST_(3)::operator[](size_type z)const -> const value_type&
    {return m_layers[z];}

template<typename CodeType>
auto TILE_INST_(3)::operator[](size_type z) -> value_type&
    {return m_layers[z];}

template<typename CodeType>
TILE_INST_(3)::Tile_Map(
    size_type new_width, size_type new_length,
    size_type new_depth, code_type filler
)
    : m_layers(new_depth, value_type(new_width, new_length, filler))
{}

template<typename CodeType>
auto TILE_INST_(3)::get_concrete(
    size_type x,
    size_type y,
    size_type z
)const -> code_type {return m_layers[z][y][x];}

template<typename CodeType>
auto TILE_INST_(3)::width_concrete()const -> size_type {
    return this->count_tiles_concrete()
        / this->height_concrete()
        / m_layers.size();
}

template<typename CodeType>
auto TILE_INST_(3)::height_concrete()const -> size_type {
    size_type toreturn(0);
    for(size_type i(0); i < m_layers.size(); ++i)
        toreturn += m_layers[i].height();
    return toreturn / m_layers.size();
}

template<typename CodeType>
auto TILE_INST_(3)::depth_concrete()const -> size_type
    {return m_layers.size();}

template<typename CodeType>
auto TILE_INST_(3)::count_tiles_concrete()const -> size_type {
    size_type toreturn(0);
    for(size_type i(0); i < m_layers.size(); ++i)
        toreturn += m_layers[i].count_tiles();
    return toreturn;
}

template<typename CodeType>
void TILE_INST_(3)::set_concrete(
    size_type x, size_type y, size_type z,
    code_type newTile
){m_layers[z][y][x] = newTile;}

template<typename CodeType>
void TILE_INST_(3)::add_x_layer_concrete(
    size_type dx,
    code_type filler
){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].add_column(dx, filler);
}

template<typename CodeType>
void TILE_INST_(3)::add_y_layer_concrete(
    size_type dy,
    code_type filler
){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].add_row(dy, filler);
}

template<typename CodeType>
void TILE_INST_(3)::add_z_layer_concrete(
    size_type dz,
    code_type filler
){
    while(dz-- > 0)
        m_layers.push_back(value_type(
            this->width_concrete(), this->height_concrete(),
            filler
        ));
}

template<typename CodeType>
void TILE_INST_(3)::remove_x_layer_concrete(size_type dx){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].remove_column(dx);
}

template<typename CodeType>
void TILE_INST_(3)::remove_y_layer_concrete(size_type dy){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].remove_row(dy);
}

template<typename CodeType>
void TILE_INST_(3)::remove_z_layer_concrete(size_type dz)
    {while(dz-- > 0)    m_layers.pop_back();}

template<typename CodeType>
void TILE_INST_(3)::insert_x_layer_concrete(
    size_type x, size_type dx,
    code_type filler
){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].insert_column(x, dx, filler);
}

template<typename CodeType>
void TILE_INST_(3)::insert_y_layer_concrete(
    size_type y, size_type dy,
    code_type filler
){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].insert_row(y, dy, filler);
}

template<typename CodeType>
void TILE_INST_(3)::insert_z_layer_concrete(
    size_type z, size_type dz,
    code_type filler
){
    m_layers.insert(
        m_layers.begin()+z, dz,
        value_type(this->width(), this->height(), filler)
    );
}

template<typename CodeType>
void TILE_INST_(3)::erase_x_layer_concrete(
    size_type x,
    size_type dx
){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].erase_column(x, dx);
}

template<typename CodeType>
void TILE_INST_(3)::erase_y_layer_concrete(
    size_type y,
    size_type dy
){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].erase_row(y, dy);
}

template<typename CodeType>
void TILE_INST_(3)::erase_z_layer_concrete(
    size_type z,
    size_type dz
){
    m_layers.erase(
        m_layers.begin()+z,
        m_layers.begin()+z+dz
    );
}

template<typename CodeType>
void TILE_INST_(3)::set_edges_concrete(code_type filler){
    m_layers.front().set_borders(filler);
    m_layers.back().set_borders(filler);
    for(size_type i(1); i < m_layers.size()-1; ++i)
        m_layers[i].set_corners(filler);
}

template<typename CodeType>
void TILE_INST_(3)::set_faces_concrete(code_type filler){
    m_layers.front().fill(filler);
    m_layers.back().fill(filler);
    for(size_type i(1); i < m_layers.size()-1; ++i)
        m_layers[i].set_borders(filler);
}

template<typename CodeType>
void TILE_INST_(3)::resize_concrete(
    size_type new_width, size_type new_length, size_type new_depth,
    code_type filler
){
    if(new_depth < m_layers.size())
        this->remove_z_layer_concrete(new_depth-m_layers.size());
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].resize(new_width, new_length, filler);
    if(m_layers.size() < new_depth)
        this->add_z_layer_concrete(m_layers.size()-new_depth, filler);
}

template<typename CodeType>
void TILE_INST_(3)::expand_concrete(
    size_type dx, size_type dy, size_type dz,
    code_type filler
){
    this->add_x_layer_concrete(dx, filler);
    this->add_y_layer_concrete(dy, filler);
    this->add_z_layer_concrete(dz, filler);
}

template<typename CodeType>
void TILE_INST_(3)::shrink_concrete(
    size_type dx,
    size_type dy,
    size_type dz
){
    this->remove_z_layer_concrete(dz);
    this->remove_y_layer_concrete(dy);
    this->remove_x_layer_concrete(dx);
}

template<typename CodeType>
void TILE_INST_(3)::fill_concrete(code_type filler){
    for(size_type i(0); i < m_layers.size(); ++i)
        m_layers[i].fill(filler);
}

template<typename CodeType>
auto TILE_INST_(3)::subscript_concrete
    (size_type z)const -> const value_type&
{return m_layers.at(z);}

template<typename CodeType>
auto TILE_INST_(3)::subscript_concrete(size_type z) -> value_type&
    {return m_layers[z];}

#undef TILE_INST_