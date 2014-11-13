#include "pch.h"
#include "Network.h"

#include "objects/Stage.h"
#include "objects/EnemySpawner.h"

void Network::handleUnitSpawn(
	unit_spawn *pkt){

	auto stage = Stage::getInstance(0);

}
void Network::handleUnitRemove(
	unit_remove *pkt){


}