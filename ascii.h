uint16_t ascii_font_lookup_table[95] = {
  0,30,60,162,484,886,1256,1274,1348,1422,1464,1506,1572,1590,1608,1626,1844,1886,2024,2202,2248,2434,2656,2682,3084,3290,3320,3390,3416,3446,3472,3702,4196,4242,4492,4702,4836,4886,4928,5154,5204,5254,5368,5418,5444,5486,5520,5734,5876,6106,6256,6570,6604,6726,6752,6794,6836,6870,6904,6938,6956,6990,7016,7034,7052,7282,7512,7690,7920,8134,8264,8566,8696,8726,8804,8854,8920,9154,9284,9498,9712,9926,10048,10386,10428,10550,10576,10618,10660,10862,10896,10986,11004,11094,11200
};

uint8_t ascii_font[11158+42+18] = {

  // exclamation_point_polygon
  0,30,0,4,0,2,0,0,255,156,0,0,2,188,0,0,253,68,0,0,254,12,0,0,0,1,0,2,0,3,

  // double_quote_polygon
  0,30,0,4,0,2,255,56,2,188,255,56,1,44,0,200,2,188,0,200,1,44,0,0,0,1,0,2,0,3,

  // pound_polygon
  0,102,0,12,0,12,255,126,0,200,0,170,0,200,254,212,0,200,255,86,255,56,255,156,1,244,0,130,255,56,255,56,254,12,254,212,255,56,1,44,0,200,0,200,1,244,1,44,255,56,0,100,254,12,0,0,0,1,0,2,0,0,0,0,0,3,0,4,0,0,0,3,0,5,0,3,0,6,0,7,0,3,0,1,0,5,0,1,0,8,0,9,0,1,0,5,0,10,0,5,0,11,

  // dollar_sign_polygon
  1,66,0,39,0,40,0,0,0,0,0,0,253,168,0,0,2,88,0,0,2,188,255,178,2,78,0,78,2,78,0,150,2,48,0,212,2,0,1,4,1,194,1,34,1,122,1,44,1,44,255,106,2,48,255,44,2,0,254,252,1,194,254,222,1,122,254,212,1,44,254,222,0,222,254,252,0,150,255,44,0,88,255,106,0,40,255,178,0,10,0,78,255,246,0,150,255,216,0,212,255,168,1,4,255,106,1,34,255,34,1,44,254,212,1,34,254,134,1,4,254,62,0,212,254,0,0,150,253,208,0,78,253,178,0,0,253,68,255,178,253,178,255,106,253,208,255,44,254,0,254,252,254,62,254,222,254,134,254,212,254,212,0,0,0,1,0,2,0,0,0,3,0,2,0,2,0,4,0,5,0,2,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,4,0,11,0,11,0,12,0,12,0,13,0,13,0,14,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,0,0,21,0,0,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,26,0,25,0,27,0,26,0,28,0,27,0,29,0,28,0,30,0,29,0,31,0,30,0,1,0,31,0,1,0,32,0,33,0,1,0,34,0,33,0,35,0,34,0,36,0,35,0,37,0,36,0,38,0,37,

  // percent_polygon
  1,146,0,50,0,49,1,24,254,137,1,0,254,168,1,39,254,101,1,44,254,62,1,39,254,24,1,24,253,243,1,0,253,212,0,225,253,188,0,189,253,173,0,150,253,168,0,111,253,173,0,75,253,188,0,44,253,212,0,20,253,243,0,5,254,24,0,0,254,62,0,5,254,101,0,20,254,137,0,44,254,168,0,75,254,192,0,111,254,207,0,150,254,212,0,189,254,207,0,225,254,192,255,0,2,44,254,232,2,13,255,31,2,68,255,67,2,83,255,106,2,88,255,145,2,83,255,181,2,68,255,212,2,44,255,236,2,13,255,251,1,232,0,0,1,194,255,251,1,155,255,236,1,119,255,212,1,88,255,181,1,64,255,145,1,49,255,106,1,44,255,67,1,49,255,31,1,64,255,0,1,88,254,232,1,119,254,217,1,155,254,212,1,194,254,217,1,232,254,212,253,68,1,44,2,188,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,1,0,23,0,24,0,25,0,26,0,24,0,27,0,26,0,28,0,27,0,29,0,28,0,30,0,29,0,31,0,30,0,32,0,31,0,33,0,32,0,34,0,33,0,35,0,34,0,36,0,35,0,37,0,36,0,38,0,37,0,39,0,38,0,40,0,39,0,41,0,40,0,42,0,41,0,43,0,42,0,44,0,43,0,45,0,44,0,46,0,45,0,47,0,46,0,25,0,47,0,48,0,49,

  // ampersand_polygon
  1,114,0,45,0,46,0,0,2,188,255,204,2,181,0,52,2,181,0,100,2,161,0,141,2,129,0,173,2,88,0,193,2,40,0,200,1,244,0,200,1,44,0,193,0,248,0,173,0,200,0,141,0,159,0,100,0,127,0,52,0,107,0,0,0,100,255,178,0,90,255,165,0,84,255,106,0,60,0,208,253,251,1,44,253,68,1,44,254,212,0,173,253,168,0,141,253,127,0,100,253,95,0,52,253,75,0,0,253,68,255,204,253,75,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,254,212,255,56,254,222,255,134,254,252,255,206,255,44,0,12,255,83,0,250,255,63,1,42,255,56,1,94,255,56,1,244,255,63,2,40,255,83,2,88,255,115,2,129,255,156,2,161,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,7,0,8,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,14,0,15,0,15,0,16,0,16,0,17,0,18,0,16,0,19,0,18,0,20,0,18,0,18,0,21,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,26,0,25,0,27,0,26,0,28,0,27,0,29,0,28,0,30,0,29,0,31,0,30,0,32,0,31,0,33,0,32,0,34,0,33,0,35,0,34,0,36,0,35,0,17,0,36,0,16,0,37,0,38,0,37,0,39,0,38,0,40,0,39,0,41,0,40,0,42,0,41,0,43,0,42,0,44,0,43,0,1,0,44,

  // single_quote_polygon
  0,18,0,2,0,1,0,0,2,188,0,0,1,44,0,0,0,1,

  // parenthesis_left_polygon
  0,74,0,9,0,8,0,34,2,60,255,163,1,148,0,200,2,188,255,83,0,209,255,56,0,0,255,83,255,47,255,163,254,108,0,34,253,196,0,200,253,68,0,0,0,1,0,2,0,0,0,1,0,3,0,3,0,4,0,4,0,5,0,5,0,6,0,6,0,7,0,7,0,8,

  // parenthesis_right_polygon
  0,74,0,9,0,8,0,173,0,209,0,200,0,0,0,93,1,148,255,222,2,60,255,56,2,188,0,173,255,47,0,93,254,108,255,222,253,196,255,56,253,68,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,1,0,5,0,5,0,6,0,6,0,7,0,7,0,8,

  // asterisk_polygon
  0,42,0,6,0,3,0,0,2,88,0,0,0,0,0,212,0,88,255,44,2,0,255,44,0,88,0,212,2,0,0,0,0,1,0,2,0,3,0,4,0,5,

  // plus_polygon
  0,42,0,5,0,4,0,0,1,44,0,0,0,0,0,0,254,212,254,212,0,0,1,44,0,0,0,0,0,1,0,1,0,2,0,1,0,3,0,4,0,1,

  // comma_polygon
  0,66,0,8,0,7,255,208,253,75,0,0,253,95,255,156,253,68,0,41,253,127,0,73,253,168,0,93,253,216,0,100,254,12,0,100,254,212,0,0,0,1,0,2,0,0,0,1,0,3,0,3,0,4,0,4,0,5,0,5,0,6,0,6,0,7,

  // minus_polygon
  0,18,0,2,0,1,1,44,0,0,254,212,0,0,0,0,0,1,

  // period_polygon
  0,18,0,2,0,1,0,0,254,12,0,0,253,68,0,0,0,1,

  // forward_slash_polygon
  0,18,0,2,0,1,1,44,2,188,254,212,253,68,0,0,0,1,

  // zero_polygon
  0,218,0,26,0,27,1,44,1,144,254,212,254,112,1,34,1,222,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,1,144,254,222,1,222,254,252,2,38,255,44,2,100,255,106,2,148,255,178,2,178,0,0,2,188,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,0,0,0,1,0,0,0,2,0,3,0,0,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,1,0,14,0,15,0,1,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,2,0,25,

  // one_polygon
  0,42,0,5,0,4,0,0,2,188,255,56,1,244,0,0,253,68,0,200,253,68,255,56,253,68,0,0,0,1,0,0,0,2,0,2,0,3,0,4,0,2,

  // two_polygon
  0,138,0,17,0,16,0,150,2,148,0,78,2,178,0,212,2,100,1,4,2,38,1,34,1,222,1,44,1,144,1,34,1,66,1,4,0,250,254,212,253,68,1,44,253,68,0,0,2,188,255,178,2,178,255,106,2,148,255,44,2,100,254,252,2,38,254,222,1,222,254,212,1,144,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,1,0,10,0,10,0,11,0,11,0,12,0,12,0,13,0,13,0,14,0,14,0,15,0,15,0,16,

  // three_polygon
  0,178,0,22,0,21,0,150,253,108,0,212,253,156,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,1,4,253,218,1,34,254,34,1,44,254,112,1,44,255,56,1,34,255,134,1,4,255,206,0,212,0,12,0,150,0,60,0,78,0,90,0,0,0,100,1,44,2,188,254,212,2,188,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,1,0,10,0,10,0,11,0,11,0,12,0,13,0,12,0,13,0,14,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,21,0,20,

  // four_polygon
  0,46,0,5,0,5,0,200,2,188,254,212,255,56,0,200,255,56,1,44,255,56,0,200,253,68,0,0,0,1,0,0,0,2,0,1,0,2,0,2,0,3,0,2,0,4,

  // five_polygon
  0,186,0,23,0,22,1,44,255,56,1,34,255,134,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,1,4,255,206,0,212,0,12,0,150,0,60,0,78,0,90,0,0,0,100,254,212,0,100,254,212,2,188,1,44,2,188,0,0,0,1,0,0,0,2,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,1,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,21,0,22,0,21,

  // six_polygon
  0,222,0,27,0,27,1,44,255,56,1,44,254,112,1,34,255,134,1,4,255,206,0,212,0,12,0,150,0,60,0,78,0,90,0,0,0,100,255,178,0,90,255,106,0,60,255,44,0,12,254,252,255,206,254,222,255,134,0,200,2,188,254,212,255,56,254,212,254,112,254,222,254,34,254,252,253,218,255,44,253,156,255,106,253,108,255,178,253,78,0,0,253,68,0,78,253,78,0,150,253,108,0,212,253,156,1,4,253,218,1,34,254,34,0,0,0,1,0,0,0,2,0,2,0,3,0,3,0,4,0,4,0,5,0,5,0,6,0,6,0,7,0,7,0,8,0,8,0,9,0,9,0,10,0,10,0,11,0,11,0,12,0,13,0,11,0,12,0,14,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,21,0,21,0,22,0,22,0,23,0,23,0,24,0,24,0,25,0,25,0,26,0,26,0,1,

  // seven_polygon
  0,26,0,3,0,2,1,44,2,188,254,212,253,68,254,212,2,188,0,0,0,1,0,2,0,0,

  // eight_polygon
  1,146,0,49,0,50,255,178,2,178,255,106,2,148,0,0,2,188,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,1,34,1,222,1,44,1,144,1,34,1,66,1,4,0,250,0,212,0,188,0,150,0,140,0,78,0,110,0,0,0,100,255,178,0,110,255,106,0,140,255,44,0,188,254,252,0,250,254,222,1,66,254,212,1,144,254,222,1,222,254,252,2,38,255,44,2,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,1,34,255,134,1,44,255,56,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,254,212,255,56,254,222,255,134,254,252,255,206,255,44,0,12,255,106,0,60,255,178,0,90,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,1,0,23,0,24,0,14,0,25,0,24,0,26,0,25,0,27,0,26,0,28,0,27,0,29,0,28,0,29,0,30,0,31,0,30,0,32,0,31,0,33,0,32,0,34,0,33,0,35,0,34,0,36,0,35,0,37,0,36,0,38,0,37,0,39,0,38,0,40,0,39,0,41,0,40,0,42,0,41,0,43,0,42,0,44,0,43,0,45,0,44,0,46,0,45,0,47,0,46,0,48,0,47,0,14,0,48,

  // nine_polygon
  0,206,0,25,0,25,255,106,2,148,255,44,2,100,255,178,2,178,0,0,2,188,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,1,34,1,222,1,44,1,144,1,34,1,66,1,4,0,250,254,212,253,68,0,212,0,188,0,150,0,140,0,78,0,110,0,0,0,100,255,178,0,110,255,106,0,140,255,44,0,188,254,252,0,250,254,222,1,66,254,212,1,144,254,222,1,222,254,252,2,38,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,11,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,1,0,24,

  // colon_polygon
  0,30,0,4,0,2,0,0,255,56,0,0,254,112,0,0,0,200,0,0,1,144,0,0,0,1,0,2,0,3,

  // semi_colon_polygon
  0,70,0,9,0,7,0,0,0,200,0,0,1,144,255,56,254,112,255,108,254,119,255,156,254,139,255,197,254,171,255,229,254,212,255,249,255,4,0,0,255,56,0,0,0,1,0,2,0,3,0,3,0,4,0,4,0,5,0,5,0,6,0,6,0,7,0,7,0,8,

  // less_than_polygon
  0,26,0,3,0,2,254,212,0,0,1,44,254,212,1,44,1,44,0,0,0,1,0,0,0,2,

  // equals_polygon
  0,30,0,4,0,2,1,44,255,56,254,212,255,56,1,44,0,200,254,212,0,200,0,0,0,1,0,2,0,3,

  // greater_than_polygon
  0,26,0,3,0,2,1,44,0,0,254,212,254,212,254,212,1,44,0,0,0,1,0,0,0,2,

  // question_mark_polygon
  0,230,0,29,0,27,0,0,255,56,0,0,255,156,0,5,255,195,0,20,255,231,0,44,0,6,0,75,0,30,0,111,0,45,0,150,0,50,0,189,0,55,0,225,0,70,1,0,0,94,1,24,0,125,1,39,0,161,1,44,0,200,1,44,1,144,1,34,1,222,1,4,2,38,0,212,2,100,0,150,2,148,0,78,2,178,0,0,2,188,255,178,2,178,255,106,2,148,255,44,2,100,254,252,2,38,254,222,1,222,254,212,1,144,0,0,253,68,0,0,254,12,0,0,0,1,0,2,0,1,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,7,0,8,0,8,0,9,0,9,0,10,0,10,0,11,0,11,0,12,0,12,0,13,0,14,0,13,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,21,0,21,0,22,0,22,0,23,0,23,0,24,0,24,0,25,0,25,0,26,0,27,0,28,

  // at_symbol_polygon
  1,238,0,61,0,61,255,106,253,108,255,178,253,78,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,254,212,0,200,254,222,1,22,254,252,1,94,255,44,1,156,255,106,1,203,255,178,1,234,0,0,1,244,0,78,1,234,0,150,1,203,0,212,1,156,1,4,1,94,1,34,1,22,1,44,0,200,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,115,0,141,255,83,0,100,255,156,0,173,255,204,0,193,0,0,0,200,0,52,0,193,0,100,0,173,0,141,0,141,0,173,0,100,0,193,0,52,0,200,0,0,0,200,255,56,0,193,255,4,0,173,254,212,0,141,254,171,0,100,254,139,0,52,254,119,0,0,254,112,255,204,254,119,255,156,254,139,255,115,254,171,255,83,254,212,255,63,255,4,255,56,255,56,255,63,255,108,255,83,255,156,255,115,255,197,255,156,255,229,255,204,255,249,0,0,0,0,0,52,255,249,0,100,255,229,0,141,255,197,0,173,255,156,0,193,255,108,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,18,0,19,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,1,0,25,0,26,0,27,0,28,0,26,0,29,0,28,0,30,0,29,0,31,0,30,0,32,0,31,0,33,0,32,0,34,0,33,0,35,0,34,0,36,0,35,0,36,0,37,0,38,0,37,0,39,0,38,0,40,0,39,0,41,0,40,0,42,0,41,0,43,0,42,0,44,0,43,0,45,0,44,0,46,0,45,0,47,0,46,0,48,0,47,0,49,0,48,0,50,0,49,0,51,0,50,0,52,0,51,0,53,0,52,0,54,0,53,0,55,0,54,0,56,0,55,0,57,0,56,0,58,0,57,0,59,0,58,0,60,0,59,0,37,0,60,

  // A_polygon
  0,46,0,5,0,5,0,193,255,56,1,44,253,68,255,63,255,56,0,0,2,188,254,212,253,68,0,0,0,1,0,0,0,2,0,3,0,0,0,2,0,3,0,4,0,2,

  // B_polygon
  0,250,0,30,0,31,0,200,1,244,0,193,2,40,0,200,1,44,0,193,0,248,0,173,0,200,0,141,0,159,0,100,0,127,0,52,0,107,0,0,0,100,254,212,0,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,1,34,255,134,1,44,255,56,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,254,212,253,68,254,212,2,188,0,0,2,188,0,52,2,181,0,100,2,161,0,141,2,129,0,173,2,88,0,0,0,1,0,2,0,0,0,2,0,3,0,3,0,4,0,4,0,5,0,5,0,6,0,6,0,7,0,7,0,8,0,8,0,9,0,10,0,8,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,15,0,16,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,22,0,23,0,23,0,9,0,24,0,9,0,25,0,24,0,26,0,25,0,27,0,26,0,28,0,27,0,29,0,28,0,1,0,29,

  // C_polygon
  0,210,0,26,0,25,254,212,1,144,254,212,254,112,254,222,1,222,254,252,2,38,255,44,2,100,255,106,2,148,255,178,2,178,0,0,2,188,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,1,34,1,222,1,44,1,144,254,222,254,34,254,252,253,218,255,44,253,156,255,106,253,108,255,178,253,78,0,0,253,68,0,78,253,78,0,150,253,108,0,212,253,156,1,4,253,218,1,34,254,34,1,44,254,112,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,1,0,14,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,21,0,21,0,22,0,22,0,23,0,23,0,24,0,24,0,25,

  // D_polygon
  0,134,0,16,0,16,1,44,1,144,1,34,1,222,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,254,212,253,68,254,212,2,188,0,0,2,188,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,0,0,0,1,0,0,0,2,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,1,0,15,

  // E_polygon
  0,50,0,6,0,5,254,212,0,100,0,100,0,100,254,212,253,68,254,212,2,188,1,44,2,188,1,44,253,68,0,0,0,1,0,0,0,2,0,3,0,0,0,4,0,3,0,2,0,5,

  // F_polygon
  0,42,0,5,0,4,254,212,0,100,0,100,0,100,254,212,253,68,254,212,2,188,1,44,2,188,0,0,0,1,0,0,0,2,0,3,0,0,0,4,0,3,

  // G_polygon
  0,226,0,28,0,27,254,212,1,144,254,212,254,112,254,222,1,222,254,252,2,38,255,44,2,100,255,106,2,148,255,178,2,178,0,0,2,188,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,1,34,1,222,1,44,1,144,254,222,254,34,254,252,253,218,255,44,253,156,255,106,253,108,255,178,253,78,0,0,253,68,0,78,253,78,0,150,253,108,0,212,253,156,1,4,253,218,1,34,254,34,1,44,254,112,1,44,0,100,0,0,0,100,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,1,0,14,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,21,0,21,0,22,0,22,0,23,0,23,0,24,0,24,0,25,0,25,0,26,0,26,0,27,

  // H_polygon
  0,50,0,6,0,5,254,212,0,100,254,212,253,68,1,44,0,100,254,212,2,188,1,44,253,68,1,44,2,188,0,0,0,1,0,0,0,2,0,3,0,0,0,2,0,4,0,5,0,2,

  // I_polygon
  0,50,0,6,0,5,0,0,253,68,1,44,253,68,0,0,2,188,254,212,2,188,1,44,2,188,254,212,253,68,0,0,0,1,0,2,0,0,0,3,0,2,0,2,0,4,0,5,0,0,

  // J_polygon
  0,114,0,14,0,13,1,34,254,34,1,44,254,112,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,1,44,2,188,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,1,

  // K_polygon
  0,50,0,6,0,5,254,212,2,188,254,212,255,56,254,212,253,68,255,89,0,0,1,44,253,68,1,44,2,188,0,0,0,1,0,1,0,2,0,1,0,3,0,4,0,3,0,3,0,5,

  // L_polygon
  0,26,0,3,0,2,254,212,2,188,254,212,253,68,1,44,253,68,0,0,0,1,0,1,0,2,

  // M_polygon
  0,42,0,5,0,4,254,212,253,68,254,212,2,188,0,0,0,0,1,44,2,188,1,44,253,68,0,0,0,1,0,1,0,2,0,2,0,3,0,3,0,4,

  // N_polygon
  0,34,0,4,0,3,254,212,253,68,254,212,2,188,1,44,253,68,1,44,2,188,0,0,0,1,0,1,0,2,0,3,0,2,

  // O_polygon
  0,214,0,26,0,26,0,0,2,188,255,178,2,178,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,1,34,1,222,1,44,1,144,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,254,212,1,144,254,222,1,222,254,252,2,38,255,44,2,100,255,106,2,148,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,7,0,8,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,20,0,21,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,1,0,25,

  // P_polygon
  0,142,0,17,0,17,0,212,2,100,0,150,2,148,1,4,2,38,1,34,1,222,1,44,1,144,1,44,0,100,1,34,0,22,1,4,255,206,0,212,255,144,0,150,255,96,0,78,255,66,0,0,255,56,254,212,255,56,254,212,2,188,254,212,253,68,0,0,2,188,0,78,2,178,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,4,0,5,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,11,0,12,0,12,0,13,0,14,0,12,0,13,0,15,0,16,0,15,0,1,0,16,

  // Q_polygon
  0,230,0,28,0,28,254,222,254,34,254,252,253,218,254,212,254,112,254,212,1,144,254,222,1,222,254,252,2,38,255,44,2,100,255,106,2,148,255,178,2,178,0,0,2,188,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,1,34,1,222,1,44,1,144,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,1,44,253,68,0,0,254,112,0,0,0,1,0,2,0,0,0,2,0,3,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,15,0,16,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,1,0,25,0,26,0,19,0,19,0,27,

  // R_polygon
  0,150,0,18,0,18,254,212,253,78,254,212,255,56,0,0,255,56,0,78,255,66,1,44,253,68,0,150,255,96,0,212,255,144,1,4,255,206,1,34,0,22,1,44,0,100,1,44,1,144,1,34,1,222,1,4,2,38,0,212,2,100,0,150,2,148,0,78,2,178,0,0,2,188,254,212,2,188,0,0,0,1,0,2,0,1,0,2,0,3,0,4,0,2,0,3,0,5,0,5,0,6,0,6,0,7,0,7,0,8,0,8,0,9,0,9,0,10,0,10,0,11,0,11,0,12,0,12,0,13,0,13,0,14,0,14,0,15,0,15,0,16,0,17,0,16,0,1,0,17,

  // S_polygon
  1,58,0,39,0,38,1,44,1,144,1,34,1,222,1,4,2,38,0,212,2,100,0,150,2,148,0,78,2,178,0,0,2,188,255,178,2,178,255,106,2,148,255,44,2,100,254,252,2,38,254,222,1,222,254,212,1,144,254,222,1,66,254,252,0,250,255,44,0,188,255,106,0,140,255,178,0,110,0,0,0,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,1,34,255,134,1,44,255,56,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,254,212,255,56,0,0,0,1,0,1,0,2,0,2,0,3,0,3,0,4,0,4,0,5,0,5,0,6,0,6,0,7,0,7,0,8,0,8,0,9,0,9,0,10,0,10,0,11,0,11,0,12,0,12,0,13,0,13,0,14,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,26,0,25,0,27,0,26,0,28,0,27,0,29,0,28,0,30,0,29,0,31,0,30,0,32,0,31,0,33,0,32,0,34,0,33,0,35,0,34,0,36,0,35,0,37,0,36,0,38,0,37,

  // T_polygon
  0,34,0,4,0,3,0,0,2,188,0,0,253,68,254,212,2,188,1,44,2,188,0,0,0,1,0,2,0,0,0,0,0,3,

  // U_polygon
  0,122,0,15,0,14,1,34,254,34,1,44,254,112,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,254,212,2,188,1,44,2,188,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,12,0,13,0,14,0,1,

  // V_polygon
  0,26,0,3,0,2,254,212,2,188,0,0,253,68,1,44,2,188,0,0,0,1,0,1,0,2,

  // W_polygon
  0,42,0,5,0,4,1,44,253,68,1,44,2,188,0,0,0,0,254,212,253,68,254,212,2,188,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,

  // X_polygon
  0,42,0,5,0,4,254,212,2,188,0,0,0,0,1,44,253,68,1,44,2,188,254,212,253,68,0,0,0,1,0,1,0,2,0,3,0,1,0,1,0,4,

  // Y_polygon
  0,34,0,4,0,3,0,0,0,0,1,44,2,188,254,212,2,188,0,0,253,68,0,0,0,1,0,2,0,0,0,0,0,3,

  // Z_polygon
  0,34,0,4,0,3,254,212,253,68,1,44,253,68,1,44,2,188,254,212,2,188,0,0,0,1,0,2,0,0,0,3,0,2,

  // bracket_left_polygon
  0,34,0,4,0,3,255,56,2,188,255,56,253,68,0,200,2,188,0,200,253,68,0,0,0,1,0,2,0,0,0,1,0,3,

  // back_slash_polygon
  0,18,0,2,0,1,254,212,2,188,1,44,253,68,0,0,0,1,

  // bracket_right_polygon
  0,34,0,4,0,3,255,56,2,188,0,200,2,188,0,200,253,68,255,56,253,68,0,0,0,1,0,1,0,2,0,2,0,3,

  // caret_polygon
  0,26,0,3,0,2,0,0,2,188,1,44,0,200,254,212,0,200,0,0,0,1,0,0,0,2,

  // underscore_polygon
  0,18,0,2,0,1,254,212,253,68,1,44,253,68,0,0,0,1,

  // backtick_polygon
  0,18,0,2,0,1,255,56,2,188,0,0,1,244,0,0,0,1,

  // a_polygon
  0,230,0,28,0,28,254,212,255,56,254,212,254,112,254,222,255,134,254,252,255,206,255,44,0,12,255,106,0,60,255,178,0,90,0,0,0,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,1,34,255,134,1,44,255,56,1,44,0,100,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,1,44,253,68,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,13,0,15,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,26,0,25,0,1,0,26,0,15,0,27,

  // b_polygon
  0,230,0,28,0,28,254,212,254,112,254,222,254,34,254,212,253,68,254,212,255,56,254,222,255,134,254,252,255,206,255,44,0,12,255,106,0,60,255,178,0,90,0,0,0,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,1,34,255,134,1,44,255,56,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,212,2,188,0,0,0,1,0,2,0,0,0,0,0,3,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,15,0,16,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,26,0,25,0,1,0,26,0,3,0,27,

  // c_polygon
  0,178,0,22,0,21,254,212,254,112,254,222,254,34,254,212,255,56,254,222,255,134,254,252,255,206,255,44,0,12,255,106,0,60,255,178,0,90,0,0,0,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,254,252,253,218,255,44,253,156,255,106,253,108,255,178,253,78,0,0,253,68,0,78,253,78,0,150,253,108,0,212,253,156,1,4,253,218,0,0,0,1,0,0,0,2,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,1,0,13,0,13,0,14,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,21,

  // d_polygon
  0,230,0,28,0,28,0,150,0,60,0,212,0,12,0,78,0,90,0,0,0,100,255,178,0,90,255,106,0,60,255,44,0,12,254,252,255,206,254,222,255,134,254,212,255,56,254,212,254,112,254,222,254,34,254,252,253,218,255,44,253,156,255,106,253,108,255,178,253,78,0,0,253,68,0,78,253,78,0,150,253,108,0,212,253,156,1,4,253,218,1,34,254,34,1,44,254,112,1,44,253,68,1,44,255,56,1,34,255,134,1,4,255,206,1,44,2,188,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,9,0,10,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,22,0,24,0,25,0,24,0,26,0,25,0,1,0,26,0,24,0,27,

  // e_polygon
  0,214,0,26,0,26,254,252,253,218,255,44,253,156,254,222,254,34,254,212,254,112,254,212,255,56,1,44,255,56,254,222,255,134,254,252,255,206,255,44,0,12,255,106,0,60,255,178,0,90,0,0,0,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,1,34,255,134,255,106,253,108,255,178,253,78,0,0,253,68,0,78,253,78,0,150,253,108,0,212,253,156,1,4,253,218,1,34,254,34,1,44,254,112,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,4,0,5,0,6,0,4,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,5,0,16,0,1,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,21,0,21,0,22,0,22,0,23,0,23,0,24,0,24,0,25,

  // f_polygon
  0,130,0,16,0,15,254,212,0,100,254,212,253,68,0,0,0,100,254,212,1,144,254,222,1,222,254,252,2,38,255,44,2,100,255,106,2,148,255,178,2,178,0,0,2,188,0,78,2,178,0,150,2,148,0,212,2,100,1,4,2,38,1,34,1,222,1,44,1,144,0,0,0,1,0,0,0,2,0,3,0,0,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,

  // g_polygon
  1,46,0,37,0,37,0,100,253,68,0,152,253,75,255,156,253,68,255,104,253,75,255,56,253,95,255,15,253,127,254,239,253,168,0,200,253,95,0,241,253,127,1,17,253,168,1,37,253,216,1,44,254,12,1,44,255,156,1,34,255,234,1,34,255,78,1,4,255,6,0,212,254,200,0,150,254,152,0,78,254,122,0,0,254,112,255,178,254,122,255,106,254,152,255,44,254,200,254,252,255,6,254,222,255,78,254,212,255,156,254,222,255,234,254,252,0,50,255,44,0,112,255,106,0,160,255,178,0,190,0,0,0,200,0,78,0,190,0,150,0,160,0,212,0,112,1,4,0,50,1,44,0,200,0,0,0,1,0,2,0,0,0,2,0,3,0,3,0,4,0,4,0,5,0,5,0,6,0,1,0,7,0,7,0,8,0,8,0,9,0,9,0,10,0,10,0,11,0,12,0,11,0,12,0,13,0,14,0,12,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,26,0,25,0,27,0,26,0,28,0,27,0,29,0,28,0,30,0,29,0,31,0,30,0,32,0,31,0,33,0,32,0,34,0,33,0,35,0,34,0,13,0,35,0,36,0,12,

  // h_polygon
  0,130,0,16,0,15,1,44,255,56,1,44,253,68,1,34,255,134,1,4,255,206,0,212,0,12,0,150,0,60,0,78,0,90,0,0,0,100,255,178,0,90,255,106,0,60,255,44,0,12,254,252,255,206,254,222,255,134,254,212,255,56,254,212,2,188,254,212,253,68,0,0,0,1,0,0,0,2,0,2,0,3,0,3,0,4,0,4,0,5,0,5,0,6,0,6,0,7,0,7,0,8,0,8,0,9,0,9,0,10,0,10,0,11,0,11,0,12,0,12,0,13,0,14,0,13,0,13,0,15,

  // i_polygon
  0,30,0,4,0,2,0,0,1,44,0,0,1,144,0,0,0,100,0,0,253,68,0,0,0,1,0,2,0,3,

  // j_polygon
  0,78,0,10,0,8,0,0,1,44,0,0,1,144,0,0,0,100,0,0,254,112,255,246,254,34,255,216,253,218,255,168,253,156,255,106,253,108,255,34,253,78,254,212,253,68,0,0,0,1,0,2,0,3,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,

  // k_polygon
  0,50,0,6,0,5,254,212,2,188,254,212,254,112,254,212,253,48,255,163,255,29,1,44,253,68,1,44,0,100,0,0,0,1,0,1,0,2,0,3,0,1,0,4,0,3,0,5,0,3,

  // l_polygon
  0,66,0,8,0,7,0,27,253,168,0,59,253,127,0,7,253,216,0,0,254,12,0,0,2,188,0,100,253,95,0,148,253,75,0,200,253,68,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,1,0,5,0,5,0,6,0,6,0,7,

  // m_polygon
  0,234,0,29,0,28,255,212,0,56,255,181,0,80,255,236,0,25,255,251,255,245,0,0,255,206,0,5,255,245,0,20,0,25,0,44,0,56,0,75,0,80,0,111,0,95,0,150,0,100,0,189,0,95,0,225,0,80,1,0,0,56,1,24,0,25,1,39,255,245,1,44,255,206,1,44,253,68,0,0,253,68,255,145,0,95,255,106,0,100,255,67,0,95,255,31,0,80,255,0,0,56,254,232,0,25,254,217,255,245,254,212,255,206,254,212,253,68,254,212,0,100,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,4,0,18,0,1,0,19,0,19,0,20,0,20,0,21,0,21,0,22,0,22,0,23,0,23,0,24,0,24,0,25,0,25,0,26,0,26,0,27,0,28,0,26,

  // n_polygon
  0,130,0,16,0,15,254,212,0,100,254,212,255,56,254,212,253,68,254,222,255,134,254,252,255,206,255,44,0,12,255,106,0,60,255,178,0,90,0,0,0,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,1,34,255,134,1,44,255,56,1,44,253,68,0,0,0,1,0,1,0,2,0,3,0,1,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,14,0,15,

  // o_polygon
  0,214,0,26,0,26,255,178,253,78,0,0,253,68,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,254,212,255,56,254,222,255,134,254,252,255,206,255,44,0,12,255,106,0,60,255,178,0,90,0,0,0,100,0,78,0,90,0,150,0,60,0,212,0,12,1,4,255,206,1,34,255,134,1,44,255,56,1,44,254,112,1,34,254,34,1,4,253,218,0,212,253,156,0,150,253,108,0,78,253,78,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,19,0,20,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,1,0,25,

  // p_polygon
  0,214,0,26,0,26,254,212,0,200,254,212,255,156,254,212,253,68,254,222,255,78,254,222,255,234,254,252,0,50,255,44,0,112,255,106,0,160,255,178,0,190,0,0,0,200,0,78,0,190,0,150,0,160,0,212,0,112,1,4,0,50,1,34,255,234,1,44,255,156,1,34,255,78,1,4,255,6,0,212,254,200,0,150,254,152,0,78,254,122,0,0,254,112,255,178,254,122,255,106,254,152,255,44,254,200,254,252,255,6,0,0,0,1,0,1,0,2,0,1,0,3,0,4,0,1,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,3,0,25,

  // q_polygon
  0,214,0,26,0,26,0,0,0,200,0,78,0,190,255,178,0,190,255,106,0,160,255,44,0,112,254,252,0,50,254,222,255,234,254,212,255,156,254,222,255,78,254,252,255,6,255,44,254,200,255,106,254,152,255,178,254,122,0,0,254,112,0,78,254,122,0,150,254,152,0,212,254,200,1,4,255,6,1,34,255,78,1,44,255,156,1,34,255,234,1,4,0,50,0,212,0,112,0,150,0,160,1,44,0,200,1,44,253,68,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,1,0,23,0,24,0,19,0,19,0,25,

  // r_polygon
  0,122,0,15,0,14,0,150,0,60,0,78,0,90,0,212,0,12,1,4,255,206,1,34,255,134,1,44,255,56,0,0,0,100,255,178,0,90,255,106,0,60,255,44,0,12,254,252,255,206,254,222,255,134,254,212,255,56,254,212,0,100,254,212,253,68,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,1,0,6,0,6,0,7,0,7,0,8,0,8,0,9,0,9,0,10,0,10,0,11,0,11,0,12,0,13,0,12,0,12,0,14,

  // s_polygon
  1,82,0,42,0,41,0,152,0,93,0,100,0,100,0,200,0,73,0,241,0,41,1,17,0,0,1,37,255,208,1,44,255,156,255,156,0,100,255,104,0,93,255,56,0,73,255,15,0,41,254,239,0,0,254,219,255,208,254,212,255,156,254,219,255,104,254,239,255,56,255,9,255,22,255,15,255,15,255,56,254,239,255,104,254,219,255,156,254,212,0,100,254,212,0,152,254,205,0,200,254,185,0,241,254,153,1,17,254,112,1,37,254,64,1,44,254,12,1,37,253,216,1,17,253,168,0,241,253,127,0,200,253,95,0,152,253,75,0,100,253,68,0,0,253,68,255,156,253,68,255,104,253,75,255,56,253,95,255,15,253,127,254,239,253,168,254,219,253,216,254,212,254,12,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,1,0,7,0,7,0,8,0,8,0,9,0,9,0,10,0,10,0,11,0,11,0,12,0,12,0,13,0,13,0,14,0,14,0,15,0,15,0,16,0,16,0,17,0,17,0,18,0,18,0,19,0,19,0,20,0,20,0,21,0,22,0,21,0,23,0,22,0,24,0,23,0,25,0,24,0,26,0,25,0,27,0,26,0,28,0,27,0,29,0,28,0,30,0,29,0,31,0,30,0,32,0,31,0,33,0,32,0,33,0,34,0,34,0,35,0,36,0,35,0,37,0,36,0,38,0,37,0,39,0,38,0,40,0,39,0,41,0,40,

  // t_polygon
  0,42,0,5,0,4,254,212,0,100,0,0,0,100,0,0,253,68,0,0,2,188,1,44,0,100,0,0,0,1,0,1,0,2,0,3,0,1,0,1,0,4,

  // u_polygon
  0,122,0,15,0,14,1,4,253,218,1,34,254,34,0,212,253,156,0,150,253,108,0,78,253,78,0,0,253,68,255,178,253,78,255,106,253,108,255,44,253,156,254,252,253,218,254,222,254,34,254,212,254,112,254,212,0,100,1,44,254,112,1,44,0,100,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,9,0,8,0,10,0,9,0,11,0,10,0,12,0,11,0,1,0,13,0,14,0,13,

  // v_polygon
  0,26,0,3,0,2,0,0,253,68,1,44,0,100,254,212,0,100,0,0,0,1,0,2,0,0,

  // w_polygon
  0,42,0,5,0,4,254,212,253,68,0,0,255,56,254,212,0,100,1,44,253,68,1,44,0,100,0,0,0,1,0,2,0,0,0,1,0,3,0,3,0,4,

  // x_polygon
  0,42,0,5,0,4,1,44,0,0,0,0,254,162,254,212,0,0,254,212,253,68,1,44,253,68,0,0,0,1,0,2,0,1,0,1,0,3,0,1,0,4,

  // y_polygon
  0,202,0,25,0,24,0,212,253,156,1,4,253,218,0,150,253,108,0,78,253,78,0,0,253,68,254,212,253,68,1,34,254,34,1,44,254,112,1,44,255,156,1,44,0,100,1,34,255,78,1,25,255,56,1,4,255,6,0,212,254,200,0,150,254,152,0,78,254,122,0,0,254,112,255,178,254,122,255,106,254,152,255,44,254,200,254,252,255,6,254,231,255,56,254,222,255,78,254,212,255,156,254,212,0,100,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,1,0,6,0,6,0,7,0,8,0,7,0,9,0,8,0,10,0,8,0,11,0,10,0,12,0,11,0,13,0,12,0,14,0,13,0,15,0,14,0,16,0,15,0,17,0,16,0,18,0,17,0,19,0,18,0,20,0,19,0,21,0,20,0,22,0,21,0,23,0,22,0,24,0,23,

  // z_polygon
  0,34,0,4,0,3,254,212,0,100,1,44,0,100,254,212,253,68,1,44,253,68,0,0,0,1,0,1,0,2,0,2,0,3,

  // left_brace_polygon
  0,90,0,11,0,10,255,176,255,47,255,236,254,108,255,166,255,156,254,212,0,0,255,166,0,100,255,176,0,209,255,236,1,148,0,76,2,60,0,200,2,188,0,76,253,196,0,200,253,68,0,0,0,1,0,2,0,0,0,3,0,2,0,3,0,4,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,1,0,9,0,9,0,10,

  // pipe_polygon
  0,18,0,2,0,1,0,0,2,188,0,0,253,68,0,0,0,1,

  // right_brace_polygon
  0,90,0,11,0,10,0,90,255,156,0,80,255,47,1,44,0,0,0,90,0,100,0,80,0,209,0,20,1,148,255,180,2,60,255,56,2,188,0,20,254,108,255,180,253,196,255,56,253,68,0,0,0,1,0,2,0,0,0,2,0,3,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,1,0,8,0,8,0,9,0,9,0,10,

  // tilde_polygon
  0,106,0,13,0,12,255,212,0,109,255,161,0,177,0,0,0,0,0,44,255,147,0,95,255,79,0,150,255,56,0,204,255,79,1,0,255,147,1,44,0,0,255,106,0,200,255,52,0,177,255,0,0,109,254,212,0,0,0,0,0,1,0,2,0,0,0,3,0,2,0,4,0,3,0,5,0,4,0,6,0,5,0,7,0,6,0,8,0,7,0,1,0,9,0,9,0,10,0,10,0,11,0,11,0,12,

  // empty
  0,18,0,2,0,1,255,156,249,92,0,100,249,92,0,0,0,1
};

int32_t lookup_ascii_address(char c){
  if(c <= 32){
    return -1;
  }
  else if(c >= 127){
    return -1;
  }
  else{
    return ascii_font_lookup_table[c-33];
  }
}

void print_lookup_table(){
  uint32_t current_index = 0;
  uint8_t num_characters = 0;

  while(current_index < 11158+42+18){
    uint8_t num_bytes_high = ascii_font[current_index+0];
    uint8_t num_bytes_low  = ascii_font[current_index+1];

    uint16_t num_bytes = (num_bytes_high << 8) + num_bytes_low;

    //debug(current_index);
    //debug(",");

    current_index  += num_bytes;
    num_characters += 1;
  }
  //debugln(" ");
  debug("NUM_CHARS: ");
  debugln(num_characters);
}