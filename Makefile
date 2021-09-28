BUILD_TARGET = boot

docker-build:
	docker compose up -d --build
docker-clean:
	docker compose down
run:
	qemu-system-x86_64.exe -drive format=raw,file=./env/bin/kos.bin,index=0,if=floppy, -m 128M
