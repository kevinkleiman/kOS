BUILD_TARGET = boot

exec:
	docker exec -u root -ti os-dev-env /bin/bash
docker-build:
	docker compose up -d --build
docker-clean:
	docker compose down
run:
	qemu-system-x86_64 -drive format=raw,file=./env/bin/kos.bin,index=0,if=floppy, -m 128M
