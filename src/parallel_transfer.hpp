#pragma once
#include "quidra/abi/runtime_entry_points.hpp"
extern "C" void quidra_real_detach(long long,long long,quidra::abi::ExactRealValue*);
extern "C" void quidra_real_attach(long long,long long,quidra::abi::ExactRealValue*);
extern "C" void quidra_real_discard_detached(long long,long long);
