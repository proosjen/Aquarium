/**
 * \file DecorSkull.h
 *
 * \author Jenn Proos
 *
 * Class that implements a Skull decor
 */

#pragma once
#include <memory>

#include "Item.h"

/**
 * Class that implements a single Skull decor
 */
class CDecorSkull : public CItem
{
public:
	CDecorSkull(CAquarium *aquarium);

	/// Default constructor (disabled)
	CDecorSkull() = delete;

	/// Copy constructor (disabled)
	CDecorSkull(const CDecorSkull &) = delete;

	virtual ~CDecorSkull();

	/**
	* Is this item a killer?
	* \returns Boolean. The default is false
	*/
	bool IsKiller() { return false; };

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
};

