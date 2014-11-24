#include "PERandom.h"

static PERandom *instance = NULL;
PERandom *PERandom::getInstance()
{
	if(instance == NULL){
		instance = new PERandom();
	}
	return instance;
}

void PERandom::purge()
{
	if(instance != NULL){
		delete instance;
	}
	instance = NULL;
}

PERandom::PERandom()
{
	srand((unsigned int)time(NULL));
	m_capacity = 100;
	m_pool = new float[m_capacity];
	m_seed = (float)(rand()%10000)/10000.0;
	this->generate();
	m_idx = 0;
}

PERandom::~PERandom()
{
	delete [] m_pool;
}

void PERandom::generate()
{
	m_pool[0] = m_seed;
	for(int i=1; i<512; ++i){
		m_pool[i] = 3.68783 * m_pool[i-1]*(1.0f-m_pool[i-1]);
	}
}

float PERandom::Rand()
{
	float ret = m_pool[m_idx ++];
	if(m_idx >= 512){
		m_seed = ret;
		this->generate();
		m_idx = 1;
	}
	return ret;
}

