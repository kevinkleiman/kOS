BUILD_TARGET = boot

build:
	docker-compose up -d --build
rm:
	docker-compose down
run:
	qemu-system-x86_64.exe -fda ./env/bin/$(BUILD_TARGET).bin
