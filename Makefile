LIBYAML_DIR ?= libyaml
LIBYAML_REPO ?= https://github.com/yaml/libyaml
LIBYAML_BRANCH ?= master
DOCKER_NAME ?= libyaml-parser
DOCKER_USER ?= $(USER)
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

libyaml-parser: $(LIBYAML_DIR)/tests/.libs/run-parser
	cp $< $@

$(LIBYAML_DIR)/tests/.libs/run-parser: $(LIBYAML_DIR)/tests/run-parser.c $(LIBYAML_DIR)/Makefile
	make -C $(LIBYAML_DIR)

$(LIBYAML_DIR)/tests/run-parser.c: libyaml-parser.c $(LIBYAML_DIR)
	cp $< $@

$(LIBYAML_DIR)/Makefile: $(LIBYAML_DIR)
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
