#ifndef MAPMAP_INTERFACE_ABSTRACTCLASSS_2833972HHHHH_HHHHHHH_
#define MAPMAP_INTERFACE_ABSTRACTCLASSS_2833972HHHHH_HHHHHHH_

#include <cstddef>

namespace Data{
    template <std::size_t Dimensions, typename CodeType>
    struct Map;

    template <typename CodeType>
    struct Map<0, CodeType>{
        using size_type         = std::size_t;
        using code_type         = CodeType;

        code_type get()const
            {return this->get_concrete();}

        static constexpr size_type width()  //x-axis
            {return 1;}

        static constexpr size_type height() //y-axis
            {return 1;}

        static constexpr size_type depth() //z-axis
            {return 1;}

        static constexpr size_type count_tiles()
            {return 1;}

        void set(code_type newTile)
            {this->set_concrete(newTile);}

        void fill(code_type filler)
            {this->fill_concrete(filler);}

        operator code_type()const
            {return this->cast_concrete();}

        operator code_type&()
            {return this->cast_concrete();}

        virtual ~Map(){}

        protected:
            virtual code_type get_concrete()const = 0;

            virtual void set_concrete(code_type newTile) = 0;
            virtual void fill_concrete(code_type filler) = 0;

            virtual code_type cast_concrete()const = 0;
            virtual code_type& cast_concrete() = 0;
    };

    template <typename CodeType>
    struct Map<1, CodeType>{
        using size_type         = std::size_t;
        using code_type         = CodeType;

        code_type get(size_type x)const
            {return this->get_concrete(x);}

        size_type width()const  //x-axis
            {return this->width_concrete();}

        static constexpr size_type height() //y-axis
            {return 1;}

        static constexpr size_type depth() //z-axis
            {return 1;}

        size_type count_tiles()const
            {return this->count_tiles_concrete();}

        void set(size_type x, code_type newTile)
            {this->set_concrete(x, newTile);}

        void add(code_type filler = code_type::Void)
            {this->add_concrete(1, filler);}

        void add(size_type dx, code_type filler = code_type::Void)
            {this->add_concrete(dx, filler);}

        void remove()
            {this->remove_concrete(1);}

        void remove(size_type dx)
            {this->remove_concrete(dx);}

        void insert(size_type x, code_type filler = code_type::Void)
            {this->insert_concrete(x, 1, filler);}

        void insert(size_type x, size_type dx, code_type filler)
            {this->insert_concrete(x, dx, filler);}

        void erase(size_type x)
            {this->erase_concrete(x, 1);}

        void erase(size_type x, size_type dx)
            {this->erase_concrete(x, dx);}

        void set_ends(code_type filler)
            {this->set_ends_concrete(filler);}

        void resize(
            size_type new_width,
            code_type filler = code_type::Void
        ){this->resize_concrete(new_width, filler);}

        void expand(
            size_type dx,
            code_type filler = code_type::Void
        ){this->expand_concrete(dx, filler);}

        void shrink(size_type dx)
            {this->shrink_concrete(dx);}

        void fill(code_type filler)
            {this->fill_concrete(filler);}

        virtual ~Map(){}

        protected:
            virtual code_type get_concrete(size_type x)const = 0;
            virtual size_type width_concrete()const = 0;
            virtual size_type count_tiles_concrete()const = 0;

            virtual void set_concrete(
                size_type x,
                code_type newTile
            ) = 0;
            virtual void add_concrete(size_type dx, code_type filler) = 0;
            virtual void remove_concrete(size_type dx) = 0;
            virtual void insert_concrete(size_type x, size_type dx, code_type filler) = 0;
            virtual void erase_concrete(size_type x, size_type dx) = 0;
            virtual void set_ends_concrete(code_type filler) = 0;
            virtual void resize_concrete(
                size_type new_width,
                code_type filler
            ) = 0;
            virtual void expand_concrete(
                size_type dx,
                code_type filler
            ) = 0;
            virtual void shrink_concrete(size_type dx) = 0;
            virtual void fill_concrete(code_type filler) = 0;
    };

    template <typename CodeType>
    struct Map<2, CodeType>{
        using size_type         = std::size_t;
        using code_type         = CodeType;

        code_type get(size_type x, size_type y)const
            {return this->get_concrete(x, y);}

        size_type width()const  //x-axis
            {return this->width_concrete();}

        size_type width(size_type y)const  //x-axis
            {return this->width_concrete(y);}

        size_type height()const //y-axis
            {return this->height_concrete();}

        size_type count_tiles()const
            {return this->count_tiles_concrete();}

        void set(size_type x, size_type y, code_type newTile)
            {this->set_concrete(x, y, newTile);}

        void add_row(code_type filler = code_type::Void)
            {this->add_row_concrete(1, filler);}

        void add_row(size_type dy, code_type filler = code_type::Void)
            {this->add_row_concrete(dy, filler);}

        void add_column(code_type filler = code_type::Void)
            {this->add_column_concrete(1, filler);}

        void add_column(size_type dx, code_type filler = code_type::Void)
            {this->add_column_concrete(dx, filler);}

            //Removes last row
        void remove_row()
            {this->remove_row_concrete(1);}

        void remove_row(size_type dy)
            {this->remove_row_concrete(dy);}

            //Removes last column
        void remove_column()
            {this->remove_column_concrete(1);}

        void remove_column(size_type dx)
            {this->remove_column_concrete(dx);}

        void insert_column(size_type x, code_type filler = code_type::Void)
            {this->insert_column_concrete(x, 1, filler);}

        void insert_column(size_type x, size_type dx, code_type filler)
            {this->insert_column_concrete(x, dx, filler);}

        void insert_row(size_type y, code_type filler = code_type::Void)
            {this->insert_row_concrete(y, 1, filler);}

        void insert_row(size_type y, size_type dy, code_type filler)
            {this->insert_row_concrete(y, dy, filler);}

        void erase_column(size_type x)
            {this->erase_column_concrete(x, 1);}

        void erase_column(size_type x, size_type dx)
            {this->erase_column_concrete(x, dx);}

        void erase_row(size_type y)
            {this->erase_row_concrete(y, 1);}

        void erase_row(size_type y, size_type dy)
            {this->erase_row_concrete(y, dy);}

        void set_borders(code_type filler)
            {this->set_borders_concrete(filler);}

        void set_corners(code_type filler)
            {this->set_corners_concrete(filler);}

        void resize(
            size_type new_width, size_type new_length,
            code_type filler = code_type::Void
        ){this->resize_concrete(new_width, new_length, filler);}

        void expand(
            size_type dx, size_type dy,
            code_type filler = code_type::Void
        ){this->expand_concrete(dx, dy, filler);}

        void shrink(size_type dx, size_type dy)
            {this->shrink_concrete(dx, dy);}

        void fill(code_type filler)
            {this->fill_concrete(filler);}

        virtual ~Map(){}

        protected:
            virtual code_type get_concrete(size_type x, size_type y)const = 0;
            virtual size_type width_concrete()const = 0;
            virtual size_type width_concrete(size_type y)const = 0;
            virtual size_type height_concrete()const = 0;
            virtual size_type count_tiles_concrete()const = 0;

            virtual void set_concrete(
                size_type x, size_type y,
                code_type newTile
            ) = 0;
            virtual void add_row_concrete(size_type dy, code_type filler) = 0;
            virtual void add_column_concrete(size_type dx, code_type filler) = 0;
            virtual void remove_row_concrete(size_type dy) = 0;
            virtual void remove_column_concrete(size_type dx) = 0;
            virtual void insert_column_concrete(
                size_type x, size_type dx,
                code_type filler
            ) = 0;
            virtual void insert_row_concrete(
                size_type y, size_type dy,
                code_type filler
            ) = 0;
            virtual void erase_column_concrete(size_type x, size_type dx) = 0;
            virtual void erase_row_concrete(size_type y, size_type dy) = 0;
            virtual void set_borders_concrete(code_type filler) = 0;
            virtual void set_corners_concrete(code_type filler) = 0;
            virtual void resize_concrete(
                size_type new_width, size_type new_length,
                code_type filler
            ) = 0;
            virtual void expand_concrete(
                size_type dx, size_type dy,
                code_type filler
            ) = 0;
            virtual void shrink_concrete(size_type dx, size_type dy) = 0;
            virtual void fill_concrete(code_type filler) = 0;
    };

    template <typename CodeType>
    struct Map<3, CodeType>{
        using size_type         = std::size_t;
        using code_type         = CodeType;

        code_type get(size_type x, size_type y, size_type z)const
            {return this->get_concrete(x, y, z);}

        size_type width()const  //x-axis
            {return this->width_concrete();}

        size_type height()const //y-axis
            {return this->height_concrete();}

        size_type depth()const //z-axis
            {return this->depth_concrete();}

        size_type count_tiles()const
            {return this->count_tiles_concrete();}

        void set(size_type x, size_type y, size_type z, code_type newTile)
            {this->set_concrete(x, y, z, newTile);}

        void add_x_layer(code_type filler = code_type::Void)
            {this->insert_x_layer_concrete(1, filler);}

        void add_x_layer(size_type dx, code_type filler = code_type::Void)
            {this->add_x_layer_concrete(dx, filler);}

        void add_y_layer(code_type filler = code_type::Void)
            {this->add_y_layer_concrete(1, filler);}

        void add_y_layer(size_type dy, code_type filler = code_type::Void)
            {this->add_y_layer_concrete(dy, filler);}

        void add_z_layer(code_type filler = code_type::Void)
            {this->add_z_layer_concrete(1, filler);}

        void add_z_layer(size_type dz, code_type filler = code_type::Void)
            {this->add_z_layer_concrete(dz, filler);}

            //Removes last x_layer
        void remove_x_layer()
            {this->remove_x_layer_concrete(1);}

        void remove_x_layer(size_type dx)
            {this->remove_x_layer_concrete(dx);}

            //Removes last y_layer
        void remove_y_layer()
            {this->remove_y_layer_concrete(1);}

        void remove_y_layer(size_type dy)
            {this->remove_y_layer_concrete(dy);}

            //Removes last z_layer
        void remove_z_layer()
            {this->remove_z_layer_concrete(1);}

        void remove_z_layer(size_type dz)
            {this->remove_y_layer_concrete(dz);}

        void insert_x_layer(size_type x, code_type filler = code_type::Void)
            {this->insert_x_layer_concrete(x, 1, filler);}

        void insert_x_layer(size_type x, size_type dx, code_type filler)
            {this->insert_x_layer_concrete(x, dx, filler);}

        void insert_y_layer(size_type y, code_type filler = code_type::Void)
            {this->insert_y_layer_concrete(y, 1, filler);}

        void insert_y_layer(size_type y, size_type dy, code_type filler)
            {this->insert_y_layer_concrete(y, dy, filler);}

        void insert_z_layer(size_type z, code_type filler = code_type::Void)
            {this->insert_z_layer_concrete(z, 1, filler);}

        void insert_z_layer(size_type z, size_type dz, code_type filler)
            {this->insert_z_layer_concrete(z, dz, filler);}

        void erase_x_layer(size_type x)
            {this->erase_x_layer_concrete(x, 1);}

        void erase_x_layer(size_type x, size_type dx)
            {this->erase_x_layer_concrete(x, dx);}

        void erase_y_layer(size_type y)
            {this->erase_y_layer_concrete(y, 1);}

        void erase_y_layer(size_type y, size_type dy)
            {this->erase_y_layer_concrete(y, dy);}

        void erase_z_layer(size_type z)
            {this->erase_z_layer_concrete(z, 1);}

        void erase_z_layer(size_type z, size_type dz)
            {this->erase_z_layer_concrete(z, dz);}

        void set_corners(code_type filler)
            {this->set_corners_concrete(filler);}

        void set_edges(code_type filler)
            {this->set_borders_concrete(filler);}

        void set_faces(code_type filler)
            {this->set_faces_concrete(filler);}

        void resize(
            size_type new_width, size_type new_length, size_type new_depth,
            code_type filler = code_type::Void
        ){this->resize_concrete(new_width, new_length, new_depth, filler);}

        void expand(
            size_type dx, size_type dy, size_type dz,
            code_type filler = code_type::Void
        ){this->expand_concrete(dx, dy, dz, filler);}

        void shrink(size_type dx, size_type dy, size_type dz)
            {this->shrink_concrete(dx, dy, dz);}

        void fill(code_type filler)
            {this->fill_concrete(filler);}

        virtual ~Map(){}

        protected:
            virtual code_type get_concrete(
                size_type x,
                size_type y,
                size_type z
            )const = 0;
            virtual size_type width_concrete()const = 0;
            virtual size_type height_concrete()const = 0;
            virtual size_type depth_concrete()const = 0;
            virtual size_type count_tiles_concrete()const = 0;

            virtual void set_concrete(
                size_type x, size_type y, size_type z,
                code_type newTile
            ) = 0;
            virtual void add_x_layer_concrete(size_type dx, code_type filler) = 0;
            virtual void add_y_layer_concrete(size_type dy, code_type filler) = 0;
            virtual void add_z_layer_concrete(size_type dz, code_type filler) = 0;
            virtual void remove_x_layer_concrete(size_type dx) = 0;
            virtual void remove_y_layer_concrete(size_type dy) = 0;
            virtual void remove_z_layer_concrete(size_type dz) = 0;
            virtual void insert_x_layer_concrete(
                size_type x, size_type dx,
                code_type filler
            ) = 0;
            virtual void insert_y_layer_concrete(
                size_type y, size_type dy,
                code_type filler
            ) = 0;
            virtual void insert_z_layer_concrete(
                size_type z, size_type dz,
                code_type filler
            ) = 0;
            virtual void erase_x_layer_concrete(size_type x, size_type dx) = 0;
            virtual void erase_y_layer_concrete(size_type y, size_type dy) = 0;
            virtual void erase_z_layer_concrete(size_type z, size_type dz) = 0;
            virtual void set_corners_concrete(code_type filler) = 0;
            virtual void set_edges_concrete(code_type filler) = 0;
            virtual void set_faces_concrete(code_type filler) = 0;
            virtual void resize_concrete(
                size_type new_width, size_type new_length, size_type new_depth,
                code_type filler
            ) = 0;
            virtual void expand_concrete(
                size_type dx, size_type dy, size_type dz,
                code_type filler
            ) = 0;
            virtual void shrink_concrete(
                size_type dx,
                size_type dy,
                size_type dz
            ) = 0;
            virtual void fill_concrete(code_type filler) = 0;
    };

    #include "Map_Code_Wrapper_Spec.inl"
}

#endif
