module Spec.GF128.Test

#reset-options "--z3rlimit 100 --initial_fuel 0 --max_fuel 0 --initial_ifuel 0"

open FStar.Mul
open Lib.IntTypes
open Lib.RawIntTypes
open Lib.Sequence
open Lib.ByteSequence
open Spec.GaloisField

module GF = Spec.GF128

(* Empty ciphertext test *)

let test1_gmul_hash_key = List.Tot.map u8_from_UInt8 [
  0x66uy; 0xe9uy; 0x4buy; 0xd4uy; 0xefuy; 0x8auy; 0x2cuy; 0x3buy;
  0x88uy; 0x4cuy; 0xfauy; 0x59uy; 0xcauy; 0x34uy; 0x2buy; 0x2euy
]

let test1_gmul_ciphertext = List.Tot.map u8_from_UInt8 []

let test1_gmul_expected = List.Tot.map u8_from_UInt8 [
  0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy;
  0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy
]


(* Test 2 *)

let test2_gmul_hash_key = List.Tot.map u8_from_UInt8 [
  0x66uy; 0xe9uy; 0x4buy; 0xd4uy; 0xefuy; 0x8auy; 0x2cuy; 0x3buy;
  0x88uy; 0x4cuy; 0xfauy; 0x59uy; 0xcauy; 0x34uy; 0x2buy; 0x2euy
]

let test2_gmul_ciphertext = List.Tot.map u8_from_UInt8 [
  0x03uy; 0x88uy; 0xdauy; 0xceuy; 0x60uy; 0xb6uy; 0xa3uy; 0x92uy;
  0xf3uy; 0x28uy; 0xc2uy; 0xb9uy; 0x71uy; 0xb2uy; 0xfeuy; 0x78uy
]

let test2_gmul_expected = List.Tot.map u8_from_UInt8 [
  0x5euy; 0x2euy; 0xc7uy; 0x46uy; 0x91uy; 0x70uy; 0x62uy; 0x88uy;
  0x2cuy; 0x85uy; 0xb0uy; 0x68uy; 0x53uy; 0x53uy; 0xdeuy; 0xb7uy
]


(* Test 3 *)

let test3_gmul_hash_key = List.Tot.map u8_from_UInt8 [
  0x5euy; 0x2euy; 0xc7uy; 0x46uy; 0x91uy; 0x70uy; 0x62uy; 0x88uy;
  0x2cuy; 0x85uy; 0xb0uy; 0x68uy; 0x53uy; 0x53uy; 0xdeuy; 0x37uy
]

let test3_gmul_ciphertext = List.Tot.map u8_from_UInt8 [
  0x66uy; 0xe9uy; 0x4buy; 0xd4uy; 0xefuy; 0x8auy; 0x2cuy; 0x3buy;
  0x88uy; 0x4cuy; 0xfauy; 0x59uy; 0xcauy; 0x34uy; 0x2buy; 0x2euy
]

let test3_gmul_expected = List.Tot.map u8_from_UInt8 [
  0xf3uy; 0x8cuy; 0xbbuy; 0x1auy; 0xd6uy; 0x92uy; 0x23uy; 0xdcuy;
  0xc3uy; 0x45uy; 0x7auy; 0xe5uy; 0xb6uy; 0xb0uy; 0xf8uy; 0x85uy
]

(* Test 4 *)

let test4_gmul_hash_key = List.Tot.map u8_from_UInt8 [
  0xacuy; 0xbeuy; 0xf2uy; 0x05uy; 0x79uy; 0xb4uy; 0xb8uy; 0xebuy;
  0xceuy; 0x88uy; 0x9buy; 0xacuy; 0x87uy; 0x32uy; 0xdauy; 0xd7uy
]

let test4_gmul_ciphertext = List.Tot.map u8_from_UInt8 [
  0xfeuy; 0xeduy; 0xfauy; 0xceuy; 0xdeuy; 0xaduy; 0xbeuy; 0xefuy;
  0xfeuy; 0xeduy; 0xfauy; 0xceuy; 0xdeuy; 0xaduy; 0xbeuy; 0xefuy;
  0xabuy; 0xaduy; 0xdauy; 0xd2uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy;
  0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy; 0x00uy;
  0x5auy; 0x8duy; 0xefuy; 0x2fuy; 0x0cuy; 0x9euy; 0x53uy; 0xf1uy;
  0xf7uy; 0x5duy; 0x78uy; 0x53uy; 0x65uy; 0x9euy; 0x2auy; 0x20uy;
  0xeeuy; 0xb2uy; 0xb2uy; 0x2auy; 0xafuy; 0xdeuy; 0x64uy; 0x19uy;
  0xa0uy; 0x58uy; 0xabuy; 0x4fuy; 0x6fuy; 0x74uy; 0x6buy; 0xf4uy;
  0x0fuy; 0xc0uy; 0xc3uy; 0xb7uy; 0x80uy; 0xf2uy; 0x44uy; 0x45uy;
  0x2duy; 0xa3uy; 0xebuy; 0xf1uy; 0xc5uy; 0xd8uy; 0x2cuy; 0xdeuy;
  0xa2uy; 0x41uy; 0x89uy; 0x97uy; 0x20uy; 0x0euy; 0xf8uy; 0x2euy;
  0x5auy; 0x8duy; 0xefuy; 0x2fuy; 0x0cuy; 0x9euy; 0x53uy; 0xf1uy;
  0xf7uy; 0x5duy; 0x78uy; 0x53uy; 0x65uy; 0x9euy; 0x2auy; 0x20uy;
  0xeeuy; 0xb2uy; 0xb2uy; 0x2auy; 0xafuy; 0xdeuy; 0x64uy; 0x19uy;
  0xa0uy; 0x58uy; 0xabuy; 0x4fuy; 0x6fuy; 0x74uy; 0x6buy; 0xf4uy;
  0x0fuy; 0xc0uy; 0xc3uy; 0xb7uy; 0x80uy; 0xf2uy; 0x44uy; 0x45uy;
  0x44uy; 0xaeuy; 0x7euy; 0x3fuy
]

let test4_gmul_expected = List.Tot.map u8_from_UInt8 [
  0xfbuy; 0xbauy; 0xaauy; 0x70uy; 0xa0uy; 0x73uy; 0x6fuy; 0xf9uy;
  0xeduy; 0x2fuy; 0xc4uy; 0x62uy; 0xdeuy; 0x72uy; 0x61uy; 0xe0uy
]


let print_and_compare (str1:string) (str2:string) (len:size_nat) (test_expected:lbytes len) (test_result:lbytes len) =
  IO.print_string str1;
  List.iter (fun a -> IO.print_string (UInt8.to_string (u8_to_UInt8 a))) (to_list test_expected);
  IO.print_string str2;
  List.iter (fun a -> IO.print_string (UInt8.to_string (u8_to_UInt8 a))) (to_list test_result);
  for_all2 (fun a b -> uint_to_nat #U8 a = uint_to_nat #U8 b) test_expected test_result

let gf128_gmul_test key cipher expected =
  let key = of_list key in
  let cipher = of_list cipher in
  let expected = of_list expected in

  let res = GF.gmul cipher key in

  let r = print_and_compare "Expected hash: " "\nComputed hash: " 16 expected res in
  if r then IO.print_string "\nSuccess!\n" else IO.print_string "\nFailure :(\n";
  r

(* Full GCM tests *)

let test () =
  IO.print_string "\nTEST 1\n";
  let r1 = gf128_gmul_test test1_gmul_hash_key test1_gmul_ciphertext test1_gmul_expected in
  IO.print_string "\nTEST 2\n";
  let r2 = gf128_gmul_test test2_gmul_hash_key test2_gmul_ciphertext test2_gmul_expected in
  IO.print_string "\nTEST 3\n";
  let r3 = gf128_gmul_test test3_gmul_hash_key test3_gmul_ciphertext test3_gmul_expected in
  IO.print_string "\nTEST 4\n";
  let r4 = gf128_gmul_test test4_gmul_hash_key test4_gmul_ciphertext test4_gmul_expected in

  // Composite result
  if r1 && r2 && r3 && r4
  then begin IO.print_string "\nComposite result: Success! \o/ \n"; true end
  else begin IO.print_string "\nComposite result: Failure :(\n"; false end