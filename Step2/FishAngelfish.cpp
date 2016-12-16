/**
 * \file FishAngelfish.cpp
 *
 * \author Jenn Proos
 */

#include "stdafx.h"
#include <string>
#include "FishAngelfish.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename
const wstring FishAngelfishImageName(L"images/angelfish.png");

/// Angelfish max speed in X direction
const double MaxSpeedX = 70;

/// Angelfish min speed in X direction
const double MinSpeedX = 35;

/// Angelfish max speed in Y direction
const double MaxSpeedY = 65;

/// Angelfish min speed in Y direction
const double MinSpeedY = 30;

/// Angelfish speed X being passed in to contructor
const double SpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);

/// Angelfish speed Y being passed in to constructor
const double SpeedY = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);

/**
 * Constructor
 * \param aquarium Aquarium this fish is a member of
 * \returns 
 */
CFishAngelfish::CFishAngelfish(CAquarium *aquarium) : CFish(aquarium, FishAngelfishImageName, SpeedX, SpeedY)
{
}

/**
 * Destructor
 */
CFishAngelfish::~CFishAngelfish()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Child node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFishAngelfish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"angelfish");

	return itemNode;
}
