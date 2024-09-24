/* This file was generated by Maki Compiler, do not edit manually */

#include <precomp.h>

#include "c_group.h"
#include <api/script/objcontroller.h>

C_Group::C_Group(ScriptObject *object) : C_GuiObject(object) {
  inited = 0;
  obj = NULL;
  C_hook(object);
}

C_Group::C_Group() {
  inited = 0;
  obj = NULL;
}

void C_Group::C_hook(ScriptObject *object) {
  ASSERT(!inited);
  ScriptObjectController *controller = object->vcpu_getController();
  obj = controller->cast(object, groupGuid);
  if (obj != object && obj != NULL)
    controller = obj->vcpu_getController();
  else
    obj = NULL;

  int iter = WASABI_API_APP->app_getInitCount();
  if (!loaded || loaded != iter) {
    loaded = iter;
    getobject_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"getObject", this);
    getnumobjects_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"getNumObjects", this);
    enumobject_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"enumObject", this);
    oncreateobject_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"onCreateObject", this);
    getmouseposx_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"getMousePosX", this);
    getmouseposy_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"getMousePosY", this);
    islayout_id = WASABI_API_MAKI->maki_addDlfRef(controller, L"isLayout", this);
  }
  inited = 1;
}

C_Group::~C_Group() {
}

ScriptObject *C_Group::getScriptObject() {
  if (obj != NULL) return obj;
  return C_GROUP_PARENT::getScriptObject();
}

ScriptObject *C_Group::getObject(const wchar_t *object_id) 
{
  ASSERT(inited);
  scriptVar a = MAKE_SCRIPT_STRING(object_id);
  scriptVar *params[1] = {&a};
  return GET_SCRIPT_OBJECT(WASABI_API_MAKI->maki_callFunction(getScriptObject(), getobject_id, params));
}

int C_Group::getNumObjects() {
  ASSERT(inited);
  return GET_SCRIPT_INT(WASABI_API_MAKI->maki_callFunction(getScriptObject(), getnumobjects_id, NULL));
}

ScriptObject *C_Group::enumObject(int num) {
  ASSERT(inited);
  scriptVar a = MAKE_SCRIPT_INT(num);
  scriptVar *params[1] = {&a};
  return GET_SCRIPT_OBJECT(WASABI_API_MAKI->maki_callFunction(getScriptObject(), enumobject_id, params));
}

void C_Group::onCreateObject(ScriptObject *newobj) {
  ASSERT(inited);
  scriptVar a = MAKE_SCRIPT_OBJECT(newobj);
  scriptVar *params[1] = {&a};
  WASABI_API_MAKI->maki_callFunction(getScriptObject(), oncreateobject_id, params);
}

int C_Group::getMousePosX() {
  ASSERT(inited);
  return GET_SCRIPT_INT(WASABI_API_MAKI->maki_callFunction(getScriptObject(), getmouseposx_id, NULL));
}

int C_Group::getMousePosY() {
  ASSERT(inited);
  return GET_SCRIPT_INT(WASABI_API_MAKI->maki_callFunction(getScriptObject(), getmouseposy_id, NULL));
}

int C_Group::isLayout() {
  ASSERT(inited);
  return GET_SCRIPT_INT(WASABI_API_MAKI->maki_callFunction(getScriptObject(), islayout_id, NULL));
}

int C_Group::loaded=0;
int C_Group::getobject_id=0;
int C_Group::getnumobjects_id=0;
int C_Group::enumobject_id=0;
int C_Group::oncreateobject_id=0;
int C_Group::getmouseposx_id=0;
int C_Group::getmouseposy_id=0;
int C_Group::islayout_id=0;
