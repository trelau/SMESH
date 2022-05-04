import os

# Specify the files to diff
a = 'src/Netgen/libsrc/occ/occgenmesh.cpp'
b = 'src/Netgen/libsrc/occ/occgenmesh2.cpp'

# Specify the patch filename
patch = 'occgenmesh2.patch'

# Call git diff
cmd = 'git diff --no-index {} {} > {}'.format(a, b, patch)
os.system(cmd)
