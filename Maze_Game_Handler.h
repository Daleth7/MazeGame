#ifndef MAZE_GAME_HANDLER_HHHHH___H___HHHH1236727818767_J_
#define MAZE_GAME_HANDLER_HHHHH___H___HHHH1236727818767_J_

#include "Tile_Map_GUI.h"
#include "Texture_Manager_GUI.h"
#include "H/Maze_Tile_Map_Generator.h"
#include "H/Orientation_Codes.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <utility>
#include <cmath>

namespace Handler{
    template <std::size_t Dim, sf::PrimitiveType TShape, typename CodeType>
    class Maze;

    template <std::size_t Dim, sf::PrimitiveType TShape>
    class Maze <Dim, TShape, Data::Tile::code>{
        public:
            using codeType      = Data::Tile::code;
            using worldType     = GUI::TileMap<Dim, TShape, codeType>;
            using mapType       = typename worldType::value_type;
            using sizeType      = typename worldType::size_type;
            using managerType   = GUI::TextureManager;
            using posPairType   = std::pair<sizeType, sizeType>;
            using generatorType
                = Data::Maze_Tile_Map_Generator<Dim-1u, codeType>;

            using musicType     = sf::Music;
            using soundType     = sf::Sound;
            using soundBuffer   = sf::SoundBuffer;
            using fillShapeType = sf::RectangleShape;
            using guiTextType   = sf::Text;
            using fontType      = sf::Font;
            using textType      = sf::Text;

            struct themeType{
                musicType       bgMusic;
                musicType       solMusic;
                soundBuffer     sfxBuf;
                managerType     manager;

                themeType()                             = default;
                themeType(const themeType&)             = delete;
                themeType(themeType&&)                  = default;
                themeType& operator=(const themeType&)  = delete;
                themeType& operator=(themeType&&)       = delete;
            };

            sizeType width()const;
            sizeType height()const;
            codeType visiblePathCode()const;
            codeType invisiblePathCode()const;
            codeType playerCode()const;
            codeType floorCode()const;
            codeType endCode()const;
            codeType preparationCode()const;
            codeType wallCode()const;
            codeType lightCode()const;
            float tileSize()const;
            const generatorType& generator()const;
            const worldType& world()const;
            const mapType& pathBG()const;
            const mapType& maze()const;
            const mapType& pathLogger()const;
            const mapType& light()const;
            const posPairType& playerPosition()const;
            const posPairType& endPosition()const;
            sizeType score()const;
            sizeType deltaScore()const;
            bool drawPath()const;
            bool solutionViewed()const;
            bool playAudio()const;
            const themeType& theme()const;
            bool drawHelp()const;

        // These changes will occur when a new mMaze is generated
            void width(sizeType newWidth);
            void height(sizeType newHeight);
            void visiblePathCode(codeType newCode);
            void invisiblePathCode(codeType newCode);
            void playerCode(codeType newCode);
            void floorCode(codeType newCode);
            void endCode(codeType newCode);
            void preparationCode(codeType newCode);
            void wallCode(codeType newCode);
            void lightCode(codeType newCode);
            void tileSize(float newTileSize);
            generatorType& generator();
            void generator(generatorType& newGen);
            worldType& world();
            mapType& pathBG();
            mapType& maze();
            mapType& pathLogger();
            mapType& light();

        // These changes occur immediately
            void drawPath(bool newDrawPath);
            void solutionViewed(bool newSolutionViewed);
            void playAudio(bool newPlayAudio);
            void theme(themeType& newTheme);
            void drawHelp(bool);

        // Game play related properties
            void generateMaze(bool showSolImmediately = false);
            void movePlayer(Data::Orientation::code dir);
            void drawTo(sf::RenderTarget& target);
            void toggleDrawPath();
            void toggleDrawHelp();

            Maze(
                sizeType newWidth, sizeType newHeight,
                codeType newVisPath, codeType newInvisPath,
                codeType newPlayer, codeType newFloor,
                codeType newEnd, codeType newPrep,
                codeType newWall, codeType newLight,
                float newTileSize, generatorType& newGen,
                sizeType newDScore, themeType& newTheme,
                bool generateImmediately = false
            );
            Maze(const Maze&)               = delete;
            Maze(Maze&&)                    = default;
            Maze& operator=(const Maze&)    = delete;
            Maze& operator=(Maze&&)         = delete;

        private:
            mapType blankMapGen(codeType code)const;
            void recalculateLight();
            void updateAudio();
            void playBgMusic();

            sizeType        mWidth, mHeight;
            codeType
                            mVisPath, mInvisPath, mPlayer, mFloor,
                            mEnd, mPrep, mWall, mLight
            ;
            float           mTileSize;
            generatorType*  pGenerator;
            mapType         mBlankLight;
            worldType       mWorld;
            mapType
                            &mPathBg, &mMaze,
                            &mPathLogger, &mLightLayer
            ;
            posPairType     mPlayerPos, mEndPos;
            sizeType        mScore, mDScore;
            fillShapeType   mWhiteBg;
            bool            mDrawPath, mSolutionViewed, mPlayAudio;
            themeType*      pTheme;
            soundType       mSfx;
            bool            mDrawHelp;
            fillShapeType   mHelpBg;
            fontType        mHelpFont;
            textType        mScoreLine, mKeysLine;
    };
}

#include "Maze_Game_Handler.inl"

#endif