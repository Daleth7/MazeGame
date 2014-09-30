#ifndef MANAAGER_INTERFACE_FOR_GUI_RESOURCES_HHHHHH_HHHH_H_H_
#define MANAAGER_INTERFACE_FOR_GUI_RESOURCES_HHHHHH_HHHH_H_H_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Image.hpp>

#include <cstddef>

namespace std{
    template <typename>
    class char_traits;

    template <typename>
    class allocator;

    template <typename, typename, typename>
    class basic_string;

    typedef basic_string<char, char_traits<char>, allocator<char> > string;
}

namespace sf{
    class InputStream;

    template <typename>
    class Vector2;

    typedef Vector2<unsigned int> Vector2u;
}

namespace GUI{
    namespace Resource{
        template <typename TextureTypeParam, typename CodeTypeParam>
        class BasicManager{
            public:
                using TextureType   = TextureTypeParam;
                using CodeType      = CodeTypeParam;

                const TextureType& getSheet()const
                    {return this->getSheetConcrete();}

                const TextureType* getSheetPtr()const
                    {return this->getSheetPtrConcrete();}

                sf::IntRect getArea(CodeType code)const
                    {return this->getAreaConcrete(code);}

                bool loadFromFile(
                    const std::string& filePath,
                    const sf::IntRect& rect = sf::IntRect()
                ){return this->loadFromFileConcrete(filePath, rect);}

                bool loadFromMemory(
                    const void* rawData, std::size_t size,
                    const sf::IntRect& rect = sf::IntRect()
                ){return this->loadFromMemoryConcrete(rawData, rect);}

                bool loadFromStream(
                    sf::InputStream& streamIn,
                    const sf::IntRect& rect = sf::IntRect()
                ){return this->loadFromFileConcrete(streamIn, rect);}

                bool loadFromImage(
                    const sf::Image& img,
                    const sf::IntRect& rect = sf::IntRect()
                ){return this->loadFromImageConcrete(img, rect);}

                sf::Vector2u getSize()const
                    {return this->getSizeConcrete();}

                sf::Image copyToImage()const
                    {return this->copyToImageConcrete();}

                void setSmooth(bool smoothTrue)
                    {this->setSmoothConcrete(smoothTrue);}

                bool isSmooth()const
                    {return this->isSmoothConcrete();}

                virtual ~BasicManager(){}

            private:
                virtual const TextureType& getSheetConcrete()const = 0;
                virtual const TextureType* getSheetPtrConcrete()const = 0;
                virtual sf::IntRect getAreaConcrete(CodeType code)const = 0;
                virtual bool loadFromFileConcrete(
                    const std::string& filePath,
                    const sf::IntRect& rect = sf::IntRect()
                ) = 0;
                virtual bool loadFromMemoryConcrete(
                    const void* rawData, std::size_t size,
                    const sf::IntRect& rect
                ) = 0;
                virtual bool loadFromStreamConcrete(
                    sf::InputStream& streamIn,
                    const sf::IntRect& rect
                ) = 0;
                virtual bool loadFromImageConcrete(
                    const sf::Image& img,
                    const sf::IntRect& rect
                ) = 0;
                virtual sf::Vector2u getSizeConcrete()const = 0;
                virtual sf::Image copyToImageConcrete()const = 0;
                virtual void setSmoothConcrete(bool smoothTrue) = 0;
                virtual bool isSmoothConcrete()const = 0;
        };
    }
}

#endif