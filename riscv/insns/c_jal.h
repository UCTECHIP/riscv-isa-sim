require_extension('C');
if (xlen == 32) {
  reg_t tmp = npc;
  set_pc(pc + insn.rvc_j_imm());
  WRITE_REG(X_RA, tmp);
} else { // c.addiw
  require(insn.rvc_rd() != 0);
  WRITE_RD(sext32(RVC_RS1 + insn.rvc_imm()));
}
p->perf_pipeline[0].stage_valid = p->perf_enable;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_INT_JUMP;
if (xlen == 32) {
  p->perf_pipeline[0].inst_rs1_enable = false;
  p->perf_pipeline[0].inst_rs1_type = PERF_INST_TYPE_INT;
  p->perf_pipeline[0].inst_rs1 = 0;
} else {
  p->perf_pipeline[0].inst_rs1_enable = true;
  p->perf_pipeline[0].inst_rs1_type = PERF_INST_TYPE_INT;
  p->perf_pipeline[0].inst_rs1 = insn.rvc_rs1();
}
p->perf_pipeline[0].inst_rs2_enable = false;
p->perf_pipeline[0].inst_rs2_type = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs2 = 0;
p->perf_pipeline[0].inst_rs3_enable = false;
p->perf_pipeline[0].inst_rs3_type = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs3 = 0;
p->perf_pipeline[0].inst_rd_enable = true;
p->perf_pipeline[0].inst_rd_type = PERF_INST_TYPE_INT;
if (xlen == 32) {
  p->perf_pipeline[0].inst_rd = X_RA;
} else {
  p->perf_pipeline[0].inst_rd = insn.rvc_rd();
}
