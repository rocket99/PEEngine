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
		P2D crossPoint(const PELine3D &line);
	private:
		P3D m_origin;
		V3D m_normal;
};




#endif
