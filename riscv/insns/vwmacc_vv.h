// vwmacc.vv vd, vs2, vs1
VI_CHECK_DSS(true);
VI_VV_LOOP_WIDEN
({
  VI_WIDE_OP_AND_ASSIGN(vs2, vs1, vd_w, *, +, int);
})
p->perf_pipeline[0].stage_valid = false;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_VECTOR_VX_MUL;
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
