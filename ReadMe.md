libyaml-parser
==============

Parser CLI for libyaml

# Usage

Print parse events for a YAML file:

```
make build
./libyaml-parser some-file.yaml
```

With Docker:
```
docker run -i -v $PWD:/cwd/ ingy/libyaml-parser some-file.yaml
```
