#ifndef TILEMAP_GUI_USING_SFML_AND_DATA_H_____1389721HHHHH_HHHH_
#define TILEMAP_GUI_USING_SFML_AND_DATA_H_____1389721HHHHH_HHHH_

#include "H/Tile_Map.h"
#include "Tile_Constants.h"
#include "Manager_GUI.h"

#include <SFML/Graphics.hpp>

#include <utility>
#include <initializer_list>
#include <vector>

namespace GUI{
    namespace Resource{
        typedef BasicManager<sf::Texture, Data::Tile::code> Manager;
    }

    template <
        std::size_t Dimension,
        sf::PrimitiveType = sf::PrimitiveType::Quads,
        typename CodeTypeParam = Data::Tile::code
    >
    class TileMap;

    template<typename CodeTypeParam>
    class TileMap<1, sf::PrimitiveType::Quads, CodeTypeParam>
        : public Data::Tile_Map<1, CodeTypeParam>
        , public sf::Drawable
        , public sf::Transformable
    {
        public:
            using DataType          = Data::Tile_Map<1, CodeTypeParam>;
            using size_type         = typename DataType::size_type;
            using code_type         = typename DataType::code_type;
            using value_type        = typename DataType::value_type;
            using container_type    = typename DataType::container_type;
            using VertexArrayType   = sf::VertexArray;

            static constexpr sf::PrimitiveType
                TileShape = sf::PrimitiveType::Quads;

/* Inherited
            code_type get(size_type x)const;
            size_type width()const;
            static constexpr size_type height()const;
            static constexpr size_type depth()const;
            size_type count_tiles()const;
            void set(size_type x, code_type newTile);
            void add(code_type filler = code_type::Void);
            void add(size_type dx, code_type filler = code_type::Void);
            void remove();
            void remove(size_type dx);
            void insert(size_type x, code_type filler = code_type::Void);
            void insert(size_type x, size_type dx, code_type filler);
            void erase(size_type x);
            void erase(size_type x, size_type dx);
            void set_ends(code_type filler);
            void resize(
                size_type new_width
                code_type filler = code_type::Void
            );
            void expand(
                size_type dx,
                code_type filler = code_type::Void
            );
            void shrink(size_type dx);
            void fill(code_type filler);

            const value_type& operator[](size_type x)const;
            value_type& operator[](size_type x);
*/

            const sf::Vector2f& getTileSize()const;

            const Resource::Manager& getManager()const;

            void setManager(const Resource::Manager& newManager);

            void setTileTexture(size_type x, code_type code);
            void setTileTexture(const code_type* codes);
            void setTileTexture(const std::initializer_list<code_type>& codes);

            void setTileColor(size_type x, const sf::Color& c);

            sf::Color getTileColor(size_type x);

            TileMap();
            TileMap(
                const Resource::Manager& newManager, sf::Vector2f newTileSize,
                size_type new_width = 0, code_type filler = code_type::Void
            );
            virtual ~TileMap(){}

        protected:
/* Inherited
            virtual code_type get_concrete(size_type x)const override;
            virtual size_type width_concrete()const override;
            virtual size_type count_tiles_concrete()const override;
*/
            virtual void set_concrete(size_type x, code_type newTile) override;
            virtual void add_concrete(size_type dx, code_type filler) override;
            virtual void remove_concrete(size_type dx) override;
            virtual void insert_concrete
                (size_type x, size_type dx, code_type filler) override;
            virtual void erase_concrete(size_type x, size_type dx) override;
            virtual void set_ends_concrete(code_type filler) override;
/* Inherited
            virtual void resize_concrete(size_type, code_type) override;
            virtual void expand_concrete(size_type dx, code_type) override;
            virtual void shrink_concrete(size_type dx) override;
*/
            virtual void fill_concrete(code_type filler) override;
            virtual void draw(
                sf::RenderTarget& target,
                sf::RenderStates states
            )const override;

        private:
            const Resource::Manager*      mManager;
            VertexArrayType     mVertices;
            sf::Vector2f        mTileSize;
    };

    template<typename CodeTypeParam>
    class TileMap<2, sf::PrimitiveType::Quads, CodeTypeParam>
        : public Data::Map<2, CodeTypeParam>
        , public sf::Drawable
        , public sf::Transformable
    {
        public:
            static constexpr sf::PrimitiveType
                TileShape = sf::PrimitiveType::Quads;

            using DataType          = Data::Map<2, CodeTypeParam>;
            using size_type         = typename DataType::size_type;
            using code_type         = typename DataType::code_type;
            using VertexArrayType   = sf::VertexArray;
            using value_type        = TileMap<1, TileShape, CodeTypeParam>;
            using container_type    = std::vector<value_type>;

/* Inherited
            void setPosition(float x, float y);
            void setPosition(const Vector2f& position);
            void setRotation(float angle);
            void setScale(float factorX, float factorY);
            void setScale(const Vector2f& factors);
            void setOrigin(float x, float y);
            void setOrigin(const Vector2f& origin);
            const Vector2f& getPosition() const;
            float getRotation() const;
            const Vector2f& getScale() const;
            const Vector2f& getOrigin() const;
            void move(float offsetX, float offsetY);
            void move(const Vector2f& offset);
            void rotate(float angle);
            void scale(float factorX, float factorY);
            void scale(const Vector2f& factor);
            const Transform& getTransform() const;
            const Transform& getInverseTransform() const;


            code_type get(size_type x, size_type y)const;
            size_type width()const;
            size_type height()const;
            size_type count_tiles()const;
            void set(size_type x, size_type y, code_type newTile);
            void add_row(code_type filler = code_type::Void);
            void add_row(size_type dy, code_type filler = code_type::Void);
            void add_column(code_type filler = code_type::Void);
            void add_column(size_type dx, code_type filler = code_type::Void);
                //Removes last row
            void remove_row();
            void remove_row(size_type dy);
                //Removes last column
            void remove_column();
            void remove_column(size_type dx);
            void insert_column(size_type x, code_type filler = code_type::Void);
            void insert_column(size_type x, size_type dx, code_type filler);
            void insert_row(size_type y, code_type filler = code_type::Void);
            void insert_row(size_type y, size_type dy, code_type filler);
            void erase_column(size_type x);
            void erase_column(size_type x, size_type dx);
            void erase_row(size_type y);
            void erase_row(size_type y, size_type dy);
            void set_corners(code_type filler);
            void set_borders(code_type filler);
            void resize(
                size_type new_width, size_type new_length,
                code_type filler = code_type::Void
            );
            void expand(
                size_type dx, size_type dy,
                code_type filler = code_type::Void
            );
            void shrink(size_type dx, size_type dy);
            void fill(code_type filler);
*/

            const value_type& operator[](size_type y)const;

            value_type& operator[](size_type y);

            const sf::Vector2f& getTileSize()const;

            const Resource::Manager& getManager()const;

            void setManager(const Resource::Manager& newManager);

            void setTileTexture(
                size_type x, size_type y,
                code_type newTile
            );
            void setTileTexture(const code_type* newTiles);
            void setTileTexture(const std::initializer_list<code_type>& codes);

            void setTileColor(size_type x, size_type y, const sf::Color& c);

            sf::Color getTileColor(size_type x, size_type y);

            TileMap();
            TileMap(
                const Resource::Manager& newManager, sf::Vector2f newTileSize,
                size_type new_width = 0, size_type new_length = 0,
                code_type filler = code_type::Void
            );
            virtual ~TileMap(){}

        protected:
            virtual code_type get_concrete
                (size_type x, size_type y)const override;
            virtual size_type width_concrete()const override;
            virtual size_type width_concrete(size_type index)const override;
            virtual size_type height_concrete()const override;
            virtual size_type count_tiles_concrete()const override;
            virtual void set_concrete
                (size_type x, size_type y, code_type newTile) override;
            virtual void add_row_concrete
                (size_type dy, code_type filler) override;
            virtual void add_column_concrete
                (size_type dx, code_type filler) override;
            virtual void remove_row_concrete(size_type dy) override;
            virtual void remove_column_concrete(size_type dx) override;
            virtual void insert_column_concrete
                (size_type x, size_type dx, code_type filler) override;
            virtual void insert_row_concrete
                (size_type y, size_type dy, code_type filler) override;
            virtual void erase_column_concrete
                (size_type x, size_type dx) override;
            virtual void erase_row_concrete(size_type y, size_type dy) override;
            virtual void set_corners_concrete(code_type filler) override;
            virtual void set_borders_concrete(code_type filler) override;
            virtual void resize_concrete(
                size_type new_width, size_type new_length,
                code_type filler
            ) override;
            virtual void expand_concrete
                (size_type dx, size_type dy, code_type filler) override;
            virtual void shrink_concrete(size_type dx, size_type dy) override;
            virtual void fill_concrete(code_type filler) override;
            virtual void draw(
                sf::RenderTarget& target,
                sf::RenderStates states
            )const override;

        private:
            container_type mRows;
    };

        /*
         * index 0 shall be the first layer drawn 
         */
    template<typename CodeTypeParam>
    class TileMap<3, sf::PrimitiveType::Quads, CodeTypeParam>
        : public Data::Map<3, CodeTypeParam>
        , public sf::Drawable
        , public sf::Transformable
    {
        public:
            static constexpr sf::PrimitiveType
                TileShape = sf::PrimitiveType::Quads;

            using DataType          = Data::Map<3, CodeTypeParam>;
            using size_type         = typename DataType::size_type;
            using code_type         = typename DataType::code_type;
            using value_type        = TileMap<2, TileShape, CodeTypeParam>;
            using VertexArrayType   = typename value_type::VertexArrayType;
            using container_type    = std::vector<value_type>;

/* Inherited
            void setPosition(float x, float y);
            void setPosition(const Vector2f& position);
            void setRotation(float angle);
            void setScale(float factorX, float factorY);
            void setScale(const Vector2f& factors);
            void setOrigin(float x, float y);
            void setOrigin(const Vector2f& origin);
            const Vector2f& getPosition() const;
            float getRotation() const;
            const Vector2f& getScale() const;
            const Vector2f& getOrigin() const;
            void move(float offsetX, float offsetY);
            void move(const Vector2f& offset);
            void rotate(float angle);
            void scale(float factorX, float factorY);
            void scale(const Vector2f& factor);
            const Transform& getTransform() const;
            const Transform& getInverseTransform() const;

            code_type get(size_type x, size_type y, size_type z)const
            size_type width()const;  //x-axis
            size_type height()const; //y-axis
            size_type depth()const; //z-axis
            size_type count_tiles()const;
            void set(size_type x, size_type y, size_type z, code_type newTile);
            void add_x_layer(code_type filler = code_type::Void);
            void add_x_layer(size_type dx, code_type filler = code_type::Void);
            void add_y_layer(code_type filler = code_type::Void);
            void add_y_layer(size_type dy, code_type filler = code_type::Void);
            void add_z_layer(code_type filler = code_type::Void);
            void add_z_layer(size_type dz, code_type filler = code_type::Void);
                //Removes last x_layer
            void remove_x_layer();
            void remove_x_layer(size_type dx);
                //Removes last y_layer
            void remove_y_layer();
            void remove_y_layer(size_type dy);
                //Removes last z_layer
            void remove_z_layer();
            void remove_z_layer(size_type dz);
            void insert_x_layer(size_type x, code_type filler = code_type::Void);
            void insert_x_layer(size_type x, size_type dx, code_type filler);
            void insert_y_layer(size_type y, code_type filler = code_type::Void);
            void insert_y_layer(size_type y, size_type dy, code_type filler);
            void insert_z_layer(size_type z, code_type filler = code_type::Void);
            void insert_z_layer(size_type z, size_type dz, code_type filler);
            void erase_x_layer(size_type x);
            void erase_x_layer(size_type x, size_type dx);
            void erase_y_layer(size_type y);
            void erase_y_layer(size_type y, size_type dy);
            void erase_z_layer(size_type z);
            void erase_z_layer(size_type z, size_type dz);
            void set_corners(code_type filler);
            void set_edges(code_type filler);
            void set_faces(code_type filler);
            void resize(
                size_type new_width, size_type new_length, size_type new_depth,
                code_type filler = code_type::Void
            );
            void expand(
                size_type dx, size_type dy, size_type dz,
                code_type filler = code_type::Void
            );
            void shrink(size_type dx, size_type dy, size_type dz);
            void fill(code_type filler);
*/

            const value_type& operator[](size_type z)const;

            value_type& operator[](size_type z);

            const sf::Vector2f& getTileSize()const;

            const Resource::Manager& getManager()const;

            void setManager(const Resource::Manager& newManager);

            void setTileTexture(
                size_type x, size_type y, size_type z,
                code_type newTile
            );
            void setTileTexture(const code_type* newTiles);
            void setTileTexture(const std::initializer_list<code_type>& codes);

            void setTileColor(
                size_type x, size_type y, size_type z,
                const sf::Color& c
            );

            sf::Color getTileColor(size_type x, size_type y, size_type z);

            TileMap();
            TileMap(
                const Resource::Manager& newManager, sf::Vector2f newTileSize,
                size_type new_width = 0, size_type new_length = 0, size_type new_depth = 0,
                code_type filler = code_type::Void
            );
            virtual ~TileMap(){}

        protected:
            virtual code_type get_concrete
                (size_type x, size_type y, size_type z)const override;
            virtual size_type width_concrete()const override;
            virtual size_type height_concrete()const override;
            virtual size_type depth_concrete()const override;
            virtual size_type count_tiles_concrete()const override;
            virtual void set_concrete(
                size_type x, size_type y, size_type z,
                code_type newTile
            ) override;
            virtual void add_x_layer_concrete(size_type dx, code_type filler) override;
            virtual void add_y_layer_concrete(size_type dy, code_type filler) override;
            virtual void add_z_layer_concrete(size_type dz, code_type filler) override;
            virtual void remove_x_layer_concrete(size_type dx) override;
            virtual void remove_y_layer_concrete(size_type dy) override;
            virtual void remove_z_layer_concrete(size_type dz) override;
            virtual void insert_x_layer_concrete
                (size_type x, size_type dx, code_type filler) override;
            virtual void insert_y_layer_concrete
                (size_type y, size_type dy, code_type filler) override;
            virtual void insert_z_layer_concrete
                (size_type z, size_type dz, code_type filler) override;
            virtual void erase_x_layer_concrete(size_type x, size_type dx) override;
            virtual void erase_y_layer_concrete(size_type y, size_type dy) override;
            virtual void erase_z_layer_concrete(size_type z, size_type dz) override;
            virtual void set_corners_concrete(code_type filler) override;
            virtual void set_edges_concrete(code_type filler) override;
            virtual void set_faces_concrete(code_type filler) override;
            virtual void resize_concrete(
                size_type new_width, size_type new_length, size_type new_depth,
                code_type filler
            ) override;
            virtual void expand_concrete(
                size_type dx, size_type dy, size_type dz,
                code_type filler
            ) override;
            virtual void shrink_concrete
                (size_type dx, size_type dy,size_type dz) override;
            virtual void fill_concrete(code_type filler) override;
            virtual void draw(
                sf::RenderTarget& target,
                sf::RenderStates states
            )const override;

        private:
            container_type mLayers;
    };

    #include "Tile_Map_GUI.inl"
}

#endif