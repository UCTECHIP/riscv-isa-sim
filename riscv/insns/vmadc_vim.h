// vmadc.vim vd, vs2, simm5
VI_XI_LOOP_CARRY
({
  auto v0 = P.VU.elt<uint64_t>(0, midx);
  const uint64_t mmask = UINT64_C(1) << mpos; \
  const uint128_t op_mask = (UINT64_MAX >> (64 - sew));
  uint64_t carry = insn.v_vm() == 0 ? (v0 >> mpos) & 0x1 : 0;

  uint128_t res = (op_mask & simm5) + (op_mask & vs2) + carry;

  carry = (res >> sew) & 0x1u;
  vd = (vd & ~mmask) | ((carry << mpos) & mmask);
})
p->perf_pipeline[0].stage_valid = false;
p->perf_pipeline[0].inst_class = PERF_INST_TYPE_VECTOR;
p->perf_pipeline[0].inst_class_offset = PERF_INST_TYPE_VECTOR_VX_ALU;
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
