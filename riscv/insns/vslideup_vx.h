//vslideup.vx vd, vs2, rs1
VI_CHECK_SLIDE(true);

const reg_t offset = RS1;
VI_LOOP_BASE
if (P.VU.vstart < offset && i < offset)
  continue;

switch (sew) {
case e8: {
  VI_XI_SLIDEUP_PARAMS(e8, offset);
  vd = vs2;
}
break;
case e16: {
  VI_XI_SLIDEUP_PARAMS(e16, offset);
  vd = vs2;
}
break;
case e32: {
  VI_XI_SLIDEUP_PARAMS(e32, offset);
  vd = vs2;
}
break;
default: {
  VI_XI_SLIDEUP_PARAMS(e64, offset);
  vd = vs2;
}
break;
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
