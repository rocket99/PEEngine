#include "PEPlane.h"

PEPlane::PEPlane(const P3D &origin, const V3D &normal)
{
	m_origin = origin;
	m_normal = normal;
}

PEPlane::~PEPlane()
{

}

