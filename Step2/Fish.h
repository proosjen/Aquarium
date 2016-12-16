/**
 * \file Fish.h
 *
 * \author Jenn Proos
 *
 * Base class for a fish
 */

#pragma once

#include "Item.h"

 /**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish : public CItem
{
public:
	/// Default constructor (disabled)
	CFish() = delete;

	/// Copy constructor (disabled)
	CFish(const CFish &) = delete;

	virtual ~CFish();

	void Update(double elapsed);

	std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

protected:
	CFish(CAquarium *aquarium, const std::wstring &filename, const double SpeedX, const double SpeedY);

private:
	/// Fish speed in the X direction
	double mSpeedX;

	/// Fish speed in the Y direction
	double mSpeedY;
};

