#include "GUI_View_Handler.h"

#include <SFML/Window/Mouse.hpp>

namespace Handler{
    View::motionType View::motion()const
        {return mMotion;}

    float View::zoom()const
        {return mZoom;}

    float View::rotation()const
        {return mView.getRotation();}

    const View::posType& View::center()const
        {return mView.getCenter();}

    const View::viewType& View::view()const
        {return mView;}

    View::operator const viewType&()const
        {return this->view();}

    void View::motion(motionType newMotion)
        {mMotion = newMotion;}

    void View::zoom(float factor){
        mZoom *= factor;
        mView.zoom(factor);
    }

    void View::rotate(float dtheta)
        {mView.setRotation(this->rotation()*dtheta);}

    void View::setCenter(float newX, float newY)
        {mView.setCenter(newX, newY);}

    void View::move(float dx, float dy)
        {mView.move(dx, dy);}

    void View::update(float dx, float dy, bool isLeftPressed)
    throw(motionType) {
        const auto& curMPos = sf::Mouse::getPosition();
        switch(mMotion){
            case dragAlong:
                if(!isLeftPressed)  break;
            case followMouse:
                this->move(
                    (mLastMPos.x-curMPos.x)*mZoom,
                    (mLastMPos.y-curMPos.y)*mZoom
                );
                break;
            case centerManually:
                this->setCenter(dx, dy);
                break;
            case moveManually:
                this->move(dx, dy);
                break;
            default:    throw mMotion; // Should not happen
        }
        mLastMPos = curMPos;
    }

    void View::updateMousePosition()
        {mLastMPos = sf::Mouse::getPosition();}


    View::View(const viewType& newView, motionType newMotion)
        : mView(newView)
        , mMotion(newMotion)
        , mLastMPos(sf::Mouse::getPosition())
        , mZoom(1.0f)
    {}
}