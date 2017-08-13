#include "stdafx.h"
#include "myKDTree.h"


myKDTree::myKDTree()
{
}


myKDTree::~myKDTree()
{
	if (left != nullptr) delete(left);
	if (right != nullptr) delete(right);
}

bool myKDTree::compx(CameraRayPoint &a, CameraRayPoint &b)
{
	return (a.info.position.x < b.info.position.x);
}

bool myKDTree::compy(CameraRayPoint &a, CameraRayPoint &b)
{
	return (a.info.position.y < b.info.position.y);
}

bool myKDTree::compz(CameraRayPoint &a, CameraRayPoint &b)
{
	return (a.info.position.z < b.info.position.z);
}

void myKDTree::bulidTree(std::vector<CameraRayPoint> data, myKDTree *root)
{
	if (data.size() == 0) return;
	if (data.size() == 1)
	{
		root->point = data[0];
		root->axis = 0;
		root->value = root->point.info.position.x;
		root->left = nullptr;
		root->right = nullptr;
		root->minBound = root->point.info.position;
		root->maxBound = root->point.info.position;
		return;
	}

	int index;

	int ran = rand() % 3;
	if (ran == 0)
	{
		std::sort(data.begin(), data.end(), myKDTree::compx);
		root->axis = 0;
		index = data.size() / 2;
		root->point = data[index];
		root->value = root->point.info.position.x;
	}
	else if (ran == 1)
	{
		std::sort(data.begin(), data.end(), myKDTree::compy);
		root->axis = 1;
		index = data.size() / 2;
		root->point = data[index];
		root->value = root->point.info.position.y;
	}
	else
	{
		std::sort(data.begin(), data.end(), myKDTree::compz);
		root->axis = 2;
		index = data.size() / 2;
		root->point = data[index];
		root->value = root->point.info.position.z;
	}

	root->minBound = root->point.info.position;
	root->maxBound = root->point.info.position;

	if (index > 0)
	{
		std::vector<CameraRayPoint> v1(data.begin(), data.begin() + index);
		root->left = new myKDTree;
		bulidTree(v1, root->left);
		if (root->left->minBound.x < root->minBound.x) root->minBound.x = root->left->minBound.x;
		if (root->left->minBound.y < root->minBound.y) root->minBound.y = root->left->minBound.y;
		if (root->left->minBound.z < root->minBound.z) root->minBound.z = root->left->minBound.z;
		if (root->left->maxBound.x > root->maxBound.x) root->maxBound.x = root->left->maxBound.x;
		if (root->left->maxBound.y > root->maxBound.y) root->maxBound.y = root->left->maxBound.y;
		if (root->left->maxBound.z > root->maxBound.z) root->maxBound.z = root->left->maxBound.z;
	}
	else root->left = nullptr;

	if (index < (int)data.size() - 1)
	{
		std::vector<CameraRayPoint> v2(data.begin() + index + 1, data.end());
		root->right = new myKDTree;
		bulidTree(v2, root->right);
		if (root->right->minBound.x < root->minBound.x) root->minBound.x = root->right->minBound.x;
		if (root->right->minBound.y < root->minBound.y) root->minBound.y = root->right->minBound.y;
		if (root->right->minBound.z < root->minBound.z) root->minBound.z = root->right->minBound.z;
		if (root->right->maxBound.x > root->maxBound.x) root->maxBound.x = root->right->maxBound.x;
		if (root->right->maxBound.y > root->maxBound.y) root->maxBound.y = root->right->maxBound.y;
		if (root->right->maxBound.z > root->maxBound.z) root->maxBound.z = root->right->maxBound.z;
	}
	else root->right = nullptr;
}

void myKDTree::getNeighbours(Vector3 pos, std::vector<CameraRayPoint> &ans, double radius, myKDTree *root)
{
	if ((root->point.info.position - pos).sqrLength() < radius*radius) ans.push_back(root->point);
	double expDis1 = 0;
	double expDis2 = 0;
	double tmp;

	if (root->left != nullptr)
	{
		tmp = pos.x - root->left->maxBound.x;
		if (tmp > 0) expDis1 += tmp*tmp;
		tmp = pos.y - root->left->maxBound.y;
		if (tmp > 0) expDis1 += tmp*tmp;
		tmp = pos.z - root->left->maxBound.z;
		if (tmp > 0) expDis1 += tmp*tmp;
		tmp = root->left->minBound.x - pos.x;
		if (tmp > 0) expDis1 += tmp*tmp;
		tmp = root->left->minBound.y - pos.y;
		if (tmp > 0) expDis1 += tmp*tmp;
		tmp = root->left->minBound.z - pos.z;
		if (tmp > 0) expDis1 += tmp*tmp;
	}

	if (root->right != nullptr)
	{
		tmp = pos.x - root->right->maxBound.x;
		if (tmp > 0) expDis2 += tmp*tmp;
		tmp = pos.y - root->right->maxBound.y;
		if (tmp > 0) expDis2 += tmp*tmp;
		tmp = pos.z - root->right->maxBound.z;
		if (tmp > 0) expDis2 += tmp*tmp;
		tmp = root->right->minBound.x - pos.x;
		if (tmp > 0) expDis2 += tmp*tmp;
		tmp = root->right->minBound.y - pos.y;
		if (tmp > 0) expDis2 += tmp*tmp;
		tmp = root->right->minBound.z - pos.z;
		if (tmp > 0) expDis2 += tmp*tmp;
	}

	if ((root->left != nullptr) && (expDis1 < radius*radius)) getNeighbours(pos, ans, radius, root->left);
	if ((root->right != nullptr) && (expDis2 < radius*radius)) getNeighbours(pos, ans, radius, root->right);
}
