/**
 * \file ChildView.cpp
 *
 * \author Jenn Proos
 */


// ChildView.cpp : implementation of the CChildView class
//
#include "stdafx.h"
#include "Step2.h"
#include "ChildView.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishMolly.h"
#include "FishAngelfish.h"
#include "FishCarp.h"
#include "DecorSkull.h"
#include "DoubleBufferDC.h"

using namespace Gdiplus;
using namespace std;

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/// Frame duration in milliseconds
const int FrameDuration = 30;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView


/**
 * Constructor
 */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ADDFISH_MOLLYFISH32773, &CChildView::OnAddfishMollyfish)
	ON_COMMAND(ID_ADDFISH_ANGELFISH, &CChildView::OnAddfishAngelfish)
	ON_COMMAND(ID_ADDFISH_KILLERCARP, &CChildView::OnAddfishKillercarp)
	ON_COMMAND(ID_ADDDECOR_ADDSKULL, &CChildView::OnAdddecorAddskull)
	ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
	ON_COMMAND(ID_FILE_OPEN32778, &CChildView::OnFileOpen32778)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CChildView message handlers


/** This function is called before the window is created.
 * \param cs A structure with the window creation parameters
 * \returns TRUE
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

/** This function is called to draw in the window.
 * 
 * This function is called in response to a drawing message 
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 */
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this); // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	
	Graphics graphics(dc.m_hDC);	// Create GDI+ graphics context

	mAquarium.OnDraw(&graphics);

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mAquarium.Update(elapsed);
}

/**
 * Add Fish/Beta menu option handler
 */
 void CChildView::OnAddfishBetafish()
 {
	 auto fish = make_shared<CFishBeta>(&mAquarium);
	 fish->SetLocation(InitialX, InitialY);
	 mAquarium.Add(fish);
	 Invalidate();
 }


/**
 * Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
 */
 void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
 {
	 mGrabbedItem = mAquarium.HitTest(point.x, point.y);

	 if (mGrabbedItem != nullptr)
	 {
		 mAquarium.Remove(mGrabbedItem);
		 mAquarium.Add(mGrabbedItem);
		 Invalidate();
	 }
 }


/**
 * Called when the left mouse button is released 
 * \param nFlags Flags associated with the mouse button release
 * \param point Where the button was pressed
 */
 void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
 {
	 OnMouseMove(nFlags, point);
 }


/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
 void CChildView::OnMouseMove(UINT nFlags, CPoint point)
 {
	// See if an item is currently being moved by the mouse
	 if (mGrabbedItem != nullptr)
	 {
		 // If an item is being moved, we only continue to
		 // move it while the left button is down
		 if (nFlags & MK_LBUTTON)
		 {
			 mGrabbedItem->SetLocation(point.x, point.y);
			 
			 // If prey is over killer
			 if (mAquarium.IsOver(mGrabbedItem))
			 {
				 mGrabbedItem = nullptr;
			 }
		 }
		 else
		 {
			 // When the left button is released, we release the
			 // item
			 mGrabbedItem = nullptr;
		 }

		 // Force the screen to redraw
		 Invalidate();
	 }
 }

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
 BOOL CChildView::OnEraseBkgnd(CDC* pDC)
 {
	 return false;
 }

 /**
 * Add Fish/Molly menu option handler
 */
 void CChildView::OnAddfishMollyfish()
 {
	 auto fish = make_shared<CFishMolly>(&mAquarium);
	 fish->SetLocation(InitialX, InitialY);
	 mAquarium.Add(fish);
	 Invalidate();
 }

 /**
 * Add Fish/Angelfish menu option handler
 */
 void CChildView::OnAddfishAngelfish()
 {
	 auto fish = make_shared<CFishAngelfish>(&mAquarium);
	 fish->SetLocation(InitialX, InitialY);
	 mAquarium.Add(fish);
	 Invalidate();
 }

 /**
 * Add Fish/Carp menu option handler
 */
 void CChildView::OnAddfishKillercarp()
 {
	 auto fish = make_shared<CFishCarp>(&mAquarium);
	 fish->SetLocation(InitialX, InitialY);
	 mAquarium.Add(fish);
	 Invalidate();
 }


/**
 * Add Decor/Skull menu option handler
 */
 void CChildView::OnAdddecorAddskull()
 {
	 auto item = make_shared<CDecorSkull>(&mAquarium);
	 item->SetLocation(InitialX, InitialY);
	 mAquarium.Add(item);
	 Invalidate();
 }


/**
 * Save the .aqua file appropriately
 */
 void CChildView::OnFileSaveas()
 {
	 CFileDialog dlg(false,  // false = Save dialog box
		 L".aqua",           // Default file extension
		 nullptr,            // Default file name (none)
		 OFN_OVERWRITEPROMPT,      // Flags (none)
		 L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||"); // Filter

	 if (dlg.DoModal() != IDOK)
		 return;

	 wstring filename = dlg.GetPathName();

	 mAquarium.Save(filename);
 }

 /**
 * This function is called when an File Open menu item is selected.
 *
 * It loads the aquarium from a file.
 */
 void CChildView::OnFileOpen32778()
 {
	 CFileDialog dlg(true,  // true = Open dialog box
		 L".aqua",           // Default file extension
		 nullptr,            // Default file name (none)
		 0,    // Flags
		 L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");  // Filter
	 if (dlg.DoModal() != IDOK)
		 return;

	 wstring filename = dlg.GetPathName();

	 mAquarium.Load(filename);
	 Invalidate();
 }

 /**
 * Handle timer events
 * \param nIDEvent The timer event ID
 */
 void CChildView::OnTimer(UINT_PTR nIDEvent)
 {
	 Invalidate();
	 CWnd::OnTimer(nIDEvent);
 }
