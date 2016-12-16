/**
 * \file FishAngelfish.h
 *
 * \author Jenn Proos
 *
 * Class that implements an Angelfish
 */

#pragma once
#include <memory>

#include "Item.h"
#include "Fish.h"


/**
 * Class that implements a single angelfish
 */
class CFishAngelfish : public CFish
{
public:
	CFishAngelfish(CAquarium *aquarium);

	/// Default constructor (disabled)
	CFishAngelfish() = delete;

	/// Copy consutrctor (disabled)
	CFishAngelfish(const CFishAngelfish &) = delete;

	virtual ~CFishAngelfish();

	/**
	* Is this item a killer?
	* \returns Boolean. The default is false
	*/
	bool IsKiller() { return false; };

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

};

