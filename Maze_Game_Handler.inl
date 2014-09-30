#define MAZ_TEMPL_ template <std::size_t Dim, sf::PrimitiveType TShape>
#define MAZ_INST_ Maze <Dim, TShape, Data::Tile::code>

#include <sstream>

namespace Handler{
    MAZ_TEMPL_
    auto MAZ_INST_::width()const -> sizeType
        {return mWidth;}

    MAZ_TEMPL_
    auto MAZ_INST_::height()const -> sizeType
        {return mHeight;}

    MAZ_TEMPL_
    auto MAZ_INST_::visiblePathCode()const -> codeType
        {return mVisPath;}

    MAZ_TEMPL_
    auto MAZ_INST_::invisiblePathCode()const -> codeType
        {return mInvisPath;}

    MAZ_TEMPL_
    auto MAZ_INST_::playerCode()const -> codeType
        {return mPlayer;}

    MAZ_TEMPL_
    auto MAZ_INST_::floorCode()const -> codeType
        {return mFloor;}

    MAZ_TEMPL_
    auto MAZ_INST_::endCode()const -> codeType
        {return mEnd;}

    MAZ_TEMPL_
    auto MAZ_INST_::preparationCode()const -> codeType
        {return mPrep;}

    MAZ_TEMPL_
    auto MAZ_INST_::wallCode()const -> codeType
        {return mWall;}

    MAZ_TEMPL_
    auto MAZ_INST_::lightCode()const -> codeType
        {return mLight;}

    MAZ_TEMPL_
    float MAZ_INST_::tileSize()const
        {return mTileSize;}

    MAZ_TEMPL_
    auto MAZ_INST_::generator()const -> const generatorType&
        {return *pGenerator;}

    MAZ_TEMPL_
    auto MAZ_INST_::world()const -> const worldType&
        {return mWorld;}

    MAZ_TEMPL_
    auto MAZ_INST_::pathBG()const -> const mapType&
        {return mPathBg;}

    MAZ_TEMPL_
    auto MAZ_INST_::maze()const -> const mapType&
        {return mMaze;}

    MAZ_TEMPL_
    auto MAZ_INST_::pathLogger()const -> const mapType&
        {return mPathLogger;}

    MAZ_TEMPL_
    auto MAZ_INST_::light()const -> const mapType&
        {return mLight;}

    MAZ_TEMPL_
    auto MAZ_INST_::playerPosition()const -> const posPairType&
        {return mPlayerPos;}

    MAZ_TEMPL_
    auto MAZ_INST_::endPosition()const -> const posPairType&
        {return mEndPos;}

    MAZ_TEMPL_
    auto MAZ_INST_::score()const -> sizeType
        {return mScore;}

    MAZ_TEMPL_
    auto MAZ_INST_::deltaScore()const -> sizeType
        {return mDScore;}

    MAZ_TEMPL_
    bool MAZ_INST_::drawPath()const
        {return mDrawPath;}

    MAZ_TEMPL_
    bool MAZ_INST_::solutionViewed()const
        {return mSolutionViewed;}

    MAZ_TEMPL_
    bool MAZ_INST_::playAudio()const
        {return mPlayAudio;}

    MAZ_TEMPL_
    auto MAZ_INST_::theme()const -> const themeType&
        {return *pTheme;}

    MAZ_TEMPL_
    bool MAZ_INST_::drawHelp()const
        {return mDrawHelp;}


    MAZ_TEMPL_
    void MAZ_INST_::width(sizeType newWidth)
        {mWidth = newWidth;}

    MAZ_TEMPL_
    void MAZ_INST_::height(sizeType newHeight)
        {mHeight = newHeight;}

    MAZ_TEMPL_
    void MAZ_INST_::visiblePathCode(codeType newCode)
        {mVisPath = newCode;}

    MAZ_TEMPL_
    void MAZ_INST_::invisiblePathCode(codeType newCode)
        {mInvisPath = newCode;}

    MAZ_TEMPL_
    void MAZ_INST_::playerCode(codeType newCode)
        {mPlayer = newCode;}

    MAZ_TEMPL_
    void MAZ_INST_::floorCode(codeType newCode)
        {mFloor = newCode;}

    MAZ_TEMPL_
    void MAZ_INST_::endCode(codeType newCode)
        {mEnd = newCode;}

    MAZ_TEMPL_
    void MAZ_INST_::preparationCode(codeType newCode)
        {mPrep = newCode;}

    MAZ_TEMPL_
    void MAZ_INST_::wallCode(codeType newCode)
        {mWall = newCode;}

    MAZ_TEMPL_
    void MAZ_INST_::lightCode(codeType newCode)
        {mLight = newCode;}

    MAZ_TEMPL_
    void MAZ_INST_::tileSize(float newTileSize)
        {mTileSize = newTileSize;}

    MAZ_TEMPL_
    auto MAZ_INST_::generator() -> generatorType&
        {return *pGenerator;}

    MAZ_TEMPL_
    void MAZ_INST_::generator(generatorType& newGen)
        {pGenerator = &newGen;}

    MAZ_TEMPL_
    auto MAZ_INST_::world() -> worldType&
        {return mWorld;}

    MAZ_TEMPL_
    auto MAZ_INST_::pathBG() -> mapType&
        {return mPathBg;}

    MAZ_TEMPL_
    auto MAZ_INST_::maze() -> mapType&
        {return mMaze;}

    MAZ_TEMPL_
    auto MAZ_INST_::pathLogger() -> mapType&
        {return mPathLogger;}

    MAZ_TEMPL_
    auto MAZ_INST_::light() -> mapType&
        {return mLightLayer;}


    MAZ_TEMPL_
    void MAZ_INST_::drawPath(bool newDrawPath)
        {mDrawPath = newDrawPath;}

    MAZ_TEMPL_
    void MAZ_INST_::solutionViewed(bool newSolutionViewed)
        {mSolutionViewed = newSolutionViewed;}

    MAZ_TEMPL_
    void MAZ_INST_::playAudio(bool newPlayAudio){
        mPlayAudio = newPlayAudio;
        pTheme->bgMusic.stop();
        pTheme->solMusic.stop();
        mSfx.stop();
        if(mPlayAudio){
            playBgMusic();
            mSfx.play();
        }
    }

    MAZ_TEMPL_
    void MAZ_INST_::theme(themeType& newTheme){
        bool oldSet = mPlayAudio;
        this->playAudio(false);
        newTheme.bgMusic.setVolume
            (pTheme->bgMusic.getVolume());
        newTheme.solMusic.setVolume
            (pTheme->solMusic.getVolume());
        pTheme = &newTheme;
        for(sizeType z(0); z < mWorld.depth(); ++z)
            mWorld[z].setManager(pTheme->manager);
        auto oldVol = mSfx.getVolume();
        mSfx.setBuffer(pTheme->sfxBuf);
        mSfx.setVolume(oldVol);
        this->playAudio(mPlayAudio = oldSet);
    }

    MAZ_TEMPL_
    void MAZ_INST_::drawHelp(bool newHelp)
        {mDrawHelp = newHelp;}


    MAZ_TEMPL_
    void MAZ_INST_::generateMaze(bool showSol){
        pTheme->solMusic.stop();
        mPathBg = blankMapGen(mFloor);
        mMaze = blankMapGen(mWall);
        mPathLogger = blankMapGen(mInvisPath);
        mLightLayer = mBlankLight = blankMapGen(mLight);
        (*pGenerator)(mMaze, mMaze.width(), mMaze.height());
        pGenerator->replace_code(mMaze, mVisPath, mFloor);
        pGenerator->replace_code(mMaze, mInvisPath, mFloor);
        auto findPos = [](
            posPairType& pos, const codeType& code,
            mapType& mazeLay
        ){
            for(sizeType y(0); y < mazeLay.height(); ++y){
                for(sizeType x(0); x < mazeLay.width(); ++x){
                    if(mazeLay.get(x, y) == code){
                        pos = {x, y};
                        y = mazeLay.height();
                        break;
                    }
                }
            }
        };
        findPos(mPlayerPos, mPlayer, mMaze);
        findPos(mEndPos, mEnd, mMaze);
        mWhiteBg.setSize({
            static_cast<float>(mMaze.width()*mTileSize),
            static_cast<float>(mMaze.height()*mTileSize)
        });
        mWhiteBg.setFillColor(sf::Color::White);
        mDrawPath = mSolutionViewed = showSol;
        recalculateLight();
        updateAudio();

        mHelpBg.setSize({mWidth*mTileSize, mWidth*mTileSize});
    }

    MAZ_TEMPL_
    void MAZ_INST_::movePlayer(Data::Orientation::code dir){
        using namespace Data::Orientation;
        sizeType
            &pX = mPlayerPos.first,
            &pY = mPlayerPos.second
        ;
        bool foundExit(false);
        switch(dir){
            case code::North:
                if(pY == 0u)    break;
                else if(mMaze.get(pX, pY-1u) == mEnd)
                    foundExit = true;
                else if(mMaze.get(pX, pY-1u) == mFloor){
                    mMaze.set(pX, pY, mFloor);
                    mMaze.set(pX, --pY, mPlayer);
                }
                break;
            case code::South:
                if(pY == mMaze.height()-1u) break;
                else if(mMaze.get(pX, pY+1u) == mEnd)
                    foundExit = true;
                else if(mMaze.get(pX, pY+1u) == mFloor){
                    mMaze.set(pX, pY, mFloor);
                    mMaze.set(pX, ++pY, mPlayer);
                }
                break;
            case code::West:
                if(pX == 0u)    break;
                else if(mMaze.get(pX-1u, pY) == mEnd)
                    foundExit = true;
                else if(mMaze.get(pX-1u, pY) == mFloor){
                    mMaze.set(pX, pY, mFloor);
                    mMaze.set(--pX, pY, mPlayer);
                }
                break;
            case code::East:
                if(pX == mMaze.width()-1u)  break;
                else if(mMaze.get(pX+1u, pY) == mEnd)
                    foundExit = true;
                else if(mMaze.get(pX+1u, pY) == mFloor){
                    mMaze.set(pX, pY, mFloor);
                    mMaze.set(++pX, pY, mPlayer);
                }
                break;
            default:
                break;
        }
        recalculateLight();
        updateAudio();
        if(foundExit){
            mMaze.set(mEndPos.first, mEndPos.second, mFloor);
            mScore += mDScore/(mSolutionViewed+1u);
            mDrawPath = true;
        }
    }

    MAZ_TEMPL_
    void MAZ_INST_::drawTo(sf::RenderTarget& target){
        target.draw(mWhiteBg);
        target.draw(mPathBg);
        target.draw(mMaze);
        target.draw(mDrawPath ? mPathLogger : mLightLayer);
        if(this->drawHelp()){
            std::stringstream ss;
            ss
                << "Score: " << mScore << '\n'
                << "Difficulty: " << pGenerator->difficulty()
                << " | Width: " << mWidth << " | Height: " << mHeight
                << "\nHas multiple solutions: "
                << std::boolalpha << pGenerator->has_mult_solutions()
            ;
            mScoreLine.setString(ss.str());
            target.draw(mHelpBg);
            target.draw(mScoreLine);
            target.draw(mKeysLine);
        }
    }

    MAZ_TEMPL_
    void MAZ_INST_::toggleDrawPath(){
        mDrawPath = !mDrawPath;
        playBgMusic();
        mSolutionViewed = true;
    }

    MAZ_TEMPL_
    void MAZ_INST_::toggleDrawHelp()
        {mDrawHelp = !mDrawHelp;}

    MAZ_TEMPL_
    MAZ_INST_::Maze(
        sizeType newWidth, sizeType newHeight,
        codeType newVisPath, codeType newInvisPath,
        codeType newPlayer, codeType newFloor,
        codeType newEnd, codeType newPrep,
        codeType newWall, codeType newLight,
        float newTileSize, generatorType& newGen,
        sizeType newDScore, themeType& newTheme,
        bool generateImmediately
    )
        : mWidth(newWidth), mHeight(newHeight)
        , mVisPath(newVisPath), mInvisPath(newInvisPath)
        , mPlayer(newPlayer), mFloor(newFloor)
        , mEnd(newEnd), mPrep(newPrep), mWall(newWall), mLight(newLight)
        , mTileSize(newTileSize), pGenerator(&newGen), mBlankLight()
        , mWorld(newTheme.manager, {mTileSize, mTileSize}
            , newWidth, newHeight, 4u, mLight)
        , mPathBg(mWorld[0]), mMaze(mWorld[1])
        , mPathLogger(mWorld[2]), mLightLayer(mWorld[3])
        , mPlayerPos(), mEndPos()
        , mScore(0u), mDScore(newDScore), mWhiteBg()
        , mDrawPath(false), mSolutionViewed(false), mPlayAudio(false)
        , pTheme(&newTheme), mSfx(newTheme.sfxBuf)
        , mDrawHelp(false), mHelpBg(), mHelpFont()
        , mScoreLine("", mHelpFont, 25u), mKeysLine("", mHelpFont, 25u)
    {
        if(generateImmediately)    this->generateMaze();
        mHelpBg.setFillColor({64, 64, 64, 64});
        if(!mHelpFont.loadFromFile("Font/RockoFLF.ttf")) throw 0xBAD1;
        mScoreLine.setColor(sf::Color::White);
        mScoreLine.setString("Score: 0");
        mKeysLine.setColor(sf::Color::White);
        mKeysLine.move(0, mScoreLine.getCharacterSize()*4u);
        mKeysLine.setString(
            "Instructions:\n"
            "\tH - Help screen\n"
            "\tSpace - New maze\n"
            "\tWASD or arrow keys - Move player\n"
            "\tEnter/Return - Have camera follow"
                " player or\n\t\tstop it\n"
            "\tClick and Drag - Move maze\n"
            "\tScroll mouse wheel - Zoom in/out\n"
            "\tBackspace - Reset view\n"
            "\t~ - Solution\n"
            "\t1, 2, or 3 - Change theme\n"
            "\tPgUp or PgDn - Change difficulty of next maze\n"
            "\tCtrl+Enter/Return - Generate with"
                " multiple or\n\t\tsingle solution");
    }


    MAZ_TEMPL_
    auto MAZ_INST_::blankMapGen(codeType code)const -> mapType {
        return mapType(
            pTheme->manager, {mTileSize, mTileSize},
            mWidth, mHeight, code
        );
    }

    MAZ_TEMPL_
    void MAZ_INST_::recalculateLight(){
        mLightLayer = mBlankLight;
        float radius((pGenerator->difficulty()>>3)+3.0f);
        const sizeType
            pX(mPlayerPos.first),
            pY(mPlayerPos.second)
        ;
        for(float x(-radius); x < radius; ++x){
            if((x+pX) < 0 || (x+pX) > (mLightLayer.width()-1u))
                continue;
            float bound(std::sqrt(radius*radius-x*x));
            for(float y(-bound); y < bound; ++y){
                if(
                    (y+pY) < 0 ||
                    (y+pY) > (mLightLayer.height()-1u)
                )   continue;
                auto lCol(mLightLayer.getTileColor(x+pX, y+pY));
                lCol.a = (std::sqrt(x*x+y*y)/radius)*255;
                mLightLayer.setTileColor(x+pX, y+pY, lCol);
            }
        }
    }

    MAZ_TEMPL_
    void MAZ_INST_::updateAudio(){
        musicType& bg = pTheme->bgMusic;
        musicType& sol = pTheme->solMusic;

        if(!mPlayAudio){
            bg.stop();
            sol.stop();
            mSfx.stop();
            return;
        }

        using std::sqrt;
        using std::pow;
        const float pToERatio =
            sqrt(
                pow(mEndPos.first*1.0-mPlayerPos.first, 2)
                + pow(mEndPos.second*1.0-mPlayerPos.second, 2)
            )
            / (sqrt(mWidth*mWidth*2.0+mHeight*mHeight*2.0))
        ;

        bg.setVolume(pToERatio*100.0);
        sol.setVolume(pToERatio*100.0);
        mSfx.setVolume(18.75*(1.0f-pToERatio));

        const auto musStop = sf::Music::Stopped;
        if(
            (!mDrawPath) && mPlayAudio &&
            bg.getStatus() == musStop
        ){
            bg.stop();
            bg.play();
        }

        if(
            mDrawPath && mPlayAudio &&
            sol.getStatus() == musStop
        ){
            sol.stop();
            sol.play();
        }

        if(mPlayAudio && mSfx.getStatus() == musStop){
            mSfx.stop();
            mSfx.play();
        }
    }

    MAZ_TEMPL_
    void MAZ_INST_::playBgMusic(){
        pTheme->bgMusic.stop();
        pTheme->solMusic.stop();
        if(!mPlayAudio) return;
        if(mDrawPath)   pTheme->solMusic.play();
        else            pTheme->bgMusic.play();
    }
}

#undef MAZ_TEMPL_
#undef MAZ_INST_