// vwmulsu.vv vd, vs2, vs1
VI_CHECK_DSS(true);
VI_VV_LOOP_WIDEN
({
  switch(P.VU.vsew) {
  case e8:
    P.VU.elt<uint16_t>(rd_num, i, true) = (int16_t)(int8_t)vs2 * (int16_t)(uint8_t)vs1;
    break;
  case e16:
    P.VU.elt<uint32_t>(rd_num, i, true) = (int32_t)(int16_t)vs2 * (int32_t)(uint16_t)vs1;
    break;
  default:
    P.VU.elt<uint64_t>(rd_num, i, true) = (int64_t)(int32_t)vs2 * (int64_t)(uint32_t)vs1;
    break;
  }
})
p->perf_pipeline[0].stage_valid = false;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_VECTOR_VX_MUL;
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
