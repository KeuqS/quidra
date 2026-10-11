#include "llvm_backend/type_lowering.hpp"

#include <bit>
#include <cstdint>
#include <iomanip>
#include <sstream>

namespace quidra::llvm_backend {

std::string float_literal(double value, const Type& type) {
    if (type.kind == TypeKind::Real16) {
        std::ostringstream out;
        out << "0xH" << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
            << abi::half::round_to(value, abi::half::binary16);
        return out.str();
    }
    const double materialized =
        type.kind == TypeKind::Real32
            ? static_cast<double>(static_cast<float>(value))
            : value;
    const auto bits = std::bit_cast<std::uint64_t>(materialized);
    std::ostringstream out;
    out << "0x" << std::hex << std::uppercase
        << std::setw(16) << std::setfill('0') << bits;
    return out.str();
}

unsigned bfloat16_literal_bits(double value) {
    return abi::half::round_to(value, abi::half::bfloat16);
}

} // namespace quidra::llvm_backend
