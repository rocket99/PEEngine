#ifndef __PEPlane_H__
#define __PEPlane_H__
#include "../PEPrefix.h"
#include "PEDataType.h"
#include "PELine.h"
class PEPlane
{
public:
    PEPlane(const P3D &origin, const V3D &normal);
    ~PEPlane();
    bool isParalleltoLine(const PELine3D &line);
    P3D crossPoint(const PELine3D &line);
    
    PELine3D crossLine(const PEPlane &P);
    
    P3D &NormalVector();
    const P3D &NormalVector() const;
    
    bool isPointOnPlane(const P3D &P);
private:
    P3D m_origin;
    V3D m_normal;
    float m_const;//m_normal.x*x + m_normal.y*y + m_normal.z*z + m_const = 0.0;
};




#endif
