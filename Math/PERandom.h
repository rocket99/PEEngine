#include "PEDataType.h"

class PERandom
{
	public:
		static PERandom *getInstance();
		static void purge();

		PERandom();
		~PERandom();
	
		float Rand();
	protected:
		size_t m_capacity;
		float *m_pool;//
		float m_seed;//种子

		void generate();
		int m_idx;
};


