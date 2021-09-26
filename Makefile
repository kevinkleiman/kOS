BUILD_TARGET = boot

build:
	docker-compose up --build
run:
	qemu-system-x86_64.exe -fda ./env/build/$(BUILD_TARGET).bin
