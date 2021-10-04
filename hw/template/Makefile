all:
	ql_symbiflow -compile -d ql-eos-s3 -P pd64 -v top.v -t top -p io.pcf
	cd build && xxd -i top.bit >top_bit.h

