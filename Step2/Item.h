/**
 * \file Item.h
 *
 * \author Jenn Proos
 *
 * Base class for any item in our aquarium.
 */

#pragma once
#include "XmlNode.h"
#include <string>
#include <memory>

class CAquarium;

/**
 * Base class for any item in our aquarium.
 */
class CItem
{
public:
	/// Default constructor (disabled)
	CItem() = delete;

	/// Copy constructor (disabled)
	CItem(const CItem &) = delete;

	virtual ~CItem();

	/** The X location of the item
	* \returns X location in pixels */
	double GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	double GetY() const { return mY; }

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	void SetLocation(double x, double y) { mX = x; mY = y; }

	/// Draw this item
	/// \param graphics Graphics device to draw on
	void Draw(Gdiplus::Graphics *graphics);

	/** Test this item to see if it has been clicked on
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on */
	bool HitTest(int x, int y);

	/// Determines if fish is a killer fish
	virtual bool IsKiller() = 0;

	virtual std::shared_ptr<xmlnode::CXmlNode>
		CItem::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	virtual void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

	/// Get the aquarium this item is in
	/// \returns Aquarium pointer
	CAquarium *GetAquarium() { return mAquarium; }

	/// Set the mirror status
	/// \param m New mirror flag
	void SetMirror(bool m) { mMirror = m; }

	/// Get the width of item image
	/// \returns item image width
	int GetWidth() { return mItemImage->GetWidth(); }

	/// Get the height of the item image
	/// \returns item image height
	int GetHeight() { return mItemImage->GetHeight(); }

protected:
	CItem(CAquarium *aquarium, const std::wstring &filename);

private:
	/// The aquarium this item is contained in
	CAquarium *mAquarium;

	// Item location in the aquarium
	double mX = 0;		///< X location for the center of the item
	double mY = 0;		///< Y location for the center of the item

	/// The image of this fish
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

	bool mMirror = false;   ///< True mirrors the item image

};

