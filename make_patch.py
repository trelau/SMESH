import os

# Specify the files to diff
a = ''
b = ''

# Specify the patch filename
patch = '.patch'

# Call git diff
cmd = 'git diff --no-index {} {} > {}'.format(a, b, patch)
os.system(cmd)
