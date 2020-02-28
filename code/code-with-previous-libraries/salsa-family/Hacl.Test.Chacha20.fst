module Hacl.Test.Chacha20

open FStar.HyperStack.All
open FStar.Mul
open Lib.IntTypes
open Lib.RawIntTypes
open Lib.Buffer

module Chacha20=Hacl.Impl.Chacha20

unfold inline_for_extraction let len = size 114

#set-options "--initial_fuel 0 --max_fuel 0 --z3rlimit 20"

val main: unit -> Stack C.exit_code (requires (fun h -> True)) (ensures (fun h0 _ h1 -> True))
let main () =
  let ciphertext = create (size 114) (u8 0) in
  let plaintext = createL [
    u8 0x4c; u8 0x61; u8 0x64; u8 0x69; u8 0x65; u8 0x73; u8 0x20; u8 0x61;  
    u8 0x6e; u8 0x64; u8 0x20; u8 0x47; u8 0x65; u8 0x6e; u8 0x74; u8 0x6c;
    u8 0x65; u8 0x6d; u8 0x65; u8 0x6e; u8 0x20; u8 0x6f; u8 0x66; u8 0x20;
    u8 0x74; u8 0x68; u8 0x65; u8 0x20; u8 0x63; u8 0x6c; u8 0x61; u8 0x73;
    u8 0x73; u8 0x20; u8 0x6f; u8 0x66; u8 0x20; u8 0x27; u8 0x39; u8 0x39;
    u8 0x3a; u8 0x20; u8 0x49; u8 0x66; u8 0x20; u8 0x49; u8 0x20; u8 0x63;
    u8 0x6f; u8 0x75; u8 0x6c; u8 0x64; u8 0x20; u8 0x6f; u8 0x66; u8 0x66;
    u8 0x65; u8 0x72; u8 0x20; u8 0x79; u8 0x6f; u8 0x75; u8 0x20; u8 0x6f;
    u8 0x6e; u8 0x6c; u8 0x79; u8 0x20; u8 0x6f; u8 0x6e; u8 0x65; u8 0x20;  
    u8 0x74; u8 0x69; u8 0x70; u8 0x20; u8 0x66; u8 0x6f; u8 0x72; u8 0x20;
    u8 0x74; u8 0x68; u8 0x65; u8 0x20; u8 0x66; u8 0x75; u8 0x74; u8 0x75;
    u8 0x72; u8 0x65; u8 0x2c; u8 0x20; u8 0x73; u8 0x75; u8 0x6e; u8 0x73;
    u8 0x63; u8 0x72; u8 0x65; u8 0x65; u8 0x6e; u8 0x20; u8 0x77; u8 0x6f;
    u8 0x75; u8 0x6c; u8 0x64; u8 0x20; u8 0x62; u8 0x65; u8 0x20; u8 0x69;
    u8 0x74; u8 0x2e
    ] in
  let expected  = createL [
    u8 0x6e; u8 0x2e; u8 0x35; u8 0x9a; u8 0x25; u8 0x68; u8 0xf9; u8 0x80;
    u8 0x41; u8 0xba; u8 0x07; u8 0x28; u8 0xdd; u8 0x0d; u8 0x69; u8 0x81;
    u8 0xe9; u8 0x7e; u8 0x7a; u8 0xec; u8 0x1d; u8 0x43; u8 0x60; u8 0xc2;
    u8 0x0a; u8 0x27; u8 0xaf; u8 0xcc; u8 0xfd; u8 0x9f; u8 0xae; u8 0x0b;
    u8 0xf9; u8 0x1b; u8 0x65; u8 0xc5; u8 0x52; u8 0x47; u8 0x33; u8 0xab;
    u8 0x8f; u8 0x59; u8 0x3d; u8 0xab; u8 0xcd; u8 0x62; u8 0xb3; u8 0x57;
    u8 0x16; u8 0x39; u8 0xd6; u8 0x24; u8 0xe6; u8 0x51; u8 0x52; u8 0xab;
    u8 0x8f; u8 0x53; u8 0x0c; u8 0x35; u8 0x9f; u8 0x08; u8 0x61; u8 0xd8;
    u8 0x07; u8 0xca; u8 0x0d; u8 0xbf; u8 0x50; u8 0x0d; u8 0x6a; u8 0x61;
    u8 0x56; u8 0xa3; u8 0x8e; u8 0x08; u8 0x8a; u8 0x22; u8 0xb6; u8 0x5e;
    u8 0x52; u8 0xbc; u8 0x51; u8 0x4d; u8 0x16; u8 0xcc; u8 0xf8; u8 0x06;
    u8 0x81; u8 0x8c; u8 0xe9; u8 0x1a; u8 0xb7; u8 0x79; u8 0x37; u8 0x36;
    u8 0x5a; u8 0xf9; u8 0x0b; u8 0xbf; u8 0x74; u8 0xa3; u8 0x5b; u8 0xe6;
    u8 0xb4; u8 0x0b; u8 0x8e; u8 0xed; u8 0xf2; u8 0x78; u8 0x5e; u8 0x42;
    u8 0x87; u8 0x4d
    ] in
  let key = createL [
    u8 0; u8   1; u8  2; u8  3; u8  4; u8  5; u8  6; u8  7;
    u8 8; u8   9; u8 10; u8 11; u8 12; u8 13; u8 14; u8 15;
    u8 16; u8 17; u8 18; u8 19; u8 20; u8 21; u8 22; u8 23;
    u8 24; u8 25; u8 26; u8 27; u8 28; u8 29; u8 30; u8 31
    ] in
  let nonce = createL [ 
    u8 0; u8 0; u8 0; u8 0; u8 0; u8 0; u8 0; u8 0x4a; u8 0; u8 0; u8 0; u8 0
    ] in
  let counter = size 1 in
  Chacha20.chacha20_encrypt_bytes len ciphertext plaintext key nonce counter;
  Lib.Print.print_compare_display len ciphertext expected;
  C.EXIT_SUCCESS