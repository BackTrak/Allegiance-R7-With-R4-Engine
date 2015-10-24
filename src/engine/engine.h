#ifndef _engine_H_
#define _engine_H_

//////////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////
//#define USEDX7 1

#define EnablePerformanceCounters

#ifdef _DEBUG
    //
    // Setting this to true will log every dx call made
    //

    extern bool g_bDumpDD;
#endif

#define DIRECTDRAW_VERSION 0x0700
#define DIRECT3D_VERSION   0x0700

#include "ddraw.h"
#include "d3d.h"

//////////////////////////////////////////////////////////////////////////////
//
// Requires ZLib
//
//////////////////////////////////////////////////////////////////////////////

#include "..\ZLib\zlib.h"

//////////////////////////////////////////////////////////////////////////////
//
// Basic 3D Types
//
//////////////////////////////////////////////////////////////////////////////

#include "..\ZLib\color.h"
#include "pixel.h"
#include "pixelformat.h"

//////////////////////////////////////////////////////////////////////////////
//
// Engine Headers
//
//////////////////////////////////////////////////////////////////////////////

class Context;
class Camera;
class Surface;
class Engine;
class Surface;
class Material;
class Palette;

#include "value.h"
#include "font.h"
#include "namespace.h"
#include "mdl.h"

// BT DX7 Shims for DX9 compatibility with the DX7 engine.
#include "DX9PackFile.h"
#include "CVRAMManager.h"
#include "CVBIBManager.h"
#include "CD3DDevice9.h"

#include "bounds.h"
#include "context.h"
#include "surface.h"
#include "material.h"
#include "palette.h"

//////////////////////////////////////////////////////////////////////////////
//
// Input
//
//////////////////////////////////////////////////////////////////////////////

#include "inputengine.h"

//////////////////////////////////////////////////////////////////////////////
//
// Engine
//
//////////////////////////////////////////////////////////////////////////////

class Engine : public IObject {
public:
    //
    // Initialization and cleanup
    //

    virtual void SetFocusWindow(Window* pwindow, bool bStartFullscreen)    = 0;
    virtual void Terminate()                                               = 0;
    virtual bool IsDeviceReady(bool& bChanges)                             = 0;

    //
    // Attributes
    //

    virtual void SetAllowSecondary(bool bAllowSecondary)                   = 0;
    virtual void SetAllow3DAcceleration(bool bAllow3DAcceleration)         = 0;
	virtual void SetMaxTextureSize(DWORD bMaxTextureSize)		   = 0;// yp Your_Persona August 2 2006 : MaxTextureSize Patch
    virtual void Set3DAccelerationImportant(bool b3DAccelerationImportant) = 0;
    virtual void SetFullscreen(bool bFullscreen)                           = 0;
    virtual void SetFullscreenSize(const WinPoint& point)                  = 0;
    virtual void ChangeFullscreenSize(bool bLarger)                        = 0;
    virtual void SetGammaLevel(float value)                                = 0;

    virtual bool            IsFullscreen()                                 = 0;
    virtual bool            PrimaryHas3DAcceleration()                     = 0;
    virtual bool            GetAllowSecondary()                            = 0;
    virtual bool            GetAllow3DAcceleration()                       = 0;
    virtual bool            Get3DAccelerationImportant()                   = 0;
    virtual bool            GetUsing3DAcceleration()                       = 0;
    virtual ZString         GetDeviceName()                                = 0;
    virtual const WinPoint& GetFullscreenSize()                            = 0;
    virtual float           GetGammaLevel()                                = 0;

    //KGJV 32B
    virtual PixelFormat* GetPrimaryPixelFormat()                           = 0;
    virtual ZString         GetPixelFormatName()                           = 0;
    //
    // For our exception handler
    //

    virtual void DebugSetWindowed() = 0;

    //
    // Screen access
    //

    virtual void BltToWindow(Window* pwindow, const WinPoint& point, Surface* psurface, const WinRect& rect) = 0;
    virtual void Flip()  = 0;

    //
    // Surface Constructors
    //

    virtual TRef<Surface> CreateSurface(HBITMAP hbitmap) = 0;

    virtual TRef<Surface> CreateSurface(
        const WinPoint& size, 
        SurfaceType     stype, 
        SurfaceSite*    psite = NULL
    ) = 0;

    virtual TRef<Surface> CreateSurface(
        const WinPoint& size,
        PixelFormat*    ppf,
        Palette*        ppalette = NULL,
        SurfaceType     stype    = SurfaceType2D(),
        SurfaceSite*    psite    = NULL
    ) = 0;

    virtual TRef<Surface> CreateSurface(
        const WinPoint& size,
        PixelFormat*    ppf,
        Palette*        ppalette,
        int             pitch,
        BYTE*           pdata,
        IObject*        pobjectMemory
    ) = 0;

    //
    // Performance counters
    //

    virtual int GetTotalTextureMemory()     = 0;
    virtual int GetAvailableTextureMemory() = 0;
    virtual int GetTotalVideoMemory()       = 0;
    virtual int GetAvailableVideoMemory()   = 0;

	// BT DX7 - Shims for DX9 methods.
	void SetEnableMipMapGeneration(bool bAllow3DAcceleration) {}

	//virtual void SetMaxTextureSize(int dwMaxTextureSize) = 0; //yp / imago 7/18/09
	void SetVSync(bool bEnable) {} 
	void SetAA(DWORD dwEnable) {} 
	void SetUsePack(bool bEnable) {} 
	void SetAutoGenMipMaps(bool bEnable) {} 

};

TRef<Engine> CreateEngine(bool bAllow3DAcceleration, bool bAllowSecondary, DWORD dwBPP);

//////////////////////////////////////////////////////////////////////////////
//
// Justification
//
//////////////////////////////////////////////////////////////////////////////

class JustificationBase {};
typedef TBitMask<JustificationBase, DWORD> Justification;

class JustifyLeft          : public Justification { public: JustifyLeft         () : Justification(0x01) {} };
class JustifyRight         : public Justification { public: JustifyRight        () : Justification(0x02) {} };
class JustifyTop           : public Justification { public: JustifyTop          () : Justification(0x04) {} };
class JustifyBottom        : public Justification { public: JustifyBottom       () : Justification(0x08) {} };
class JustifyXCenter       : public Justification { public: JustifyXCenter      () : Justification(0x10) {} };
class JustifyYCenter       : public Justification { public: JustifyYCenter      () : Justification(0x20) {} };
class JustifyLeftClipRight : public Justification { public: JustifyLeftClipRight() : Justification(0x40) {} };
class JustifyCenter        : public Justification { public: JustifyCenter       () : Justification(0x30) {} };

//////////////////////////////////////////////////////////////////////////////
//
// Modeling Headers
//
//////////////////////////////////////////////////////////////////////////////

#include "transform.h"
#include "keyframe.h"
#include "model.h"
#include "camera.h"
#include "viewport.h"
#include "geometry.h"
#include "bspgeo.h"
#include "image.h"

//////////////////////////////////////////////////////////////////////////////
//
// Panes
//
//////////////////////////////////////////////////////////////////////////////

#include "pane.h"
#include "toppane.h"
#include "paneimage.h"

//////////////////////////////////////////////////////////////////////////////
//
// Popups
//
//////////////////////////////////////////////////////////////////////////////

#include "popup.h"
#include "menu.h"

//////////////////////////////////////////////////////////////////////////////
//
// EngineWindow and EngineApp
//
//////////////////////////////////////////////////////////////////////////////

#include "caption.h"
#include "engineapp.h"
#include "enginewindow.h"

//////////////////////////////////////////////////////////////////////////////
//
// Sub classes
//
//////////////////////////////////////////////////////////////////////////////

#include "frameimage.h"
#include "button.h"
#include "controls.h"

#endif
