# Project
This is a base of ray tracing renderer in c++ with SFML.

# Setup
If you don't have meson or ninja, you can install the like this :
```bash
pip install meson ninja
```
Don't forget to put them into the path.

This step isn't requiered if you already have openal.
```bash
make install
```
This step needed sudo permission.

You may want to install more that just requiered to have lighter repo.
```bash
make fullinstall
```

# Compilation
```bash
make
```

# Update
In case of update of a dependency, you may do this command to have it.
```bash
make update
```

# Running
```bash
make run
```

# Keys
w -> go forward\
s -> go backward\
a -> go left\
d -> go right\
space -> go up\
lshift -> go down\
left -> rotate left\
right -> rotate right\
up -> rotate up\
down -> rotate down\
lctrl -> sprint\
1 -> set render precision to 1\
2 -> set render precision to 2\
3 -> set render precision to 3\
4 -> set render precision to 4\
5 -> set render precision to 5\
6 -> set render precision to 6\
7 -> set render precision to 7\
8 -> set render precision to 8\
9 -> set render precision to 9\
0 -> set render precision to 10\
