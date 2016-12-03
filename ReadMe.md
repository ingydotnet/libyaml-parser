libyaml-parser
==============

Parser CLI for libyaml

Try:

```
curl -s https://raw.githubusercontent.com/ingydotnet/libyaml-parser/master/test/example-2.27-invoice.yaml | docker run -iv $PWD:/cwd ingy/libyaml-parser
```

# Usage

Print parse events for YAML files (or stdin):

```
libyaml-parser file1.yaml file2.yaml ...
cat file.yaml | libyaml-parser
```

With Docker:

```
alias my-yaml-parser='docker run -iv $PWD:/cwd ingy/libyaml-parser'
my-yaml-parser file1.yaml file2.yaml ...
cat file.yaml | my-yaml-parser
```

# Build

Run:

```
make build
```

## Docker Image Build

```
make build
./libyaml-parser some-file.yaml
```

With Docker:
```
docker run -i -v $PWD:/cwd/ ingy/libyaml-parser some-file.yaml
=======
make docker
```
