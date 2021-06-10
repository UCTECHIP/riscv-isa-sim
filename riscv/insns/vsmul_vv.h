// vsmul.vv vd, vs2, vs1
VRM xrm = P.VU.get_vround_mode();
int64_t int_max = INT64_MAX >> (64 - P.VU.vsew);
int64_t int_min = INT64_MIN >> (64 - P.VU.vsew);
int64_t sign_mask = uint64_t(1) << (P.VU.vsew - 1);

VI_VV_LOOP
({
  int64_t vs1_sign;
  int64_t vs2_sign;
  int64_t result_sign;

  vs1_sign = vs1 & sign_mask;
  vs2_sign = vs2 & sign_mask;
  bool overflow = vs1 == vs2 && vs1 == int_min;

  int128_t result = (int128_t)vs1 * (int128_t)vs2;
  result_sign = (vs1_sign ^ vs2_sign) & sign_mask;

  // rounding
  INT_ROUNDING(result, xrm, sew - 1);
  // remove guard bits
  result = result >> (sew - 1);

  // saturation
  if (overflow) {
    result = int_max;
    P.VU.vxsat |= 1;
  }

  vd = result;
})
p->perf_pipeline[0].stage_valid = false;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_VECTOR_VXP_MUL;
p->perf_pipeline[0].inst_rs1_enable = true;
p->perf_pipeline[0].inst_rs1_type = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_rs1 = insn.rs1();
p->perf_pipeline[0].inst_rs2_enable = true;
p->perf_pipeline[0].inst_rs2_type = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_rs2 = insn.rs2();
p->perf_pipeline[0].inst_rs3_enable = false;
p->perf_pipeline[0].inst_rs3_type = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_rs3 = insn.rd();
p->perf_pipeline[0].inst_rd_enable = true;
p->perf_pipeline[0].inst_rd_type = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_rd = insn.rd();
