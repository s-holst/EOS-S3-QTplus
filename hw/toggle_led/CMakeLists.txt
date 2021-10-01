add_file_target(FILE top.v SCANNER_TYPE verilog)
add_file_target(FILE top_tb.v SCANNER_TYPE verilog)
add_file_target(FILE io.pcf)

add_fpga_target(
  NAME top-ql-io
  BOARD io
  SOURCES top.v
  TESTBENCH_SOURCES top_tb.v
  INPUT_IO_FILE io.pcf
  EXPLICIT_ADD_FILE_TARGET
)

add_jlink_output(
  PARENT top-ql-io
)

add_openocd_output(
  PARENT top-ql-io
)

add_dependencies(all_ql_tests_bit  top-ql-io_bit)
add_dependencies(all_ql_tests_prog top-ql-io_jlink)
add_dependencies(all_ql_tests_prog top-ql-io_openocd)
add_dependencies(all_quick_tests top-ql-io_analysis)
add_dependencies(all_quick_tests testbench_top_tb)

