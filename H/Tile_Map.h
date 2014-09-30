#ifndef NEWTILEMAP_U_H3847777_H8HHH_
#define NEWTILEMAP_U_H3847777_H8HHH_

#include "Map.h"

#include "Tile_Codes.h"

#include <vector>

namespace Data{
    template <std::size_t N, typename CodeType = Data::Tile::code>
    class Tile_Map;

    template <typename CodeType>
    class Tile_Map<0, CodeType> : public Map<0, CodeType>{
        public:
            using size_type     = std::size_t;
            using code_type     = typename Map<0, CodeType>::code_type;
            using value_type    = typename Map<0, CodeType>::code_type;
/* Inherited
            code_type get()const;
            static constexpr size_type width();
            static constexpr size_type height();
            static constexpr size_type depth();
            static constexpr size_type count_tiles();
            void set(code_type newTile);
            void fill(code_type filler);
            operator code_type()const;
            operator code_type&();
*/
            constexpr Tile_Map(value_type new_val);
            Tile_Map() = default;
            virtual ~Tile_Map(){}

        protected:
            virtual code_type get_concrete()const override;
            virtual void set_concrete(code_type newTile) override;
            virtual void fill_concrete(code_type filler) override;
            virtual code_type cast_concrete()const override;
            virtual code_type& cast_concrete() override;

        private:
            value_type  m_val;
    };

    template <typename CodeType>
    class Tile_Map<1, CodeType> : public Map<1, CodeType>{
        public:
            using size_type         = typename Map<1, CodeType>::size_type;
            using code_type         = typename Map<1, CodeType>::code_type;
            using value_type        = Tile_Map<0, CodeType>;
            using container_type    = std::vector<value_type>;
/* Inherited
            code_type get(size_type x)const;
            size_type width()const;
            static constexpr size_type height();
            static constexpr size_type depth();
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
                size_type new_width,
                code_type filler = code_type::Void
            );
            void expand(
                size_type dx,
                code_type filler = code_type::Void
            );
            void shrink(size_type dx);
            void fill(code_type filler);
*/

            const value_type& operator[](size_type x)const;
            value_type& operator[](size_type x);
            Tile_Map(size_type new_width = 0, code_type filler = code_type::Void);
            virtual ~Tile_Map(){}

        protected:
            virtual code_type get_concrete(size_type x)const override;
            virtual size_type width_concrete()const override;
            virtual size_type count_tiles_concrete()const override;
            virtual void set_concrete(
                size_type x,
                code_type newTile
            ) override;
            virtual void add_concrete(size_type dx, code_type filler) override;
            virtual void remove_concrete(size_type dx) override;
            virtual void insert_concrete(
                size_type x, size_type dx, code_type filler
            ) override;
            virtual void erase_concrete(size_type x, size_type dx) override;
            virtual void set_ends_concrete(code_type filler) override;
            virtual void resize_concrete(
                size_type new_width,
                code_type filler
            ) override;
            virtual void expand_concrete(
                size_type dx,
                code_type filler
            ) override;
            virtual void shrink_concrete(size_type dx) override;
            virtual void fill_concrete(code_type filler) override;

        private:
            container_type  m_tiles;
    };

    template <typename CodeType>
    class Tile_Map<2, CodeType> : public Map<2, CodeType>{
        public:
            using size_type         = typename Map<2, CodeType>::size_type;
            using code_type         = typename Map<2, CodeType>::code_type;
            using value_type        = Tile_Map<1, CodeType>;
            using ivalue_type       = typename value_type::value_type;
            using container_type    = std::vector<value_type>;
/* Inherited
            code_type get(size_type x, size_type y)const;
            size_type width()const;
            size_type width(size_type y)const;
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
            Tile_Map(
                size_type new_width = 0, size_type new_length = 0,
                code_type filler = code_type::Void
            );
            virtual ~Tile_Map(){}

        protected:
            virtual code_type get_concrete(size_type x, size_type y)const override;
            virtual size_type width_concrete()const override;
            virtual size_type width_concrete(size_type index)const override;
            virtual size_type height_concrete()const override;
            virtual size_type count_tiles_concrete()const override;
            virtual void set_concrete(
                size_type x, size_type y,
                code_type newTile
            ) override;
            virtual void add_row_concrete(
                size_type dy,
                code_type filler
            ) override;
            virtual void add_column_concrete(
                size_type dx,
                code_type filler
            ) override;
            virtual void remove_row_concrete(size_type dy) override;
            virtual void remove_column_concrete(size_type dx) override;
            virtual void insert_column_concrete(
                size_type x, size_type dx,
                code_type filler
            ) override;
            virtual void insert_row_concrete(
                size_type y, size_type dy,
                code_type filler
            ) override;
            virtual void erase_column_concrete(
                size_type x,
                size_type dx
            ) override;
            virtual void erase_row_concrete(size_type y, size_type dy) override;
            virtual void set_corners_concrete(code_type filler) override;
            virtual void set_borders_concrete(code_type filler) override;
            virtual void resize_concrete(
                size_type new_width, size_type new_length,
                code_type filler
            ) override;
            virtual void expand_concrete(
                size_type dx, size_type dy,
                code_type filler
            ) override;
            virtual void shrink_concrete(size_type dx, size_type dy) override;
            virtual void fill_concrete(code_type filler) override;
            virtual const value_type& subscript_concrete(size_type y)const;
            virtual value_type& subscript_concrete(size_type y);

        private:
            container_type m_rows;
    };

    template<typename CodeType>
    class Tile_Map<3, CodeType> : public Map<3, CodeType>{
        public:
            using size_type         = typename Map<3, CodeType>::size_type;
            using code_type         = typename Map<3, CodeType>::code_type;
            using value_type        = Tile_Map<2, CodeType>;
            using ivalue_type       = typename value_type::value_type;
            using iivalue_type      = typename ivalue_type::value_type;
            using container_type    = std::vector<value_type>;
/* Inherited
            code_type get(size_type x, size_type y, size_type z)const;
            size_type width()const;
            size_type height()const;
            size_type depth()const;
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
            Tile_Map(
                size_type new_width = 0,
                size_type new_length = 0,
                size_type new_depth = 0,
                code_type filler = code_type::Void
            );
            virtual ~Tile_Map(){}

        protected:
            virtual code_type get_concrete(
                size_type x,
                size_type y,
                size_type z
            )const override;
            virtual size_type width_concrete()const override;
            virtual size_type height_concrete()const override;
            virtual size_type depth_concrete()const override;
            virtual size_type count_tiles_concrete()const override;
            virtual void set_concrete(
                size_type x, size_type y, size_type z,
                code_type newTile
            ) override;
            virtual void add_x_layer_concrete(
                size_type dx,
                code_type filler
            ) override;
            virtual void add_y_layer_concrete(
                size_type dy,
                code_type filler
            ) override;
            virtual void add_z_layer_concrete(
                size_type dz,
                code_type filler
            ) override;
            virtual void remove_x_layer_concrete(size_type dx) override;
            virtual void remove_y_layer_concrete(size_type dy) override;
            virtual void remove_z_layer_concrete(size_type dz) override;
            virtual void insert_x_layer_concrete(
                size_type x, size_type dx,
                code_type filler
            ) override;
            virtual void insert_y_layer_concrete(
                size_type y, size_type dy,
                code_type filler
            ) override;
            virtual void insert_z_layer_concrete(
                size_type z, size_type dz,
                code_type filler
            ) override;
            virtual void erase_x_layer_concrete(
                size_type x,
                size_type dx
            ) override;
            virtual void erase_y_layer_concrete(
                size_type y,
                size_type dy
            ) override;
            virtual void erase_z_layer_concrete(
                size_type z,
                size_type dz
            ) override;
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
            virtual void shrink_concrete(
                size_type dx,
                size_type dy,
                size_type dz
            ) override;
            virtual void fill_concrete(code_type filler) override;
            virtual const value_type& subscript_concrete(size_type z)
                const override;
            virtual value_type& subscript_concrete(size_type z) override;

        private:
            container_type m_layers;
    };

#include "Tile_Map.inl"

}

#endif