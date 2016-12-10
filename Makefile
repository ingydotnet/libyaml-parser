LIBYAML_REPO ?= https://github.com/yaml/libyaml
LIBYAML_BRANCH ?= master
DOCKER_NAME ?= libyaml-parser
DOCKER_USER ?= ingy
DOCKER_TAG ?= latest
DOCKER_IMAGE ?= $(DOCKER_USER)/$(DOCKER_NAME):$(DOCKER_TAG)

define HELP
This Makefile supports the following targets:

    build    - Build ./libyaml-test-parser
    test     - Run tests
    docker   - Build Docker image

endef
export HELP

help:
	@echo "$$HELP"

build: libyaml-parser

libyaml-parser: libyaml/tests/.libs/run-parser
	cp $< $@

libyaml/tests/.libs/run-parser: libyaml/tests/run-parser.c libyaml/Makefile
	make -C libyaml

libyaml/tests/run-parser.c: libyaml-parser.c libyaml
	cp $< $@

libyaml/Makefile: libyaml
	( cd $< && ./bootstrap && ./configure )
	touch $@

libyaml:
	git clone $(LIBYAML_REPO) $@
	rm libyaml/tests/run-parser.c

.PHONY: test
test: build
	prove -lv test/

docker:
	docker build --tag $(DOCKER_IMAGE) .

push: docker
	docker push $(DOCKER_IMAGE)

shell: docker
	docker run -it --entrypoint=/bin/sh $(DOCKER_IMAGE)

clean:
	rm -fr libyaml libyaml-parser
