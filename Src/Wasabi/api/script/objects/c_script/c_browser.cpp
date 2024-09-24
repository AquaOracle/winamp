/* This file was generated by Maki Compiler, do not edit manually */

#include <precomp.h>

#include "c_browser.h"
#include <api/script/objcontroller.h>

C_Browser::C_Browser(ScriptObject *object) : C_GuiObject(object) {
  inited = 0;
  C_hook(object);
}

C_Browser::C_Browser() {
  inited = 0;
  obj = NULL;
}

void C_Browser::C_hook(ScriptObject *object) {
  ASSERT(!inited);
  ScriptObjectController *controller = object->vcpu_getController();
  obj = controller->cast(object, browserGuid);
  if (obj != object && obj != NULL)
    controller = obj->vcpu_getController();
  else
    obj = NULL;

  int iter = WASABI_API_APP->app_getInitCount();
  if (!loaded || loaded != iter) {
    loaded = iter;
    navigateurl_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"navigateUrl", this);
    back_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"back", this);
    forward_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"forward", this);
    stop_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"stop", this);
    refresh_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"refresh", this);
    home_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"home", this);
    settargetname_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"setTargetName", this);
    onbeforenavigate_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"onBeforeNavigate", this);
    ondocumentcomplete_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"onDocumentComplete", this);
		onmedialink_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"onMediaLink", this);
  }
  inited = 1;
}

C_Browser::~C_Browser() {
}

ScriptObject *C_Browser::getScriptObject() {
  if (obj != NULL) return obj;
  return C_BROWSER_PARENT::getScriptObject();
}

void C_Browser::navigateUrl(const wchar_t *url) 
{
  ASSERT(inited);
  scriptVar a = MAKE_SCRIPT_STRING(url);
  scriptVar *params[1] = {&a};
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), navigateurl_id, params);
}

void C_Browser::back() {
  ASSERT(inited);
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), back_id, NULL);
}

void C_Browser::forward() {
  ASSERT(inited);
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), forward_id, NULL);
}

void C_Browser::stop() {
  ASSERT(inited);
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), stop_id, NULL);
}

void C_Browser::refresh() {
  ASSERT(inited);
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), refresh_id, NULL);
}

void C_Browser::home() {
  ASSERT(inited);
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), home_id, NULL);
}

void C_Browser::setTargetName(const wchar_t *targetname) {
  ASSERT(inited);
  scriptVar a = MAKE_SCRIPT_STRING(targetname);
  scriptVar *params[1] = {&a};
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), settargetname_id, params);
}

int C_Browser::onBeforeNavigate(const wchar_t *url, int flags, const wchar_t *targetframename) {
  ASSERT(inited);
  scriptVar a = MAKE_SCRIPT_STRING(url);
  scriptVar b = MAKE_SCRIPT_INT(flags);
  scriptVar c = MAKE_SCRIPT_STRING(targetframename);
  scriptVar *params[3] = {&a, &b, &c};
  return GET_SCRIPT_INT(WASABI_API_MAKI->maki_callFunction(getScriptObject(), onbeforenavigate_id, params));
}

void C_Browser::onDocumentComplete(const wchar_t *url) {
  ASSERT(inited);
  scriptVar a = MAKE_SCRIPT_STRING(url);
  scriptVar *params[1] = {&a};
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), ondocumentcomplete_id, params);
}

void C_Browser::onMediaLink(const wchar_t *url)
{
	ASSERT(inited);
  scriptVar a = MAKE_SCRIPT_STRING(url);
  scriptVar *params[1] = {&a};
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), onmedialink_id, params);
}

int C_Browser::loaded=0;
int C_Browser::navigateurl_id=0;
int C_Browser::back_id=0;
int C_Browser::forward_id=0;
int C_Browser::stop_id=0;
int C_Browser::refresh_id=0;
int C_Browser::home_id=0;
int C_Browser::settargetname_id=0;
int C_Browser::onbeforenavigate_id=0;
int C_Browser::ondocumentcomplete_id=0;
int C_Browser::onmedialink_id=0;

