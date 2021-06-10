// vfncvt.rod.f.f.v vd, vs2, vm
VI_VFP_CVT_SCALE
({
  ;
},
{
  softfloat_roundingMode = softfloat_round_odd;
  auto vs2 = P.VU.elt<float32_t>(rs2_num, i);
  P.VU.elt<float16_t>(rd_num, i, true) = f32_to_f16(vs2);
},
{
  softfloat_roundingMode = softfloat_round_odd;
  auto vs2 = P.VU.elt<float64_t>(rs2_num, i);
  P.VU.elt<float32_t>(rd_num, i, true) = f64_to_f32(vs2);
},
{
  ;
},
{
  require(p->supports_extension(EXT_ZFH));
},
{
  require(p->supports_extension('F'));
},
false, (P.VU.vsew >= 16))
p->perf_pipeline[0].stage_valid = false;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_VECTOR_VF_FP2FP;
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
