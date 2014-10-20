//
//  PEPointSet.h
//  Engine
//
//  Created by rocket99 on 14-10-10.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEPointSet__
#define __Engine__PEPointSet__

#include <stdio.h>
#include "../PEPrefix.h"
#include "../Math/PEMath.h"
#include "PEPolygonNode.h"

class PEPoint2DSet:public PERealNode
{
public:
    PEPoint2DSet():m_allPoints(NULL), m_pointNum(0){};
    ~PEPoint2DSet(){
        if (m_allPoints != NULL) {
            delete m_allPoints;
        }
    };
    
    static PEPoint2DSet *createWithPoints(P2D *points, int num);
    bool initwithPoints(P2D *points, int num);
    
    PEPolygonNode *MaxConvexPolygon();
    
    void draw();
    void drawFBO();
    void drawMethod();
private:
    P2D *m_allPoints;
    int m_pointNum;

    typedef struct vert{
        P2D coord;
        struct vert *next;
    } VertNode;
    void expandConvex(VertNode *head, std::vector<P2D> &points);
    void removeInnerPoint(VertNode *head, std::vector<P2D> &points);
    bool isInnerPoint(VertNode *head, const P2D &point);
    
    GLfloat *m_data;
};


#endif /* defined(__Engine__PEPointSet__) */
