// vfcvt.f.x.v vd, vd2, vm
VI_VFP_VF_LOOP
({
  auto vs2_i = P.VU.elt<int16_t>(rs2_num, i);
  vd = i32_to_f16(vs2_i);
},
{
  auto vs2_i = P.VU.elt<int32_t>(rs2_num, i);
  vd = i32_to_f32(vs2_i);
},
{
  auto vs2_i = P.VU.elt<int64_t>(rs2_num, i);
  vd = i64_to_f64(vs2_i);
})
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
