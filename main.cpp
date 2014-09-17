#include "PEEngine.h"
#include "PEScene.h"

//edit test to local sync
int main(int argc, char *argv[])
{
	Size3D size = GLOBAL_WORLD_SIZE;
	PEScene *scene = PEScene::createWithSize("test", size.x, size.y);
	if(scene == NULL){
		return -1;
	}
	scene->start();
	scene->release();
	return 0;
}


