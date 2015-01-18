#!/bin/bash

source /opt/rh/devtoolset-2/enable

mkdir src
cd src

# GLS, HEPMC, boost, YODA, fastjet ---> rivet
wget http://rivet.hepforge.org/hg/bootstrap/raw-file/2.2.0/rivet-bootstrap
chmod a+x rivet-bootstrap
./rivet-bootstrap

# lhapdf6
wget http://www.hepforge.org/archive/lhapdf/LHAPDF-6.1.5.tar.gz
tar xzf LHAPDF-6.1.5.tar.gz
cd LHAPDF-6.1.5
./configure --prefix=/home/hschulz/src/local --with-boost=/home/hschulz/src/local
make -j3
make install
cd ..

# openloops
svn checkout http://openloops.hepforge.org/svn/OpenLoops/branches/public ./OpenLoops
cd OpenLoops
./scons
cd ..

# qd ---> blackhat
wget http://crd.lbl.gov/~dhbailey/mpdist/qd-2.3.13.tar.gz
tar xzf qd-2.3.13.tar.gz 
cd qd-2.3.13
./configure --prefix=/home/hschulz/src/local --enable-shared
make -j3
make install
cd ..

# BLACK HAT --- only compile on one thread! Memory requirements HUGE
wget http://www.hepforge.org/archive/blackhat/blackhat-0.9.9.tar.gz
tar xzf blackhat-0.9.9.tar.gz
cd blackhat-0.9.9
./configure --prefix=/home/hschulz/src/local --with-QDpath=/home/hschulz/local
make
make install
cd ..

# MCFM
wget http://mcfm.fnal.gov/MCFM-6.8.tar.gz
tar xzf MCFM-6.8.tar.gz
cd MCFM-6.8
./Install
make
cd ..
