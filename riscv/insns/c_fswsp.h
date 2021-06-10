require_extension('C');
if (xlen == 32) {
  require_extension('F');
  require_fp;
  MMU.store_uint32(RVC_SP + insn.rvc_swsp_imm(), RVC_FRS2.v[0]);
} else { // c.sdsp
  MMU.store_uint64(RVC_SP + insn.rvc_sdsp_imm(), RVC_RS2);
}
p->perf_pipeline[0].stage_valid = p->perf_enable;
p->perf_pipeline[0].inst_class = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_class_offset = (xlen == 32) ? PERF_INST_TYPE_FLOAT_STORE : PERF_INST_TYPE_INT_STORE;
p->perf_pipeline[0].inst_rs1_enable = true;
p->perf_pipeline[0].inst_rs1_type = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs1 = RVC_SP;
p->perf_pipeline[0].inst_rs2_enable = true;
p->perf_pipeline[0].inst_rs2_type = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs2 = insn.rvc_rs2();
p->perf_pipeline[0].inst_rs3_enable = false;
p->perf_pipeline[0].inst_rs3_type = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs3 = 0;
p->perf_pipeline[0].inst_rd_enable = false;
p->perf_pipeline[0].inst_rd_type = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rd = 0;
