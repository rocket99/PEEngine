//
//  PEPolygon.cpp
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEPolygon.h"


PEPolygon::PEPolygon():
m_data(NULL), m_num(0)
{
    
}

PEPolygon::~PEPolygon()
{
    delete [] m_data;
}

PEPolygon *PEPolygon::createWithPoints(P2D *points, int num)
{
    PEPolygon *polygon = new PEPolygon;
    if(polygon->initWithPoints(points, num)){
        return polygon;
    }
    return polygon;
}

bool PEPolygon::initWithPoints(P2D *points, int num)
{
    if(!PENode::init()){
        return false;
    }
    m_num = num;
    for(int i=0; i<m_num; ++i){
        m_points.push_back(points[i]);
    }
    m_data = (float *)malloc(sizeof(float)*m_num*3);
    for(int i=0; i<m_num; ++i){
        m_data[3*i+0] = m_points[i].x;
        m_data[3*i+1] = m_points[i].y;
        m_data[3*i+2] = 0.0;
    }
    return true;
}


void PEPolygon::draw()
{
    if (!m_isVisible) {
        return;
    }
    this->PENode::draw();
    if (glIsProgram(m_program) == GL_FALSE) {
        return;
    }
    glUseProgram(m_program);
    GLint loc = glGetUniformLocation(m_program, UNIFORM_COLOR);
    if(loc >= 0){
        glUniform4f(loc, m_color.r, m_color.g, m_color.b, m_color.a);
    }
    this->setSpaceUniform();
    this->setWorldMatUniform();
    this->setModelViewProjectUniform();
    this->setColorUniform();
    this->setMaterialUniformBlock();
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_data);
    glDrawArrays(GL_LINE_LOOP, 0, m_num);
    glDisableVertexAttribArray(0);
    this->deleteMaterialUbo();
}

