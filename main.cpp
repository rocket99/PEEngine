#include "PEEngine.h"

//edit test to local sync
int main(int argc, char *argv[])
{
	PEScene *scene = PEScene::createWithSize("test", 800, 600);
	if(scene == NULL){
		return -1;
	}
	scene->start();
	scene->release();
	return 0;
}
