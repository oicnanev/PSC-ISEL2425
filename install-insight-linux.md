# Insight installation How-To

## tested in ubuntu 2404 LTS and Parrot Linux

It required a little to put together all the dependencies and the following are the steps followed the get that working.

![Snapshot_2024-09-11_11-20-43](https://github.com/user-attachments/assets/93866a5a-89c5-4097-8fba-7726497e77cd)

### 1. Dependencies

#### 1.1 General

```bash
sudo apt install autoconf autogen libgmp-dev libmpfr-dev
```

#### 1.2 For Bfd

```bash
sudo apt install texinfo zlib1g-dev
```

#### 1.3 For libgui

```bash
sudo apt install tcl-dev tk-dev mesa-common-dev libjpeg-dev libtogl-dev
```

#### 1.4 For GDB

```bash
sudo apt install  python-dev-is-python3 flex bison itcl3 itk3 iwidgets4
```

### 2. Get Insight lastest version

```bash
git clone --recursive git://sourceware.org/git/insight.git
```

### 3. Run autoconf

Inside the cloned repository run the autoconf command:

```bash
cd insight
autoconf
```

### 4. Configuration Script

#### 4.1 Create a configuration script (here insight.sh):

```bash
nano insight.sh
```

#### 4.2 Configuration comands

In the insight.sh add the following command:

```bash
./configure --prefix=/usr/. \
--libdir=/usr/lib64 \
--disable-binutils \
--disable-elfcpp \
--disable-gas \
--disable-gold \
--disable-gprof \
--disable-ld \
--disable-rpath \
--disable-zlib \
--enable-sim \
--with-gdb-datadir=/usr/share/insight \
--with-jit-reader-dir=/usr/lib64/insight \
--with-separate-debug-dir='/usr/lib/debug' \
--with-expat \
--with-python \
--without-libunwind
```

```CTRL + X``` to exit nano followed by ```Y``` to save the file

#### 4.3 Change the file attributes

```bash
chmod +x insight.sh
```

#### 4.4 Run the script

```bash
./insight.sh
```

### 5. Run make

```bash
make
```

### 6. Install insight

```bash
sudo make install
```

### 7. Run insight
```bash
insight
```
