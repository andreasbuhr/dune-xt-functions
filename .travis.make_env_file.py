#!/usr/bin/env python3
#
# ~~~
# This file is part of the dune-xt-functions project:
#   https://github.com/dune-community/dune-xt-functions
# Copyright 2009-2018 dune-xt-functions developers and contributors. All rights reserved.
# License: Dual licensed as BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
# Authors:
#   Rene Milk (2017 - 2018)
# ~~~

import os
from os.path import expanduser
from shlex import quote
home = expanduser("~")

prefixes = os.environ.get('ENV_PREFIXES', 'TRAVIS CI encrypt TOKEN TESTS').split(' ')
blacklist = ['TRAVIS_COMMIT_MESSAGE']
env_file = os.environ.get('ENV_FILE', os.path.join(home, 'env'))
with open(env_file, 'wt') as env:
    for k,v in os.environ.items():
        for pref in prefixes:
            if k.startswith(pref) and k not in blacklist:
                env.write('{}={}\n'.format(k,quote(v)))