
#ifndef _AIUNIT_H
#define	_AIUNIT_H

#include "AStarSearch.h"
#include "WorldMap.h"
#include "GameObject.h"
#include <TooN/TooN.h>

using namespace TooN;

class Director; // forward decl

class AIUnit : public GameObject {
public:
    AIUnit( WorldMap* m, btDynamicsWorld* w, double x, double y, double z );
    virtual ~AIUnit();
    void tick( Director* d );
    double getX();
    double getY();
    double getZ();
    double getRotationAngle();
    Vector<3> getRotationAxis();
    void navigateTo( Waypoint* goal );
    void push( double x, double y, double z );
    void removeFromWorld( btDynamicsWorld* w );

    static int type;
    virtual int getType();
private:
    int currTick, lastNode;
    double xDir, yDir, zDir;
    double xPos, yPos, zPos;
    double xPosPrev, yPosPrev, zPosPrev;
    double rotAngle;
    Vector<3> rotAxis;
    btRigidBody* boxBody;
    list<Waypoint*> path;
    WorldMap* map;
    AStarSearch search;
    static btCollisionShape* boxShape;
};

#endif	/* _AIUNIT_H */

