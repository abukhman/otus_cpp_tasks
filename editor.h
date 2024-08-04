#ifndef _EDITOR_H_
#define _EIDTOR_H_
#include <memory>
#include <string>

class Editor {
  Model _m;
  View _v;

 public:
  void onLoadDocument(const std::string& fileName) {
    _m.load(fileName);
    const auto& figures = _m.getFig();
    for (int i = 0; i < figures.size(); i++) {
      figures[i]->show();
    }
  }

  void onSaveDocument(const std::string& fileName) {
    _m.save(fileName);
  }

  int addElement(elem_id type) {
    std::cout<<"Create element with id "<<type<<std::endl;
    int id = 0; // возвращаем id созданного элемента
    return 0;
  }

  void removeElement(int id) {
    // Поиск в векторе элемента с id
    // и удаление его
    std::cout<<"Remove id "<<id<<std::endl;
  }
};

#endif
