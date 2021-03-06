#ifndef object_h
#define object_h

#include <vector>
#include "Render.h"
#include "math/Matrix4.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"

class Object: public Render {

private:

    void updateMatrices();

protected:

    std::vector<Object*> objects;

    Object* parent;

    Matrix4* viewMatrix;
    Matrix4* viewProjectionMatrix;
    Vector3* cameraPosition;

    Matrix4 modelMatrix;
    Matrix4 modelViewProjectionMatrix;

    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    Vector3 center;

    Vector3 worldPosition;

public:
    Object();
    virtual ~Object();

    void addObject(Object* obj);
    void removeObject(Object* obj);

    void transform(Matrix4* viewMatrix, Matrix4* viewProjectionMatrix, Vector3* cameraPosition);
    Matrix4 getModelMatrix();
    Matrix4 getModelViewProjectMatrix();

    void setPosition(const float x, const float y, const float z);
    void setPosition(Vector3 position);
    Vector3 getPosition();
    Vector3 getWorldPosition();

    void setRotation(const float xAngle, const float yAngle, const float zAngle);
    void setRotation(Quaternion rotation);
    Quaternion getRotation();

    void setScale(const float factor);
    void setScale(Vector3 scale);
    Vector3 getScale();

    void setCenter(const float x, const float y, const float z);
    void setCenter(Vector3 center);
    Vector3 getCenter();

    virtual void update();

  	bool load();
    bool draw();
    void destroy();

};

#endif /* object_h */
