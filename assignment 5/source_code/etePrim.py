#!/usr/bin/env python2

from ete2 import Tree

tree = Tree('prim.nw',format = 1)

print tree.get_ascii(attributes = ['name'])