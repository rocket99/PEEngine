//
//  PEPointSet.cpp
//  Engine
//
//  Created by rocket99 on 14-10-10.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEPointSet.h"

PEPoint2DSet *PEPoint2DSet::createWithPoints(P2D *points, int num)
{
    PEPoint2DSet *set = new PEPoint2DSet;
    if(set->initwithPoints(points, num)){
        set->autoRelease();
        return set;
    }
    delete set;
    return NULL;
}

bool PEPoint2DSet::initwithPoints(P2D *points, int num)
{
    if (!PERealNode::init()) {
        return false;
    }
    m_pointNum = num;
    m_allPoints = new P2D[m_pointNum];
    for(int i=0; i<m_pointNum; ++i){
        m_allPoints[i] = points[i];
    }
    m_data = new GLfloat[m_pointNum*3];
    for(int i=0; i<m_pointNum; ++i){
        m_data[3*i+0] = m_allPoints[i].x;
        m_data[3*i+1] = m_allPoints[i].y;
        m_data[3*i+2] = 0.0;
    }
    return true;
}

PEPolygonNode *PEPoint2DSet::MaxConvexPolygon()
{
    if(m_pointNum < 3){
        return NULL;
    }
    
    P2D left = m_allPoints[0];
    P2D top = m_allPoints[0];
    P2D right = m_allPoints[0];
    P2D bottom = m_allPoints[0];
    for (int i=1; i<m_pointNum; ++i) {
        if (m_allPoints[i].x < left.x) {
            left = m_allPoints[i];
        }
        if (m_allPoints[i].y > top.y) {
            top = m_allPoints[i];
        }
        if (m_allPoints[i].x > right.x) {
            right = m_allPoints[i];
        }
        if (m_allPoints[i].y < bottom.y) {
            bottom = m_allPoints[i];
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
    for (int i=0; i<m_pointNum; ++i) {
        if(m_allPoints[i] != left && m_allPoints[i] != top &&
           m_allPoints[i] != right && m_allPoints[i] != bottom)
            tmpPoint.push_back(m_allPoints[i]);
    }
    
    while (tmpPoint.size() > 0) {
        this->removeInnerPoint(head, tmpPoint);
        this->expandConvex(head, tmpPoint);
    }
    
    tmpPoint.clear();
    lst = head;
    do {
        tmpPoint.push_back(lst->coord);
        lst= lst->next;
    }while(lst != head);
    PEPolygonNode *polygon = PEPolygonNode::createWithPoints(tmpPoint);
    tmpPoint.clear();
    return polygon;
}

void PEPoint2DSet::removeInnerPoint(VertNode *head, std::vector<P2D> &points)
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
void PEPoint2DSet::expandConvex(VertNode *head, std::vector<P2D> &points){
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

bool PEPoint2DSet::isInnerPoint(VertNode *head, const P2D &point)
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


void PEPoint2DSet::draw()
{
    if (!m_isVisible) {
        return;
    }
    this->PENode::draw();
    m_program = m_program1;
    if (glIsProgram(m_program) == GL_FALSE) {
        return;
    }
    glUseProgram(m_program);
    this->setModelViewProjectUniform();
    this->setLightProjectViewUniform();
    this->setDepthTexUnifrom();
    this->drawMethod();
}

void PEPoint2DSet::drawFBO()
{
    if (!m_isVisible) {
        return;
    }
    this->PENode::draw();
    m_program = m_program0;
    if (glIsProgram(m_program) == GL_FALSE) {
        return;
    }
    glUseProgram(m_program);
    this->setLightProjectViewUniform(UNIFORM_MODELPROJECT);
    this->drawMethod();
}

void PEPoint2DSet::drawMethod()
{
    GLint loc = glGetUniformLocation(m_program, UNIFORM_COLOR);
    if(loc >= 0){
        glUniform4f(loc, m_color.r, m_color.g, m_color.b, m_color.a);
    }
    this->setSpaceUniform();
    this->setCameraPosUniform();
    this->setWorldMatUniform();
    this->setColorUniform();
    this->setMaterialUniformBlock();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(ATTRIB_POINT_LOC, 3, GL_FLOAT, GL_FALSE, 0, m_data);
    glDrawArrays(GL_POINTS, 0, m_pointNum);
    glDisableVertexAttribArray(0);
    this->deleteMaterialUbo();
}

