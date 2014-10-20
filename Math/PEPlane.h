#ifndef __PEPlane_H__
#define __PEPlane_H__
#include "../PEPrefix.h"
#include "PEDataType.h"
#include "PELine.h"
class PEPlane
{
public:
    PEPlane(const P3D &origin, const V3D &normal);//一个点，一个发向量确定一条直线
    ~PEPlane();
    bool isParalleltoLine(const PELine3D &line);
    bool isParalleltoLine(const PELine3D &line) const;
    P3D crossPoint(const PELine3D &line);
    P3D crossPoint(const PELine3D &line) const;
    PELine3D crossLine(const PEPlane &P);
    PELine3D crossLine(const PEPlane &P) const;
    P3D &NormalVector();
    const P3D &NormalVector() const;
    bool isPointOnPlane(const P3D &P);
    bool isPointOnPlane(const P3D &P) const;
    
    PELine3D reflectLine(const PELine3D &line);
private:
    P3D m_origin;
    V3D m_normal;
    float m_const;//m_normal.x*x + m_normal.y*y + m_normal.z*z + m_const = 0.0;
};




#endif
