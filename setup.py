#!/usr/bin/env python
# -*- coding: utf8 -*-
try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

_nbt = Extension(
    'opennbt._nbt',
    sources=['opennbt/_nbtmodule.c']
)

setup(
    name='OpenNBT',
    version='1.1.0',
    description='Tiny, liberally-licensed NBT library. NBT is the datafile format used in Minecraft.',
    author='Tyler Kennedy',
    author_email='tk@tkte.ch',
    url='https://github.com/TkTech/OpenNBT',
    packages=[
        'opennbt'
    ],
    scripts=[
        'scripts/debug-nbt',
        'scripts/debug-region'
    ],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Operating System :: OS Independent',
        'License :: OSI Approved :: MIT License'
    ],
    ext_modules=[_nbt]
)
