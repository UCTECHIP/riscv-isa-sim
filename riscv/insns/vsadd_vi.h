// vsadd.vi vd, vs2 simm5
VI_CHECK_SSS(false);
VI_LOOP_BASE
bool sat = false;
switch(sew) {
case e8: {
  VI_PARAMS(e8);
  vd = sat_add<int8_t, uint8_t>(vs2, vsext(simm5, sew), sat);
  break;
}
case e16: {
  VI_PARAMS(e16);
  vd = sat_add<int16_t, uint16_t>(vs2, vsext(simm5, sew), sat);
  break;
}
case e32: {
  VI_PARAMS(e32);
  vd = sat_add<int32_t, uint32_t>(vs2, vsext(simm5, sew), sat);
  break;
}
default: {
  VI_PARAMS(e64);
  vd = sat_add<int64_t, uint64_t>(vs2, vsext(simm5, sew), sat);
  break;
}
}
P.VU.vxsat |= sat;
VI_LOOP_END
p->perf_pipeline[0].stage_valid = false;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_VECTOR_VXP_ALU;
p->perf_pipeline[0].inst_rs1_enable = true;
p->perf_pipeline[0].inst_rs1_type = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_rs1 = insn.rs1();
p->perf_pipeline[0].inst_rs2_enable = true;
p->perf_pipeline[0].inst_rs2_type = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_rs2 = insn.rs2();
p->perf_pipeline[0].inst_rs3_enable = false;
p->perf_pipeline[0].inst_rs3_type = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_rs3 = insn.rd();
p->perf_pipeline[0].inst_rd_enable = true;
p->perf_pipeline[0].inst_rd_type = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_rd = insn.rd();
