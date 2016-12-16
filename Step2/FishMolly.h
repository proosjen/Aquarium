/**
 * \file FishMolly.h
 *
 * \author Jenn Proos
 *
 * Class that implements a Molly fish
 */

#pragma once
#include <memory>

#include "Item.h"
#include "Fish.h"

/**
 * Class that implements a single molly fish
 */
class CFishMolly : public CFish
{
public:
	CFishMolly(CAquarium *aquarium);

	/// Default constructor (disabled)
	CFishMolly() = delete;

	/// Copy consutrctor (disabled)
	CFishMolly(const CFishMolly &) = delete;

	virtual ~CFishMolly();

	/**
	* Is this item a killer?
	* \returns Boolean. The default is false
	*/
	bool IsKiller() { return false; };

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
};

