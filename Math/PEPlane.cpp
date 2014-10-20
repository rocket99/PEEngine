#include "PEPlane.h"

PEPlane::PEPlane(const P3D &origin, const V3D &normal)
{
	m_origin = origin;
	m_normal = normal;
    m_const = -dot(m_normal, m_origin);
}

PEPlane::~PEPlane()
{

}

bool PEPlane::isParalleltoLine(const PELine3D &line)
{
    float value = dot(line.Direct(), m_normal);
    return (value == 0.0);
}

bool PEPlane::isParalleltoLine(const PELine3D &line) const
{
    float value = dot(line.Direct(), m_normal);
    return (value == 0.0);
}

P3D PEPlane::crossPoint(const PELine3D &line)
{
    float t = -(m_const + dot(line.Offset(), m_normal))/dot(line.Direct(), m_normal);
    return line.Direct()*t + line.Offset();
}

P3D PEPlane::crossPoint(const PELine3D &line) const
{
    float t = -(m_const + dot(line.Offset(), m_normal))/dot(line.Direct(), m_normal);
    return line.Direct()*t + line.Offset();
}

PELine3D PEPlane::crossLine(const PEPlane &P0)
{
    P3D vec = cross(m_normal, P0.m_normal);
    V3D cc = cross(m_normal, vec);
    PELine3D line(cc, m_origin.x, m_origin.y, m_origin.z);
    P3D p = P0.crossPoint(line);
    return PELine3D(vec, p.x, p.y, p.z);
}

PELine3D PEPlane::crossLine(const PEPlane &P0) const
{
    P3D vec = cross(m_normal, P0.m_normal);
    V3D cc = cross(m_normal, vec);
    PELine3D line(cc, m_origin.x, m_origin.y, m_origin.z);
    P3D p = P0.crossPoint(line);
    return PELine3D(vec, p.x, p.y, p.z);
}

PELine3D PEPlane::reflectLine(const PELine3D &line)
{
    P3D P0 = this->crossPoint(line);//交点
    
    V3D n0 = m_normal.normal();
    V3D in = line.Direct().normal();
    if (dot(n0, in) < 0.0) {
        in = -1.0f * in;
    }
    V3D out = 2.0 * dot(n0, in)*n0 - in;
    return PELine3D(out.normal(), P0.x, P0.y, P0.z);
}

bool PEPlane::isPointOnPlane(const P3D &P)
{
    return m_const+dot(m_normal, P) == 0.0;
}

bool PEPlane::isPointOnPlane(const P3D &P) const
{
    return m_const+dot(m_normal, P) == 0.0;
}

P3D &PEPlane::NormalVector()
{
    return m_normal;
}

const P3D &PEPlane::NormalVector() const
{
    return m_normal;
}


