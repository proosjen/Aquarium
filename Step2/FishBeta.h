/**
 * \file FishBeta.h
 *
 * \author Jenn Proos
 *
 * Class that implements a Beta fish
 */

#pragma once
#include <memory>

#include "Item.h"
#include "Fish.h"

/**
 * Class that implements a single beta fish
 */
class CFishBeta : public CFish
{
public:
	CFishBeta(CAquarium *aquarium);

	/// Default constructor (disabled)
	CFishBeta() = delete;

	/// Copy constructor (disabled)
	CFishBeta(const CFishBeta &) = delete;

	virtual ~CFishBeta();

	/**
	* Is this item a killer?
	* \returns Boolean. The default is false
	*/
	bool IsKiller() { return false; };

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
};

