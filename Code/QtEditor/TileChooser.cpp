#include "TileChooser.h"

TileChooser::TileChooser(const QString& path) : currentTileIndex(0)
{
	QDir directory(path);

	for(	const QString& i
		: directory.entryList(QStringList("*.qml"), QDir::Files) )
	{
		this->tileList.push_back(new Tile(path+"/"+i));
	}

	this->setIcon(*(this->tileList[this->currentTileIndex]->getIcon()));
	this->setIconSize(QSize(TILE_WIDTH, TILE_HEIGHT));

	this->connect(this, SIGNAL(released()), SLOT(releasedHandler()));
}

const Tile* TileChooser::getCurrentTile() const
{
	return this->tileList[this->currentTileIndex];
}

void TileChooser::releasedHandler()
{
	this->currentTileIndex
		= (this->currentTileIndex+1)%this->tileList.size();

	this->setIcon(*(this->tileList[this->currentTileIndex]->getIcon()));
}
