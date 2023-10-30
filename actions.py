#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Copyright © 2007 TUBITAK/UEKAE
# Licensed under the GNU General Public License, version 2.
# See the file http://www.gnu.org/copyleft/gpl.txt.

from pisi.actionsapi import autotools
from pisi.actionsapi import pisitools
from pisi.actionsapi import shelltools

WorkDir = "CdArsiv-0.5"
def setup():
    pass
def build():
    autotools.make()
def install():
    pisitools.dobin("./cdarsiv")