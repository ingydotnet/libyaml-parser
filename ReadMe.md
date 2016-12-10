libyaml-parser
==============

Parser CLI for libyaml

# Try it Now with Docker:

```
curl -s https://raw.githubusercontent.com/ingydotnet/libyaml-parser/master/test/example-2.27-invoice.yaml | docker run -iv $PWD:/cwd ingy/libyaml-parser
```

# Synopsis

```
git clone https://github.com/ingydotnet/libyaml-parser
cd libyaml-parser
make build
make test
```

# Usage

Print parse events for a YAML file (or stdin):

```
./libyaml-parser file.yaml
./libyaml-parser < file.yaml
cat file.yaml | ./libyaml-parser
```

Run with Docker:

```
alias my-yaml-parser='docker run -iv $PWD:/cwd ingy/libyaml-parser'
my-yaml-parser file.yaml
my-yaml-parser < file.yaml
cat file.yaml | my-yaml-parser
```

# Build

## Native Build

```
make build
```

## Docker Image Build

```
DOCKER_USER=ingy make docker
```
