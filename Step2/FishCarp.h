/**
 * \file FishCarp.h
 *
 * \author Jenn Proos
 *
 * Class that implements a Killer Carp fish
 */

#pragma once
#include <memory>

#include "Item.h"
#include "Fish.h"


/**
 * Class that implements a single killer carp fish
 */
class CFishCarp : public CFish
{
public:
	CFishCarp(CAquarium *aquarium);

	/// Default constructor (disabled)
	CFishCarp() = delete;

	/// Copy consutrctor (disabled)
	CFishCarp(const CFishCarp &) = delete;

	virtual ~CFishCarp();

	/**
	* Is this item a killer?
	* \returns true - it will kill!
	*/
	bool IsKiller() { return true; };

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
};

