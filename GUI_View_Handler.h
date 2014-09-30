#ifndef VIEW_HHHHH_HANDLE232333888723R_HHHH___
#define VIEW_HHHHH_HANDLE232333888723R_HHHH___

#include <SFML/Graphics/View.hpp>

namespace Handler{
    class View{
        public:
            using viewType  = sf::View;
            using posType   = sf::Vector2f;
            using mPosType  = sf::Vector2i;

            enum motionType : unsigned char{
                followMouse, dragAlong,
                centerManually, moveManually
            };

            motionType motion()const;
            float zoom()const;
            float rotation()const;
            const posType& center()const;
            const viewType& view()const;

            operator const viewType&()const;

            void motion(motionType);
            void zoom(float factor);
            void rotate(float dtheta);
            void setCenter(float newX, float newY);
            void move(float dx, float dy);
                // Based on motion type
            void update(
                float dx = 0.0f, float dy = 0.0f,
                bool isLeftPressed = false
            ) throw (motionType);
            void updateMousePosition();

            View(const viewType& newView, motionType = moveManually);

        private:
            viewType    mView;
            motionType  mMotion;
            mPosType    mLastMPos;
            float       mZoom;  // Keep a separate copy for resetting
    };
}

#endif