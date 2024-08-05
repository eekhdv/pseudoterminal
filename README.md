# pseudoterminal (pty | pst) Utility
This C project demonstrates how to create and utilize a pseudoterminal (pst).

## Key Features

* Minimal Dependencies: By relying solely on fundamental system calls (open, read, write, ioctl), this project remains lightweight and avoids external library dependencies.
* Data transfering: Periodically writes data by emulating UART Tx.
* Data receiving: Periodically reads data using polling, emulating UART Rx.

## Usage

### Compile:

```sh
cd pseudoterminal
make
```

### Run:
```
cd bin
./psttest.o
```

## Interact (Optional):

1. Open the terminal and launch this project.
2. Open two more terminals.
3. In one terminal, you can send data via `echo "hello from tty" > /dev/pts/...`
4. In the second terminal, you can read data using `read X < /dev/pts/...`;

