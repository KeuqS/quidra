#!/usr/bin/env python3
"""Reject tuple-blind ownership decisions in general lowering."""
from pathlib import Path
import re,sys
root=Path(__file__).resolve().parents[1]
patterns=(r"requires_lifetime_management\(",r"requires_value_clone\(",r"is_pointer_runtime_type\(",r"uses_shared_immutable_storage\(",r"(?:ir::)?(?:Retain|Clone|Release)\s*\{")
# Helpers expand aggregates. The remaining sites are scalar complex parts
# or explicit pointer liveness retains; neither is a general value copy.
allow={"ownership_expansion.hpp"}
scalar_sites={
    "complex_literals.hpp": {"if (part.kind == TypeKind::Real) builder.emit(ir::Release{out, part});", "builder.emit(ir::Release{re, part});", "builder.emit(ir::Release{im, part});"},
    "operator_lowering.cpp": {"held=builder_.fresh();builder_.emit(Retain{held,right,middle_type});"},
    "control_flow_lowering.cpp": {"builder_.emit(Clone{initial,array,array_type});", "uses_shared_immutable_storage(item) &&", "builder_.emit(Retain{kept,value,source.type});", "builder_.emit(Clone{cloned,value,source.type});"},
}
failures=[]
for path in sorted((root/'src/lowering').glob('*')):
    if path.suffix not in ('.cpp','.hpp') or path.name in allow: continue
    for line,text in enumerate(path.read_text().splitlines(),1):
        if text.strip() in scalar_sites.get(path.name,set()): continue
        if any(re.search(pattern,text) for pattern in patterns):
            failures.append(f'{path.relative_to(root)}:{line}: {text.strip()}')
if failures:
    print('\n'.join(failures),file=sys.stderr);sys.exit(1)
