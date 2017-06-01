#pragma once

#include <QtCore/qglobal.h>

#include "applicationmodel.hpp"

namespace soda {
namespace ui {

class GuiApplicationModel : public ApplicationModel {
  Q_OBJECT
public:
  explicit GuiApplicationModel(QCoreApplication *application);

  GuiApplicationModel(const GuiApplicationModel &other) = delete;
  const GuiApplicationModel &
  operator=(const GuiApplicationModel &other) = delete;
};

} // namespace ui
} // namespace soda
