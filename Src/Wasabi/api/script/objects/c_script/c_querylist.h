/* This file was generated by Maki Compiler, do not edit manually */

#ifndef __C_QUERYLIST_H
#define __C_QUERYLIST_H

#include "c_guiobject.h"

#define C_QUERYLIST_PARENT C_GuiObject

class C_QueryList : public C_QUERYLIST_PARENT {
  public:

  C_QueryList(ScriptObject *object);
  C_QueryList();
  virtual ~C_QueryList();

  virtual void C_hook(ScriptObject *o);

  ScriptObject *getScriptObject();

  virtual void onResetQuery();

  private:

  ScriptObject *obj;
  int inited;
  static int loaded;
  static int onresetquery_id;
};

#endif
