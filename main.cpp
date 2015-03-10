#include "PEEngine.h"
#include "TestScene.h"
#include "NormalMapScene.h"
#include "JuliaScene.h"

//edit test to local sync
int main(int argc, char *argv[])
{
	
	printf("choose secne:\n");
	printf("0:common\n1:normal map\n2:julia fract\n3:\n");

	Size3D size = GLOBAL_WORLD_SIZE;
	PEScene *scene = nullptr;
	unsigned int a = getchar();
	switch(a){
		case '0':
			scene = TestScene::Scene(size);
			break;
		case '1':
			scene = NormalMapScene::Scene(size);
			break;
		case '2':
			{
				Size3D size0; size0.x = size0.y= size.z = 800;
				scene = JuliaScene::Scene(size);
			}
			break;
		case '3':
			scene = TestScene::Scene(size);
			break;
		default:
			break;
	}
	if(nullptr == scene){
		return -1;
	}
	scene->start();
	return 0;
}


