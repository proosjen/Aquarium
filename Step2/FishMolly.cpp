/**
 * \file FishMolly.cpp
 *
 * \author Jenn Proos
 */

#include "stdafx.h"
#include <string>
#include "FishMolly.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename
const wstring FishMollyImageName(L"images/molly.png");

/// Molly fish max speed in X direction
const double MaxSpeedX = 110;

/// Molly fish min speed in X direction
const double MinSpeedX = 30;

/// Molly fish max speed in Y direction
const double MaxSpeedY = 50;

/// Molly fish min speed in Y direction
const double MinSpeedY = 25;

/// Molly fish speed X being passed in to constructor
const double SpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);

/// Molly fish speed Y being passed in to constructor
const double SpeedY = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);

/**
 * Constructor
 * \param aquarium Aquarium this fish is a member of 
 * \returns 
 */
CFishMolly::CFishMolly(CAquarium *aquarium) : CFish(aquarium, FishMollyImageName, SpeedX, SpeedY)
{
}

/**
 * Destructor
 */
CFishMolly::~CFishMolly()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Child node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFishMolly::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"molly");

	return itemNode;
}