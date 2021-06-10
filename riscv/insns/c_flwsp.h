require_extension('C');
if (xlen == 32) {
  require_extension('F');
  require_fp;
  WRITE_FRD(f32(MMU.load_uint32(RVC_SP + insn.rvc_lwsp_imm())));
} else { // c.ldsp
  require(insn.rvc_rd() != 0);
  WRITE_RD(MMU.load_int64(RVC_SP + insn.rvc_ldsp_imm()));
}
p->perf_pipeline[0].stage_valid = p->perf_enable;
p->perf_pipeline[0].inst_class = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_class_offset = (xlen == 32) ? PERF_INST_TYPE_FLOAT_LOAD : PERF_INST_TYPE_INT_LOAD;
p->perf_pipeline[0].inst_rs1_enable = true;
p->perf_pipeline[0].inst_rs1_type = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs1 = RVC_SP;
p->perf_pipeline[0].inst_rs2_enable = false;
p->perf_pipeline[0].inst_rs2_type = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs2 = 0;
p->perf_pipeline[0].inst_rs3_enable = false;
p->perf_pipeline[0].inst_rs3_type = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs3 = 0;
p->perf_pipeline[0].inst_rd_enable = true;
p->perf_pipeline[0].inst_rd_type = (xlen == 32) ? PERF_INST_TYPE_FLOAT : PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rd = insn.rd();
