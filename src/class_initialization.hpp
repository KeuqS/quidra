#pragma once
#include "quidra/ast.hpp"

namespace quidra {
// Give source-visible class names their receiver meaning before module renaming.
void elaborate_class_initialization(ClassDecl& declaration);
}
