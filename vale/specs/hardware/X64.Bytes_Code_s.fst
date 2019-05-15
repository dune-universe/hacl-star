module X64.Bytes_Code_s

open X64.Machine_s
open X64.Instruction_s

type instr_annotation_t = instr_t_record -> Type0

noeq type instruction_t (a:instr_annotation_t) =
  // Generic instruction (should be able to express most instructions)
  | Instr :
      i:instr_t_record ->
      oprs:instr_operands_t i.outs i.args ->
      annotation:a i ->
      instruction_t a
  // Stack operations
  // TODO: taint analysis for these
  | Push       : src:operand -> t:taint -> instruction_t a
  | Pop        : dst:operand -> t:taint -> instruction_t a
  | Alloc      : n:nat -> instruction_t a
  | Dealloc    : n:nat -> instruction_t a

type ocmp:eqtype =
  | OEq: o1:operand{not (OMem? o1 || OStack? o1)} -> o2:operand{not (OMem? o2 || OStack? o2)} -> ocmp
  | ONe: o1:operand{not (OMem? o1 || OStack? o1)} -> o2:operand{not (OMem? o2 || OStack? o2)} -> ocmp
  | OLe: o1:operand{not (OMem? o1 || OStack? o1)} -> o2:operand{not (OMem? o2 || OStack? o2)} -> ocmp
  | OGe: o1:operand{not (OMem? o1 || OStack? o1)} -> o2:operand{not (OMem? o2 || OStack? o2)} -> ocmp
  | OLt: o1:operand{not (OMem? o1 || OStack? o1)} -> o2:operand{not (OMem? o2 || OStack? o2)} -> ocmp
  | OGt: o1:operand{not (OMem? o1 || OStack? o1)} -> o2:operand{not (OMem? o2 || OStack? o2)} -> ocmp

type code_t (a:instr_annotation_t) = precode (instruction_t a) ocmp
type codes_t (a:instr_annotation_t) = list (code_t a)
