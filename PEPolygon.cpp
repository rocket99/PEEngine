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
    GLint loc = glGetUniformLocation(m_program, "u_space");
    if(loc >=0){
        glUniform3f(loc, m_worldSize.x, m_worldSize.y, m_worldSize.z);
    }
    loc = glGetUniformLocation(m_program, "u_position");
    if(loc >= 0){
        this->getWorldPos();
        glUniform3f(loc, m_worldPos.x, m_worldPos.y, m_worldPos.z);
    }
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_data);
    glDrawArrays(GL_LINE_LOOP, 0, m_num);
    glDisableVertexAttribArray(0);
}