// vmsbf.m vd, vs2, vm
require(P.VU.vsew >= e8 && P.VU.vsew <= e64);
require_vector(true);
require(P.VU.vstart == 0);
require_vm;
require(insn.rd() != insn.rs2());

reg_t vl = P.VU.vl;
reg_t rd_num = insn.rd();
reg_t rs2_num = insn.rs2();

bool has_one = false;
for (reg_t i = P.VU.vstart; i < vl; ++i) {
  const int midx = i / 64;
  const int mpos = i % 64;
  const uint64_t mmask = UINT64_C(1) << mpos; \

  bool vs2_lsb = ((P.VU.elt<uint64_t>(rs2_num, midx) >> mpos) & 0x1) == 1;
  bool do_mask = (P.VU.elt<uint64_t>(0, midx) >> mpos) & 0x1;


  if (insn.v_vm() == 1 || (insn.v_vm() == 0 && do_mask)) {
    auto &vd = P.VU.elt<uint64_t>(rd_num, midx, true);
    uint64_t res = 0;
    if (!has_one && !vs2_lsb) {
      res = 1;
    } else if(!has_one && vs2_lsb) {
      has_one = true;
    }
    vd = (vd & ~mmask) | ((res << mpos) & mmask);
  }
}
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
