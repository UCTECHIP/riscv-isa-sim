if (STATE.v && STATE.prv == PRV_U) {
  require_novirt();
} else if (get_field(STATE.mstatus, MSTATUS_TW)) {
  require_privilege(PRV_M);
} else if (STATE.v) { // VS-mode
  if (get_field(STATE.hstatus, HSTATUS_VTW))
    require_novirt();
} else {
  require_privilege(PRV_S);
}
wfi();
p->perf_pipeline[0].stage_valid = p->perf_enable;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_INT;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_INT_PRIV;
p->perf_pipeline[0].inst_rs1_enable = false;
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

