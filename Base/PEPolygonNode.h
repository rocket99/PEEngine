//
//  PEPolygonNode.h
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEPolygonNode__
#define __Engine__PEPolygonNode__

#include <iostream>
#include "PERealNode.h"

class PEPolygonNode:public PERealNode
{
public:
    PEPolygonNode();
    ~PEPolygonNode();
    static PEPolygonNode *createWithPoints(P2D *points, int num);
    bool initWithPoints(P2D *points, int num);
    
    static PEPolygonNode *createWithPoints(const vector<P2D> &points);
    bool initWithPoints(const vector<P2D> &points);
    
    virtual void draw();
    virtual void drawFBO();
private:
    float *m_data;
    vector <P2D> m_points;
    int m_num;
    void drawMethod();
};
#endif /* defined(__Engine__PEPolygonNode__) */
