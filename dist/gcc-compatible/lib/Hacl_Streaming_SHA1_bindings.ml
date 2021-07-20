open Ctypes
module Bindings(F:Cstubs.FOREIGN) =
  struct
    open F
    module Hacl_Streaming_SHA2_applied =
      (Hacl_Streaming_SHA2_bindings.Bindings)(Hacl_Streaming_SHA2_stubs)
    open Hacl_Streaming_SHA2_applied
    type hacl_Streaming_SHA1_state_sha1 = hacl_Streaming_MD5_state_md5
    let hacl_Streaming_SHA1_state_sha1 =
      typedef hacl_Streaming_MD5_state_md5 "Hacl_Streaming_SHA1_state_sha1"
    let hacl_Streaming_SHA1_legacy_create_in_sha1 =
      foreign "Hacl_Streaming_SHA1_legacy_create_in_sha1"
        (void @-> (returning (ptr hacl_Streaming_MD5_state_md5)))
    let hacl_Streaming_SHA1_legacy_init_sha1 =
      foreign "Hacl_Streaming_SHA1_legacy_init_sha1"
        ((ptr hacl_Streaming_MD5_state_md5) @-> (returning void))
    let hacl_Streaming_SHA1_legacy_update_sha1 =
      foreign "Hacl_Streaming_SHA1_legacy_update_sha1"
        ((ptr hacl_Streaming_MD5_state_md5) @->
           (ocaml_bytes @-> (uint32_t @-> (returning void))))
    let hacl_Streaming_SHA1_legacy_finish_sha1 =
      foreign "Hacl_Streaming_SHA1_legacy_finish_sha1"
        ((ptr hacl_Streaming_MD5_state_md5) @->
           (ocaml_bytes @-> (returning void)))
    let hacl_Streaming_SHA1_legacy_free_sha1 =
      foreign "Hacl_Streaming_SHA1_legacy_free_sha1"
        ((ptr hacl_Streaming_MD5_state_md5) @-> (returning void))
  end