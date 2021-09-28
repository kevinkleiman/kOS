# k-os
A chaotic lightweight operating system easy to get started, and made for learning!

## Prerequisites
- `Docker` is installed
- Latest version of `qemu` is installed

## To get started
1. Run `make docker-build`
  - This will set up the dockerized development environment used for compiling and building our OS

2. Exec into the development container with `docker exec -u root -ti os-dev-env /bin/bash` **Works with powershell only for some reason??!!**
  - This allows us to start working within our dockerized development environment

3. From inside the docker container run `make build` when changes are made to the source code
  - This compiles, links, and builds all `C` and `Assembly` source files which `qemu` will boot

4. From the project directory (outside the docker container) run `make run`
  - This will run `qemu` (assuming a Windows dev environment), an `x86 emulator` which will run the compiled binaries
