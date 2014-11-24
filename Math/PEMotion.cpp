#include "PEMotion.h"

PEMotion::PEMotion()
{
	m_position = Point3D(0.0, 0.0, 0.0);
	m_velocity = Point3D(0.0, 0.0, 0.0);
	m_acceleration = Point3D(0.0, 0.0, 0.0);


}

PEMotion::~PEMotion()
{

}

P3D & PEMotion::Position()
{
	return m_position;
}

V3D &PEMotion::Velocity()
{
	return m_velocity;
}

V3D &PEMotion::Accelerate()
{
	return m_acceleration;
}

void PEMotion::LorenzMotion(float delta)
{
	m_velocity.x = 10.0 *(m_position.y-m_position.x);
	m_velocity.y = m_position.x*(28.0-m_position.z) - m_position.y;
	m_velocity.z = m_position.x*m_position.y - 8.0/3.0*m_position.z;
	m_position += delta*m_velocity;
}



