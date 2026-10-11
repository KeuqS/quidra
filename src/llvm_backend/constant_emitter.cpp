#include "llvm_backend/constant_emitter.hpp"

#include "constant_numeric_eval.hpp"
#include "llvm_backend/copy_idioms.hpp"
#include "llvm_backend/bare_integer.hpp"
#include "llvm_backend/runtime_abi.hpp"
#include "llvm_backend/small_rational.hpp"
#include "llvm_backend/type_lowering.hpp"

#include <string>

namespace quidra::llvm_backend {

using namespace llvm_text;
using namespace llvm_text::types;

void ConstantEmitter::reserve(const ir::ConstantString& n,const ir::Instruction&){
    pool_.intern(n.value);
}

void ConstantEmitter::reserve(const ir::ConstantExact& n,const ir::Instruction&){
    SmallRational small{};
    if(n.type.kind==TypeKind::Real&&small_rational_literal(n.spelling,small))return;
    long long word=0;
    if(is_bare_integer(n.type)&&bare_integer_inline_literal(n.spelling,word))return;
    pool_.intern(n.spelling);
    if(is_bare_integer(n.type))pool_.intern_integer_literal(n.spelling);
}

void ConstantEmitter::emit(const ir::ConstantInt& n,const ir::Instruction&){
    symbols_.set_type(n.out,n.type);
    copy_by_leading_zero_add(builder_,symbols_.value(n.out),llvm_type(n.type),n.value);
    symbols_.acquire_owned(n.out,n.type,symbols_.value(n.out));
}

void ConstantEmitter::emit(const ir::ConstantFloat& n,const ir::Instruction&){
    symbols_.set_type(n.out,n.type);
    // A literal's decimal value is rounded once, to the type's own format,
    // never through binary64 first.
    const auto literal=n.spelling.empty()
        ?std::optional<double>{}:constant_eval::real_literal_value(n.spelling,n.type);
    if(n.type.kind==TypeKind::Real16b){
        // A real16b is its bfloat16 bits.
        copy_by_leading_zero_add(builder_,symbols_.value(n.out),i16,
                                 static_cast<long long>(bfloat16_literal_bits(literal.value_or(n.value))));
        return;
    }
    copy_by_leading_zero_fadd(builder_,symbols_.value(n.out),llvm_type(n.type),
                              float_literal(literal.value_or(n.value),n.type));
}

// Node calls consume managed numeric parameters through stable mirrors.
// Inline and immortal integer literals have no-op drops, while a heap real
// literal owns its freshly allocated value. Publish both before any call.
void ConstantEmitter::emit(const ir::ConstantExact& n,const ir::Instruction&){
    symbols_.set_type(n.out,n.type);
    if(n.type.kind==TypeKind::Real){
        // A literal with a small form is that constant; any other one is
        // read by the runtime at run time.
        SmallRational small{};
        if(small_rational_literal(n.spelling,small)){
            const auto constant="{ i64 "+std::to_string(small.numerator)+", i64 "+
                                std::to_string(small.denominator)+" }";
            copy_by_select_true(builder_,symbols_.value(n.out),exact_real_type,constant);
            symbols_.acquire_owned(n.out,n.type,symbols_.value(n.out));
            return;
        }
        const auto g=pool_.intern(n.spelling);
        builder_.call(symbols_.value(n.out),exact_real_type,LlvmOperand::global(real_helper::literal),{{ptr,LlvmOperand::global(g)}});
        symbols_.acquire_owned(n.out,n.type,symbols_.value(n.out));
        return;
    }
    // An integer literal within the inline range is its word; any other one
    // is made once, by the runtime, at its first use.
    long long word=0;
    if(bare_integer_inline_literal(n.spelling,word)){
        copy_by_leading_zero_add(builder_,symbols_.value(n.out),bare_integer_type,word);
        symbols_.acquire_owned(n.out,n.type,symbols_.value(n.out));
        return;
    }
    const auto g=pool_.intern(n.spelling);
    const auto cache=pool_.intern_integer_literal(n.spelling);
    builder_.call(symbols_.value(n.out),bare_integer_type,LlvmOperand::global(int_helper::literal),{{ptr,LlvmOperand::global(g)},{ptr,LlvmOperand::global(cache)}});
    symbols_.acquire_owned(n.out,n.type,symbols_.value(n.out));
}

void ConstantEmitter::emit(const ir::ConstantBool& n,const ir::Instruction&){
    symbols_.set_type(n.out,Type::simple(TypeKind::Bool));
    copy_by_leading_false_xor(builder_,symbols_.value(n.out),n.value?"true":"false");
}

void ConstantEmitter::emit(const ir::ConstantString& n,const ir::Instruction&){
    symbols_.set_type(n.out,Type::simple(TypeKind::String));
    const auto g=pool_.intern(n.value);
    builder_.getelementptr(symbols_.value(n.out),Inbounds::yes,LlvmType::array(n.value.size()+1,i8),
                           LlvmOperand::global(g),{{i64,0},{i64,0}});
}

} // namespace quidra::llvm_backend
