// vfmv_vf vd, vs1
require_align(insn.rd(), P.VU.vflmul);
VI_VFP_COMMON
switch(P.VU.vsew) {
  case e16:
    for (reg_t i=P.VU.vstart; i<vl; ++i) {
      auto &vd = P.VU.elt<float16_t>(rd_num, i, true);
      auto rs1 = f16(READ_FREG(rs1_num));

      vd = rs1;
    }
    break;
  case e32:
    for (reg_t i=P.VU.vstart; i<vl; ++i) {
      auto &vd = P.VU.elt<float32_t>(rd_num, i, true);
      auto rs1 = f32(READ_FREG(rs1_num));

      vd = rs1;
    }
    break;
  case e64:
    for (reg_t i=P.VU.vstart; i<vl; ++i) {
      auto &vd = P.VU.elt<float64_t>(rd_num, i, true);
      auto rs1 = f64(READ_FREG(rs1_num));

      vd = rs1;
    }
    break;
}

P.VU.vstart = 0;
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
