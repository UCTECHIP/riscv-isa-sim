require_extension('D');
require_fp;
bool less = f64_lt_quiet(f64(FRS1), f64(FRS2)) ||
            (f64_eq(f64(FRS1), f64(FRS2)) && (f64(FRS1).v & F64_SIGN));
if (isNaNF64UI(f64(FRS1).v) && isNaNF64UI(f64(FRS2).v))
  WRITE_FRD(f64(defaultNaNF64UI));
else
  WRITE_FRD(less || isNaNF64UI(f64(FRS2).v) ? FRS1 : FRS2);
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

