#ifndef TILEMANAGER_GUI_FOR_BASIC_TILE_SPRITE_TEXURES_HHHH_HHH_H_HH_
#define TILEMANAGER_GUI_FOR_BASIC_TILE_SPRITE_TEXURES_HHHH_HHH_H_HH_

#include "Manager_GUI.h"

#include "Tile_Constants.h"

#include <SFML/Graphics/Texture.hpp>

namespace GUI{
    class TextureManager
        : public Resource::BasicManager<sf::Texture, Data::Tile::code>
    {
        using BasicType = Resource::BasicManager<sf::Texture, Data::Tile::code>;
        public:
            using BasicType::TextureType;
            using BasicType::CodeType;

/* Inherited
            const TextureType& getSheet()const;
            const TextureType* getSheetPtr()const;
            sf::IntRect getArea(CodeType code)const;
            bool loadFromFile(
                const std::string& filePath,
                const sf::IntRect& rect = sf::IntRect()
            );
            bool loadFromMemory(
                const void* rawData, std::size_t size,
                const sf::IntRect& rect = sf::IntRect()
            );
            bool loadFromStream(
                InputStream& streamIn,
                const sf::IntRect& rect = sf::IntRect()
            );
            bool loadFromImage(
                const sf::Image& img,
                const sf::IntRect& rect = sf::IntRect()
            );
            sf::Vector2u getSize()const;
            sf::Image copyToImage()const;
            void setSmooth(bool smoothTrue);
            bool isSmooth()const;
*/

            TextureManager()                                    = default;
            TextureManager(const TextureManager&)               = default;
            TextureManager(TextureManager&&)                    = default;
            TextureManager& operator=(const TextureManager&)    = default;
            TextureManager& operator=(TextureManager&&)         = default;
            virtual ~TextureManager(){}

        private:
            virtual const TextureType& getSheetConcrete()const override
                {return mTex;}

            virtual const TextureType* getSheetPtrConcrete()const override
                {return &mTex;}

            virtual sf::IntRect getAreaConcrete(CodeType code)const override{
                const Data::Tile::raw_type raw
                    (static_cast<Data::Tile::raw_type>(code));
                using namespace Constant;
                return sf::IntRect{
                    static_cast<int>(imgSize*(raw%pngGridWidth)),
                    static_cast<int>(imgSize*(raw/pngGridWidth)),
                    imgSize, imgSize};
            }

            virtual bool loadFromFileConcrete(
                const std::string& filePath,
                const sf::IntRect& rect = sf::IntRect()
            ) override{return mTex.loadFromFile(filePath, rect);}

            virtual bool loadFromMemoryConcrete(
                const void* rawData, std::size_t size,
                const sf::IntRect& rect
            ) override{return mTex.loadFromMemory(rawData, size, rect);}

            virtual bool loadFromStreamConcrete(
                sf::InputStream& streamIn,
                const sf::IntRect& rect
            ) override{return mTex.loadFromStream(streamIn, rect);}

            virtual bool loadFromImageConcrete(
                const sf::Image& img,
                const sf::IntRect& rect
            ) override{return mTex.loadFromImage(img, rect);}

            virtual sf::Vector2u getSizeConcrete()const override
                {return mTex.getSize();}

            virtual sf::Image copyToImageConcrete()const override
                {return mTex.copyToImage();}

            virtual void setSmoothConcrete(bool smoothTrue) override
                {mTex.setSmooth(smoothTrue);}

            virtual bool isSmoothConcrete()const override
                {return mTex.isSmooth();}

        private:
            TextureType mTex;
    };
}

#endif