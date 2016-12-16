/**
 * \file FishBeta.cpp
 *
 * \author Jenn Proos
 */

#include "stdafx.h"
#include <string>
#include "FishBeta.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename
const wstring FishBetaImageName(L"images/beta.png");

/// Beta fish max speed in X direction
const double MaxSpeedX = 90;

/// Beta fish min speed in X direction
const double MinSpeedX = 40;

/// Beta fish max speed in Y direction
const double MaxSpeedY = 100;

/// Beta fish min speed in Y direction
const double MinSpeedY = 35;

/// Beta fish speed X being passed into constructor
const double SpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);

/// Beta fish speed Y being passed into constructor
const double SpeedY = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);


/**
 * Constructor
 * \param aquarium Aquarium this fish is a member of
 * \returns 
 */
CFishBeta::CFishBeta(CAquarium *aquarium) : CFish(aquarium, FishBetaImageName, SpeedX, SpeedY)
{
}

/**
 * Destructor
 */
CFishBeta::~CFishBeta()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Child node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"beta");

	return itemNode;
}


