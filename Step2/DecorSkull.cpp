/**
 * \file DecorSkull.cpp
 *
 * \author Jenn Proos
 */

#include "stdafx.h"
#include <string>
#include "DecorSkull.h"

using namespace Gdiplus;
using namespace std;

/// Skull filename
const wstring DecorSkullImageName(L"images/scull.png");


/**
* Constructor
* \param aquarium Aquarium this decor is a member of
* \returns
*/
CDecorSkull::CDecorSkull(CAquarium *aquarium) : CItem(aquarium, DecorSkullImageName)
{
}

/**
 * Destructor
 */
CDecorSkull::~CDecorSkull()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Child node 
*/
std::shared_ptr<xmlnode::CXmlNode>
CDecorSkull::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);

	itemNode->SetAttribute(L"type", L"scull");

	return itemNode;
}