touchblk: clean dummy.dat
	gcc touchblk.c -o touchblk

clean:
	rm -f touchblk

run:
	./touchblk

bpf:
	sudo python3 fblktrace.py

dummy.dat:
	dd if=/dev/urandom of=dummy.dat bs=1024 count=1024

drop_cache:
	echo 1 | sudo tee /proc/sys/vm/drop_caches