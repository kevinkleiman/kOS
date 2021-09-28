BUILD_TARGET = boot

build:
	docker compose up -d --build
rm:
	docker compose down
run:
	qemu-system-x86_64.exe -drive format=raw,file=./env/bin/kos.bin,index=0,if=floppy, -m 128M
