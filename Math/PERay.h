//
//  PERay.h
//  Engine
//
//  Created by rocket99 on 14-9-16.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PERay__
#define __Engine__PERay__

#include <iostream>
#include "PEVector.h"
#include "PEDataType.h"

class PERay
{
public:
    PERay();
    PERay(const P3D &origin, const V3D &vec);
    ~PERay();
    
    P3D &Origin();
    V3D &Direction();
    
    PERay *getParent();
    void setParent(PERay *ray);
private:
    P3D m_origin;
    V3D m_direction;
    PERay *m_parent;
};
#endif /* defined(__Engine__PERay__) */
