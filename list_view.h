#pragma once

#include "resource.h"

extern "C" void __cdecl LISTVIEW_Register(void);
extern "C" void COMCTL32_RefreshSysColors(void);

typedef struct
{
	COLORREF clrBtnHighlight;       /* COLOR_BTNHIGHLIGHT                  */
	COLORREF clrBtnShadow;          /* COLOR_BTNSHADOW                     */
	COLORREF clrBtnText;            /* COLOR_BTNTEXT                       */
	COLORREF clrBtnFace;            /* COLOR_BTNFACE                       */
	COLORREF clrHighlight;          /* COLOR_HIGHLIGHT                     */
	COLORREF clrHighlightText;      /* COLOR_HIGHLIGHTTEXT                 */
	COLORREF clrHotTrackingColor;   /* COLOR_HOTLIGHT                      */
	COLORREF clr3dHilight;          /* COLOR_3DHILIGHT                     */
	COLORREF clr3dShadow;           /* COLOR_3DSHADOW                      */
	COLORREF clr3dDkShadow;         /* COLOR_3DDKSHADOW                    */
	COLORREF clr3dFace;             /* COLOR_3DFACE                        */
	COLORREF clrWindow;             /* COLOR_WINDOW                        */
	COLORREF clrWindowText;         /* COLOR_WINDOWTEXT                    */
	COLORREF clrGrayText;           /* COLOR_GREYTEXT                      */
	COLORREF clrActiveCaption;      /* COLOR_ACTIVECAPTION                 */
	COLORREF clrInfoBk;             /* COLOR_INFOBK                        */
	COLORREF clrInfoText;           /* COLOR_INFOTEXT                      */
} COMCTL32_SysColor;
