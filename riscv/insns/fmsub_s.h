require_extension('F');
require_fp;
softfloat_roundingMode = RM;
WRITE_FRD(f32_mulAdd(f32(FRS1), f32(FRS2), f32(f32(FRS3).v ^ F32_SIGN)));
set_fp_exceptions;
p->perf_pipeline[0].stage_valid = p->perf_enable;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_FLOAT_MADD;
p->perf_pipeline[0].inst_rs1_enable = true;
p->perf_pipeline[0].inst_rs1_type = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_rs1 = insn.rs1();
p->perf_pipeline[0].inst_rs2_enable = true;
p->perf_pipeline[0].inst_rs2_type = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_rs2 = insn.rs2();
p->perf_pipeline[0].inst_rs3_enable = true;
p->perf_pipeline[0].inst_rs3_type = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_rs3 = insn.rs3();
p->perf_pipeline[0].inst_rd_enable = true;
p->perf_pipeline[0].inst_rd_type = PERF_INST_TYPE_FLOAT;
p->perf_pipeline[0].inst_rd = insn.rd();

