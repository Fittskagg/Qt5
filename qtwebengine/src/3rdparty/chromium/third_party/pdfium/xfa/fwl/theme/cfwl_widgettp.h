// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef XFA_FWL_THEME_CFWL_WIDGETTP_H_
#define XFA_FWL_THEME_CFWL_WIDGETTP_H_

#include <memory>
#include <vector>

#include "core/fxcrt/fx_coordinates.h"
#include "core/fxcrt/fx_system.h"
#include "core/fxcrt/retain_ptr.h"
#include "xfa/fwl/theme/cfwl_utils.h"
#include "xfa/fxgraphics/cxfa_graphics.h"

class CFDE_TextOut;
class CFGAS_FontMgr;
class CFGAS_GEFont;
class CFWL_ThemeBackground;
class CFWL_ThemePart;
class CFWL_ThemeText;
class CFWL_Widget;

#if _FX_PLATFORM_ != _FX_PLATFORM_WINDOWS_
class CFX_FontSourceEnum_File;
#endif

class CFWL_WidgetTP {
 public:
  virtual ~CFWL_WidgetTP();

  virtual void Initialize();
  virtual void Finalize();

  virtual void DrawBackground(CFWL_ThemeBackground* pParams);
  virtual void DrawText(CFWL_ThemeText* pParams);

  const RetainPtr<CFGAS_GEFont>& GetFont() const;

 protected:
  struct CColorData {
    FX_ARGB clrBorder[4];
    FX_ARGB clrStart[4];
    FX_ARGB clrEnd[4];
    FX_ARGB clrSign[4];
  };

  CFWL_WidgetTP();

  void InitializeArrowColorData();
  void InitTTO();
  void FinalizeTTO();

  void DrawBorder(CXFA_Graphics* pGraphics,
                  const CFX_RectF* pRect,
                  CFX_Matrix* pMatrix = nullptr);
  void FillBackground(CXFA_Graphics* pGraphics,
                      const CFX_RectF* pRect,
                      CFX_Matrix* pMatrix = nullptr);
  void FillSolidRect(CXFA_Graphics* pGraphics,
                     FX_ARGB fillColor,
                     const CFX_RectF* pRect,
                     CFX_Matrix* pMatrix = nullptr);
  void DrawFocus(CXFA_Graphics* pGraphics,
                 const CFX_RectF* pRect,
                 CFX_Matrix* pMatrix = nullptr);
  void DrawArrow(CXFA_Graphics* pGraphics,
                 const CFX_RectF* pRect,
                 FWLTHEME_DIRECTION eDict,
                 FX_ARGB argSign,
                 CFX_Matrix* pMatrix = nullptr);
  void DrawBtn(CXFA_Graphics* pGraphics,
               const CFX_RectF* pRect,
               FWLTHEME_STATE eState,
               CFX_Matrix* pMatrix = nullptr);
  void DrawArrowBtn(CXFA_Graphics* pGraphics,
                    const CFX_RectF* pRect,
                    FWLTHEME_DIRECTION eDict,
                    FWLTHEME_STATE eState,
                    CFX_Matrix* pMatrix = nullptr);

  uint32_t m_dwRefCount;
  std::unique_ptr<CFDE_TextOut> m_pTextOut;
  RetainPtr<CFGAS_GEFont> m_pFDEFont;
  std::unique_ptr<CColorData> m_pColorData;
};

void FWLTHEME_Release();

class CFWL_FontData {
 public:
  CFWL_FontData();
  virtual ~CFWL_FontData();

  bool Equal(const WideStringView& wsFontFamily,
             uint32_t dwFontStyles,
             uint16_t wCodePage);
  bool LoadFont(const WideStringView& wsFontFamily,
                uint32_t dwFontStyles,
                uint16_t wCodePage);
  RetainPtr<CFGAS_GEFont> GetFont() const;

 protected:
  WideString m_wsFamily;
  uint32_t m_dwStyles;
  uint32_t m_dwCodePage;
  std::unique_ptr<CFGAS_FontMgr> m_pFontMgr;
  RetainPtr<CFGAS_GEFont> m_pFont;
};

class CFWL_FontManager {
 public:
  static CFWL_FontManager* GetInstance();
  static void DestroyInstance();

  RetainPtr<CFGAS_GEFont> FindFont(const WideStringView& wsFontFamily,
                                   uint32_t dwFontStyles,
                                   uint16_t dwCodePage);

 protected:
  CFWL_FontManager();
  virtual ~CFWL_FontManager();

  static CFWL_FontManager* s_FontManager;
  std::vector<std::unique_ptr<CFWL_FontData>> m_FontsArray;
};

#endif  // XFA_FWL_THEME_CFWL_WIDGETTP_H_
