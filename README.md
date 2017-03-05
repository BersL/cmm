## cmm
A C-- Language Complier.
It compile source code of C-- language, whose syntax is a subset of the C programming language, to MIPS Assembly.

### Currently Suport:
- Unary/Binary expression
- Multiple variable declration and assignment
- `int` and `double` data type
- `struct` syntax (array member is not supported)
- Array
- If-Else and while statement
- Function call


## Dependency
- `OS X/macOS` 10.11+
- `flex++` 2.5+
- `bison++` 3.0.4+

## Build
```shell
$ make
```

## Usage
```shell
$ bin/cmm source_file
```
`-p` will print syntax tree

## Test
Add test source files into `testcase` directory and run

```shell
$ make test
```
