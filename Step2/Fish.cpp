/**
 * \file Fish.cpp
 *
 * \author Jenn Proos
 */

#include "stdafx.h"
#include "Fish.h"
#include "Aquarium.h"


 /**
 * Constructor
 * \param aquarium The aquarium we are in
 * \param filename Filename for the image we use
 * \param SpeedX The X speed of our fish
 * \param SpeedY The Y speed of our fish
 */
CFish::CFish(CAquarium *aquarium, const std::wstring &filename, const double SpeedX, const double SpeedY) : CItem(aquarium, filename)
{
	mSpeedX = ((double)rand() / RAND_MAX) * SpeedX;
	mSpeedY = ((double)rand() / RAND_MAX) * SpeedY;

}


CFish::~CFish()
{
}

/**
* Handle updates in time of our fish
*
* This is called before we draw and allows us to
* move our fish. We add our speed times the amount
* of time that has elapsed.
* \param elapsed Time elapsed since the class call
*/
void CFish::Update(double elapsed)
{
	SetLocation(GetX() + mSpeedX * elapsed,
		GetY() + mSpeedY * elapsed);

	// same direction in load
	if (mSpeedX > 0)
	{
		SetMirror(false);
	}

	if (mSpeedX > 0 && GetX() >= ((GetAquarium()->GetWidth() - 10) - (GetWidth() / 2)))
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}

	if (mSpeedX < 0 && GetX() <= (GetWidth() / 2) + 10)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}

	if (mSpeedY > 0 && GetY() >= ((GetAquarium()->GetHeight() - 10) - (GetHeight() / 2)))
	{
		mSpeedY = -mSpeedY;
	}

	if (mSpeedY < 0 && GetY() <= (GetHeight() / 2) + 10)
	{
		mSpeedY = -mSpeedY;
	}
}

/**
* Save this fish to an XML node
* \param node The node we are going to be a child of
* \returns Child node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);

	itemNode->SetAttribute(L"speedX", mSpeedX);
	itemNode->SetAttribute(L"speedY", mSpeedY);

	return itemNode;
}

/**
* Load the attributes for a fish node.
*
* This is the  base class version that loads the attributes
* common to all fish. Override this to load custom attributes
* for specific fish.
*
* \param node The Xml node we are loading the fish from
*/
void CFish::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CItem::XmlLoad(node);

	mSpeedX = node->GetAttributeDoubleValue(L"speedX", 0);
	mSpeedY = node->GetAttributeDoubleValue(L"speedY", 0);
}