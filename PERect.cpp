//
//  PERect.cpp
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PERect.h"

PERect::PERect():m_width(1.0f),m_height(1.0f)
{}
PERect::~PERect(){}

PERect *PERect::create(float width, float height)
{
    PERect *rect = new PERect();
    if(rect->initWithSize(width, height)){
        return rect;
    }
    delete rect;
    return NULL;
}

bool PERect::initWithSize(float width, float height)
{
    if (!PENode::init()) {
        return false;
    }
    m_width = width;
    m_height = height;
    m_data = (float *)malloc(sizeof(float)*(12+8));
    
    m_data[0] = -0.5*m_width;
    m_data[1] = -0.5*m_height;
    m_data[2] = 0.0;
    
    m_data[3] = -0.5*m_width;
    m_data[4] = 0.5*m_height;
    m_data[5] = 0.0;
    
    m_data[6] = 0.5*m_width;
    m_data[7] = 0.5*m_height;
    m_data[8] = 0.0;
    
    m_data[9] = 0.5*m_width;
    m_data[10] = -0.5*m_height;
    m_data[11] = 0.0;
    
    m_data[12] = 0.0; m_data[13] = 0.0;
    m_data[14] = 0.0; m_data[15] = 1.0;
    m_data[16] = 1.0; m_data[17] = 1.0;
    m_data[18] = 1.0; m_data[19] = 0.0;
    return true;
}

Color4F &PERect::Color()
{
    return m_color;
}

void PERect::draw()
{
    if(m_isVisible == false){
        return;
    }
    if(glIsProgram(m_program) == GL_FALSE){
        return;
    }
    glUseProgram(m_program);
    
    GLint loc = glGetUniformLocation(m_program, UNIFORM_POSITION);
    if(loc >= 0){
        this->setWorldPos();
        glUniform3f(loc, m_worldPos.x, m_worldPos.y, m_worldPos.z);
    }
    loc = glGetUniformLocation(m_program, UNIFORM_SPACE);
    if(loc >= 0){
        glUniform3f(loc, m_worldSize.x, m_worldSize.y, m_worldSize.z);
    }
    loc = glGetUniformLocation(m_program, UNIFORM_ROTATE);
    if(loc >=0){
        this->setWorldRotate();
        m_worldRotate.display();
        glUniformMatrix4fv(loc, 1, GL_FALSE, m_worldRotate.getData());
    }
    loc = glGetUniformLocation(m_program, UNIFORM_COLOR);
    if(loc >= 0){
        glUniform4f(loc, m_color.r, m_color.g, m_color.b, m_color.a);
    }
    
    loc = glGetUniformLocation(m_program, UNIFORM_TEXTURE);
    if(loc >=0){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glUniform1i(loc, 0);
    }
    
    glEnableVertexAttribArray(ATTRIB_POINT_LOC);
    glVertexAttribPointer(ATTRIB_POINT_LOC, 3, GL_FLOAT, GL_FALSE, 0, m_data);
    glEnableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glVertexAttribPointer(ATTRIB_TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 0, &m_data[12]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(ATTRIB_POINT_LOC);
    glDisableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
}
