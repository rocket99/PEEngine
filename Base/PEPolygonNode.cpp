//
//  PEPolygonNode.cpp
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEPolygonNode.h"
#include "../Math/PEMath.h"


PEPolygonNode::PEPolygonNode():
m_data(NULL), m_num(0)
{
    
}

PEPolygonNode::~PEPolygonNode()
{
    delete [] m_data;
}

PEPolygonNode *PEPolygonNode::createWithPoints(P2D *points, int num)
{
    PEPolygonNode *polygon = new PEPolygonNode;
    if(polygon->initWithPoints(points, num)){
        polygon->autoRelease();
        return polygon;
    }
    return polygon;
}

bool PEPolygonNode::initWithPoints(P2D *points, int num)
{
    if(!PERealNode::init()){
        return false;
    }
    m_num = num;
    PEPolygon polygon(points, num);
    m_polygon = polygon;
    this->initData();
    return true;
}

PEPolygonNode *PEPolygonNode::createWithPoints(const vector<P2D> &points)
{
    PEPolygonNode *poly = new PEPolygonNode;
    if(poly->initWithPoints(points)){
        poly->autoRelease();
        return poly;
    }
    delete poly;
    return NULL;
}

bool PEPolygonNode::initWithPoints(const vector<P2D> &points)
{
    if(!PERealNode::init()){
        return false;
    }
    PEPolygon polygon(points);
    m_polygon = polygon;
    m_num = m_polygon.verticeNum();
    this->initData();
    return true;
}

PEPolygonNode *PEPolygonNode::create(const PEPolygon &polygon)
{
    PEPolygonNode *node = new PEPolygonNode;
    if(node->initWithPolygon(polygon)){
        node->autoRelease();
        return node;
    }
    delete node;
    return NULL;
}

bool PEPolygonNode::initWithPolygon(const PEPolygon &polygon)
{
    if(!PERealNode::init()){
        return false;
    }
    m_polygon = polygon;
    m_num = m_polygon.verticeNum();
    this->initData();
    return true;
}


void PEPolygonNode::initData()
{
    m_data = (float *)malloc(sizeof(float)*m_num*3);
    vector<P2D> points = m_polygon.GetPoints();
    for(int i=0; i<m_num; ++i){
        m_data[3*i+0] = points[i].x;
        m_data[3*i+1] = points[i].y;
        m_data[3*i+2] = 0.0;
    }

}

void PEPolygonNode::draw()
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

void PEPolygonNode::drawFBO()
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

void PEPolygonNode::drawMethod()
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
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_num);
    glDisableVertexAttribArray(0);
    this->deleteMaterialUbo();
}

