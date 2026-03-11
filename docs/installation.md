# Installation Guide

This document describes how to install the Novus compiler and project manager on your system.

## Prerequisites

Ensure you have the following installed:
- LLVM 18 (with `llc-18` and `llvm-config-18`)
- GCC
- Flex and Bison
- Make
- Python 3

## Standard Installation

To build and install Novus to the default location (`/usr/local`):

```bash
make
sudo make install
```

This will install:
- `novusc`: The Novus compiler (to `/usr/local/bin`)
- `novum`: The project management tool (to `/usr/local/bin`)
- `std.nov`: The standard library (to `/usr/local/lib/novus/`)

## Custom Installation Path

You can specify a custom installation prefix using the `PREFIX` variable:

```bash
make
make install PREFIX=$HOME/.local
```

Make sure `$HOME/.local/bin` is in your `PATH`.

## Post-Installation

Once installed, you can use `novum` from anywhere on your system to manage Novus projects:

```bash
novum init my_new_app
cd my_new_app
novum run
```

## Uninstalling

To remove Novus from your system:

```bash
# Assuming default prefix
sudo rm /usr/local/bin/novusc
sudo rm /usr/local/bin/novum
sudo rm -rf /usr/local/lib/novus
```
