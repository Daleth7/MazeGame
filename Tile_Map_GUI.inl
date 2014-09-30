#define TILE_INST_(N)   \
    TileMap<N, sf::PrimitiveType::Quads, CodeTypeParam>

template<typename CodeTypeParam>
const sf::Vector2f& TILE_INST_(1)::getTileSize()const
    {return mTileSize;}

template<typename CodeTypeParam>
const Resource::Manager& TILE_INST_(1)::getManager()const
    {return *mManager;}

template<typename CodeTypeParam>
void TILE_INST_(1)::setManager(const Resource::Manager& newManager)
    {mManager = &newManager;}

template<typename CodeTypeParam>
void TILE_INST_(1)::setTileTexture(size_type x, code_type code){
    sf::IntRect rect = mManager->getArea(code);
    for(size_type i(0); i < 4u; ++i)
        mVertices[x*4u+i].texCoords = sf::Vector2f{
            rect.left+rect.width*static_cast<float>(i > 0 && i < 3),
            rect.top+rect.height*static_cast<float>(i > 1)};
}

template<typename CodeTypeParam>
void TILE_INST_(1)::setTileTexture(const code_type* codes){
    for(size_type i(0); i < this->count_tiles(); ++i)
        this->setTileTexture(i, codes[i]);
}

template<typename CodeTypeParam>
void TILE_INST_(1)::setTileTexture
    (const std::initializer_list<code_type>& codes)
{this->setTileTexture(codes.begin());}

template<typename CodeTypeParam>
void TILE_INST_(1)::setTileColor(size_type x, const sf::Color& c){
    for(size_type i(0); i < 4u; ++i)
        mVertices[x*4u+i].color = c;
}

template<typename CodeTypeParam>
sf::Color TILE_INST_(1)::getTileColor(size_type x){
    sf::Color toreturn{0, 0, 0, 0};
    for(size_type i(0); i < 4u; ++i){
        toreturn.r += mVertices[x*4u+i].color.r/4u;
        toreturn.r += mVertices[x*4u+i].color.g/4u;
        toreturn.r += mVertices[x*4u+i].color.b/4u;
        toreturn.r += mVertices[x*4u+i].color.a/4u;
    }
    return toreturn;
}

template<typename CodeTypeParam>
TILE_INST_(1)::TileMap()
    : DataType::Tile_Map()
    , sf::Drawable::Drawable(), sf::Transformable::Transformable()
    , mManager(nullptr), mVertices(), mTileSize()
{}

template<typename CodeTypeParam>
TILE_INST_(1)::TileMap(
    const Resource::Manager& newManager, sf::Vector2f newTileSize,
    size_type new_width, code_type filler
)
    : DataType::Tile_Map(new_width, filler)
    , sf::Drawable::Drawable(), sf::Transformable::Transformable()
    , mManager(&newManager)
    , mVertices(TileShape, new_width*4), mTileSize(newTileSize)
{
    for(size_type i(0); i < new_width; ++i){
        for(size_type j(0); j < 4u; ++j){
            mVertices[i*4+j].position.x
                = (i+(j>0 && j<3))*mTileSize.x;
            mVertices[i*4+j].position.y = mTileSize.y*(j>1);
        }
        this->setTileTexture(i, filler);
    }
}

template<typename CodeTypeParam>
void TILE_INST_(1)::set_concrete(size_type x, code_type newTile){
    DataType::set_concrete(x, newTile);
    this->setTileTexture(x, newTile);
}

template<typename CodeTypeParam>
void TILE_INST_(1)::add_concrete(size_type dx, code_type filler){
    size_type oldWidth(this->width_concrete());
    DataType::add_concrete(dx, filler);
    while(oldWidth < this->width_concrete()){
        for(size_type i(0); i < 4u; ++i)
            mVertices.append(sf::Vertex(
                {(oldWidth*4u+i+(i>0 && i<3))*mTileSize.x,
                mTileSize.y*(i>1)}));
        this->setTileTexture(oldWidth++, filler);
    }
}

template<typename CodeTypeParam>
void TILE_INST_(1)::remove_concrete(size_type dx){
    DataType::remove_concrete(dx);
    mVertices.resize(mVertices.getVertexCount()-(dx*4u));
}

template<typename CodeTypeParam>
void TILE_INST_(1)::insert_concrete
    (size_type x, size_type dx, code_type filler)
{
    DataType::insert_concrete(x, dx, filler);
    const size_type d4 = dx*4u;
    mVertices.resize(mVertices.getVertexCount()+d4);
    size_type toShift((this->count_tiles()-1-x)*4u);
    VertexArrayType& vS(mVertices); sf::Vector2f& tS(mTileSize);
    while(toShift-- > 0){
        const size_type i(x*4u+toShift), j(toShift%4u);
        using std::swap;
        swap(vS[d4+i].texCoords, vS[i].texCoords);
        const bool rEdge(j > 0 && j < 3), bEdge(j > 1);
        vS[d4+i].position = {((i+d4)/4u+rEdge)*tS.x, bEdge*tS.y};
    }
    for(size_type i(0); i < dx; ++i)
        this->setTileTexture(x+i, filler);
}

template<typename CodeTypeParam>
void TILE_INST_(1)::erase_concrete(size_type x, size_type dx){
    DataType::erase_concrete(x, dx);
    x <<= 2; dx <<= 2;
    for(size_type i(0); i < dx; ++i)
        mVertices[i+x].texCoords = mVertices[i+x+dx].texCoords;
    mVertices.resize(mVertices.getVertexCount()-(dx));
}

template<typename CodeTypeParam>
void TILE_INST_(1)::set_ends_concrete(code_type filler){
    DataType::set_ends_concrete(filler);
    this->setTileTexture(0, filler);
    this->setTileTexture(this->width_concrete()-1, filler);
}

template<typename CodeTypeParam>
void TILE_INST_(1)::fill_concrete(code_type filler){
    for(size_type i(0); i < this->width_concrete(); ++i){
        this->set(i, filler);
        this->setTileTexture(i, filler);
    }
}

template<typename CodeTypeParam>
void TILE_INST_(1)::draw
    (sf::RenderTarget& target, sf::RenderStates states)
const{
    states.texture = mManager->getSheetPtr();
    states.transform *= this->getTransform();
    target.draw(mVertices, states);
}

template<typename CodeTypeParam>
auto TILE_INST_(2)::operator[](size_type y)const -> const value_type&
    {return mRows.at(y);}

template<typename CodeTypeParam>
auto TILE_INST_(2)::operator[](size_type y) -> value_type&
    {return mRows[y];}

template<typename CodeTypeParam>
const sf::Vector2f& TILE_INST_(2)::getTileSize()const
    {return mRows.front().getTileSize();}

template<typename CodeTypeParam>
const Resource::Manager& TILE_INST_(2)::getManager()const
    {return mRows.front().getManager();}

template<typename CodeTypeParam>
void TILE_INST_(2)::setManager(const Resource::Manager& newManager){
    for(size_type i(0); i < mRows.size(); ++i)
        mRows[i].setManager(newManager);
}

template<typename CodeTypeParam>
void TILE_INST_(2)::setTileTexture
    (size_type x, size_type y, code_type newTile)
{mRows[y].setTileTexture(x, newTile);}

template<typename CodeTypeParam>
void TILE_INST_(2)::setTileTexture(const code_type* newTiles){
    size_type index(0);
    for(
        size_type y(0);
        y < this->height();
        index += this->width(y), ++y
    )   (*this)[y].setTileTexture(newTiles + index);
}

template<typename CodeTypeParam>
void TILE_INST_(2)::setTileTexture
    (const std::initializer_list<code_type>& codes)
{this->setTileTexture(codes.begin());}

template<typename CodeTypeParam>
void TILE_INST_(2)::setTileColor
    (size_type x, size_type y, const sf::Color& c)
{mRows[y].setTileColor(x, c);}

template<typename CodeTypeParam>
sf::Color TILE_INST_(2)::getTileColor(size_type x, size_type y)
    {return mRows[y].getTileColor(x);}

template<typename CodeTypeParam>
TILE_INST_(2)::TileMap()
    : DataType::Map()
    , sf::Drawable::Drawable(), sf::Transformable::Transformable()
    , mRows()
{}

template<typename CodeTypeParam>
TILE_INST_(2)::TileMap(
    const Resource::Manager& newManager, sf::Vector2f newTileSize,
    size_type new_width, size_type new_length, code_type filler
)
    : DataType::Map()
    , sf::Drawable::Drawable(), sf::Transformable::Transformable()
    , mRows(new_length
        , value_type(newManager, newTileSize, new_width, filler))
{
    for(size_type i(0); i < new_length; ++i)
        mRows[i].move(0, i*newTileSize.y);
}

template<typename CodeTypeParam>
auto TILE_INST_(2)::get_concrete
    (size_type x, size_type y)const -> code_type
{return mRows.at(y).get(x);}

template<typename CodeTypeParam>
auto TILE_INST_(2)::width_concrete()const -> size_type
    {return this->count_tiles_concrete() / this->height();}

template<typename CodeTypeParam>
auto TILE_INST_(2)::width_concrete(size_type index)const -> size_type
    {return mRows.at(index).width();}

template<typename CodeTypeParam>
auto TILE_INST_(2)::height_concrete()const -> size_type
    {return mRows.size();}

template<typename CodeTypeParam>
auto TILE_INST_(2)::count_tiles_concrete()const -> size_type {
    size_type toreturn(0);
    for(const auto& row : mRows)    toreturn += row.count_tiles();
    return toreturn;
}

template<typename CodeTypeParam>
void TILE_INST_(2)::set_concrete
    (size_type x, size_type y, code_type newTile)
{mRows[y].set(x, newTile);}

template<typename CodeTypeParam>
void TILE_INST_(2)::add_row_concrete(size_type dy, code_type filler){
    while(dy-- > 0)
        mRows.push_back(value_type(
            this->getManager(), this->getTileSize(),
            this->width_concrete(), filler));
}

template<typename CodeTypeParam>
void TILE_INST_(2)::add_column_concrete(size_type dx, code_type filler)
    {for(auto& row : mRows)  row.add(dx, filler);}

template<typename CodeTypeParam>
void TILE_INST_(2)::remove_row_concrete(size_type dy)
    {while(dy-- > 0) mRows.pop_back();}

template<typename CodeTypeParam>
void TILE_INST_(2)::remove_column_concrete(size_type dx)
    {for(auto& row : mRows) row.remove(dx);}

template<typename CodeTypeParam>
void TILE_INST_(2)::insert_column_concrete
    (size_type x, size_type dx, code_type filler)
{for(auto& row : mRows)   row.insert(x, dx, filler);}

template<typename CodeTypeParam>
void TILE_INST_(2)::insert_row_concrete
    (size_type y, size_type dy, code_type filler)
{
    mRows.insert(mRows.begin()+y, dy, value_type(
        this->getManager(), this->getTileSize(),
        this->width_concrete(), filler));
}

template<typename CodeTypeParam>
void TILE_INST_(2)::erase_column_concrete(size_type x, size_type dx)
    {for(auto& row : mRows)   row.erase(x, dx);}

template<typename CodeTypeParam>
void TILE_INST_(2)::erase_row_concrete(size_type y, size_type dy){
    mRows.erase(mRows.begin()+y, mRows.begin()+y+dy);
    for(size_type i(y); i < mRows.size(); ++i){
        mRows[i].move(0
            , -static_cast<float>(dy*this->getTileSize().y));
    }
}

template<typename CodeTypeParam>
void TILE_INST_(2)::set_corners_concrete(code_type filler){
    mRows.front().set_ends(filler);
    mRows.back().set_ends(filler);
}

template<typename CodeTypeParam>
void TILE_INST_(2)::set_borders_concrete(code_type filler){
    mRows.front().fill(filler);
    mRows.back().fill(filler);
    for(size_type i(1); i < mRows.size()-1; ++i)
        mRows[i].set_ends(filler);
}

template<typename CodeTypeParam>
void TILE_INST_(2)::resize_concrete(
    size_type new_width, size_type new_length,
    code_type filler
){
    if(new_length < mRows.size())
        this->remove_row_concrete(mRows.size()-new_length);
    for(auto& row : mRows)  row.resize(new_width, filler);
    if(mRows.size() < new_length)
        this->add_row_concrete(new_length - mRows.size(), filler);
}

template<typename CodeTypeParam>
void TILE_INST_(2)::expand_concrete(
    size_type dx, size_type dy,
    code_type filler
){
    for(auto& row : mRows)  row.add(dx, filler);
    this->add_row_concrete(dy, filler);
}

template<typename CodeTypeParam>
void TILE_INST_(2)::shrink_concrete(size_type dx, size_type dy){
    this->remove_row_concrete(dy);
    for(auto& row : mRows)  row.remove(dx);
}

template<typename CodeTypeParam>
void TILE_INST_(2)::fill_concrete(code_type filler)
    {for(auto& row : mRows) row.fill(filler);}

template<typename CodeTypeParam>
void TILE_INST_(2)::draw(
    sf::RenderTarget& target,
    sf::RenderStates states
)const{
    states.transform *= this->getTransform();
    for(const auto& row : mRows) target.draw(row, states);
}

template<typename CodeTypeParam>
auto TILE_INST_(3)::operator[](size_type z)const -> const value_type&
    {return mLayers.at(z);}

template<typename CodeTypeParam>
auto TILE_INST_(3)::operator[](size_type z) -> value_type&
    {return mLayers[z];}

template<typename CodeTypeParam>
const sf::Vector2f& TILE_INST_(3)::getTileSize()const
    {return mLayers.front().getTileSize();}

template<typename CodeTypeParam>
const Resource::Manager& TILE_INST_(3)::getManager()const
    {return mLayers.front().getManager();}

template<typename CodeTypeParam>
void TILE_INST_(3)::setManager(const Resource::Manager& newManager){
    for(size_type i(0); i < mLayers.size(); ++i)
        mLayers[i].setManager(newManager);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::setTileTexture(
    size_type x, size_type y, size_type z,
    code_type newTile
){mLayers[z].setTileTexture(x, y, newTile);}

template<typename CodeTypeParam>
void TILE_INST_(3)::setTileTexture(const code_type* newTiles){
    size_type index(0);
    for(
        size_type z(0);
        z < this->depth();
        index += this->height(z)*this->width(z), ++z
    )   (*this)[z].setTileTexture(newTiles + index);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::setTileTexture
    (const std::initializer_list<code_type>& codes)
{this->setTileTexture(codes.begin());}

template<typename CodeTypeParam>
void TILE_INST_(3)::setTileColor(
    size_type x, size_type y, size_type z,
    const sf::Color& c
){mLayers[z].setTileColor(x, y, c);}

template<typename CodeTypeParam>
sf::Color TILE_INST_(3)::getTileColor
    (size_type x, size_type y, size_type z)
{return mLayers[z].getTileColor(x, y);}

template<typename CodeTypeParam>
TILE_INST_(3)::TileMap()
    : DataType::Map()
    , sf::Drawable::Drawable(), sf::Transformable::Transformable()
    , mLayers()
{}

template<typename CodeTypeParam>
TILE_INST_(3)::TileMap(
    const Resource::Manager& newManager, sf::Vector2f newTileSize,
    size_type new_width, size_type new_length, size_type new_depth,
    code_type filler
)
    : DataType::Map()
    , sf::Drawable::Drawable(), sf::Transformable::Transformable()
    , mLayers(new_depth
        , value_type(newManager, newTileSize,
        new_width, new_length, filler))
{}

template<typename CodeTypeParam>
auto TILE_INST_(3)::get_concrete
    (size_type x, size_type y, size_type z)const -> code_type
{return mLayers.at(z).get(x, y);}

template<typename CodeTypeParam>
auto TILE_INST_(3)::width_concrete()const -> size_type
    {return this->count_tiles() / this->depth() / this->height();}

template<typename CodeTypeParam>
auto TILE_INST_(3)::height_concrete()const -> size_type {
    size_type toreturn(0);
    for(size_type i(0); i < this->depth(); ++i)
        toreturn += mLayers.at(i).height();
    return toreturn / this->depth();
}

template<typename CodeTypeParam>
auto TILE_INST_(3)::depth_concrete()const -> size_type
    {return mLayers.size();}

template<typename CodeTypeParam>
auto TILE_INST_(3)::count_tiles_concrete()const -> size_type{
    size_type toreturn(0);
    for(size_type i(0); i < this->depth(); ++i)
        toreturn += mLayers.at(i).count_tiles();
    return toreturn;
}

template<typename CodeTypeParam>
void TILE_INST_(3)::set_concrete(
    size_type x, size_type y, size_type z,
    code_type newTile
) {mLayers.at(z).set(x, y, newTile);}

template<typename CodeTypeParam>
void TILE_INST_(3)::add_x_layer_concrete
    (size_type dx, code_type filler)
{
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).add_column(dx, filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::add_y_layer_concrete
    (size_type dy, code_type filler)
{
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).add_row(dy, filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::add_z_layer_concrete(size_type dz, code_type filler)
    {this->insert_z_layer_concrete(this->depth()-1u, dz, filler);}

template<typename CodeTypeParam>
void TILE_INST_(3)::remove_x_layer_concrete(size_type dx) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).remove_column(dx);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::remove_y_layer_concrete(size_type dy) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).remove_row(dy);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::remove_z_layer_concrete(size_type dz)
    {while(dz-- > 0) mLayers.pop_back();}

template<typename CodeTypeParam>
void TILE_INST_(3)::insert_x_layer_concrete(
    size_type x, size_type dx,
    code_type filler
) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).insert_column(x, dx, filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::insert_y_layer_concrete(
    size_type y, size_type dy,
    code_type filler
) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).insert_row(y, dy, filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::insert_z_layer_concrete(
    size_type z, size_type dz,
    code_type filler
) {
    value_type new_layer(
        this->getManager(), this->getTileSize(),
        this->width(), this->height(), filler
    );
    mLayers.insert(mLayers.begin()+z, dz, new_layer);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::erase_x_layer_concrete(size_type x, size_type dx) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).erase_column(x, dx);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::erase_y_layer_concrete(size_type y, size_type dy) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).erase_row(y, dy);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::erase_z_layer_concrete(size_type z, size_type dz)
    {mLayers.erase(mLayers.begin()+z, mLayers.begin()+z+dz);}

template<typename CodeTypeParam>
void TILE_INST_(3)::set_corners_concrete(code_type filler) {
    mLayers.front().set_corners(filler);
    mLayers.back().set_corners(filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::set_edges_concrete(code_type filler) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).set_corners(filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::set_faces_concrete(code_type filler) {
    mLayers.front().fill(filler);
    mLayers.back().fill(filler);
    for(size_type z(1); z < this->depth()-1; ++z)
        mLayers.at(z).set_borders(filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::resize_concrete(
    size_type new_width, size_type new_length, size_type new_depth,
    code_type filler
) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).resize(new_width, new_length, filler);
    value_type new_layer(
        this->getManager(), this->getTileSize(),
        this->width(), this->height(), filler
    );
    mLayers.resize(new_depth, new_layer);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::expand_concrete(
    size_type dx, size_type dy, size_type dz,
    code_type filler
) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).expand(dx, dy, filler);
    this->add_z_layer(dz, filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::shrink_concrete(
    size_type dx,
    size_type dy,
    size_type dz
) {
    this->remove_z_layer(dz);
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).shrink(dx, dy);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::fill_concrete(code_type filler) {
    for(size_type z(0); z < this->depth(); ++z)
        mLayers.at(z).fill(filler);
}

template<typename CodeTypeParam>
void TILE_INST_(3)::draw(
    sf::RenderTarget& target,
    sf::RenderStates states
)const{
    states.transform *= this->getTransform();
    for(const auto& layer : mLayers)
        target.draw(layer, states);
}

#undef TILE_INST_