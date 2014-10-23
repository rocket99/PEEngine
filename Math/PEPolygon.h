//
//  PEPolygon.h
//  Engine
//
//  Created by rocket99 on 14/10/20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//  Convex Polygon 必须是连通域

#ifndef __Engine__PEPolygon__
#define __Engine__PEPolygon__

#include <stdio.h>
#include "PEDataType.h"
#include "PELine.h"

class PEPolygon
{
public:
    PEPolygon():m_list(NULL){m_points.clear();};
    PEPolygon(P2D *points, int num);
    PEPolygon(const std::vector<P2D> &points);
    PEPolygon(const PEPolygon &polygon);
    ~PEPolygon();
    
    vector<P2D> &Points();
    const vector<P2D> &Points() const;
    vector<P2D> GetPoints();
    vector<P2D> GetPoints() const;
    
    void addPoint(const P2D &P);
    void addPoint(const P2D &P, int idx);
    bool isConvexOrNot();
    bool isInnerPoint(const P2D &P);
    
    PEPolygon minus(const PEPolygon &ploy);
    
    float area();//面积
    P2D gravityCenter();
    int verticeNum();
    
    void operator = (const PEPolygon &polygon);
private:
    vector<P2D> m_points;
    
    typedef struct vert{
        P2D coord;
        struct vert *next;
        struct vert *prev;
    } VertNode;
    
    void expandConvex(VertNode *head, std::vector<P2D> &points);
    void removeInnerPoint(VertNode *head, std::vector<P2D> &points);
    bool isInnerPoint(VertNode *head, const P2D &point);
    
    VertNode *m_list;
    void initVertList();
    void deleteVertList();
};

#endif /* defined(__Engine__PEPolygon__) */
