#include "runtime_report.hpp"
#include "node_runtime_owner.hpp"
#include "quidra/abi/process_status.hpp"
#include "quidra/abi/runtime_entry_points.hpp"
#include "quidra/abi/runtime_failure.hpp"
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <new>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include "runtime_parallel.hpp"
#include "quidra/abi/exact_codes.hpp"
#include "quidra/native_extension.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstring>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <unordered_map>

// The ABI shared with generated code.
namespace abi = quidra::abi;

// Separate integer and real responsibilities share one compiler-private scope.
namespace {

#define QUIDRA_EXACT_SECTION 0
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 1
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 2
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 3
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 4
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 5
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 6
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 7
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 8
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 9
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 10
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 11
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 12
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 13
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 14
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 15
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 16
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 17
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 18
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 19
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 20
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 21
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 22
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 23
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 24
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 25
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 26
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 27
#include "runtime_exact_real.cpp"
#undef QUIDRA_EXACT_SECTION
#define QUIDRA_EXACT_SECTION 28
#include "runtime_integer.cpp"
#undef QUIDRA_EXACT_SECTION
