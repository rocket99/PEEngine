//
//  PEPolygon.cpp
//  Engine
//
//  Created by rocket99 on 14/10/20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEPolygon.h"
#include "PEDataType.h"

PEPolygon::PEPolygon(P2D *points, int num)
{
    if(num < 3){return;}
    
    P2D left = points[0];
    P2D top = points[0];
    P2D right = points[0];
    P2D bottom = points[0];
    for (int i=1; i<num; ++i) {
        if (points[i].x < left.x) {
            left = points[i];
        }
        if (points[i].y > top.y) {
            top = points[i];
        }
        if (points[i].x > right.x) {
            right = points[i];
        }
        if (points[i].y < bottom.y) {
            bottom = points[i];
        }
    }
    VertNode * head = new VertNode;
    head->coord = left;
    VertNode *lst = head;
    if(left != top){
        VertNode *lst0 = new VertNode;
        lst0->coord = top;
        lst->next = lst0;
        lst = lst0;
    }
    if (top != right) {
        VertNode *lst0 = new VertNode;
        lst0->coord = right;
        lst->next = lst0;
        lst = lst0;
    }
    if (right != bottom) {
        if (bottom != left) {
            VertNode *lst0 = new VertNode;
            lst0->coord = bottom;
            lst->next = lst0;
            lst = lst0;
        }
    }
    
    lst->next = head;
    std::vector<P2D> tmpPoint;
    for (int i=0; i<num; ++i) {
        if(points[i] != left && points[i] != top &&
           points[i] != right && points[i] != bottom)
            tmpPoint.push_back(points[i]);
    }
    
    while (tmpPoint.size() > 0) {
        this->removeInnerPoint(head, tmpPoint);
        this->expandConvex(head, tmpPoint);
    }
    
    lst = head;
    do {
        m_points.push_back(lst->coord);
        lst= lst->next;
    }while(lst != head);
    
    this->initVertList();
}

PEPolygon::PEPolygon(const std::vector<P2D> &points)
{
    P2D left = points[0];
    P2D top = points[0];
    P2D right = points[0];
    P2D bottom = points[0];
    for (int i=1; i<points.size(); ++i) {
        if (points[i].x < left.x) {
            left = points[i];
        }
        if (points[i].y > top.y) {
            top = points[i];
        }
        if (points[i].x > right.x) {
            right = points[i];
        }
        if (points[i].y < bottom.y) {
            bottom = points[i];
        }
    }
    VertNode * head = new VertNode;
    head->coord = left;
    VertNode *lst = head;
    if(left != top){
        VertNode *lst0 = new VertNode;
        lst0->coord = top;
        lst->next = lst0;
        lst = lst0;
    }
    if (top != right) {
        VertNode *lst0 = new VertNode;
        lst0->coord = right;
        lst->next = lst0;
        lst = lst0;
    }
    if (right != bottom) {
        if (bottom != left) {
            VertNode *lst0 = new VertNode;
            lst0->coord = bottom;
            lst->next = lst0;
            lst = lst0;
        }
    }
    
    lst->next = head;
    std::vector<P2D> tmpPoint;
    for (int i=0; i<points.size(); ++i) {
        if(points[i] != left && points[i] != top &&
           points[i] != right && points[i] != bottom)
            tmpPoint.push_back(points[i]);
    }
    
    while (tmpPoint.size() > 0) {
        this->removeInnerPoint(head, tmpPoint);
        this->expandConvex(head, tmpPoint);
    }
    
    lst = head;
    do {
        m_points.push_back(lst->coord);
        lst= lst->next;
    }while(lst != head);
    
    this->initVertList();
}

PEPolygon::PEPolygon(const PEPolygon &polygon)
{
    m_points = polygon.GetPoints();
    this->initVertList();
}

PEPolygon::~PEPolygon()
{
    m_points.clear();
    this->deleteVertList();
}

void PEPolygon::expandConvex(VertNode *head, std::vector<P2D> &points)
{
    std::vector<P2D>::iterator it = points.begin();
    while(it != points.end()){
        if (this->isInnerPoint(head, *it)) {
            points.erase(it);
        }else{
            ++ it;
        }
    }
}

void PEPolygon::removeInnerPoint(VertNode *head, std::vector<P2D> &points)
{
    if (points.size() <= 0 ) {
        return;
    }
    VertNode *lst = head;
    do{
        P2D tmpPoint = points[0];
        V2D A = lst->coord - points[0];
        V2D B = lst->next->coord - points[0];
        float dd = A.x*B.y - A.y*B.x;
        for (int i=0; i<points.size(); ++i) {
            V2D A = lst->coord - points[i];
            V2D B = lst->next->coord - points[i];
            float tmpdd = A.x*B.y - A.y*B.x;
            if(tmpdd > dd){
                dd = tmpdd;
                tmpPoint = points[i];
            }
        }
        if(dd > 0.0){
            VertNode *node = new VertNode;
            node->coord = tmpPoint;
            node->next = lst->next;
            lst->next = node;
            lst = node->next;
        }else{
            lst = lst->next;
        }
    }while(lst != head);
}

bool PEPolygon::isInnerPoint(VertNode *head, const P2D &point)
{
    VertNode *lst = head;
    do{
        PELine2D line(lst->coord, lst->next->coord);
        if (line.PointAtWhichSide(point) != PELine2D::Line_Left_Side){
            lst = lst->next;
        }else{
            return false;
        }
    }while(lst != head);
    return true;
}

bool PEPolygon::isInnerPoint(const P2D &P)
{
    return this->isInnerPoint(m_list, P);
}

vector<P2D> & PEPolygon::Points()
{
    return m_points;
}

const vector<P2D> &PEPolygon::Points() const
{
    return m_points;
}

vector<P2D> PEPolygon::GetPoints()
{
    return m_points;
}

vector<P2D> PEPolygon::GetPoints() const
{
    return m_points;
}

void PEPolygon::addPoint(const P2D &P)
{
    m_points.push_back(P);
}

void PEPolygon::addPoint(const P2D &P, int idx)
{
    vector<P2D>::iterator iter = m_points.begin();
    for (int i=0; i<idx; ++i) {
        ++ iter;
    }
    m_points.insert(iter, P);
}

bool PEPolygon::isConvexOrNot()
{
    VertNode *lst = m_list;
    PELine2D line(lst->prev->coord, lst->coord);
    PELine2D::LineSide side0 = line.PointAtWhichSide(lst->next->coord);
    lst = lst->next;
    while(lst != m_list){
        PELine2D line(lst->prev->coord, lst->coord);
        PELine2D::LineSide side1 = line.PointAtWhichSide(lst->next->coord);
        if (side1 != side0 && side0 != PELine2D::LineSide::In_Line) {
            return false;
        }
        side0 = side1;
        lst = lst->next;
    }
    return true;
}

void PEPolygon::initVertList()
{
    m_list = new VertNode;
    m_list->coord = m_points[0];
    m_list->next = NULL;
    m_list->prev = NULL;
    VertNode *lst = m_list;
    for (int i=1; i<m_points.size(); ++i) {
        VertNode *node = new VertNode;
        node->coord = m_points[i];
        node->prev = lst;
        lst->next = node;
        node->next = NULL;
        lst = node;
    }
    lst->next = m_list;
    m_list->prev = lst;
}

void PEPolygon::deleteVertList()
{
    VertNode *lst = m_list->next;
    lst->prev->next = NULL;
    while (lst != NULL) {
        delete m_list;
        m_list = lst;
        lst = m_list->next;
    }
}

float PEPolygon::area()
{
    float sum = 0.0f;
    P2D A = m_list->coord;
    VertNode *lst = m_list->next;
    while (lst->next != m_list) {
        sum += P2D::areaOfTriangle(A, lst->coord, lst->next->coord);
    }
    return sum;
}

P2D PEPolygon::gravityCenter()
{
    float area = 0.0;
    P2D sum = Point2D(0.0, 0.0);
    P2D A = m_list->coord;
    VertNode *lst = m_list->next;
    while (lst->next != m_list) {
        P2D P = P2D::gravityCenterOfTriangle(A, lst->next->coord, lst->next->next->coord);
        float a = P2D::areaOfTriangle(A, lst->coord, lst->next->coord);
        area += a;
        sum += a*P;
    }
    return sum/area;
}

void PEPolygon::operator = (const PEPolygon &polygon)
{
    m_points = polygon.GetPoints();
    this->initVertList();
}

int PEPolygon::verticeNum()
{
    return (int)m_points.size();
}

//PEPolygon PEPolygon::minus(const PEPolygon &poly)
//{
//    
//}

