BUILD_TARGET = boot

exec:
	docker exec -u root -ti os-dev-env /bin/bash
build:
	docker compose up -d --build
clean:
	docker compose down
