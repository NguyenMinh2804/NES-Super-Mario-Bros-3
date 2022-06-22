#include "Tree.h"
#include "Sprites.h"

void CTree::Render()
{
	CAnimations::GetInstance()->Get(ANI_TREE_ID)->Render(x, y);
}

void CTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TREE_BBOX_WIDTH / 2;
	t = y - TREE_BBOX_HEIGHT / 2;
	r = l + TREE_BBOX_WIDTH;
	b = t + TREE_BBOX_HEIGHT;
}