touchblk: clean
	gcc touchblk.c -o touchblk

clean:
	rm -f touchblk

run:
	./touchblk

bpf:
	sudo python3 fblktrace.py