/*
   Copyright (C) 2011 Samsung Electronics
   Copyright (C) 2012 Intel Corporation. All rights reserved.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef EwkViewImpl_h
#define EwkViewImpl_h

#include "EwkViewCallbacks.h"
#include "RefPtrEfl.h"
#include "WKEinaSharedString.h"
#include "WKGeometry.h"
#include "WKRetainPtr.h"
#include <Evas.h>
#include <WebCore/IntRect.h>
#include <WebCore/TextDirection.h>
#include <WebCore/Timer.h>
#include <WebKit2/WKBase.h>
#include <wtf/HashMap.h>
#include <wtf/OwnPtr.h>
#include <wtf/RefPtr.h>
#include <wtf/text/WTFString.h>

#if ENABLE(TOUCH_EVENTS)
#include "ewk_touch.h"
#endif

#if USE(ACCELERATED_COMPOSITING)
#include "EvasGLContext.h"
#include "EvasGLSurface.h"
#endif

namespace WebKit {
class FindClientEfl;
class FormClientEfl;
class InputMethodContextEfl;
class PageClientBase;
class PageLoadClientEfl;
class PagePolicyClientEfl;
class PageUIClientEfl;
class ResourceLoadClientEfl;
class WebPageGroup;
class WebPageProxy;
class WebPopupItem;
class WebPopupMenuProxyEfl;

#if ENABLE(VIBRATION)
class VibrationClientEfl;
#endif
}

namespace WebCore {
class AffineTransform;
class Color;
class Cursor;
class IntSize;
}

class EwkContext;
class Ewk_Back_Forward_List;
class Ewk_Color_Picker;
class Ewk_Popup_Menu;
class Ewk_Settings;

#if USE(ACCELERATED_COMPOSITING)
typedef struct _Evas_GL_Context Evas_GL_Context;
typedef struct _Evas_GL_Surface Evas_GL_Surface;
#endif

typedef struct Ewk_View_Smart_Data Ewk_View_Smart_Data;

class EwkViewImpl {
public:

    enum ViewBehavior {
        LegacyBehavior,
        DefaultBehavior
    };
    EwkViewImpl(Evas_Object* view, PassRefPtr<EwkContext> context, PassRefPtr<WebKit::WebPageGroup> pageGroup, ViewBehavior);
    ~EwkViewImpl();

    static EwkViewImpl* fromEvasObject(const Evas_Object* view);

    Evas_Object* view() { return m_view; }
    WKPageRef wkPage();
    WebKit::WebPageProxy* page() { return m_pageProxy.get(); }
    EwkContext* ewkContext() { return m_context.get(); }
    Ewk_Settings* settings() { return m_settings.get(); }
    Ewk_Back_Forward_List* backForwardList() { return m_backForwardList.get(); }

    WebCore::IntSize size() const;
    bool isFocused() const;
    bool isVisible() const;

    WebCore::AffineTransform transformToScene() const;
    WebCore::AffineTransform transformFromScene() const;
    WebCore::AffineTransform transformToScreen() const;

    const char* url() const { return m_url; }
    const char* faviconURL() const { return m_faviconURL; }
    const char* title() const;
    WebKit::InputMethodContextEfl* inputMethodContext();

    const char* themePath() const;
    void setThemePath(const char* theme);
    const char* customTextEncodingName() const;
    void setCustomTextEncodingName(const String& encoding);

    bool mouseEventsEnabled() const { return m_mouseEventsEnabled; }
    void setMouseEventsEnabled(bool enabled);
#if ENABLE(TOUCH_EVENTS)
    bool touchEventsEnabled() const { return m_touchEventsEnabled; }
    void setTouchEventsEnabled(bool enabled);
#endif

    void setCursor(const WebCore::Cursor& cursor);
    void setImageData(void* imageData, const WebCore::IntSize& size);

    void update(const WebCore::IntRect& rect = WebCore::IntRect());

    static void addToPageViewMap(EwkViewImpl* viewImpl);
    static void removeFromPageViewMap(EwkViewImpl* viewImpl);
    static const Evas_Object* viewFromPageViewMap(const WKPageRef);

#if ENABLE(FULLSCREEN_API)
    void enterFullScreen();
    void exitFullScreen();
#endif

    WKRect windowGeometry() const;
    void setWindowGeometry(const WKRect&);

#if USE(ACCELERATED_COMPOSITING)
    bool createGLSurface(const WebCore::IntSize& viewSize);
    bool enterAcceleratedCompositingMode();
    bool exitAcceleratedCompositingMode();
#endif

#if ENABLE(INPUT_TYPE_COLOR)
    void requestColorPicker(WKColorPickerResultListenerRef listener, const WebCore::Color&);
    void dismissColorPicker();
#endif

    WKPageRef createNewPage(WKDictionaryRef windowFeatures);
    void closePage();

    void requestPopupMenu(WebKit::WebPopupMenuProxyEfl*, const WebCore::IntRect&, WebCore::TextDirection, double pageScaleFactor, const Vector<WebKit::WebPopupItem>& items, int32_t selectedIndex);
    void closePopupMenu();

    void updateTextInputState();

    void requestJSAlertPopup(const WKEinaSharedString& message);
    bool requestJSConfirmPopup(const WKEinaSharedString& message);
    WKEinaSharedString requestJSPromptPopup(const WKEinaSharedString& message, const WKEinaSharedString& defaultValue);

    template<EwkViewCallbacks::CallbackType callbackType>
    EwkViewCallbacks::CallBack<callbackType> smartCallback() const
    {
        return EwkViewCallbacks::CallBack<callbackType>(m_view);
    }

#if USE(TILED_BACKING_STORE)
    void informLoadCommitted();
#endif
    void informContentsSizeChange(const WebCore::IntSize& size);
    unsigned long long informDatabaseQuotaReached(const String& databaseName, const String& displayName, unsigned long long currentQuota, unsigned long long currentOriginUsage, unsigned long long currentDatabaseUsage, unsigned long long expectedUsage);

#if USE(TILED_BACKING_STORE)
    WebKit::PageClientBase* pageClient() { return m_pageClient.get(); }

    void setScaleFactor(float scaleFactor) { m_scaleFactor = scaleFactor; }
    float scaleFactor() const { return m_scaleFactor; }

    void setScrollPosition(WebCore::IntPoint position) { m_scrollPosition = position; }
    const WebCore::IntPoint scrollPosition() const { return m_scrollPosition; }
#endif
#if USE(ACCELERATED_COMPOSITING)
    Evas_GL* evasGL() { return m_evasGL.get(); }
    Evas_GL_Context* evasGLContext() { return m_evasGLContext ? m_evasGLContext->context() : 0; }
    Evas_GL_Surface* evasGLSurface() { return m_evasGLSurface ? m_evasGLSurface->surface() : 0; }
    void clearEvasGLSurface() { m_evasGLSurface.clear(); }
#endif

    // FIXME: needs refactoring (split callback invoke)
    void informURLChange();

    bool isHardwareAccelerated() const { return m_isHardwareAccelerated; }

private:
    inline Ewk_View_Smart_Data* smartData() const;
    void displayTimerFired(WebCore::Timer<EwkViewImpl>*);

    void informIconChange();

    static void onMouseDown(void* data, Evas*, Evas_Object*, void* eventInfo);
    static void onMouseUp(void* data, Evas*, Evas_Object*, void* eventInfo);
    static void onMouseMove(void* data, Evas*, Evas_Object*, void* eventInfo);
#if ENABLE(TOUCH_EVENTS)
    void feedTouchEvents(Ewk_Touch_Event_Type type);
    static void onTouchDown(void* /* data */, Evas* /* canvas */, Evas_Object* ewkView, void* /* eventInfo */);
    static void onTouchUp(void* /* data */, Evas* /* canvas */, Evas_Object* ewkView, void* /* eventInfo */);
    static void onTouchMove(void* /* data */, Evas* /* canvas */, Evas_Object* ewkView, void* /* eventInfo */);
#endif
    static void onFaviconChanged(const char* pageURL, void* eventInfo);

    // Note, initialization order matters.
    Evas_Object* m_view;
    RefPtr<EwkContext> m_context;
#if USE(ACCELERATED_COMPOSITING)
    OwnPtr<Evas_GL> m_evasGL;
    OwnPtr<WebKit::EvasGLContext> m_evasGLContext;
    OwnPtr<WebKit::EvasGLSurface> m_evasGLSurface;
#endif
    OwnPtr<WebKit::PageClientBase> m_pageClient;
    RefPtr<WebKit::WebPageProxy> m_pageProxy;
    OwnPtr<WebKit::PageLoadClientEfl> m_pageLoadClient;
    OwnPtr<WebKit::PagePolicyClientEfl> m_pagePolicyClient;
    OwnPtr<WebKit::PageUIClientEfl> m_pageUIClient;
    OwnPtr<WebKit::ResourceLoadClientEfl> m_resourceLoadClient;
    OwnPtr<WebKit::FindClientEfl> m_findClient;
    OwnPtr<WebKit::FormClientEfl> m_formClient;
#if ENABLE(VIBRATION)
    OwnPtr<WebKit::VibrationClientEfl> m_vibrationClient;
#endif
    OwnPtr<Ewk_Back_Forward_List> m_backForwardList;
#if USE(TILED_BACKING_STORE)
    float m_scaleFactor;
    WebCore::IntPoint m_scrollPosition;
#endif
    OwnPtr<Ewk_Settings> m_settings;
    const void* m_cursorIdentifier; // This is an address, do not free it.
    WKEinaSharedString m_faviconURL;
    WKEinaSharedString m_url;
    mutable WKEinaSharedString m_title;
    WKEinaSharedString m_theme;
    mutable WKEinaSharedString m_customEncoding;
    bool m_mouseEventsEnabled;
#if ENABLE(TOUCH_EVENTS)
    bool m_touchEventsEnabled;
#endif
    WebCore::Timer<EwkViewImpl> m_displayTimer;
    OwnPtr<Ewk_Popup_Menu> m_popupMenu;
    OwnPtr<WebKit::InputMethodContextEfl> m_inputMethodContext;
    OwnPtr<Ewk_Color_Picker> m_colorPicker;
    bool m_isHardwareAccelerated;
};

#endif // EwkViewImpl_h
