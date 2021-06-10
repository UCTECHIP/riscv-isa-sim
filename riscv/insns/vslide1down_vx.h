//vslide1down.vx vd, vs2, rs1
VI_CHECK_SLIDE(false);

VI_LOOP_BASE
if (i != vl - 1) {
  switch (sew) {
  case e8: {
    VI_XI_SLIDEDOWN_PARAMS(e8, 1);
    vd = vs2;
  }
  break;
  case e16: {
    VI_XI_SLIDEDOWN_PARAMS(e16, 1);
    vd = vs2;
  }
  break;
  case e32: {
    VI_XI_SLIDEDOWN_PARAMS(e32, 1);
    vd = vs2;
  }
  break;
  default: {
    VI_XI_SLIDEDOWN_PARAMS(e64, 1);
    vd = vs2;
  }
  break;
  }
} else {
  switch (sew) {
  case e8:
    P.VU.elt<uint8_t>(rd_num, vl - 1, true) = RS1;
    break;
  case e16:
    P.VU.elt<uint16_t>(rd_num, vl - 1, true) = RS1;
    break;
  case e32:
    P.VU.elt<uint32_t>(rd_num, vl - 1, true) = RS1;
    break;
  default:
    P.VU.elt<uint64_t>(rd_num, vl - 1, true) = RS1;
    break;
  }
}
VI_LOOP_END
p->perf_pipeline[0].stage_valid = false;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_VECTOR_VX_PERMUTATION;
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
