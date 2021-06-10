require_extension('Q');
require_fp;
bool greater = f128_lt_quiet(f128(FRS2), f128(FRS1)) ||
               (f128_eq(f128(FRS2), f128(FRS1)) && (f128(FRS2).v[1] & F64_SIGN));
if (isNaNF128(f128(FRS1)) && isNaNF128(f128(FRS2)))
  WRITE_FRD(f128(defaultNaNF128()));
else
  WRITE_FRD(greater || isNaNF128(f128(FRS2)) ? FRS1 : FRS2);
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

