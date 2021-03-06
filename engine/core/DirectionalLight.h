#ifndef directionallight_h
#define directionallight_h

#include "Light.h"
#include "math/Vector3.h"

class DirectionalLight: public Light {

public:

    DirectionalLight();
    virtual ~DirectionalLight();

    void setDirection(Vector3 direction);
    void setDirection(float x, float y, float z);

};

#endif /* directionallight_h */
