// vfwcvt.f.x.v vd, vs2, vm
VI_VFP_CVT_SCALE
({
  auto vs2 = P.VU.elt<int8_t>(rs2_num, i);
  P.VU.elt<float16_t>(rd_num, i, true) = i32_to_f16(vs2);
},
{
  auto vs2 = P.VU.elt<int16_t>(rs2_num, i);
  P.VU.elt<float32_t>(rd_num, i, true) = i32_to_f32(vs2);
},
{
  auto vs2 = P.VU.elt<int32_t>(rs2_num, i);
  P.VU.elt<float64_t>(rd_num, i, true) = i32_to_f64(vs2);
},
{
  require(p->supports_extension(EXT_ZFH));
},
{
  require(p->supports_extension('F'));
},
{
  require(p->supports_extension('D'));
},
true, (P.VU.vsew >= 8))
p->perf_pipeline[0].stage_valid = false;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_VECTOR_VF_INT2FP;
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
