#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include <src/engine/math/kinematics.h>
#include <src/engine/math/matrix.h>
#include <src/engine/math/vector.h>



namespace e172 {

class PhysicalObject {
    Kinematics<double> rotationKinematics;
    Kinematics<Vector> positionKinematics;
    double m_mass = 1;
    double m_friction = 1;

    Matrix m_rotationMatrix;
public:
    class ConnectionNode {
        friend PhysicalObject;
        PhysicalObject *m_object = nullptr;
        Vector m_offset;
        double m_rotation;
    };
    ConnectionNode connectionNode(const Vector& offset, double rotation);

    void resetPhysicsProperties(e172::Vector position, double rotation, e172::Vector velocity = e172::Vector(), double rotationVelocity = 0);

    PhysicalObject();
    inline auto rotation() const { return rotationKinematics.value(); };
    inline auto position() const { return positionKinematics.value(); };

    inline auto rotationVelocity() const { return rotationKinematics.velocity(); };
    inline auto velocity() const { return positionKinematics.velocity(); };

    inline auto rotationAcceleration() const { return rotationKinematics.acceleration(); };
    inline auto acceleration() const { return positionKinematics.acceleration(); };

    void addRotationForce(double value);

    void addRotationGravityForce(double destiantionRotation, double coeficient = 1);
    void addRotationPursuitForce(const PhysicalObject *object, double deltaTime);
    void addRotationFollowForce(double destiantionRotation, double maxAngleDistance, double coeficient = 1);
    void addRotationRestoringForce(double destiantionRotation, double coeficient = 1);

    void addTargetRotationForse(double destinationAngle, double rotationForceModule, double maxRotationVelocity);


    void addForce(const Vector& value);
    void addForwardForce(double module);
    void addLeftForce(double module);
    void addRightForce(double module);

    void addLimitedRotationForce(double value, double maxAngleVelocity);

    void addLimitedForce(const Vector& value, double maxVelocity);
    void addLimitedForwardForce(double module, double maxVelocity);
    void addLimitedLeftForce(double module, double maxVelocity);
    void addLimitedRightForce(double module, double maxVelocity);


    void addPursuitForce(const PhysicalObject *object, double deltaTime);
    void addGravityForce(const Vector &gravityCenter, double coeficient = 1);
    void addFollowForce(const Vector &targetPoint, double maxDistance, double coeficient = 1);
    void addRestoringForce(const Vector &destiantionPosition, double coeficient = 1);


    static void connectNodes(ConnectionNode node0, ConnectionNode node1, double coeficient = 1, double rotationCoeficient = 1);

    double mass() const;
    void setMass(double mass);
    double friction() const;
    void setFriction(double friction);

    void proceedPhysics(double deltaTime);

    Matrix rotationMatrix() const;
};

}
#endif // PHYSICALOBJECT_H
