require_extension(EXT_ZFH);
require_fp;
WRITE_FRD(fsgnj16(FRS1, FRS2, false, false));
p->perf_pipeline[0].stage_valid = p->perf_enable;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_FLOAT_FP2FP;
p->perf_pipeline[0].inst_rs1_enable = true;
p->perf_pipeline[0].inst_rs1_type = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_rs1 = insn.rs1();
p->perf_pipeline[0].inst_rs2_enable = true;
p->perf_pipeline[0].inst_rs2_type = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_rs2 = insn.rs2();
p->perf_pipeline[0].inst_rs3_enable = false;
p->perf_pipeline[0].inst_rs3_type = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_rs3 = 0;
p->perf_pipeline[0].inst_rd_enable = true;
p->perf_pipeline[0].inst_rd_type = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_rd = insn.rd();
