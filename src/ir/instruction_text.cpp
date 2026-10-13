// instruction_text (instruction_text.hpp): one if-constexpr line per rendered
// instruction kind.
#include "ir/instruction_text.hpp"

#include "quidra/abi/error_record.hpp"
#include "quidra/abi/tensor_index.hpp"

#include <sstream>

namespace quidra::ir {

namespace {

const char* finite_cause_name(FiniteCause cause){
    switch(cause){
        case FiniteCause::addition: return "+";
        case FiniteCause::subtraction: return "-";
        case FiniteCause::multiplication: return "*";
        case FiniteCause::division: return "/";
        case FiniteCause::power: return "^";
    }
    return "?";
}

// error.make: a user error's text and code, or a Core code's spelling and
// its details by name (a name detail with a closed list unquoted); then
// the cause.
void write_error_make(std::ostream& out,const ErrorMake& n){
    out<<"%"<<n.out<<" = error.make";
    const auto operand=[&](const ErrorDetailOperand& detail,bool quote){
        if(detail.value)out<<" %"<<*detail.value;
        else if(quote)out<<" \""<<detail.constant<<"\"";
        else out<<" "<<detail.constant;
    };
    if(const auto* schema=abi::error_value_schema(n.schema)){
        out<<" "<<schema->spelling;
        for(std::size_t i=0;i<n.details.size()&&i<schema->details.size();++i){
            if(n.details[i].absent)continue;
            out<<" "<<schema->details[i].name;
            operand(n.details[i],schema->details[i].values.empty());
        }
    }else{
        for(const auto& detail:n.details)operand(detail,true);
        if(!n.code.empty())out<<" code \""<<n.code<<"\"";
    }
    if(n.cause)out<<" cause %"<<*n.cause;
}


// A slice item's operands as written: ` [%s<:%e:%k]`, an omitted side empty.
std::string slice_bounds_text(const SliceBounds& b){
    std::string text=" [";
    if(b.start) text+="%"+std::to_string(*b.start);
    if(b.start_form==SliceStart::exclusive_ascending) text+="<";
    if(b.start_form==SliceStart::exclusive_descending) text+=">";
    text+=":";
    if(b.end_form==SliceEnd::exclusive_ascending) text+="<";
    if(b.end_form==SliceEnd::exclusive_descending) text+=">";
    if(b.end) text+="%"+std::to_string(*b.end);
    if(b.step) text+=":%"+std::to_string(*b.step);
    text+="]";
    return text;
}
} // namespace

std::string instruction_text(const Instruction& i){ std::ostringstream out; std::visit([&](const auto& n){using T=std::decay_t<decltype(n)>;
    if constexpr(std::is_same_v<T,SourceLocation>)out<<"source "<<n.line<<":"<<n.column;
    if constexpr(std::is_same_v<T,ConstantInt>)out<<"%"<<n.out<<" = const.int "<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ConstantFloat>)out<<"%"<<n.out<<" = const.float "<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ConstantExact>)out<<"%"<<n.out<<" = const.exact "<<n.spelling<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ConstantBool>)out<<"%"<<n.out<<" = const.bool "<<(n.value?"true":"false");
    if constexpr(std::is_same_v<T,ConstantString>)out<<"%"<<n.out<<" = const.string \""<<n.value<<"\"";
    if constexpr(std::is_same_v<T,StringQuote>)out<<"%"<<n.out<<" = string.quote %"<<n.text;
    if constexpr(std::is_same_v<T,TupleMake>){out<<"%"<<n.out<<" = tuple.make "<<type_name(n.type);for(auto value:n.elements)out<<" %"<<value;}
    if constexpr(std::is_same_v<T,TupleGet>)out<<"%"<<n.out<<" = tuple.get %"<<n.tuple<<", "<<n.index<<(n.take?" take":"");
    if constexpr(std::is_same_v<T,AddressTupleElement>)out<<"%"<<n.out<<" = address.tuple.element %"<<n.address<<", "<<n.index;
    if constexpr(std::is_same_v<T,ArrayMake>)out<<"%"<<n.out<<" = array.make "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ArrayAlloc>)out<<"%"<<n.out<<" = array.alloc %"<<n.length;
    if constexpr(std::is_same_v<T,ClassMake>)out<<"%"<<n.out<<" = class.make "<<type_name(n.type);
    if constexpr(std::is_same_v<T,FieldGet>)out<<"%"<<n.out<<" = field.get %"<<n.object<<", "<<n.index;
    if constexpr(std::is_same_v<T,FieldSet>)out<<"field.set %"<<n.object<<", "<<n.index<<", %"<<n.value;
    if constexpr(std::is_same_v<T,DeclareLocal>)out<<"local "<<n.name<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,DeclareReference>)out<<(n.is_const?"const reference ":"reference ")<<n.name<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,AddressLocal>)out<<"%"<<n.out<<" = address.local "<<n.name;
    if constexpr(std::is_same_v<T,AddressField>)out<<"%"<<n.out<<" = address.field %"<<n.object<<", "<<n.index;
    if constexpr(std::is_same_v<T,AddressElement>)out<<"%"<<n.out<<" = address.element %"<<n.array<<", %"<<n.index<<" : "<<type_name(n.element_type);
    if constexpr(std::is_same_v<T,LoadAddress>)out<<"%"<<n.out<<" = address.load %"<<n.address;
    if constexpr(std::is_same_v<T,StoreAddress>)out<<"address.store %"<<n.address<<", %"<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,BindReference>)out<<"reference.bind "<<n.name<<", %"<<n.address;
    if constexpr(std::is_same_v<T,ReferenceAddress>)out<<"%"<<n.out<<" = reference.address "<<n.name;
    if constexpr(std::is_same_v<T,LoadReference>)out<<"%"<<n.out<<" = reference.load "<<n.name<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,StoreReference>)out<<"reference.store "<<n.name<<", %"<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ArrayLength>)out<<"%"<<n.out<<" = array.length %"<<n.array;
    if constexpr(std::is_same_v<T,ArrayCanAppendMove>)out<<"%"<<n.out<<" = array.can_append_move %"<<n.array;
    if constexpr(std::is_same_v<T,ArrayGrowMove>)out<<"%"<<n.out<<" = array.grow_move %"<<n.array<<" : "<<type_name(n.array_type);
    if constexpr(std::is_same_v<T,ArraySorted>){out<<"%"<<n.out<<" = array.sorted %"<<n.array;if(n.descending_constant)out<<" descending";else if(n.descending)out<<" descending %"<<*n.descending;out<<" : "<<type_name(n.array_type);}
    if constexpr(std::is_same_v<T,StringIndex>)out<<"%"<<n.out<<" = string.index %"<<n.text<<", %"<<n.index;
    if constexpr(std::is_same_v<T,StringIndexAsciiCompare>)out<<"%"<<n.out<<" = string.index_ascii_compare %"<<n.text<<", %"<<n.index<<", "<<static_cast<unsigned>(n.byte)<<(n.negate?" !=":" ==");
    if constexpr(std::is_same_v<T,StringAsciiCountPrefix>)out<<"%"<<n.out<<" = string.ascii_count_prefix %"<<n.text<<", %"<<n.count<<", %"<<n.initial<<", "<<static_cast<unsigned>(n.byte)<<(n.negate?" !=":" ==");
    if constexpr(std::is_same_v<T,StringLength>)out<<"%"<<n.out<<" = string.length %"<<n.text;
    if constexpr(std::is_same_v<T,StringEmpty>)out<<"%"<<n.out<<" = string."<<(n.negate?"nonempty ":"empty ")<<"%"<<n.text;
    if constexpr(std::is_same_v<T,StringContains>)out<<"%"<<n.out<<" = string.contains %"<<n.text<<", %"<<n.needle;
    if constexpr(std::is_same_v<T,StringStartsWith>)out<<"%"<<n.out<<" = string.starts_with %"<<n.text<<", %"<<n.prefix;
    if constexpr(std::is_same_v<T,StringEndsWith>)out<<"%"<<n.out<<" = string.ends_with %"<<n.text<<", %"<<n.suffix;
    if constexpr(std::is_same_v<T,StringFind>)out<<"%"<<n.out<<" = string.find %"<<n.text<<", %"<<n.needle;
    if constexpr(std::is_same_v<T,BinSlicePlanned>)out<<"%"<<n.out<<" = bin.slice_planned %"<<n.bin<<slice_bounds_text(n.bounds);
    if constexpr(std::is_same_v<T,StringSliceStepped>)out<<"%"<<n.out<<" = string.slice_stepped %"<<n.text<<slice_bounds_text(n.bounds);
    if constexpr(std::is_same_v<T,StringSlice>)out<<"%"<<n.out<<" = string.slice %"<<n.text<<", %"<<n.start<<", %"<<n.end;
    if constexpr(std::is_same_v<T,StringTrim>)out<<"%"<<n.out<<" = string.trim %"<<n.text;
    if constexpr(std::is_same_v<T,StringSplit>)out<<"%"<<n.out<<" = string.split %"<<n.text<<", %"<<n.separator;
    if constexpr(std::is_same_v<T,StringSplitIterBegin>)out<<"%"<<n.out<<" = string.split_iter.begin %"<<n.text<<", %"<<n.separator<<(n.move_source?" move":"");
    if constexpr(std::is_same_v<T,StringSplitIterNext>)out<<"%"<<n.text<<", %"<<n.has_value<<" = string.split_iter.next %"<<n.cursor;
    if constexpr(std::is_same_v<T,StringSplitIterEnd>)out<<"string.split_iter.end %"<<n.cursor;
    if constexpr(std::is_same_v<T,StringParseTwoSigned>)out<<"%"<<n.left<<", %"<<n.right<<", %"<<n.ok<<" = string.parse_two_signed %"<<n.text<<", "<<static_cast<unsigned>(n.separator);
    if constexpr(std::is_same_v<T,StringUtf8>)out<<"%"<<n.out<<" = string.utf8 %"<<n.text;
    if constexpr(std::is_same_v<T,StringFromUtf8>)out<<"%"<<n.out<<" = string.from_utf8 %"<<n.bin;
    if constexpr(std::is_same_v<T,StringFromUtf8ArrayDirect>)out<<"%"<<n.text<<", %"<<n.ok<<", %"<<n.error<<" = string.from_utf8_array_direct %"<<n.array;
    if constexpr(std::is_same_v<T,StringCodepoints>)out<<"%"<<n.out<<" = string.codepoints %"<<n.text;
    if constexpr(std::is_same_v<T,StringJoin>)out<<"%"<<n.out<<" = string.join %"<<n.values<<", %"<<n.separator;
    if constexpr(std::is_same_v<T,StringConcat>){out<<"%"<<n.out<<" = string.concat";for(const auto value:n.values)out<<" %"<<value;}
    if constexpr(std::is_same_v<T,StringBuild>){out<<"%"<<n.out<<" = string.build";for(const auto& part:n.parts){out<<" %"<<part.value<<":"<<type_name(part.type);if(part.kind==StringBuildPartKind::QuotedString)out<<":quoted";}out<<" sep %"<<n.separator;}
    if constexpr(std::is_same_v<T,StringBuildAppendMove>){out<<"%"<<n.out<<", %"<<n.added_length<<" = string.build_append %"<<n.text;for(const auto& part:n.parts){out<<" %"<<part.value<<":"<<type_name(part.type);if(part.kind==StringBuildPartKind::QuotedString)out<<":quoted";}out<<" sep %"<<n.separator;}
    if constexpr(std::is_same_v<T,StringCanAppendMove>)out<<"%"<<n.out<<" = string.can_append_move %"<<n.text;
    if constexpr(std::is_same_v<T,StringAppendMove>){out<<"%"<<n.out<<" = string.append_move %"<<n.text;for(const auto value:n.suffixes)out<<" %"<<value;}
    if constexpr(std::is_same_v<T,BinAlloc>)out<<"%"<<n.out<<" = bin.alloc %"<<n.length<<", %"<<n.fill;
    if constexpr(std::is_same_v<T,BinLength>)out<<"%"<<n.out<<" = bin.length %"<<n.bin;
    if constexpr(std::is_same_v<T,BinGet>)out<<"%"<<n.out<<" = bin.get %"<<n.bin<<", %"<<n.index;
    if constexpr(std::is_same_v<T,BinSet>)out<<"bin.set %"<<n.bin<<", %"<<n.index<<", %"<<n.value;
    if constexpr(std::is_same_v<T,ParseBin>)out<<"%"<<n.out<<" = bin.parse %"<<n.text<<" : "<<type_name(n.result_type)<<(n.success_proven?" success-proven":"");
    if constexpr(std::is_same_v<T,NumericConvert>)out<<"%"<<n.out<<" = convert %"<<n.value<<" : "<<type_name(n.source_type)<<" -> "<<type_name(n.target_type)<<(n.checked_range?" checked":"")<<(n.inline_proven?" inline":"");
    if constexpr(std::is_same_v<T,FallibleNumericConvert>)out<<"%"<<n.out<<" = convert.fallible %"<<n.value<<" : "<<type_name(n.source_type)<<" -> "<<type_name(n.result_type);
    if constexpr(std::is_same_v<T,TensorCreate>)out<<"%"<<n.out<<" = tensor.create %"<<n.shape<<" : "<<type_name(n.type)<<" init="<<(n.fill_mode==tensor_fill_mode::uninitialized?"uninitialized":n.fill_mode==tensor_fill_mode::zeros?"zeros":"ones")<<(n.gpu?" gpu=%"+std::to_string(*n.gpu):" cpu");
    if constexpr(std::is_same_v<T,TensorTransfer>)out<<"%"<<n.out<<" = tensor."<<(n.gpu?"gpu":"cpu")<<" %"<<n.tensor<<(n.gpu?", %"+std::to_string(*n.gpu):"")<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,TensorReshape>)out<<"%"<<n.out<<" = tensor.reshape %"<<n.tensor<<", %"<<n.shape<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,TensorTranspose>)out<<"%"<<n.out<<" = tensor.transpose %"<<n.tensor<<", %"<<n.axis0<<", %"<<n.axis1<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,TensorContiguous>)out<<"%"<<n.out<<" = tensor.contiguous %"<<n.tensor<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,TensorGather>)out<<"%"<<n.out<<" = tensor.gather %"<<n.tensor<<", %"<<n.indices<<", %"<<n.shape<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,TensorScatter>)out<<"%"<<n.out<<" = tensor.scatter %"<<n.tensor<<", %"<<n.indices<<", %"<<n.shape<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,TensorShape>)out<<"%"<<n.out<<" = tensor.shape %"<<n.tensor<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,TensorDevice>)out<<"%"<<n.out<<" = tensor.device %"<<n.tensor;
    if constexpr(std::is_same_v<T,TensorIsContiguous>)out<<"%"<<n.out<<" = tensor.is_contiguous %"<<n.tensor;
    if constexpr(std::is_same_v<T,TensorIsTracked>)out<<"%"<<n.out<<" = tensor.is_tracked %"<<n.tensor;
    if constexpr(std::is_same_v<T,TensorHasGrad>)out<<"%"<<n.out<<" = tensor.has_grad %"<<n.tensor;
    if constexpr(std::is_same_v<T,TensorClearGrad>)out<<"tensor.clear_grad %"<<n.tensor;
    if constexpr(std::is_same_v<T,TensorItem>)out<<"%"<<n.out<<" = tensor.item %"<<n.tensor<<" : "<<type_name(n.element_type);
    if constexpr(std::is_same_v<T,TensorTrack>)out<<"%"<<n.out<<" = tensor."<<(n.mode==tensor_track_mode::untrack?"untrack":n.mode==tensor_track_mode::track?"track":"retrack")<<" %"<<n.tensor<<(n.target?" target %"+std::to_string(n.target):"");
    if constexpr(std::is_same_v<T,TensorBackward>){out<<"tensor.backward %"<<n.tensor;for(const auto&target:n.targets)out<<" "<<(target.autograd_target?"target":"tensor")<<" %"<<target.value;}
    if constexpr(std::is_same_v<T,TensorGrad>)out<<"%"<<n.out<<" = tensor.grad %"<<n.tensor;
    if constexpr(std::is_same_v<T,TensorBinary>)out<<"%"<<n.out<<" = tensor.binary "<<n.op<<" %"<<n.left<<", %"<<n.right<<" : "<<type_name(n.result_type);
    if constexpr(std::is_same_v<T,TensorIndex>){
        out<<"%"<<n.out<<" = tensor.index %"<<n.tensor;
        for(const auto& item:n.items){
            if(item.kind!=abi::tensor_index_spec::index){
                // A marked slice shows its markers and the word marked; the
                // half-open start:<end shows none.
                namespace spec=abi::tensor_index_spec;
                const bool marked=spec::is_marked_slice(item.kind);
                out<<(marked?" marked [":" [");
                if(item.start)out<<"%"<<*item.start;
                if(marked&&spec::marked_start(item.kind)==SliceStart::exclusive_ascending)out<<"<";
                out<<":";
                if(marked&&spec::marked_end(item.kind)==SliceEnd::exclusive_ascending)out<<"<";
                if(item.stop)out<<"%"<<*item.stop;
                if(item.step)out<<":%"<<*item.step;
                out<<"]";
            }else if(item.index){
                out<<" %"<<*item.index;
            }
        }
        out<<" : "<<type_name(n.type);
    }
    if constexpr(std::is_same_v<T,ArrayNumericCast>)out<<"%"<<n.out<<" = array.numeric_cast %"<<n.array<<" : "<<type_name(n.source_type)<<" -> "<<type_name(n.target_type);
    if constexpr(std::is_same_v<T,TensorCast>)out<<"%"<<n.out<<" = tensor.numeric_cast %"<<n.tensor<<" : "<<type_name(n.source_type)<<" -> "<<type_name(n.target_type);
    if constexpr(std::is_same_v<T,ShapedConstraintCheck>){out<<"shape.constraint %"<<n.value<<" rank"<<(n.ellipsis ? ">=" : "=")<<n.extents.size();if(n.ellipsis)out<<" ellipsis="<<*n.ellipsis;}
    if constexpr(std::is_same_v<T,ExtentEqualCheck>)out<<(n.for_collection_lengths?"for.length.check %":"extent.check %")<<n.actual<<", %"<<n.expected;
    if constexpr(std::is_same_v<T,ParseNumber>)out<<"%"<<n.out<<" = parse %"<<n.text<<" : "<<type_name(n.target_type)<<" -> "<<type_name(n.result_type);
    if constexpr(std::is_same_v<T,ParseNumberDirect>)out<<"%"<<n.value_out<<", %"<<n.ok_out<<", %"<<n.error_out<<" = parse.direct %"<<n.text<<" : "<<type_name(n.target_type);
    if constexpr(std::is_same_v<T,ExactAtom>)out<<"%"<<n.out<<" = exact.atom "<<n.provider<<":"<<n.opcode<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ExactUnary>)out<<"%"<<n.out<<" = exact.unary "<<n.provider<<":"<<n.opcode<<" %"<<n.input<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,RealLoopCount>)out<<"%"<<n.out<<" = real.loop_count %"<<n.start<<", %"<<n.end<<", %"<<n.step<<" : "<<type_name(n.type)<<" "<<(n.descending?"descending":"ascending")<<" "<<n.start_inclusive<<" "<<n.end_inclusive;
    if constexpr(std::is_same_v<T,RealLoopValue>)out<<"%"<<n.out<<" = real.loop_value %"<<n.start<<", %"<<n.step<<", %"<<n.multiplier<<" : "<<type_name(n.type)<<" fma %"<<n.native_fma;
    if constexpr(std::is_same_v<T,ExactLoopPlan>)out<<"%"<<n.out<<" = exact.loop_plan %"<<n.start<<", %"<<n.end<<", %"<<n.step<<" "<<n.descending<<" "<<n.start_inclusive<<" "<<n.end_inclusive;
    if constexpr(std::is_same_v<T,ExactFromScaled>)out<<"%"<<n.out<<" = exact.from_scaled %"<<n.numerator<<", %"<<n.denominator;
    if constexpr(std::is_same_v<T,ExactLoopValue>)out<<"%"<<n.out<<" = exact.loop_value %"<<n.start<<", %"<<n.step<<", %"<<n.multiplier;
    if constexpr(std::is_same_v<T,ExactScaledCompare>)out<<"%"<<n.out<<" = exact.scaled_compare %"<<n.numerator<<", %"<<n.denominator<<" "<<n.op<<" "<<n.constant_n<<"/"<<n.constant_d;
    if constexpr(std::is_same_v<T,ExactScaledConvert>)out<<"%"<<n.out<<" = exact.scaled_convert %"<<n.numerator<<", %"<<n.denominator<<" : "<<type_name(n.target)<<" result "<<type_name(n.result_type);
    if constexpr(std::is_same_v<T,ExactRound>){
        out<<"%"<<n.out<<" = exact.round %"<<n.value<<" : "<<type_name(n.type);
        if(!n.slot.empty())out<<" -> "<<n.slot;
    }
    if constexpr(std::is_same_v<T,ExactConstant>)out<<"%"<<n.out<<" = exact.constant "<<n.slot<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ExactOp>){
        out<<"%"<<n.out<<" = exact.op "<<n.provider<<":"<<n.opcode;
        for(std::size_t i=0;i<n.inputs.size();++i)out<<(i?", %":" %")<<n.inputs[i];
        out<<" : "<<type_name(n.type);
    }
    if constexpr(std::is_same_v<T,ArrayInitializationComplete>)out<<"%"<<n.out<<" = array.initialization.complete %"<<n.array;
    if constexpr(std::is_same_v<T,ArraySlice>)out<<"%"<<n.out<<" = array.slice %"<<n.array<<slice_bounds_text(n.bounds)<<" : "<<type_name(n.array_type);
    if constexpr(std::is_same_v<T,SliceLoopPlan>)out<<"%"<<n.out<<" = slice.loop_plan %"<<n.length<<slice_bounds_text(n.bounds)<<", first-address %"<<n.first_address;
    if constexpr(std::is_same_v<T,ArraySliceSet>)out<<"array.slice_set %"<<n.array<<slice_bounds_text(n.bounds)<<", %"<<n.value<<" : "<<type_name(n.array_type);
    if constexpr(std::is_same_v<T,ArrayGet>)out<<"%"<<n.out<<" = array.get %"<<n.array<<", %"<<n.index<<(n.bounds_guard?" bounds-guard %"+std::to_string(*n.bounds_guard):"");
    if constexpr(std::is_same_v<T,ArraySet>)out<<"array.set %"<<n.array<<", %"<<n.index<<", %"<<n.value<<(n.bounds_guard?" bounds-guard %"+std::to_string(*n.bounds_guard):"");
    if constexpr(std::is_same_v<T,Clone>)out<<"%"<<n.out<<" = clone %"<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,Retain>)out<<"%"<<n.out<<" = retain %"<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,Release>)out<<"release %"<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,Unary>)out<<"%"<<n.out<<" = "<<n.op<<" %"<<n.operand<<(n.inline_proven?" inline":"");
    if constexpr(std::is_same_v<T,Binary>)out<<"%"<<n.out<<" = "<<n.op<<" %"<<n.left<<", %"<<n.right<<(n.overflow_proven?" no-overflow":"")<<(n.inline_proven?" inline":"");
    if constexpr(std::is_same_v<T,ToString>)out<<"%"<<n.out<<" = text %"<<n.value<<" : "<<type_name(n.source_type);
    if constexpr(std::is_same_v<T,FormatNumber>){
        out<<"%"<<n.out<<" = format %"<<n.value<<" : "<<type_name(n.source_type);
        if(n.integer_width)out<<" int="<<*n.integer_width;
        if(n.fractional_digits)out<<" frac="<<*n.fractional_digits;
        if(n.significant_digits)out<<" sig="<<*n.significant_digits;
        if(n.zero)out<<" zero";
    }
    if constexpr(std::is_same_v<T,ParallelBlock>){out<<"%"<<n.out<<" = parallel "<<n.table_name;if(n.iterations)out<<" for %"<<n.iterations->count;for(const auto& node:n.nodes){out<<" node "<<node.function<<" pred";for(auto p:node.predecessors)out<<" "<<p;}}
    if constexpr(std::is_same_v<T,AddressReferenceSlot>)out<<"%"<<n.out<<" = ref.slot "<<n.name;
    if constexpr(std::is_same_v<T,LoadLocal>)out<<"%"<<n.out<<(n.move_out?" = load.move ":" = load ")<<n.name;
    if constexpr(std::is_same_v<T,StoreLocal>)out<<(n.borrowed?"store.borrow ":"store ")<<n.name<<", %"<<n.value;
    if constexpr(std::is_same_v<T,FunctionRef>)out<<"%"<<n.out<<" = fn.ref "<<n.function<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,IndirectCall>){
        if(n.result.kind!=TypeKind::Void&&n.result.kind!=TypeKind::Never)out<<"%"<<n.out<<" = ";
        out<<"call.indirect %"<<n.callee<<"(";
        for(std::size_t index=0;index<n.args.size();++index){if(index)out<<", ";out<<"%"<<n.args[index];}
        out<<")";
    }
    if constexpr(std::is_same_v<T,Call>){
        if(n.result.kind!=TypeKind::Void&&n.result.kind!=TypeKind::Never)out<<"%"<<n.out<<" = ";
        out<<(n.shape_forwarder?"call.shape_forward ":"call ")<<n.callee<<"(";
        for(std::size_t index=0;index<n.args.size();++index){
            if(index)out<<", ";
            if(n.args[index].writable_address)out<<"&%"<<*n.args[index].writable_address;
            else out<<"%"<<n.args[index].value;
        }
        out<<")";
    }
    if constexpr(std::is_same_v<T,VariantMake>)out<<"%"<<n.out<<" = variant "<<n.tag;
    if constexpr(std::is_same_v<T,VariantTag>)out<<"%"<<n.out<<" = variant.tag %"<<n.container;
    if constexpr(std::is_same_v<T,VariantPayload>)out<<"%"<<n.out<<" = variant.payload %"<<n.container;
    if constexpr(std::is_same_v<T,Print>)out<<"%"<<n.out<<" = print %"<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ReplDisplay>)out<<"repl.display %"<<n.value<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ReplReplayMode>)out<<"repl.replay "<<(n.active?"on":"off");
    if constexpr(std::is_same_v<T,Input>)out<<"%"<<n.out<<" = input";
    if constexpr(std::is_same_v<T,Exit>)out<<"exit %"<<n.status;
    if constexpr(std::is_same_v<T,FailError>)out<<"fail.error %"<<n.error;
    if constexpr(std::is_same_v<T,ForStepCheck>)out<<"for.check_step %"<<n.step<<(n.descending?" descending":" ascending");
    if constexpr(std::is_same_v<T,Return>)out<<"return %"<<n.value;
    if constexpr(std::is_same_v<T,ReturnVoid>)out<<"return";
    if constexpr(std::is_same_v<T,Jump>)out<<"jump "<<n.target;
    if constexpr(std::is_same_v<T,Branch>)out<<"branch %"<<n.condition<<", "<<n.if_true<<", "<<n.if_false;
    if constexpr(std::is_same_v<T,Pin>)out<<"pin %"<<n.value;
    if constexpr(std::is_same_v<T,Unpin>)out<<"unpin %"<<n.value;
    if constexpr(std::is_same_v<T,TraversalSiteCheck>)out<<"for.check_site %"<<n.expected<<", %"<<n.current;
    if constexpr(std::is_same_v<T,IterationShapeCheck>)out<<"for.check_shape %"<<n.array<<", %"<<n.entry_array<<", %"<<n.entry_length;
    if constexpr(std::is_same_v<T,ErrorMake>)write_error_make(out,n);
    if constexpr(std::is_same_v<T,ErrorMessage>)out<<"%"<<n.out<<" = error.message %"<<n.error;
    if constexpr(std::is_same_v<T,ErrorHop>){
        out<<"%"<<n.out<<" = error.hop %"<<n.container<<" call "<<n.name<<" at "<<n.line<<":"<<n.column<<" via "<<abi::error_hop_via(n.kind);
        if(n.callee!=0)out<<" callee %"<<n.callee;
    }
    if constexpr(std::is_same_v<T,ErrorCode>)out<<"%"<<n.out<<" = error.code %"<<n.error;
    if constexpr(std::is_same_v<T,ErrorCause>)out<<"%"<<n.out<<" = error.cause %"<<n.error<<" : "<<type_name(n.result_type);
    if constexpr(std::is_same_v<T,ErrorDetail>)out<<"%"<<n.out<<" = error.detail %"<<n.error<<" "<<(n.detail<abi::error_detail_names.size()?abi::error_detail_names[n.detail]:std::string_view("?"))<<" : "<<type_name(n.result_type);
    if constexpr(std::is_same_v<T,FieldReferenceAddress>)out<<"%"<<n.out<<" = field.reference %"<<n.object<<", "<<n.index;
    if constexpr(std::is_same_v<T,FieldReferenceRoot>)out<<"%"<<n.out<<" = field.reference_root %"<<n.object<<", "<<n.index;
    if constexpr(std::is_same_v<T,BindFieldReference>)out<<"field.bind_reference %"<<n.object<<", "<<n.index<<", %"<<n.address<<", root %"<<n.root;
    if constexpr(std::is_same_v<T,SelfReferenceCheck>)out<<"reference.self_check %"<<n.holder_root<<", %"<<n.target_root;
    if constexpr(std::is_same_v<T,StoredTargetsCheck>)out<<"reference.targets_check %"<<n.value<<", root %"<<n.destination_root;
    if constexpr(std::is_same_v<T,RootSerial>)out<<"%"<<n.out<<" = reference.root_serial";
    if constexpr(std::is_same_v<T,ReferenceBoundCheck>)out<<"reference.check_bound %"<<n.address<<", '"<<n.path<<"'";
    if constexpr(std::is_same_v<T,InitializedCheck>)out<<"init.check %"<<n.flag<<", "<<(n.subject==InitializedSubject::binding?"binding":n.subject==InitializedSubject::field?"field":"argument")<<" '"<<n.path<<"'";
    if constexpr(std::is_same_v<T,FiniteCheck>){
        // Every value a check reads: the tested values and their operands.
        const auto checked=[&](const CheckedReal& c){out<<" %"<<c.value<<" ("<<finite_cause_name(c.cause)<<" %"<<c.left<<", %"<<c.right<<")";};
        out<<"finite.check";for(const auto& c:n.primary)checked(c);
        if(!n.covered.empty()){out<<" covers";for(const auto& c:n.covered)checked(c);}
    }
    if constexpr(std::is_same_v<T,FiniteFlagUpdate>)out<<"finite.flag "<<n.flag<<", %"<<n.value.value<<" ("<<finite_cause_name(n.value.cause)<<" %"<<n.value.left<<", %"<<n.value.right<<")";
    if constexpr(std::is_same_v<T,FiniteFlagCheck>)out<<"finite.flag.check "<<n.flag<<" ("<<finite_cause_name(n.value.cause)<<")";
    if constexpr(std::is_same_v<T,ComplexMake>)out<<"%"<<n.out<<" = complex %"<<n.re<<", %"<<n.im<<" : "<<type_name(n.type);
    if constexpr(std::is_same_v<T,ComplexPart>)out<<"%"<<n.out<<" = complex."<<(n.part==0?"real":"imag")<<" %"<<n.value<<" : "<<type_name(n.type);
},i);return out.str();}

} // namespace quidra::ir
