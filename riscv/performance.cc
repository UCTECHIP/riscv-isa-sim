#include "processor.h"
#include "performance.h"
#include "log_file.h"
void processor_t::perf_reset() {
  int i,j,k;
  this->perf_file = (new log_file_t("Performance.md"))->get();
  this->perf_enable = false;
  for (i = 0; i < PERF_PIPE_STAGE; i++) {
    this->perf_pipeline[i].stage_valid = false;
  }

  for (i = 0; i < PERF_NUM_INST_TYPE_INT; i++) {
    this->perf_inst_type_int[i] = 0;
  }

  for (i = 0; i < PERF_NUM_INST_TYPE_FLOAT; i++) {
    this->perf_inst_type_float[i] = 0;
  }

  for (i = 0; i < PERF_NUM_INST_TYPE_VECTOR; i++) {
    this->perf_inst_type_vector[i] = 0;
  }
  for (i = 0; i < PERF_PIPE_STAGE; i++) {
    this->perf_waw[i] = 0;
    this->perf_war[i] = 0;
    for (j = 0; j < PERF_NUM_INST_TYPE_INT; j++) {
      for (k = 0; k < PERF_NUM_INST_TYPE_INT; k++) {
        this->perf_raw_x_x[i][j][k] = 0;
      }
    }
    for (j = 0; j < PERF_NUM_INST_TYPE_FLOAT; j++) {
      for (k = 0; k < PERF_NUM_INST_TYPE_FLOAT; k++) {
        this->perf_raw_f_f[i][j][k] = 0;
      }
    }
    for (j = 0; j < PERF_NUM_INST_TYPE_VECTOR; j++) {
      for (k = 0; k < PERF_NUM_INST_TYPE_VECTOR; k++) {
        this->perf_raw_v_v[i][j][k] = 0;
      }
    }
    for (j = 0; j < PERF_NUM_INST_TYPE; j++) {
      for (k = 0; k < PERF_NUM_INST_TYPE; k++) {
        this->perf_raw_a_a[i][j][k] = 0;
      }
    }
  }
  this->perf_struct_int = 0;
  this->perf_struct_float = 0;
  this->perf_struct_vx = 0;
  this->perf_struct_vf = 0;
  this->perf_div_model_int = 0;
  this->perf_div_model_float = 0;
  this->perf_div_model_vx = 0;
  this->perf_div_model_vf = 0;
}



void processor_t::perf_inst_pipe()
{
  for (int i = PERF_PIPE_STAGE-1; i > 0; i--) {
    this->perf_pipeline[i] = this->perf_pipeline[i-1];
  }
}

void processor_t::perf_inst_type_statistic()
{
  uint64_t inst_class = this->perf_pipeline[0].inst_class;
  uint64_t inst_class_offset = this->perf_pipeline[0].inst_class_offset;
  if(this->perf_pipeline[0].stage_valid) {
    if(inst_class == PERF_INST_TYPE_INT) {
      this->perf_inst_type_int[inst_class_offset]++;
    } else if(inst_class == PERF_INST_TYPE_FLOAT) {
      this->perf_inst_type_float[inst_class_offset]++;
    } else if(inst_class == PERF_INST_TYPE_VECTOR) {
      this->perf_inst_type_vector[inst_class_offset]++;
    }
  }
}

void processor_t::perf_data_hazard_raw()
{
  for (int i = 1 ; i < PERF_PIPE_STAGE; i++) {
    bool rs1_int_zero = \
      (this->perf_pipeline[0].inst_class == PERF_INST_TYPE_INT) && \
      (this->perf_pipeline[0].inst_rs1 == 0);
    bool rs1_rd_raw = \
      !rs1_int_zero && \
      (this->perf_pipeline[0].inst_rs1 != 0) && \
      this->perf_pipeline[0].stage_valid && this->perf_pipeline[i].stage_valid && \
      this->perf_pipeline[0].inst_rs1_enable && this->perf_pipeline[i].inst_rd_enable && \
      (this->perf_pipeline[0].inst_rs1_type == this->perf_pipeline[i].inst_rd_type) && \
      (this->perf_pipeline[0].inst_rs1 == this->perf_pipeline[i].inst_rd);
    bool rs2_int_zero = \
      (this->perf_pipeline[0].inst_class == PERF_INST_TYPE_INT) && \
      (this->perf_pipeline[0].inst_rs2 == 0);
    bool rs2_rd_raw = \
      !rs2_int_zero && \
      this->perf_pipeline[0].stage_valid && this->perf_pipeline[i].stage_valid && \
      this->perf_pipeline[0].inst_rs2_enable && this->perf_pipeline[i].inst_rd_enable && \
      ((this->perf_pipeline[0].inst_rs2_type == this->perf_pipeline[i].inst_rd_type) && \
      (this->perf_pipeline[0].inst_rs2 == this->perf_pipeline[i].inst_rd));
    bool rs3_rd_raw = \
      this->perf_pipeline[0].stage_valid && this->perf_pipeline[i].stage_valid && \
      this->perf_pipeline[0].inst_rs3_enable && this->perf_pipeline[i].inst_rd_enable && \
      ((this->perf_pipeline[0].inst_rs3_type == this->perf_pipeline[i].inst_rd_type) && \
      (this->perf_pipeline[0].inst_rs3 == this->perf_pipeline[i].inst_rd));

    bool exist_raw = rs1_rd_raw || rs2_rd_raw || rs3_rd_raw;

    if(this->perf_pipeline[0].inst_class == this->perf_pipeline[i].inst_class) {
      switch(this->perf_pipeline[0].inst_class) {
        case PERF_INST_TYPE_INT:
          this->perf_raw_x_x[i][this->perf_pipeline[0].inst_class_offset][this->perf_pipeline[i].inst_class_offset] += exist_raw;
          break;
        case PERF_INST_TYPE_FLOAT:
          this->perf_raw_f_f[i][this->perf_pipeline[0].inst_class_offset][this->perf_pipeline[i].inst_class_offset] += exist_raw;
          break;
        case PERF_INST_TYPE_VECTOR:
          this->perf_raw_v_v[i][this->perf_pipeline[0].inst_class_offset][this->perf_pipeline[i].inst_class_offset] += exist_raw;
          break;
        default: break;
      }
    } else {
      this->perf_raw_a_a[i][this->perf_pipeline[0].inst_class][this->perf_pipeline[i].inst_class] += exist_raw;
    }
  }
}

void processor_t::perf_data_hazard_waw()
{
  for (int i = 1 ; i < PERF_PIPE_STAGE; i++) {
    bool rd_int_zero = \
      (this->perf_pipeline[0].inst_class == PERF_INST_TYPE_INT) && \
      (this->perf_pipeline[0].inst_rd == 0);
    bool exist_waw = \
      !rd_int_zero && \
      this->perf_pipeline[0].stage_valid && this->perf_pipeline[i].stage_valid && \
      this->perf_pipeline[0].inst_rd_enable && this->perf_pipeline[i].inst_rd_enable && \
      ((this->perf_pipeline[0].inst_rd_type == this->perf_pipeline[i].inst_rd_type) && \
      (this->perf_pipeline[0].inst_rd == this->perf_pipeline[i].inst_rd));
    this->perf_waw[i] += exist_waw;
  }
}

void processor_t::perf_data_hazard_war()
{
  for (int i = 1 ; i < PERF_PIPE_STAGE; i++) {
    bool rd_int_zero = \
      (this->perf_pipeline[0].inst_class == PERF_INST_TYPE_INT) && \
      (this->perf_pipeline[0].inst_rd == 0);
    bool rd_rs1_war = \
      this->perf_pipeline[0].stage_valid && this->perf_pipeline[i].stage_valid && \
      this->perf_pipeline[0].inst_rd_enable && this->perf_pipeline[i].inst_rs1_enable && \
      ((this->perf_pipeline[0].inst_rd_type == this->perf_pipeline[i].inst_rs1_type) && \
      (this->perf_pipeline[0].inst_rd == this->perf_pipeline[i].inst_rs1));
    bool rd_rs2_war = \
      this->perf_pipeline[0].stage_valid && this->perf_pipeline[i].stage_valid && \
      this->perf_pipeline[0].inst_rd_enable && this->perf_pipeline[i].inst_rs2_enable && \
      ((this->perf_pipeline[0].inst_rd_type == this->perf_pipeline[i].inst_rs2_type) && \
      (this->perf_pipeline[0].inst_rd == this->perf_pipeline[i].inst_rs2));
    bool rd_rs3_war = \
      this->perf_pipeline[0].stage_valid && this->perf_pipeline[i].stage_valid && \
      this->perf_pipeline[0].inst_rd_enable && this->perf_pipeline[i].inst_rs3_enable && \
      ((this->perf_pipeline[0].inst_rd_type == this->perf_pipeline[i].inst_rs3_type) && \
      (this->perf_pipeline[0].inst_rd == this->perf_pipeline[i].inst_rs3));
    bool exist_war = !rd_int_zero && (rd_rs1_war || rd_rs2_war || rd_rs3_war);
    this->perf_war[i] += exist_war;
  }
}

void processor_t::perf_struct_hazard()
{
  bool will_occupy_int_div = this->perf_pipeline[0].stage_valid && \
    (this->perf_pipeline[0].inst_class == PERF_INST_TYPE_INT) && \
    (this->perf_pipeline[0].inst_class_offset == PERF_INST_TYPE_INT_DIV);
  bool will_occupy_float_div = this->perf_pipeline[0].stage_valid && \
    (this->perf_pipeline[0].inst_class == PERF_INST_TYPE_FLOAT) && \
    (this->perf_pipeline[0].inst_class_offset == PERF_INST_TYPE_FLOAT_DIV);
  bool will_occupy_vector_vx_div = this->perf_pipeline[0].stage_valid && \
    (this->perf_pipeline[0].inst_class == PERF_INST_TYPE_VECTOR) && \
    ((this->perf_pipeline[0].inst_class_offset == PERF_INST_TYPE_VECTOR_VX_DIV)  || \
     (this->perf_pipeline[0].inst_class_offset == PERF_INST_TYPE_VECTOR_VX_MUL));
  bool will_occupy_vector_vf_div = this->perf_pipeline[0].stage_valid && \
    (this->perf_pipeline[0].inst_class == PERF_INST_TYPE_VECTOR) && \
    (this->perf_pipeline[0].inst_class_offset == PERF_INST_TYPE_VECTOR_VF_DIV);

  this->perf_struct_int += (will_occupy_int_div && (this->perf_div_model_int != 0));
  this->perf_struct_float += (will_occupy_float_div && (this->perf_div_model_float != 0));
  this->perf_struct_vx += (will_occupy_vector_vx_div && (this->perf_div_model_vx != 0));
  this->perf_struct_vf += (will_occupy_vector_vf_div && (this->perf_div_model_vf != 0));

  if(will_occupy_int_div && this->perf_pipeline[0].stage_valid) {
    this->perf_div_model_int = MODEL_INT_DIV_LATENCY;
  } else if (this->perf_div_model_int != 0) {
    this->perf_div_model_int --;
  }

  if(this->perf_pipeline[0].stage_valid && will_occupy_float_div) {
    this->perf_div_model_float = MODEL_FLOAT_DIV_LATENCY;
  } else if (this->perf_div_model_float != 0) {
    this->perf_div_model_float --;
  }

  if(this->perf_pipeline[0].stage_valid && will_occupy_vector_vx_div) {
    this->perf_div_model_vx = MODEL_INT_DIV_LATENCY;
  } else if (this->perf_div_model_vx != 0) {
    this->perf_div_model_vx --;
  }

  if(this->perf_pipeline[0].stage_valid && will_occupy_vector_vf_div) {
    this->perf_div_model_vf = MODEL_FLOAT_DIV_LATENCY;
  } else if (this->perf_div_model_vf != 0) {
    this->perf_div_model_vf --;
  }

}

 
void processor_t::perf_print_report(size_t id) {

char perf_pipe_name[PERF_PIPE_STAGE][30] = {"ID-ID", "ID-EXE", "ID-MEM", "ID-WB"};
char perf_inst_type_name[PERF_NUM_INST_TYPE][30] = {"XP", "FP", "VP"};
char perf_inst_type_int_name[PERF_NUM_INST_TYPE_INT][30] = {
  "X_alu",
  "X_mul",
  "X_div",
  "X_load",
  "X_store",
  "X_amo",
  "X_branch",
  "X_jump",
  "X_priv"
};
char perf_inst_type_float_name[PERF_NUM_INST_TYPE_FLOAT][30] = {
  "F_xp2fp",
  "F_fp2fp",
  "F_fp2xp",
  "F_load",
  "F_store",
  "F_madd",
  "F_div"
};
char perf_inst_type_vector_name[PERF_NUM_INST_TYPE_VECTOR][30] = {
  "VX_alu",
  "VX_reduction",
  "VX_mul",
  "VX_div",
  "VX_permutation",
  "VX_load_unit_stride",
  "VX_load_stride",
  "VX_load_index",
  "VX_load_reg",
  "VX_store_unit_stride",
  "VX_store_stride",
  "VX_store_index",
  "VX_store_reg",
  "VXP_alu",
  "VXP_mul",
  "VF_int2fp",
  "VF_fp2fp",
  "VF_fp2int",
  "VF_madd",
  "VF_div",
  "vp2xp",
  "xp2vp",
  "vp2fp",
  "fp2vp"
};
  uint64_t perf_inst_type_int_total = 0;
  uint64_t perf_inst_type_float_total = 0;
  uint64_t perf_inst_type_vector_total = 0;
  for (int i = 0; i < PERF_NUM_INST_TYPE_INT; i++)
    perf_inst_type_int_total += this->perf_inst_type_int[i];
  for (int i = 0; i < PERF_NUM_INST_TYPE_FLOAT; i++)
    perf_inst_type_float_total += this->perf_inst_type_float[i];
  for (int i = 0; i < PERF_NUM_INST_TYPE_VECTOR; i++)
    perf_inst_type_vector_total += this->perf_inst_type_vector[i];
  if (perf_inst_type_int_total == 0)
    perf_inst_type_int_total = 1;
  if (perf_inst_type_float_total == 0)
    perf_inst_type_float_total = 1;
  if (perf_inst_type_vector_total == 0)
    perf_inst_type_vector_total = 1;

  fprintf(this->perf_file, "# ***Performance Of Core %ld***\n\n\n\n", id);
  fprintf(this->perf_file, "# Performance Quantity Report\n\n");
  fprintf(this->perf_file, "**COMPANY**: UC TECH IP\n");
  fprintf(this->perf_file, "**VERSION**: v0.1\n");
  fprintf(this->perf_file, "**REFERENCE**: White paper of Processor Performance Quantity\n");
  fprintf(this->perf_file, "----\n\n");

  fprintf(this->perf_file, "## 1. Inst Type Statistic\n");

  fprintf(this->perf_file, "### 1.1 Integer Instruction\n");
  fprintf(this->perf_file, "|Inst Type | Number | Percentage |\n");
  fprintf(this->perf_file, "|:--|:--:|:--:|\n");
  for (int i = 0; i < PERF_NUM_INST_TYPE_INT; i++) {
    fprintf(this->perf_file, "|%s|%ld|%f|\n", \
      perf_inst_type_int_name[i], \
      this->perf_inst_type_int[i], \
      (float)this->perf_inst_type_int[i]/(float)perf_inst_type_int_total);
  }

  fprintf(this->perf_file, "### 1.2 Floating Point Instruction\n");
  fprintf(this->perf_file, "|Inst Type | Number | Percentage |\n");
  fprintf(this->perf_file, "|:--|:--:|:--:|\n");
  for (int i = 0; i < PERF_NUM_INST_TYPE_FLOAT; i++) {
    fprintf(this->perf_file, "|%s|%ld|%f|\n", \
      perf_inst_type_float_name[i], \
      this->perf_inst_type_float[i], \
      (float)this->perf_inst_type_float[i]/(float)perf_inst_type_float_total);
  }

  fprintf(this->perf_file, "### 1.3 Vector Instruction\n");
  fprintf(this->perf_file, "|Inst Type | Number | Percentage |\n");
  fprintf(this->perf_file, "|:--|:--:|:--:|\n");
  for (int i = 0; i < PERF_NUM_INST_TYPE_VECTOR; i++) {
    fprintf(this->perf_file, "|%s|%ld|%f|\n",
      perf_inst_type_vector_name[i],
      this->perf_inst_type_vector[i],
      (float)this->perf_inst_type_vector[i]/(float)perf_inst_type_vector_total);
  }
  fprintf(this->perf_file, "## 2. Data Hazard -- RAW\n");

  fprintf(this->perf_file, "### 2.1 Int-Int RAW\n\n");

  for (int i = 1; i < PERF_PIPE_STAGE; i++) {
    fprintf(this->perf_file, "#### 2.1.%d %s RAW\n\n", i, perf_pipe_name[i]);
    fprintf(this->perf_file, "|RAW Hazard Inst Type | Number |\n");
    fprintf(this->perf_file, "|:--|:--:|\n");
    for (int j = 0; j < PERF_NUM_INST_TYPE_INT; j++) {
      for (int k = 0; k < PERF_NUM_INST_TYPE_INT; k++) {
        fprintf(this->perf_file, "|%s ::: %s | %ld |\n", perf_inst_type_int_name[j], perf_inst_type_int_name[k], this->perf_raw_x_x[i][j][k]);
      }
    }
  }

  fprintf(this->perf_file, "### 2.2 Float-Float RAW\n\n");

  for (int i = 1; i < PERF_PIPE_STAGE; i++) {
    fprintf(this->perf_file, "#### 2.2.%d %s RAW\n\n", i, perf_pipe_name[i]);
    fprintf(this->perf_file, "|RAW Hazard Inst Type | Number |\n");
    fprintf(this->perf_file, "|:--|:--:|\n");
    for (int j = 0; j < PERF_NUM_INST_TYPE_FLOAT; j++) {
      for (int k = 0; k < PERF_NUM_INST_TYPE_FLOAT; k++) {
        fprintf(this->perf_file, "|%s ::: %s | %ld |\n", perf_inst_type_float_name[j], perf_inst_type_float_name[k], this->perf_raw_f_f[i][j][k]);
      }
    }
  }
  fprintf(this->perf_file, "### 2.3 Vector-Vector RAW\n\n");

  for (int i = 1; i < PERF_PIPE_STAGE; i++) {
    fprintf(this->perf_file, "#### 2.3.%d %s RAW\n\n", i, perf_pipe_name[i]);
    fprintf(this->perf_file, "|RAW Hazard Inst Type | Number |\n");
    fprintf(this->perf_file, "|:--|:--:|\n");
    for (int j = 0; j < PERF_NUM_INST_TYPE_VECTOR; j++) {
      for (int k = 0; k < PERF_NUM_INST_TYPE_VECTOR; k++) {
        fprintf(this->perf_file, "|%s ::: %s | %ld |\n", perf_inst_type_vector_name[j], perf_inst_type_vector_name[k], this->perf_raw_v_v[i][j][k]);
      }
    }
  }

  fprintf(this->perf_file, "### 2.4 allType-allType RAW\n\n");

  for (int i = 1; i < PERF_PIPE_STAGE; i++) {
    fprintf(this->perf_file, "#### 2.4.%d %s RAW\n\n", i, perf_pipe_name[i]);
    fprintf(this->perf_file, "|RAW Hazard Inst Type | Number |\n");
    fprintf(this->perf_file, "|:--|:--:|\n");
    for (int j = 0; j < PERF_NUM_INST_TYPE; j++) {
      for (int k = 0; k < PERF_NUM_INST_TYPE; k++) {
        fprintf(this->perf_file, "|%s ::: %s | %ld |\n", perf_inst_type_name[j], perf_inst_type_name[k], this->perf_raw_a_a[i][j][k]);
      }
    }
  }

  fprintf(this->perf_file, "## 3. Data Hazard -- WAW\n");

  fprintf(this->perf_file, "|Stage-Stage WAW | Number |\n");
  fprintf(this->perf_file, "|:--|:--:|\n");
  for (int i = 1; i < PERF_PIPE_STAGE; i++) {
    fprintf(this->perf_file, "|%s | %ld |\n", perf_pipe_name[i], this->perf_waw[i]);
  }

  fprintf(this->perf_file, "## 4. Data Hazard -- WAR\n");

  fprintf(this->perf_file, "|Stage-Stage WAR | Number |\n");
  fprintf(this->perf_file, "|:--|:--:|\n");
  for (int i = 1; i < PERF_PIPE_STAGE; i++) {
    fprintf(this->perf_file, "| %s | %ld |\n", perf_pipe_name[i], this->perf_war[i]);
  }

  fprintf(this->perf_file, "## 5. Structure Hazard\n");

  fprintf(this->perf_file, "|Structure Hazard Type|Number|\n");
  fprintf(this->perf_file, "|:--|:--:|\n");
  fprintf(this->perf_file, "|Int Structure Hazard | %ld |\n", this->perf_struct_int);
  fprintf(this->perf_file, "|Float Structure Hazard | %ld |\n", this->perf_struct_float);
  fprintf(this->perf_file, "|vectorInt Structure Hazard | %ld |\n", this->perf_struct_vx);
  fprintf(this->perf_file, "|vectorFloat Structure Hazard | %ld |\n", this->perf_struct_vf);


  fprintf(this->perf_file, "## 6. Control Hazard\n");

}



