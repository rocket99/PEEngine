#ifndef __PEMotion_H__
#define __PEMotion_H__

#include "PEDataType.h"

class PEMotion
{
	public:
		PEMotion();
		~PEMotion();
		void LorenzMotion(float delta);
		
		P3D &Position();
		V3D &Velocity();
		V3D &Accelerate();

	protected:
		P3D m_position;
		V3D m_velocity;
		V3D m_acceleration;
		
		V3D m_rotateAxis;
		float m_rotateAngle;
		float m_angleVelocity;
		float m_angleAcceleration;
};


#endif
