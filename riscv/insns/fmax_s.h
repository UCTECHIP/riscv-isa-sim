require_extension('F');
require_fp;
bool greater = f32_lt_quiet(f32(FRS2), f32(FRS1)) ||
               (f32_eq(f32(FRS2), f32(FRS1)) && (f32(FRS2).v & F32_SIGN));
if (isNaNF32UI(f32(FRS1).v) && isNaNF32UI(f32(FRS2).v))
  WRITE_FRD(f32(defaultNaNF32UI));
else
  WRITE_FRD(greater || isNaNF32UI(f32(FRS2).v) ? FRS1 : FRS2);
set_fp_exceptions;
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

