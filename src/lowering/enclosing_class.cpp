// load_receiver: the receiver of the method or constructor being lowered.

#include "lowering/enclosing_class.hpp"

namespace quidra::lowering {

ValueId load_receiver(ir::FunctionBuilder& builder, const EnclosingClass& enclosing_class) {
    auto out=builder.fresh();
    const auto type=Type::class_type(enclosing_class.name());
    if (enclosing_class.receiver_reference())
        builder.emit(LoadReference{out,enclosing_class.receiver_local(),type});
    else
        builder.emit(LoadLocal{out,enclosing_class.receiver_local(),type});
    return out;
}

} // namespace quidra::lowering
