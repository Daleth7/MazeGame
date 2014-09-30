#include "Maze_Game_Handler.h"
#include "GUI_View_Handler.h"
#include "H/Maze_Map_Generator.h"

#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>
#include <cmath>

int main(){
    std::srand(std::time(nullptr));

    using handlerType = Handler::Maze<
        3u, sf::PrimitiveType::Quads,
        Data::Tile::code>;

        // Constants
    const handlerType::sizeType
        tileCount(60), tileSize(10),
        delScore(100), delDiff(5),
        minSize(35)
    ;
    const handlerType::codeType
        vis_pcode(Data::Tile::code::Magma),
        invis_pcode(Data::Tile::code::Snow),
        playcode(Data::Tile::code::Water),
        fcode(Data::Tile::code::Void),
        endcode(Data::Tile::code::Sand),
        prepcode(Data::Tile::code::Ice),
        wallcode(Data::Tile::code::Dirt),
        lightcode(Data::Tile::code::Cloud)
    ;

    auto calc_diff = [](handlerType::sizeType x){
        return x/4u+9u/std::log10(36)*std::log10(x)
            + std::sqrt(27*x/20.0);
        };

        // Create the generator first
    Data::Maze_Map_Generator<2, handlerType::codeType> mazeGen(
        invis_pcode, wallcode, playcode, endcode,
        vis_pcode, prepcode, calc_diff(tileCount),
        false, nullptr, invis_pcode);

        // Load resources
    handlerType::themeType basicTheme, bwPokeTheme, colPokeTheme;
    if(!(
        basicTheme.manager.loadFromFile("Sprites/maze_texture.png")         &&
        bwPokeTheme.manager.loadFromFile("Sprites/Poke_Texture.png")        &&
        colPokeTheme.manager.loadFromFile("Sprites/Poke_Texture_RGB.png")   &&
        bwPokeTheme.bgMusic.openFromFile("Audio/MtMoon_Cropped.wav")        &&
        colPokeTheme.bgMusic.openFromFile("Audio/MtMoon_Cropped.wav")       &&
        bwPokeTheme.solMusic.openFromFile("Audio/rival_appears.wav")        &&
        colPokeTheme.solMusic.openFromFile("Audio/rival_appears.wav")       &&
        bwPokeTheme.sfxBuf.loadFromFile("Audio/Zapdos.wav")
    ))  return 0xBAD;
    colPokeTheme.sfxBuf = bwPokeTheme.sfxBuf;

        // Set up the game handler
    handlerType mazeGame(
        tileCount, tileCount,
        vis_pcode, invis_pcode, playcode, fcode,
        endcode, prepcode, wallcode, lightcode,
        tileSize, mazeGen, delScore, basicTheme);

        // Set the generator with the solution layer
    mazeGen.path_logger(mazeGame.pathLogger());

    using namespace sf;

        // Set up the window and screen
    std::size_t fpsLim(30);
    const std::string title = "Maze Game (Press H for help) - Score: ";
    RenderWindow screen({600, 600}, title + "0");
        screen.setFramerateLimit(fpsLim);

        // Set up the camera
    constexpr Handler::View::motionType
        drag(Handler::View::motionType::dragAlong),
        followPlayer(Handler::View::motionType::centerManually)
    ;
    Handler::View camera(screen.getView(), drag);

        // Set up the title screen
    {
        Sprite titleScreen;
        Texture titleBg;
        if(!titleBg.loadFromFile("Sprites/title.png"))
            throw 0xBAD2;
        titleScreen.setTexture(titleBg);
        screen.draw(titleScreen);
        screen.display();
    }

        // Now run the game
    mazeGame.generateMaze();

    while(screen.isOpen()){
        Event event;
        while(screen.pollEvent(event)){
            switch(event.type){
                case Event::Closed:
                    screen.close();
                    break;
                case Event::KeyPressed:
                    switch(event.key.code){
                        case Keyboard::Space:
                            screen.setTitle("Generating...");
                            if(event.key.control)
                                mazeGame.generateMaze(true);
                            else
                                mazeGame.generateMaze();
                            break;
                        case Keyboard::Tilde:
                            mazeGame.toggleDrawPath();
                            break;
                        case Keyboard::Up:
                        case Keyboard::W:
                            mazeGame.movePlayer(Data::Orientation::code::North);
                            break;
                        case Keyboard::Down:
                        case Keyboard::S:
                            mazeGame.movePlayer(Data::Orientation::code::South);
                            if(
                                    Keyboard::isKeyPressed(Keyboard::LControl) ||
                                    Keyboard::isKeyPressed(Keyboard::RControl)
                            )   screen.capture().saveToFile("Maze_Screenshot.png");
                            break;
                        case Keyboard::Left:
                        case Keyboard::A:
                            mazeGame.movePlayer(Data::Orientation::code::West);
                            break;
                        case Keyboard::Right:
                        case Keyboard::D:
                            mazeGame.movePlayer(Data::Orientation::code::East);
                            break;
                        case Keyboard::BackSpace:
                            camera.setCenter(screen.getSize().x/2u, screen.getSize().y/2u);
                            camera.zoom(1.0f/camera.zoom());
                            break;
                        case Keyboard::Num1:
                            mazeGame.playAudio(false);
                            mazeGame.theme(basicTheme);
                            break;
                        case Keyboard::Num2:
                            mazeGame.theme(bwPokeTheme);
                            mazeGame.playAudio(true);
                            break;
                        case Keyboard::Num3:
                            mazeGame.theme(colPokeTheme);
                            mazeGame.playAudio(true);
                            break;
                        case Keyboard::PageUp:
                            mazeGame.width(mazeGame.width()+delDiff);
                            mazeGame.height(mazeGame.height()+delDiff);
                            mazeGen.difficulty(calc_diff(mazeGame.width()));
                            break;
                        case Keyboard::PageDown:
                            if(mazeGame.width() != minSize){
                                mazeGame.width(mazeGame.width()-delDiff);
                                mazeGame.height(mazeGame.height()-delDiff);
                            }else{
                                mazeGame.width(minSize);
                                mazeGame.height(minSize);
                            }
                            mazeGen.difficulty(calc_diff(mazeGame.width()));
                            break;
                        case Keyboard::H:
                            mazeGame.toggleDrawHelp();
                            break;
                        case Keyboard::Return:
                            if(event.key.control){
                                mazeGen.has_mult_solutions
                                    (!mazeGen.has_mult_solutions());
                                break;
                            }
                            if(camera.motion() == followPlayer)
                                camera.motion(drag);
                            else
                                camera.motion(followPlayer);
                            break;
                        default:
                            break;
                    }
                    break;
                case Event::MouseMoved:
                    camera.update(0.f, 0.f
                        , Mouse::isButtonPressed(Mouse::Left));
                    break;
                case Event::MouseWheelMoved:
                    camera.zoom(1.0f-event.mouseWheel.delta/25.0f);
                    break;
                default:    break;
            }
        }

        camera.updateMousePosition();
        if(camera.motion() == followPlayer){
            camera.setCenter(
                mazeGame.playerPosition().first*mazeGame.tileSize()
                    - mazeGame.tileSize()/2u,
                mazeGame.playerPosition().second*mazeGame.tileSize()
                    - mazeGame.tileSize()/2u
            );
        }

        std::stringstream ss;
            ss << mazeGame.score();
        screen.setTitle(title + ss.str());

        screen.clear();
        screen.setView(camera);
        mazeGame.drawTo(screen);
        screen.display();
    }

    return 0;
}
