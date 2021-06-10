//vslide1up.vx vd, vs2, rs1
VI_CHECK_SLIDE(true);

VI_LOOP_BASE
if (i != 0) {
  if (sew == e8) {
    VI_XI_SLIDEUP_PARAMS(e8, 1);
    vd = vs2;
  } else if(sew == e16) {
    VI_XI_SLIDEUP_PARAMS(e16, 1);
    vd = vs2;
  } else if(sew == e32) {
    VI_XI_SLIDEUP_PARAMS(e32, 1);
    vd = vs2;
  } else if(sew == e64) {
    VI_XI_SLIDEUP_PARAMS(e64, 1);
    vd = vs2;
  }
} else {
  if (sew == e8) {
    P.VU.elt<uint8_t>(rd_num, 0, true) = RS1;
  } else if(sew == e16) {
    P.VU.elt<uint16_t>(rd_num, 0, true) = RS1;
  } else if(sew == e32) {
    P.VU.elt<uint32_t>(rd_num, 0, true) = RS1;
  } else if(sew == e64) {
    P.VU.elt<uint64_t>(rd_num, 0, true) = RS1;
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
