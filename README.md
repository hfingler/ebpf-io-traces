# ebpf-io-traces


sudo apt-get -y install bison build-essential cmake flex git libedit-dev \
  libllvm6.0 llvm-6.0-dev libclang-6.0-dev python zlib1g-dev libelf-dev libfl-dev python3-distutils


Disable readahead

echo 0 | sudo tee /sys/block/mmcblk0/queue/read_ahead_kb



vm_fault_t filemap_fault(struct vm_fault *vmf)