# C with standard library

This project tries to work with the **Linux**
kernel directly.

## Build

```
make tok
make echo
```

Cleanup:
```
make clean
```

## Example

```
./tok <<EOF
run(echo, 'Hello, World!')
EOF
run
(
echo
,
'Hello, World!'
)
```

```
./echo
Hello  # input
World  # input
Hello
World
```

```
./echo
Hello  # input
Hello  # input
Hello
```
