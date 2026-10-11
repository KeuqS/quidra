#pragma once
#include "quidra/checker.hpp"
#include <string>
#include <vector>

namespace quidra::golden {
// Source copies whose values can reach an explicit gradient destination or
// gradient-state operation. Field paths and control-flow joins are conservative.
std::vector<std::string> target_copy_sites(const CheckedProgram& checked);
}
