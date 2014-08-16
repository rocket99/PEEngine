#include "PEMatrix.h"

//edit test to local sync
int main(int argc, char *argv[])
{
	PEMatrix *idMat = PEMatrix::IdentityMat(3);
	idMat->setElm(0, 2, 2);
	idMat->setElm(2, 0, 4);
	idMat->setElm(0, 0, 4);
	idMat->display();
	PEMatrix *inv = idMat->inverse();
	inv->display();
	PEMatrix *mat1 = (*inv)*(*idMat);
	mat1->display();
	PELog("id matrix morel %.3f", idMat->morel());
	PELog("Hello, github!\n");
	delete idMat;
	delete  inv;
	delete mat1;
	return 0;
}
