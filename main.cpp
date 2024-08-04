#include "elem.h"
#include "view.h"
#include "model.h"
#include "editor.h"


int main() {
  Editor ed;

  // Данные функции имитируют обработку событий в GUI
  // добавлены здесь, что удовлетворить пункту задания:
  // Функции, являющиеся обработчиками GUI, собрать в 
  // одном файле с функцией main.
  ed.addElement(POINT);
  ed.removeElement(0);
  ed.onSaveDocument("test");
  ed.onLoadDocument("test");
  return 0;

};
