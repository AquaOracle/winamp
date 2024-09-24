/* This file was generated by Maki Compiler, do not edit manually */

#ifndef __C_DROPDOWNLIST_H
#define __C_DROPDOWNLIST_H

#include "c_guiobject.h"

#define C_DROPDOWNLIST_PARENT C_GuiObject

class C_DropDownList : public C_DROPDOWNLIST_PARENT {
  public:

  C_DropDownList(ScriptObject *object);
  C_DropDownList();
  virtual ~C_DropDownList();

  virtual void C_hook(ScriptObject *o);

  ScriptObject *getScriptObject();

  virtual const wchar_t *getItemSelected();
  virtual void onSelect(int id, int hover);
  virtual void setListHeight(int h);
  virtual void openList();
  virtual void closeList();
  virtual void setItems(const wchar_t *lotsofitems);
  virtual int addItem(const wchar_t *_text);
  virtual void delItem(int id);
  virtual int findItem(const wchar_t *_text);
  virtual int getNumItems();
  virtual void selectItem(int id, int hover);
  virtual const wchar_t *getItemText(int id);
  virtual int getSelected();
  virtual const wchar_t *getSelectedText();
  virtual const wchar_t *getCustomText();
  virtual void deleteAllItems();
  virtual void setNoItemText(const wchar_t *txt);

  private:

  ScriptObject *obj;
  int inited;
  static int loaded;
  static int getitemselected_id;
  static int onselect_id;
  static int setlistheight_id;
  static int openlist_id;
  static int closelist_id;
  static int setitems_id;
  static int additem_id;
  static int delitem_id;
  static int finditem_id;
  static int getnumitems_id;
  static int selectitem_id;
  static int getitemtext_id;
  static int getselected_id;
  static int getselectedtext_id;
  static int getcustomtext_id;
  static int deleteallitems_id;
  static int setnoitemtext_id;
};

#endif
