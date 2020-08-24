module Hacl.Spec.Bignum.Base

open FStar.Mul
open Lib.IntTypes
open Lib.Sequence


#reset-options "--z3rlimit 50 --fuel 0 --ifuel 0"

inline_for_extraction noextract
let carry = x:uint64{uint_v x == 0 \/ uint_v x == 1}

(**
 This is non-stateful version of code/fallback functions
*)
inline_for_extraction noextract
val addcarry_u64: c:carry -> a:uint64 -> b:uint64 ->
  Pure (carry & uint64)
  (requires True)
  (ensures  fun (c', r) ->
    uint_v r + uint_v c' * pow2 64 == uint_v a + uint_v b + uint_v c)

let addcarry_u64 cin x y =
  let res = x +. cin +. y in
  let c = logand (logor (lt_mask res x) (logand (eq_mask res x) cin)) (u64 1) in
  logand_lemma (eq_mask res x) cin;
  logor_lemma (lt_mask res x) (logand (eq_mask res x) cin);
  logand_mask (logor (lt_mask res x) (logand (eq_mask res x) cin)) (u64 1) 1;
  c, res


inline_for_extraction noextract
val subborrow_u64: c:carry -> a:uint64 -> b:uint64 ->
  Pure (carry & uint64)
  (requires True)
  (ensures  fun (c', r) ->
    uint_v r - uint_v c' * pow2 64 == uint_v a - uint_v b - uint_v c)

let subborrow_u64 cin x y =
  let res = x -. y -. cin in
  let c = logand (logor (gt_mask res x) (logand (eq_mask res x) cin)) (u64 1) in
  logand_lemma (eq_mask res x) cin;
  logor_lemma (gt_mask res x) (logand (eq_mask res x) cin);
  logand_mask (logor (gt_mask res x) (logand (eq_mask res x) cin)) (u64 1) 1;
  c, res



let mask_values (x:uint64) =
  v x = v (zeros U64 SEC) \/ v x = v (ones U64 SEC)

inline_for_extraction noextract
val mask_select: mask:uint64 -> a:uint64 -> b:uint64 -> uint64
let mask_select mask a b =
  (mask &. a) |. ((lognot mask) &. b)

val mask_select_lemma: mask:uint64 -> a:uint64 -> b:uint64 -> Lemma
  (requires mask_values mask)
  (ensures  mask_select mask a b == (if v mask = 0 then b else a))

let mask_select_lemma mask a b =
  if v mask = 0 then begin
    logand_lemma mask a;
    assert (v (mask &. a) = 0);
    lognot_lemma mask;
    assert (v (lognot mask) = v (ones U64 SEC));
    logand_lemma (lognot mask) b;
    assert (v ((lognot mask) &. b) == v b);
    logor_lemma (mask &. a) ((lognot mask) &. b);
    assert (v (mask_select mask a b) == v b) end
  else begin
    logand_lemma mask a;
    assert (v (mask &. a) = v a);
    lognot_lemma mask;
    assert (v (lognot mask) = 0);
    logand_lemma (lognot mask) b;
    assert (v ((lognot mask) &. b) == 0);
    logor_zeros (mask &. a);
    assert (v (mask_select mask a b) == v a) end


val lseq_mask_select_lemma: #len:size_nat ->a:lseq uint64 len -> b:lseq uint64 len -> mask:uint64 -> Lemma
  (requires mask_values mask)
  (ensures  map2 (mask_select mask) a b == (if v mask = 0 then b else a))

let lseq_mask_select_lemma #len a b mask =
  let res = map2 (mask_select mask) a b in

  let lemma_aux (i:nat{i < len}) : Lemma (v res.[i] == (if v mask = 0 then v b.[i] else v a.[i])) =
    mask_select_lemma mask a.[i] b.[i] in

  Classical.forall_intro lemma_aux;
  if v mask = 0 then eq_intro res b else eq_intro res a
