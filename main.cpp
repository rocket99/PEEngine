#include "PEEngine.h"
#include "TestScene.h"

//edit test to local sync
int main(int argc, char *argv[])
{
	Size3D size = GLOBAL_WORLD_SIZE;
	PEScene *scene = TestScene::Scene(size);
	if(scene == NULL){
		return -1;
	}
	scene->start();

//	scene->release();
	return 0;
}


