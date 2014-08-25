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
    if(PEPolygon->initWithPoints(points, num)){
        return polygon;
    }
    
}

bool PEPolygon::initWithPoints(P2D *points, int num)
{
    
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
    GLint loc = glGetUniformLocation(m_program, UNIFORM_SPACE);
    if(loc >=0){
        glUniform3f(loc, m_worldSize.x, m_worldSize.y, m_worldSize.z);
    }
    loc = glGetUniformLocation(m_program, UNIFORM_POSITION);
    if(loc >= 0){
        this->getWorldPos();
        glUniform3f(loc, m_worldPos.x, m_worldPos.y, m_worldPos.z);
    }
    loc = glGetUniformLocation(m_program, UNIFORM_ROTATE);
    if(loc >= 0){
        glUniformMatrix4fv(loc, 1, GL_FALSE, m_rotate.getData());
    }
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_data);
    glDrawArrays(GL_LINE_LOOP, 0, m_num);
    glDisableVertexAttribArray(0);
}