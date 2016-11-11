FROM ubuntu

RUN apt-get update \
 && apt-get install -y \
        build-essential \
        git \
        gist vim \
 && true

COPY $PWD/ /libyaml-parser/

RUN apt-get install -y \
        autoconf \
        libtool \
 && true

RUN (cd /libyaml-parser/ && make clean build)

WORKDIR /cwd/

ENTRYPOINT ["/libyaml-parser/libyaml-parser"]
