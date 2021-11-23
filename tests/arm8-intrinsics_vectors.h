static uint32_t num_vectors = 121;

static uint64_t a_vectors[121] =
  {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x16,
    0x63,
    0x68,
    0x81,
    0xc6,
    0x05,
    0x82,
    0x58,
    0x1f,
    0xca,
    0x292a,
    0xb90c,
    0xefd7,
    0x898e,
    0x79fa,
    0x1ea2,
    0x8549,
    0x74cb,
    0x1a2a,
    0xf168,
    0x992e,
    0xc740,
    0xcfd5,
    0x08ea,
    0x70d4,
    0xcb70,
    0x040b,
    0x4702,
    0x6a49,
    0x0798,
    0x2efd6f,
    0x18839b,
    0x2eaa22,
    0x1f49e8,
    0x16cedd,
    0x8af38a,
    0x73d10c,
    0x9632e3,
    0x090443,
    0x16aa38,
    0xf2fc7c0e,
    0x73daaaa3,
    0xf72699b9,
    0x2aa1dc6d,
    0x42456548,
    0x7e7a0d97,
    0x087ed325,
    0xba361c5c,
    0x7b63a853,
    0xc977fe91,
    0xb619dc3313,
    0xfacd05edb6,
    0x7342522f24,
    0xeebebfb19c,
    0xc746272c04,
    0xd5c6a78484,
    0x9e01d470e4,
    0x206dcaa93e,
    0x9b5f8e9410,
    0x6c6b730fdd,
    0x2335ef94,
    0x6d3053f2,
    0x91012746,
    0xd9ef97d5,
    0x84e5cc6e,
    0x6d292dca,
    0xb2714c0e,
    0x224e5dad,
    0x06ca7277,
    0xa465fecf,
    0x37cdad31de31,
    0xbd3b57f5a772,
    0xafaf4f06d795,
    0x536ab4765e7a,
    0x85096aa50725,
    0x3f867497f785,
    0x18ab7a0be690,
    0x6651faff3153,
    0x7f29a199ef0d,
    0x76047421709b,
    0x6cd7875b7199ff,
    0xe667ea116b683d,
    0xa23e5d485f5282,
    0x26f0d554146e0c,
    0xe16e7b428a081e,
    0x57d911702c4a9b,
    0x741fa5d85faa2c,
    0x53a63e27c50a8b,
    0xe740816035efec,
    0x642b495f362b9a,
    0x60cf2a90b0ffead0,
    0x2d7d1b049516cf3d,
    0xd5f59b77103c1ead,
    0xc8831fcf622ae0aa,
    0x7d850025bef29643,
    0x8c4ab5ab50b028af,
    0x48c4105305529504,
    0x3126a7f2bd42e54a,
    0x01d448053add15d1,
    0x0ac431a82ee253c5,
    0x4caa8a655d67c8cf,
    0x8ea0751bea97b644,
    0xc006c03f7822a984,
    0xe5dcbbf0015e871b,
    0x680f9259fa50ea9f,
    0x05d3629d93d21055,
    0x2deb29d26de1223f,
    0xc91fdad045674b3c,
    0x3b18d4269e15b8f5,
    0x89111f7d5fb2de3e
  };

static uint64_t b_vectors[121] =
  {
    0x0,
    0xe4,
    0xd3,
    0xd4,
    0x21,
    0x47,
    0xf5,
    0xd4,
    0x00,
    0x24,
    0x02,
    0x37,
    0x39,
    0xd4,
    0x63,
    0x11,
    0x63,
    0x32,
    0x88,
    0x47,
    0x56,
    0xea0c,
    0xc14a,
    0xe867,
    0xe122,
    0xef7a,
    0xcd15,
    0xc582,
    0x0da5,
    0x7f8f,
    0xce45,
    0xd0f6e8,
    0x30a33f,
    0x2f2512,
    0xd0ac9e,
    0x7590bb,
    0x8dde26,
    0xf7708f,
    0x469028,
    0x2f0059,
    0xb6d5df,
    0xec7c8e8b,
    0x8ab46530,
    0x77d4fed9,
    0x459e9173,
    0xd35cd136,
    0x19ad2309,
    0x35f5924e,
    0xa6cbd1f1,
    0x8847b1b1,
    0xd8951f94,
    0x97badbe0,
    0x27048001,
    0xb6c0557e,
    0xb93d0d8c,
    0xdf88141c,
    0x71edcf4d,
    0x84d6eb8d,
    0x7815d2a3,
    0x801e9404,
    0xfd91537c,
    0x8cfb3202,
    0x10369caa,
    0x4d29d997,
    0xb7f6779d,
    0xa727b9c3,
    0x1cfa9b2c,
    0x3b171a5e,
    0xdac6cd3b,
    0x3357dc40,
    0x14193225,
    0x11d88155e6,
    0x68abbe543f,
    0x1465ead504,
    0xfcc5a9588c,
    0xc64bfa2384,
    0xcd4e4b8d67,
    0xe9466df9c1,
    0x99fe716f8f,
    0xee844be096,
    0x45f7308492,
    0x6c9ebc7e5640,
    0x792a5f551e84,
    0xb11dcc26e121,
    0xb7ced6ff6aba,
    0x95a24e68b661,
    0x4e7f792a1dec,
    0xb9182348433d,
    0xf03834efd2f8,
    0x0dcac79524d2,
    0xf95f323ccb7b,
    0x8db77e291bc12c,
    0x465b6f91026022,
    0x27826f649d70d9,
    0x5dc9d8e023af9d,
    0x1e8ca56fc88aac,
    0x6cafbef7d5d977,
    0x3fc6915d6a6ef7,
    0x469598042d7b6a,
    0x127d5758e0f120,
    0x9d998f7e5fa7b5,
    0x5b7f7f5ee6819729,
    0x04db9b79467c78f2,
    0x225ef65e23b43007,
    0x7258d8442b7135ef,
    0x6e6395330e3ac575,
    0xa4d817a1226b0c82,
    0x6233914411973a29,
    0x825543d1f489cd46,
    0x41c1d19d73b05564,
    0x4ee75579a5b00596,
    0xffcb45eade0def34,
    0xb4d47d898dfc9c85,
    0x599d5e0a3034e7bc,
    0x0d0239b38b93fdf5,
    0x80468b4b99e134c6,
    0x3358d83b531cd95d,
    0x07989c8a10dae70e,
    0xe2ddfe3e4781eed0,
    0x33c98eccca637bfd,
    0xbf43063a9daa049d
  };

static uint64_t cin_vectors[121] =
  {
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x0,
    0x1,
    0x1,
    0x0,
    0x1,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x0,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x1,
    0x0,
    0x1,
    0x0
  };

static uint64_t addcarry_res_vectors[121] =
  {
    0x0,
    0xe5,
    0xd4,
    0xd5,
    0x22,
    0x47,
    0xf6,
    0xd5,
    0x1,
    0x24,
    0x3,
    0x4e,
    0x9c,
    0x13c,
    0xe4,
    0xd7,
    0x69,
    0xb4,
    0xe1,
    0x67,
    0x121,
    0x11337,
    0x17a57,
    0x1d83f,
    0x16ab1,
    0x16975,
    0xebb8,
    0x14acb,
    0x8271,
    0x99ba,
    0x1bfae,
    0xd19016,
    0x316a80,
    0x2ff4e7,
    0xd0b588,
    0x76018f,
    0x8ea996,
    0xf7749a,
    0x46d72a,
    0x2f6aa3,
    0xb6dd78,
    0xecab8bfb,
    0x8acce8cc,
    0x7803a8fb,
    0x45bddb5b,
    0xd373a014,
    0x1a381694,
    0x3669635a,
    0xa76204d5,
    0x8850b5f4,
    0xd8abc9cd,
    0x18ab757ef,
    0x9adf2aa5,
    0x1ade6ef38,
    0xe3dee9f9,
    0x121cd7965,
    0xf067dce4,
    0x8d55beb2,
    0x1324beeff,
    0xfb823c57,
    0x1c709520d,
    0xb6a6d76516,
    0xfadd3c8a61,
    0x738f7c08bb,
    0xef76b62939,
    0xc7ed4ee5c8,
    0xd5e3a21fb1,
    0x9e3ceb8b42,
    0x2148917679,
    0x9b92e67050,
    0x6c7f8c4202,
    0x11fbb7457a,
    0x6918eea831,
    0x14f6ebfc4a,
    0xfd9f98f061,
    0xc6d0dfeff2,
    0xcdbb74bb32,
    0xe9f8df45cf,
    0x9a20bfcd3c,
    0xee8b16530e,
    0x469b968362,
    0xa46c69b03471,
    0x13665b74ac5f6,
    0x160cd1b2db8b6,
    0x10b398b75c935,
    0x11aabb90dbd87,
    0x8e05edc21572,
    0xd1c39d5429ce,
    0x1568a2fef044c,
    0x8cf4692f13e0,
    0x16f63a65e3c17,
    0xfa8f05848d5b2c,
    0x12cc359a26dc860,
    0xc9c0ccacfcc35c,
    0x84baae34381da9,
    0xfffb20b25292cb,
    0xc488d068022413,
    0xb3e63735ca1923,
    0x9a3bd62bf285f5,
    0xf9bdd8b916e10c,
    0x101c4d8dd95d34f,
    0xbc4ea9ef978181f9,
    0x3258b67ddb934830,
    0xf85491d533f04eb4,
    0x3adbf8138d9c169a,
    0xebe89558cd2d5bb9,
    0x3122cd4c731b3531,
    0xaaf7a19716e9cf2d,
    0xb37bebc4b1ccb290,
    0x439619a2ae8d6b35,
    0x59ab8721d492595c,
    0x4c75d0503b75b804,
    0x4374f2a5789452ca,
    0x19a41e49a8579141,
    0xf2def5a38cf28510,
    0xe8561da594321f65,
    0x392c3ad8e6eee9b2,
    0x3583c65c7ebc094e,
    0xabfdd90e8ce93a0c,
    0x6ee262f3687934f3,
    0x485425b7fd5ce2db
  };

static uint64_t addcarry_cout_vectors[121] =
  {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x0,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x0,
    0x1
  };

static uint64_t subborrow_res_vectors[121] =
  {
    0x0,
    0xffffffffffffff1b,
    0xffffffffffffff2c,
    0xffffffffffffff2b,
    0xffffffffffffffde,
    0xffffffffffffffb9,
    0xffffffffffffff0a,
    0xffffffffffffff2b,
    0xffffffffffffffff,
    0xffffffffffffffdc,
    0xfffffffffffffffd,
    0xffffffffffffffde,
    0x2a,
    0xffffffffffffff94,
    0x1e,
    0xb5,
    0xffffffffffffffa1,
    0x50,
    0xffffffffffffffcf,
    0xffffffffffffffd7,
    0x73,
    0xffffffffffff3f1d,
    0xfffffffffffff7c1,
    0x76f,
    0xffffffffffffa86b,
    0xffffffffffff8a7f,
    0xffffffffffff518c,
    0xffffffffffffbfc7,
    0x6725,
    0xffffffffffff9a9a,
    0x2322,
    0xffffffffff2fa246,
    0xffffffffffd02400,
    0xffffffffffd1aac3,
    0xffffffffff2f5c4c,
    0xffffffffff8ae019,
    0xffffffffff72ed4a,
    0xffffffffff08937c,
    0xffffffffffb9b6da,
    0xffffffffffd169ef,
    0xffffffffff4931b8,
    0xffffffff13b26ee3,
    0xffffffff75641e6a,
    0xffffffff8859ab49,
    0xffffffffba80b875,
    0xffffffff2cb9fda6,
    0xffffffffe6ddd080,
    0xffffffffca7e3ebe,
    0xffffffff59ca60f1,
    0xffffffff77c15292,
    0xffffffff27818aa3,
    0x5b41a02d,
    0x4cd62aa1,
    0x4066443a,
    0xffffffff7164cee1,
    0xffffffff62bd512b,
    0xc8c3e4a,
    0xffffffff83a7e798,
    0x422049b9,
    0xfffffffffb45144f,
    0xffffffffcbe6ab15,
    0xb58ce10110,
    0xfabccf510b,
    0x72f528558d,
    0xee06c939ff,
    0xc69eff7240,
    0xd5a9ace957,
    0x9dc6bd5686,
    0x1f9303dc03,
    0x9b2c36b7d0,
    0x6c5759ddb8,
    0xffffffee4ab499ae,
    0xffffff97c171ffb3,
    0xffffffec2b165242,
    0xffffff0414463f49,
    0xffffff3a38eba8ea,
    0xffffff331edda062,
    0xffffff176c03524d,
    0xffffff6623dcee1e,
    0xffffff11827e91e0,
    0xffffffbaad357a3c,
    0xffffcb2ef0b387f1,
    0x4410f8a088ee,
    0xfffffe9182dff674,
    0xffff9b9bdd76f3bf,
    0xffffef671c3c50c3,
    0xfffff106fb6dd998,
    0xffff5f9356c3a352,
    0xffff7619c60f5e5a,
    0x715eda04ca3a,
    0xffff7ca541e4a51f,
    0xffdf20093255d8d2,
    0xa00c7a8069081a,
    0x7abbede3c1e1a8,
    0xffc926fc73f0be6f,
    0xc2e1d5d2c17d71,
    0xffeb295278567123,
    0x3459147af53b35,
    0xd10a623978f21,
    0xd4c32a0754fecc,
    0xffc691b9e0d683e5,
    0x54fab31ca7e53a7,
    0x28a17f8b4e9a564a,
    0xb396a518ec87eea6,
    0x562a478b36b9aaba,
    0xf216af2b0b7d0cd,
    0xe7729e0a2e451c2d,
    0xe6907f0ef3bb5adb,
    0xaed16420c8b91804,
    0xc0127667c72cc06d,
    0xbbdcdc2e89324e2e,
    0x4cdf447a7f59d99a,
    0xd9cbf7925c9b19be,
    0x6669623547edc1c7,
    0xd8da823c75ca8926,
    0xe7c9070e606fb5d9,
    0xd27a8a6240b536f8,
    0x26528d485d063b30,
    0xe641dc91fde55c6c,
    0x74f4559d3b23cf7,
    0xc9ce1942c208d9a1
  };

static uint64_t subborrow_cout_vectors[121] =
  {
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x0,
    0x0,
    0x1,
    0x0,
    0x1,
    0x1,
    0x0,
    0x1,
    0x1,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x0,
    0x1,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x1,
    0x1,
    0x0,
    0x0,
    0x1,
    0x0,
    0x1,
    0x0,
    0x0,
    0x0,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x0,
    0x1,
    0x1,
    0x0,
    0x1,
    0x0,
    0x1
  };
