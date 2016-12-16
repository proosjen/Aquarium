/**
 * \file FishCarp.cpp
 *
 * \author Jenn Proos
 */

#include "stdafx.h"
#include <string>
#include "FishCarp.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename
const wstring FishCarpImageName(L"images/carp.png");

/// Carp fish max speed in X direction
const double MaxSpeedX = 70;

/// Carp fish min speed in X direction
const double MinSpeedX = 20;

/// Carp fish max speed in Y direction
const double MaxSpeedY = 50;

/// Carp fish min speed in Y direction
const double MinSpeedY = 10;

/// Carp fish speed X being passed in to constructor
const double SpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);

/// Carp fish speed Y being passed in to constructor
const double SpeedY = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);

/**
 * Constructor
 * \param aquarium Aquarium this fish is a member of
 * \returns 
 */
CFishCarp::CFishCarp(CAquarium *aquarium) : CFish(aquarium, FishCarpImageName, SpeedX, SpeedY)
{
}

/**
 * Destructor
 */
CFishCarp::~CFishCarp()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Child node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFishCarp::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"carp");

	return itemNode;
}
