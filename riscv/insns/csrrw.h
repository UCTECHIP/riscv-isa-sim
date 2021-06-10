int csr = validate_csr(insn.csr(), true);
if(csr != 0x8FF) {
  reg_t old = p->get_csr(csr, insn, true);
  p->set_csr(csr, RS1);
  WRITE_RD(sext_xlen(old));
  serialize();
}
p->perf_pipeline[0].stage_valid = p->perf_enable;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_INT_PRIV;
p->perf_pipeline[0].inst_rs1_enable = true;
p->perf_pipeline[0].inst_rs1_type = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs1 = insn.rs1();
p->perf_pipeline[0].inst_rs2_enable = false;
p->perf_pipeline[0].inst_rs2_type = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs2 = insn.rs2();
p->perf_pipeline[0].inst_rs3_enable = false;
p->perf_pipeline[0].inst_rs3_type = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rs3 = 0;
p->perf_pipeline[0].inst_rd_enable = false;
p->perf_pipeline[0].inst_rd_type = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_rd = insn.rd();
if(csr == 0x8FF) {
  p->perf_enable = RS1 != 0;
}
